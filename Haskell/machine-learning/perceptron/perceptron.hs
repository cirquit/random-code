{-# LANGUAGE BangPatterns #-}

module Main where

import System.Random (randomRIO)
import Control.Monad (replicateM)
import Debug.Trace

-- | Perceptron implementation in Haskell (dirty)
--
type Input   = [Double]
type Data    = [(Input, Double)]
type Weights = [Double]
type Rate    = Double            -- [0,1]

round' :: Int -> Double -> Double
round' n = (/10^n). fromInteger . round . (* 10^n)

f :: (Num a, Ord a) => a -> Double
f x
  | x < 0     = 0
  | otherwise = 1.0

runInput :: [Double] -> [Double] -> Double
runInput inputs ws = f $ sum $ zipWith (*) inputs ws

learn :: Rate -> Data -> Weights -> Weights
learn rate []          ws = ws
learn rate ((xs,y):ds) ws
        | y == y_hat = learn rate ds ws
        | otherwise  = learn rate ds (update xs ws)
    where
        y_hat = runInput xs ws

        update :: [Double] -> [Double] -> [Double]
        update xs = map (\(x,w) -> round' 3 (w + rate * (y - y_hat) * x)) . zip xs

run :: Rate -> Data -> Weights -> Weights
run rate = go 0 
    where go :: Int -> Data -> Weights -> Weights
          go n d w = let w' = learn rate d w
                     in case w == w' of
                            True  -> trace ("Steps: " ++ show n) w
                            False -> trace (show w) $ go (n+1) d w'

test :: Weights -> Data -> IO ()
test weights dt = do
    let f x
          | runInput x weights == 1 = "True"
          | otherwise               = "False"
        pretty (x,i) = putStrLn $ show i ++ " - " ++ f x

    mapM_ pretty (zip (map fst dt) [0..])

-- | Data
--
odds :: Data
odds = [ (x0, 0) -- 0
       , (x1, 1) -- 1
       , (x2, 0) -- 2
       , (x3, 1) -- 3
       , (x4, 0) -- 4
       , (x5, 1) -- 5
       , (x6, 0) -- 6
       , (x7, 1) -- 7
       , (x8, 0) -- 8
       , (x9, 1) -- 9
       ]

-- > run 0.1 odds weights
-- > rweights >>= return . run 0.1 odds
-- > test it odds

mul3 :: Data
mul3 = [ (x0, 0) -- 0
       , (x1, 0) -- 1
       , (x2, 0) -- 2
       , (x3, 1) -- 3
       , (x4, 0) -- 4
       , (x5, 0) -- 5
       , (x6, 1) -- 6
       , (x7, 0) -- 7
       , (x8, 0) -- 8
       , (x9, 1) -- 9
       ]

-- > run 0.1 mul3 weights
-- > rweights >>= return . run 0.1 mul3
-- > test it mul3

ors :: Data
ors = [ ([1,0,0], 0)
      , ([1,0,1], 1)
      , ([1,1,0], 1)
      , ([1,1,1], 1)
      ]

-- > run 0.1 ors (weightsc 3)
-- > test it ors

custom :: Data
custom = [ ([1, 2,   4  ],  1)
         , ([1, 0.5, 1.5],  1)
         , ([1, 1,   0.5],  0)
         , ([1, 0,   0.5],  0)
         ]

-- > run 0.1 custom (weightsc 3)
-- > test it custom

weightsc :: Int -> [Double]
weightsc n = replicate n 0.0

weights :: [Double]
weights = replicate (length (xs !! 0)) 0.0

rweights :: IO [Double]
rweights = replicateM (length (xs !! 0)) $ randomRIO (-1.0,1.0)

xs :: [Input]
xs = [x0, x1, x2, x3, x4, x5, x6, x7, x8, x9]

x0 = [1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1] :: [Double] -- 0
x1 = [0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0] :: [Double] -- 1
x2 = [1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1] :: [Double] -- 2
x3 = [1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1] :: [Double] -- 3
x4 = [1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1] :: [Double] -- 4
x5 = [1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1] :: [Double] -- 5
x6 = [1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1] :: [Double] -- 6
x7 = [1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1] :: [Double] -- 7
x8 = [1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1] :: [Double] -- 8
x9 = [1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1] :: [Double] -- 9