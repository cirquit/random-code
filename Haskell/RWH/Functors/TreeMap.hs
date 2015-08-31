module TreeMap where

{-# LANGUAGE FlexibleInstances :#-}

import Data.Functor ((<$>))

data Tree a = Node (Tree a) (Tree a) | Leaf a
        deriving (Show)



tree = Node (Leaf Nothing) (Node (Leaf (Just "tree")) (Leaf (Just "munich")))

treeLengths :: Tree [a] -> Tree Int
treeLengths (Leaf s) = Leaf (length s)
treeLengths (Node l r) = Node (treeLengths l) (treeLengths r)

treeMap :: (a -> b) -> Tree a -> Tree b
treeMap f (Leaf s) = Leaf (f s)
treeMap f (Node l r) = Node (treeMap f l) (treeMap f r)


instance Functor Tree where
        fmap = treeMap

-- testing Functors

-- infix use of fmap & map

(<$>?) :: Functor f => (a -> b) -> f a -> f b
(<$>?) = fmap

infix 9 <$>?


test1 = (1+) `fmap` [1,2,3,4] ++ [4,5,6,7] -- = [2,3,4,5,4,5,6,7] ??????

test2 = fmap (1+) [1,2,3,4] ++ [4,5,6,7]        

test3 = (1+) <$>? [1,2,3,4] ++ [4,5,6,7] -- = [2,3,4,5,5,6,7,8] ??????

{-instance Functor (Either Int) where
        fmap _ (Left n) = Left n
        fmap f (Right r) = Right (f r)


--try these and start ghc with -XFlexibleInstances:
        fmap (=="cheeseburger") (Left 1 :: Either Int String) -- returns Left 1 because he knows that if its Right, he can use the function
        fmap (=="cheeseburger") (Right "test" :: Either Int String) --
        fmap (=="cheeseburger") (Left 1 :: Either Int Char) --error because he knows he cant even check the right type
        fmap (+1) (Left "test" :: Either String Int)
        fmap (+1) (Left "test" :: Either String Char)

--functors have to have two rules - composability and identity

fmap id (Just 7) = Just 7
(fmap even . fmap length) == fmap (even . length)
-}







