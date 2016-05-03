module Day14 where


data Reindeer = Reindeer { name :: String, kms :: Int, seconds :: Int, rest :: Int}
  deriving Show

parse :: String -> [Reindeer]
parse = map (go . words . init) . lines
  where go :: [String] -> Reindeer
        go [name,_,_,km,_,_,sec,_,_,_,_,_,_,rest , _] = Reindeer name (readInt km) (readInt sec) (readInt rest)
        go                                          r@_  = error $ "no parse: " ++  concat r

        readInt :: String -> Int
        readInt = read

part1 :: IO ()
part1 = do
    txt <- readFile "lib/day14-input.txt"
    mapM_ print $ parse txt