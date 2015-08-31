module Main where


import Data.Function (on)
import Control.Monad (when, forM_)

-- | Helper

fizz = cycle ["","","Fizz"]
buzz = cycle ["","","","","Buzz"]
nums = [1..100] :: [Int]

(??) :: Int -> String -> String
x ?? "" = show x
_ ?? y  = y

infixr 9 ??


-- | 1)

fizz1 :: IO ()
fizz1 = forM_ [1..100] $ \x -> do
  let m3 = x `mod` 3 == 0
      m5 = x `mod` 5 == 0
  when m3         $ putStr "Fizz"
  when m5         $ putStr "Buzz"
  when (m3 || m5) $ putStr "\n"
  when (not m3 && not m5) (putStrLn (show x))

-- | 2)

fizz2 :: IO ()
fizz2 = forM_ [1..100] $ \x -> do
  let m3 = x `mod` 3 == 0
      m5 = x `mod` 5 == 0
  if m3 && m5 then putStrLn "FizzBuzz"
  else if m3  then putStrLn "Fizz"
  else if m5  then putStrLn "Buzz"
              else putStrLn $ show x

-- | 3)

fizz3 :: IO ()
fizz3 = mapM_ putStrLn list
  where list = zipWith3 (\x y z -> z ?? (x ++ y)) fizz buzz nums

-- | 4)

fizz4 :: IO ()
fizz4 = mapM_ (putStrLn . (\(x,y) -> x ?? y))  list
  where list = zip [1..100] $ (zipWith (++) `on` cycle) ["","","Fizz"] ["","","","","Buzz"]

-- | 5)

fizz5 :: IO ()
fizz5 = mapM_ putStrLn list
  where list  = map fun [1..100]
        fun x = case (x `mod` 3, x `mod` 5) of
                  (0,0) -> "FizzBuzz"
                  (0,_) -> "Fizz"
                  (_,0) -> "Buzz"
                  _     -> show x


-- | 6)

fizz6 :: IO ()
fizz6 = mapM_ putStrLn [fun x | x <- [1..100]]
  where fun y
          | y `mod` 15 == 0 = "FizzBuzz"
          | y `mod` 5  == 0 = "Buzz"
          | y `mod` 3  == 0 = "Fizz"
          | otherwise       = show y