module Main where

import Numeric.LinearAlgebra

x1 = [  3,   4,   5,   6,   7,   8] :: [Double]
y1 = [150, 155, 150, 170, 160, 175] :: [Double]

x2 = [-0.2, 0.2, 1]     :: [Double]
y2 = [0.49, 0.64, 1.39] :: [Double]

x3 = [1,2,3,4]  :: [Double]
y3 = [6,5,7,10] :: [Double]

-- | Least square estimator
--
lse :: Int -> [Double] -> [Double] -> Matrix Double
lse deg x y = pinv (tx' <> x') <> tx' <> y'
    where

        tx' = trans x'

        x' :: Matrix Double 
        x' = (lx><deg) (foldr (\x xs -> pow x (deg-1) ++ xs) [] x)

        y' :: Matrix Double
        y' = (ly><1) y

        lx = length x
        ly = length y

        pow x deg = go [] x deg
            where go :: [Double] -> Double -> Int -> [Double]
                  go acc _ 0   = 1:acc
                  go acc x deg = go (x**fromIntegral(deg):acc) x (deg-1)

-- | prettify for gnuplot
--
toF :: Matrix Double -> String
toF = concatMap (\(i,[x]) -> show (round' x) ++ "*" ++ "x**"++ (show i) ++ " + ") .  zip [0..] . toLists 
  where round' = (/100) . fromInteger . round . (*100) :: Double -> Double

-- | Mean square estimator
mse :: Matrix Double -> [(Double, Double)] -> Double
mse m xys = nth . sum $ map (\(x,y) -> ((f x) - y)**2) xys
  where l = toLists m :: [[Double]]
        f x = sum $ zipWith (\(i, [w]) x -> w * x^i) (zip [0..] l) (repeat x)
        nth = (/ fromIntegral (length xys))

-- | data -> fitting -> gnuplot
plot :: Int -> [Double] -> [Double] -> String
plot deg x y = toF $ lse deg x y