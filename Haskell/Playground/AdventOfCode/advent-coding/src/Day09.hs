module Day09 where

import Data.List


-- 316 too high

type Connections = [(String, String, Int)]

solution :: IO ()
solution = do
  txt <- readFile "lib/day09-input.txt"
  let c = parser txt
      (c1, c2, _) = unzip3 c
      cities      = nub $ union c1 c2
      allpaths    = permutations cities

      possiblePaths = filter (isValid c) allpaths

      -- result        = minimum $ map (calculatePath c) possiblePaths -- part1
      result        = maximum $ map (calculatePath c) possiblePaths    -- part2

  print result

  --mapM_ print $ parser txt

calculatePath :: Connections -> [String] -> Int
calculatePath c [_]      = 0
calculatePath c (x:y:xs) =
   case find (\(a,b,_) -> a == x && b == y) c of
        (Just (_,_,i)) -> i + calculatePath c (y:xs)
        Nothing        -> error "blub"



isValid :: Connections -> [String] -> Bool
isValid _ [_]      = True
isValid c (x:y:xs) =
    case find (\(a,b,_) -> a == x && b == y) c of
        (Just _) -> True && isValid c (y:xs)
        Nothing  -> False



parser :: String -> Connections
parser = go [] . map words . lines
    where
        go :: Connections -> [[String]] -> Connections
        go g [] = g
        go g ((s1:"to":s2:"=":num:[]):xs)
          | [(n,[])] <- readInt num = go ((s2, s1, n):(s1,s2,n):g) xs
          | otherwise               = error $ "no parse for: " ++ num
        
        readInt :: String -> [(Int, String)]
        readInt = reads

