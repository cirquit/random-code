{-# OPTIONS_GHC -O -fglasgow-exts -ddump-simpl-stats #-}
-- {-# RULES
--   "treeMap/treeMap"  forall f g t.
-- 
--   treeMap f (treeMap g t) = treeMap (f . g) t
--   #-}

-- {-# RULES
--   "treeFold/treeMap"  forall f b g t.
--   treeFold f b (treeMap g t) =
--     treeFold (\l x r -> f l (g x) r) b t
--   #-}



module Main where

import System.Random

data Tree a = Cons a (Tree a) (Tree a) | Empty

instance (Show a) => Show (Tree a) where

  show tree = '[' : (go tree) ++ "]"
    where
      go Empty          = []
      go (Cons v t1 t2) = show v ++ show' t1 ++ show' t2

      show' n@(Cons _ _ _) = ':' : go n
      show' Empty          = []

treeMap :: (a -> b) -> Tree a -> Tree b
treeMap f Empty        = Empty
treeMap f (Cons x l r) = Cons (f x) (treeMap f l) (treeMap f r)

treeFold :: (a -> b -> b -> b) -> b -> Tree a -> b
treeFold f b Empty        = b
treeFold f b (Cons x l r) = f x (treeFold f b l)  (treeFold f b r)

treeSum :: Num a => Tree a -> a
treeSum t = treeFold (\x l r -> x+l+r) 0 t


createNDepth :: StdGen -> Int -> Tree Int
createNDepth std = go (randomRs (0,100) std)
    where go :: [Int] -> Int -> Tree Int
          go _      0 = Empty
          go (x:xs) d = Cons x (go rs (d-1)) (go rs' (d-1))
              where (rs, rs') = splitAt (2^d-1) xs


main :: IO ()
main = do
  rnd <- getStdGen
  let d1M = createNDepth rnd 1000000

  print 1






