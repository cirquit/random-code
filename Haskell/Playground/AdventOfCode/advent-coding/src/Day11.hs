module Day11 where

import Data.List

differentPairs :: String -> Bool
differentPairs = go []
  where go (x:y:xs) _ = True
        go found (x:y:xs)
          | pair x y, [x,y] `notElem` found = go ([x,y]:found) (y:xs)
          | otherwise                       = go        found  (y:xs)
        go       _  _ = False

        pair x y = x == y

increasingStraight :: String -> Bool
increasingStraight (x:y:z) = or $ map (\(a,b,c) -> [a,b,c] `isInfixOf` ['a'..'z']) trips
  where trips = zip3 (x:y:z) (y:z) z

increasingStraight' :: String -> Bool
increasingStraight' [a,b,c]    = [a,b,c] `isInfixOf` ['a'..'z']
increasingStraight' (a:b:c:xs) = [a,b,c] `isInfixOf` ['a'..'z'] || increasingStraight' (b:c:xs)



noIOLs :: String -> Bool
noIOLs l = 'i' `notElem` l
        && 'o' `notElem` l
        && 'l' `notElem` l

genPW :: String -> [String]
genPW str = str' : genPW str'
  where 
        str' = inc str

        inc :: String -> String
        inc [] = []
        inc xs
            | overflowed = inc (init xs) ++ [c]
            | otherwise  =      init xs  ++ [c]
          where (c, overflowed) = succ' (last xs)

        succ' 'z' = ('a'   , True)
        succ' 'h' = ('j'   , False)
        succ' 'n' = ('p'   , False)
        succ' 'k' = ('m'   , False)
        succ'  x  = (succ x, False)


part1n2 = do
  let res = take 2 [x | x <- genPW "vzbxkghb", differentPairs x, increasingStraight' x]
  print res