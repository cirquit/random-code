module Main where

import qualified Data.Text.IO as TIO (readFile, putStrLn)
import qualified Data.Text    as T   (words, unwords, append)

import Data.MarkovChain (run)
import System.Random    (newStdGen, randomRIO, mkStdGen)

main :: IO ()
main = do
  input0 <- TIO.readFile "b_04_06_2015.txt"
  input1 <- TIO.readFile "b_05_06_2015.txt"
  input2 <- TIO.readFile "b_08_06_2015.txt"
  input3 <- TIO.readFile "b_09_06_2015.txt"
  gen    <- newStdGen
  -- let gen = mkStdGen 123
  index  <- randomRIO (0,1000)
  let input     = T.words $ input0 `T.append` input1 `T.append` input2 `T.append` input3
  let predSize  = 1
  let result    = (T.unwords . take 30) (run predSize input index gen)
  TIO.putStrLn result


