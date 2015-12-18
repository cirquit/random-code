{-# LANGUAGE ViewPatterns #-}

module Day05 where

import Data.Map as M

-- Part 1

contains3Vowels :: String -> Bool
contains3Vowels = go 0
  where go :: Int -> String -> Bool
        go 3 _ = True
        go _ [] = False
        go n (x:xs)
          | x `elem` vowels = go (n+1) xs
          | otherwise       = go  n    xs

        vowels = "aeiou"

doubleLetters :: String -> Bool
doubleLetters []  = False
doubleLetters [x] = False
doubleLetters (x:y:xs)
  | x == y    = True
  | otherwise = doubleLetters (y:xs)


noPairs :: String -> Bool
noPairs []  = True
noPairs [x] = True
noPairs (x:y:xs)
    | [x,y] `elem` badPairs = False
    | otherwise             = noPairs (y:xs)
  where badPairs = ["ab", "cd", "pq", "xy"]

part1 = do
  text <- readFile "day05-input.txt"
  let input = lines text
      len   = length [x | x <- input, noPairs x, doubleLetters x, contains3Vowels x]
  print len


-- Part 2

oneLetterBetween :: String -> Bool
oneLetterBetween (x:y:z:xs)
  | x == z    = True
  | otherwise = oneLetterBetween (y:z:xs)
oneLetterBetween _ = False

complexPairs :: String -> Bool
complexPairs = go empty
  where go :: Map String Int -> String -> Bool
        go m [x,y]
            | (Just _) <- val = True
          where (val, m') = insertLookupWithKey (\_ a _ -> a) [x,y] 1 m
        go m (x:y:z:xs)
            | (Just _) <- val = True
            | x == y && x == z  = go m' (  z:xs)
            | otherwise         = go m' (y:z:xs)
          where (val, m') = insertLookupWithKey (\_ a _ -> a) [x,y] 1 m
        go m _ = False

part2 = do
  text <- readFile "day05-input.txt"
  let input = lines text
      len   = length [x | x <- input, oneLetterBetween x, complexPairs x]
  print len
