{-# LANGUAGE FlexibleContexts #-}

module Day06 where

import Data.List.Split

import Data.Array.IO

import Control.Monad


data TurnType = On | Off | Toggle
  deriving Show

type Coords = (Int, Int)

-- Part 1

turnp1 :: Coords -> TurnType -> IOArray (Int, Int) Int ->  IO ()
turnp1 c On     a = do
    r <- readArray a c
    writeArray a c (r + 1)
turnp1 c Off    a = do
    r <- readArray a c
    writeArray a c (max (r-1) 0)
turnp1 c Toggle a = do
    r <- readArray a c
    writeArray a c (r+2)

-- Part2

turnp2 :: Coords -> TurnType -> IOArray (Int, Int) Int ->  IO ()
turnp2 c On     a = do
    r <- readArray a c
    writeArray a c (r + 1)
turnp2 c Off    a = do
    r <- readArray a c
    writeArray a c (max (r-1) 0)
turnp2 c Toggle a = do
    r <- readArray a c
    writeArray a c (r+2)


mapThrough :: Coords -> Coords -> TurnType -> IOArray (Int, Int) Int -> IO ()
mapThrough (a,b) (c,d) ttype arr = do
    forM_ [a..c] (\x -> forM_ [b..d] (\y -> turnp2 (x,y) ttype arr))


parse :: String -> (Coords, Coords, TurnType)
parse l = go (words l)
  where
      go ["turn"  , "off", ab, "through", cd] = (coord ab, coord cd, Off   )
      go ["turn"  , "on" , ab, "through", cd] = (coord ab, coord cd, On    )
      go ["toggle",        ab, "through", cd] = (coord ab, coord cd, Toggle)
      go _                                    = error $ "noparse..." ++ l

      coord :: String -> Coords
      coord l = (read x, read y)
        where [x,y] = splitOn "," l

mapInput :: [String] -> IOArray (Int, Int) Int -> IO ()
mapInput []     arr = return ()
mapInput (x:xs) arr = do
  let (from, to, ttype) = parse x
  mapThrough from to ttype arr
  mapInput xs arr




part2 = do
   text <- readFile "lib/day06-input.txt"
   array <- newArray ((0,0), (999,999)) 0 :: IO (IOArray (Int, Int) Int)
   let input  = lines text

   mapInput input array

   l <- getElems array
   print $ sum l




