module Day25 where

indexRow :: Int -> Int
indexRow row = (row * (row + 1)) `div` 2

indexCol :: (Int, Int) -> Int
indexCol (row, column) = ((rc - 2) * (rc - 1)) `div` 2 - (row * (row - 1)) `div` 2
  where rc     = row + column

--indexRow :: Int -> Int
--indexRow row = go row 1
--  where go row n
--          | row == n  = n
--          | otherwise = n + go row (n + 1)

--indexCol :: (Int, Int) -> Int
--indexCol (col, row) = go (col-1) 1 row
--  where go col count n
--          | col == count = n
--          | otherwise    = n + go col (count+1) (n+1)

index :: (Int, Int) -> Int
index (col, row) = indexRow row + indexCol (row, col)


stream :: [Integer]
stream = iterate (\x -> (x * 252533) `mod` 33554393) 20151125


-- row 2981 column 3075

part1 :: IO ()
part1 = print $ stream !! (index (2981,3075) - 1)