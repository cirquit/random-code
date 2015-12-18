{-# LANGUAGE BangPatterns #-}

module Day07 where

import Data.Bits
import Data.Maybe
import Data.List
import Data.Char

data Circuit = I Int
             | Var    String
             | NOT    Circuit
             | AND    Circuit Circuit
             | OR     Circuit Circuit
             | LSHIFT Circuit Int
             | RSHIFT Circuit Int

parseToMap :: String -> [(String, Circuit)]
parseToMap = map toCircuit . lines
    where
        toCircuit :: String -> (String, Circuit)
        toCircuit = go . words
            where go :: [String] -> (String, Circuit)
                  go [    a, "AND"    ,   b, "->", c] = let ( a',  b') = getVars (  a,   b) in (c, a' `AND`   b')
                  go [    a, "OR"     ,   b, "->", c] = let ( a',  b') = getVars (  a,   b) in (c, a' `OR`    b')
                  go [    a, "RSHIFT" , num, "->", c] = let ( a', I i) = getVars (  a, num) in (c, a' `RSHIFT` i)
                  go [    a, "LSHIFT" , num, "->", c] = let ( a', I i) = getVars (  a, num) in (c, a' `LSHIFT` i)
                  go ["NOT",         a,      "->", c] =                                        (c,   NOT (Var a))
                  go [  num,                 "->", c] = let ( i,    _) = getVars (num, num) in (c,             i)
                  go                               w  = error $ "no parse for: " ++ show w

        getVars :: (String, String) ->  (Circuit, Circuit)
        getVars (a,b)
            | [(i, [])] <- ra, [(j, [])] <- rb = (  I i,   I j)
            | [(i, [])] <- ra                  = (  I i, Var b)
            |                  [(j, [])] <- rb = (Var a,   I j)
            | otherwise                        = (Var a, Var b)
          where ra = reads a :: [(Int, String)]
                rb = reads b :: [(Int, String)]



part1 = do
  text <- readFile "lib/day07-input.txt"
  let m = parseToMap text

      lparse :: String -> Int
      lparse a = (map parse m) !! i
          where i = fromJust (findIndex (\(b, _) -> a == b) m)

                parse :: (String, Circuit) -> Int
                parse (_, (NOT a   ))   = complement (toInt a)
                parse (_, (AND a  b))   = (toInt a) .&. (toInt b)
                parse (_, (OR  a  b))   = (toInt a) .|. (toInt b)
                parse (_, (RSHIFT a i)) = shiftR (toInt a) i
                parse (_, (LSHIFT a i)) = shiftL (toInt a) i
                parse (_, a)            = toInt a

                toInt (Var a) = lparse a
                toInt (I   i) = i


  print $ lparse "a"