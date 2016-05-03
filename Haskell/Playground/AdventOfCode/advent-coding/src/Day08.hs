module Day08 where

import Debug.Trace
import Data.Char

part1 :: IO ()
part1 = do
    text <- readFile "lib/day08-input.txt"
    let f l = length l - go l
    (print . sum . map f . words) text
  where
      go :: String -> Int
      go []                = 0
      go ('\"'        :xs) = go xs
      go ('\\':'x':_:_:xs) = 1 + go xs
      go ('\\':'\\'   :xs) = 1 + go xs
      go ('\\'        :xs) = 1 + go xs
      go (           _:xs) = 1 + go xs


part2 :: IO ()
part2 = do
    text <- readFile "lib/day08-input.txt"
    let g l = length (show l) - length l
    (print . sum . map g . words) text
