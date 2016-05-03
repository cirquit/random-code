{-# LANGUAGE BangPatterns #-}

import Data.List
import Data.Array

-- array (non-zero-count, start-offset, array_data)
array_size=101

myindex :: Int -> Int -> Int
myindex key offset
    | key >= offset = key - offset
    | otherwise     = key - offset + array_size

mylookup :: Int -> (t, Int, Array Int e) -> e
mylookup x (_, offset, arr) = arr ! idx
    where idx = myindex x offset

addOrReplace :: Int -> Int -> (Int, Int, Array Int (Int,Int)) -> (Int, Int, Array Int (Int,Int))
addOrReplace key value (count, offset, arr) = (count', offset, arr // [(idx,(key,value))])
    where idx             = myindex key offset
          (_, prev_value) = arr ! idx
          count' = case (prev_value, value) of
                      (0,0)     -> count
                      (0,_)     -> count + 1
                      (_,0)     -> count - 1
                      otherwise -> count

difference :: (Int,Int,Array Int (Int,Int)) -> [Int] -> [Int] -> [Int]
difference (count, offset, arr) [] []
    | count == 0 = []
    | otherwise  = [ k | x <- [0..array_size-1], let (k,v) = (arr ! x), v /= 0]
difference m (x:xs) y = difference new_m xs y
    where (_,v) = mylookup x m
          !new_m = addOrReplace x (v + 1) m
difference m [] (y:ys) = difference new_m [] ys
    where (_,v) = mylookup y m
          !new_m = if v == 0
            then m
            else addOrReplace y (v - 1) m

readInt :: String -> Int
readInt = read

main = do
    _ <- readLn :: IO Int
    pp <- readFile "fst-list.txt"
    _ <- readLn :: IO Int
    qq <- readFile "snd-list.txt"
    let p      = map readInt . words $ pp
        q      = map readInt . words $ qq
        arr    = array (0,100) [(i,(0,0)) | i <- [0..100]]
        triple = (0, head q, arr)
    putStrLn . unwords . map show . sort $ difference triple q p