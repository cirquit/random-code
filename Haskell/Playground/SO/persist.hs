module Main where

-- import Control.Monad.Trans.Either
import Control.Monad.Trans
import Control.Monad

data May a = Obv a | Nope
    deriving Show

instance Functor May where

--  fmap :: (a -> b) -> May a -> May b
    fmap f (Obv x) = Obv $ f x
    fmap _  Nope   = Nope

instance Applicative May where

--  pure :: a -> May a
    pure x = Obv x

--  (<*>) :: May (a -> b) -> f a -> May b
    Obv f <*> o = fmap f o
    Nope  <*> _ = Nope

instance Monad May where

--  return  :: a -> May a
    return x = pure x

--  (>>=) :: May a -> (a -> May b) -> May b
    Obv x >>= f = f x
    Nope  >>= _ = Nope

newtype MayT m a = MayT { runMayT :: m (May a) }

instance Functor m => Functor (MayT m) where

--  fmap :: Functor m => (a -> b) -> MayT m a -> MayT m b
    fmap f x = MayT . fmap (fmap f) $ runMayT x

instance (Functor m, Monad m) => Applicative (MayT m) where

--  pure :: (Functor m, Monad m) => a -> MayT m a
    pure = MayT . pure . Obv

--  (<*>) :: (Functor m, Monad m) => MayT m (a -> b) -> MayT m a -> MayT m b
    (<*>) mf ma = MayT $ do
         f <- runMayT mf
         a <- runMayT ma
         case (f,a) of
              (Obv f', Obv a') -> return $ Obv (f' a')
              _                -> return Nope

instance MonadTrans MayT where

-- lift :: (Monad m) => m a -> MayT m a
   lift ma = MayT $ (return . Obv) =<< ma


instance (Monad m) => Monad (MayT m) where

--  return :: Monad m => a -> MayT m a
    return = MayT . return . Obv

--    (>>=) :: Monad m => MayT m a -> (a -> MayT m b) -> MayT m b
    (>>=) ma f = MayT $ do
         a <- runMayT ma
         case a of
             (Obv x) -> runMayT (f x)
             Nope    -> return Nope

test :: InterpreterMT IO Int
test = InterpreterMT (return (PropInterpreter 1))

testMT :: MayT IO Int
testMT = MayT (return (Nope))

-- testM :: EitherT IO Int
-- testM = EitherT (return ())

data InterpreterM a = ExeInterpreter a
                    | PropInterpreter a
    deriving (Show,Eq)

instance Functor InterpreterM where

    fmap f (ExeInterpreter a) = ExeInterpreter $ f a
    fmap f (PropInterpreter a) = PropInterpreter $ f a


newtype InterpreterMT m a = InterpreterMT { runInterpreterMT :: m (InterpreterM a) }

instance (Monad m) => Monad (InterpreterMT m) where

--  return :: Monad m => a -> InterpreterMT m a
    return x = InterpreterMT $ return (ExeInterpreter x)
    --InterpreterMT $ (return . ExeInterpreter) x

--  (>>=) :: Monad m => InterpreterMT m a -> (a -> InterpreterMT m b) -> InterpreterMT m b
    (>>=) ima f = InterpreterMT $ do
        ia <- runInterpreterMT ima
        case ia of
            (ExeInterpreter  a) -> runInterpreterMT $ f a
            (PropInterpreter b) -> return (PropInterpreter b) -- runInterpreterMT $ f a


instance (Functor m) => Functor (InterpreterMT m) where
    fmap f x = InterpreterMT . fmap (fmap f) $ runInterpreterMT x

instance (Functor m, Monad m) => Applicative (InterpreterMT m) where

    pure = return
    (<*>) = ap

instance MonadTrans InterpreterMT where

--  lift :: Monad m => m a -> InterpreterMT m a
--    lift ma = InterpreterMT $ (return . ExeInterpreter) =<< ma
    lift = InterpreterMT . liftM ExeInterpreter