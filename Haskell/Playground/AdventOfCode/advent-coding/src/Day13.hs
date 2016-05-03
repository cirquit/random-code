module Day13 where

import Data.List

type Feelings = [(String, String, Int)]

parse :: String -> Feelings
parse =  map (go . words . init) . lines
  where go :: [String] -> (String, String, Int)
        go [name, _, "lose", num, _, _, _, _, _, _, to] = (name, to, (- readInt num))
        go [name, _, "gain", num, _, _, _, _, _, _, to] = (name, to,    readInt num )

        go                                          x@_ = error $ "no parse: " ++ concat x
        readInt :: String -> Int
        readInt = read

getHappiness :: String -> String -> Feelings -> Int
getHappiness x y feels =
    case find (\(a,b,_) -> x == a && y == b) feels of
        Just (a,b,i) -> i
        Nothing      -> error $ "no parse: " ++ x ++ '|':y

happiness :: Feelings -> [String] -> Int
happiness feels (x:xs) = doubleHappiness x (last xs) feels + go feels (x:xs)
    where go :: Feelings -> [String] -> Int
          go feels [y] = 0
          go feels (x:y:xs) = doubleHappiness x y feels + go feels (y:xs)

          doubleHappiness n1 n2 feels = feel1 + feel2
              where feel1 = getHappiness n1 n2 feels
                    feel2 = getHappiness n2 n1 feels

part1 :: IO ()
part1 = do
  txt <- readFile "lib/day13-input.txt"
  let feels    = parse txt
      (p,_,_) = unzip3 feels
      people  = nub p
      positions = permutations people
      rating  = maximum . map (happiness feels) $ positions

  print rating


createMyself :: [String] -> [(String, String, Int)]
createMyself []     = []
createMyself (x:xs) = ("Me", x, 0):(x,"Me", 0) : createMyself xs

part2 :: IO ()
part2 = do
  txt <- readFile "lib/day13-input.txt"
  let feels   = parse txt
      (p,_,_) = unzip3 feels
      people  = nub p
      feels'  = createMyself people ++ feels
      people' = "Me":people
      positions = permutations people'

      rating  = maximum . map (happiness feels') $ positions
  print rating