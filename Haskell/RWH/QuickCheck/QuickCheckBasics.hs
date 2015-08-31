{-# LANGUAGE FlexibleInstances #-}

module QuickCheckBasics where


import Test.QuickCheck.Arbitrary
import Test.QuickCheck.Gen
import Test.QuickCheck
import System.Random
import Data.List



--- ### How to get some random numbers ###

-- import Test.QuickCheck.Arbitrary
-- import Test.QuickCheck.Gen

randomBools = sample' arbitrary :: IO [Bool] -- random length, random results

randomInts = sample' arbitrary :: IO [Int] -- same here

-- how to get a defined length

-- import System.Random

randomBools' :: Int -> [Bool]
randomBools' length = unGen arbitrary (mkStdGen (545646)) length :: [Bool]
-- returns a list of 10 Bools, but the seed is 42
-- to get a totally random seed you need to call newStdGen or getStdGen
-- THIS IS NOT IO

randomInts' :: Int -> IO [Int]
randomInts' length = do
                        x <- getStdGen
                        let nums = unGen arbitrary x length :: [Int]
                        return nums
-- THIS IS IO


-- ############################################################################

qsort :: Ord a => [a] -> [a]
qsort [] = []
qsort (x:xs) = qsort l ++ [x] ++ qsort r
        where l = filter (<x) xs
              r = filter (>=x) xs




-- to check something, we have to define the property we want to check

property_sorting xs = qsort xs == sort xs -- does my own sorting algorithm sort the same as the already implemented?

prop_idempotent xs = qsort (qsort xs) == qsort xs-- is it sufficient?



-- how to check

withOutput = verboseCheck (prop_idempotent :: String -> Bool)

withoutOutput = quickCheck (prop_idempotent :: [Integer] -> Bool)

-- it has its own language to ensure some special cases like a not empty list

blub xs = not (null xs) ==> head (qsort xs) == minimum xs

-- let's define some arbitrary for our own data

-- ## example code

data Anleitung = Zero | One | Two
        deriving (Eq, Enum, Show)

data Baum = Ast Baum Baum | Zweig Baum | Blatt
        deriving (Show)

holzhacker :: Baum -> Int
holzhacker (Ast a b) = 1 + holzhacker a + holzhacker b
holzhacker (Zweig a) = 1 + holzhacker a
holzhacker (Blatt)   = 0

holz :: Baum -> Int
holz baum = holz_acc 0 [baum]
        where holz_acc :: Int -> [Baum] -> Int
              holz_acc acc [] = acc
              holz_acc acc ((Blatt):ts) = holz_acc acc ts
              holz_acc acc ((Zweig a):ts) = holz_acc (acc+1) (a:ts)
              holz_acc acc ((Ast a b):ts) = holz_acc (acc+1) (a:b:ts)
-- ## end example code


property'' xs = holz xs == holz xs -- just to see some examples of random generated trees

withOutputHolz = verboseCheck (property'' :: Baum -> Bool)

-- this one is for recursive data types
instance Arbitrary Baum where
       arbitrary = do
                n <- choose (1,3) :: Gen Int
                case n of
                        1 -> return Blatt
                        2 -> arbitrary >>= \x -> return (Zweig x)
                        3 -> arbitrary >>= \x -> arbitrary >>= \y -> return (Ast x y)

-- this one is for lists
instance Arbitrary Anleitung where
        arbitrary = elements [Zero, One, Two]


