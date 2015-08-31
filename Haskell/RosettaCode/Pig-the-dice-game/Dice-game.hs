module Dice where

import System.Random (randomRIO)

data Score = Score { stack :: Int, score :: Int }

main :: IO ()
main = loop (Score 0 0) (Score 0 0)

loop :: Score -> Score -> IO ()
loop p1 p2 = do
  putStrLn $ "\nPlayer 1 ~ " ++ show (score p1)
  p1' <- askPlayer p1
  putStrLn $ "\nPlayer 2 ~ " ++ show (score p2)
  p2' <- askPlayer p2
  case (p1', p2') of
    (Score _ s1, _         ) | s1 >= 100 -> putStrLn "P1 won!"
    (_         , Score _ s2) | s2 >= 100 -> putStrLn "P2 won!"
    _                                    -> loop p1' p2'

askPlayer :: Score -> IO Score
askPlayer (Score stack score) = do
  putStr   "\n(h)old or (r)oll?"
  answer <- getChar
  roll   <- randomRIO (1,6)
  case (answer, roll) of
    ('h', _) -> do
      putStrLn $ " Score = " ++ show (stack + score)
      return $ Score 0 (stack + score)
    ('r', 1) -> do
      putStrLn $ "\nSorry - stack was resetted. You got a 1!"
      return $ Score 0 score
    ('r', _) -> do
      putStr $ " => " ++ show stack
      askPlayer $ Score (stack + roll) score
    _        -> do
      putStrLn "\nInvalid input - please try again."
      askPlayer $ Score stack score








