module Day10 where

import Data.List

input = "3113322113"

part1 = do
  let (res, _) = until (\(_, i) -> i == 40) (\(x,y) -> (pronounce x, y + 1)) (input, 0)
  (print . length) res

part2 = do
  let (res, _) = until (\(_, i) -> i == 50) (\(x,y) -> (pronounce x, y + 1)) (input, 0)
  (print . length) res

pronounce :: String -> String
pronounce l = concatMap (\(x:xs) -> show (length (x:xs)) ++ [x]) (group l)