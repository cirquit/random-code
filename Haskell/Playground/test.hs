module Test where

import qualified Data.Set as S
import System.Random (randomRIO)
import Control.Monad (replicateM)

genUnique :: Int -> IO (S.Set Int)
genUnique n = fillUp =<< S.fromList <$> replicateM n (randomRIO (1, 1000000))
  where fillUp :: S.Set Int -> IO (S.Set Int)
        fillUp s
          | S.size s /= n = fillUp =<< (flip S.insert s) <$> randomRIO (1, 1000000)
          | otherwise     = return s


test :: IO Int
test = (S.size . S.unions) <$> (replicateM 100 $ genUnique 500)

main :: IO ()
main = do
  x <- replicateM 500 test
  print $ sum x `div` length x
