module Day12 where

import Data.List.Split
import Data.Char
import Data.List


part1 = do
  txt <- readFile "lib/day12-input.txt"
  let res = sumUp txt
  print res

delims '\"' = False
delims '}'  = False
delims '{'  = False
delims ':'  = False
delims ']'  = False
delims '['  = False
delims x
  | isAlpha x = False
delims  _   = True

-- part2

trySum :: String -> Int
trySum [] = 0
trySum l
    | redElem top           = 0
    | null top && null kids = 0
    | otherwise             = sumUp top + foldl (\acc x -> acc + trySum x) 0 kids
  where (top, kids) = getJSONContents l


sumUp :: String -> Int
sumUp = sum . map read . filter (/= "") . map (filter delims) . splitOn ","

topElem :: String -> String -> Bool
topElem e ('[':_) = False
topElem e       l = e `isInfixOf` l

redElem :: String -> Bool
redElem = topElem "red"

getJSONContents :: String -> (String, [String])
getJSONContents (x:xs) = let (top, kids) = go ([],[]) [] 0 (init xs)
                         in  (x:top ++ [last xs], kids)
  where 
        go :: (String, [String])  -- end accumulator
           -> String              -- accumulator for embraced results
           -> Int                 -- parenthesis lvl count (0 = toplvl, should be positive)
           -> String              -- input string
           -> (String, [String])
        go (top, kids) kid n []                                -- end case
          | 0 <- n    = ((reverse top), reverse      kids )
          | otherwise = ((reverse top), reverse (kid:kids))  -- badly formatted string => add to kids

        go (top, kids) kid n ('{':xs)
          | 0 <- n    = go (top, kids) ('{':kid)    1  xs
          | otherwise = go (top, kids) ('{':kid) (n+1) xs
        
        go (top, kids) kid n ('}':xs)
          | 1 <- n    = go (top, ((reverse ('}':kid)):kids))       []     0  xs
          | otherwise = go (top,                      kids ) ('}':kid) (n-1) xs

        go (top, kids) kid n ('[':xs)
          | 0 <- n    = go (top, kids) ('[':kid)    1  xs
          | otherwise = go (top, kids) ('[':kid) (n+1) xs
        
        go (top, kids) kid n (']':xs)
          | 1 <- n    = go (top, ((reverse (']':kid)):kids))       []     0  xs
          | otherwise = go (top,                      kids ) (']':kid) (n-1) xs


        go (top, kids) kid n (x:xs)
          | 0 <- n    = go ((x:top),   kids)    kid  0 xs
          | otherwise = go (    top,   kids) (x:kid) n xs

-- 96852 was right

part2 :: IO ()
part2 = do
    txt <- readFile "lib/day12-input.txt"
    print $ trySum txt
