{-# LANGUAGE BangPatterns #-}

module Day07 where

import Data.Bits
import Data.Maybe
import Debug.Trace
import qualified Data.Map as M
import Data.List
import Data.Char

data Circuit = I Int
             | Var    String
             | NOT    Circuit
             | AND    Circuit Circuit
             | OR     Circuit Circuit
             | LSHIFT Circuit Int
             | RSHIFT Circuit Int

instance Show Circuit where
  show (I i)        = show i
  show (Var str)    = str
  show (NOT a)      = "!(" ++ show a ++ ")"
  show (OR  a b)    = "(" ++ show a ++ " || " ++ show b ++ ")"
  show (AND a b)    = "(" ++ show a ++ " && " ++ show b ++ ")"
  show (RSHIFT a i) = "(" ++ show a ++ " >> " ++ show i ++ ")"
  show (LSHIFT a i) = "(" ++ show a ++ " << " ++ show i ++ ")"

--getTerm :: String -> M.Map String Circuit -> Circuit
--getTerm str m = fromJust (M.lookup str m)

--constructTerm :: Circuit -> M.Map String Circuit -> Circuit
--constructTerm (I i)        _ = I i
--constructTerm (Var str)    m = Var    $ constructTerm (getTerm str m)
--constructTerm (NOT    a)   m = NOT    $ constructTerm a
--constructTerm (OR     a b) m = OR     $ (constructTerm a) (constructTerm b)
--constructTerm (AND    a b) m = AND    $ (constructTerm a) (constructTerm b)
--constructTerm (RSHIFT a i) m = RSHIFT $ (constructTerm a) i
--constructTerm (LSHIFT a i) m = LSHIFT $ (constructTerm a) i


-- fib :: Int -> Int
-- fib 0 = 1
-- fib 1 = 1
-- fib n = fib (n-1) + fib (n-2)


--reduceMap :: M.Map String Circuit -> M.Map String Circuit
--reduceMap m = go (M.toList m) m
--  where -- go :: [(String, Circuit)] -> 
--        go (x:xs) m = case x of
--            (_, I _) -> parse m


--subst :: (String, Circuit) -> Circuit -> Circuit
--subst (str, c) (I i)        = i
--subst (str, c) (Var str')
--  | str == str' = c
--  | otherwise   = (Var str')
--subt t (NOT    a)   = NOT (subst t a)
--subt t (OR     a b) = OR  (subst t a) (subst t b)
--subt t (AND    a b) = AND (subst t a) (subst t b)
--subt t (RSHIFT a i) = RSHIFT (subst t a) i
--subt t (LSHIFT a i) = LSHIFT (subst t a) i



getValue :: Circuit -> M.Map String Circuit -> Int
getValue (I i) m = i
getValue (Var str) m
    | (Just c) <- M.lookup str m = parse c m
    | otherwise                  = error $ "couldn't find var " ++ str



parse :: Circuit -> M.Map String Circuit -> Int
parse (I i)        _ = i
parse (Var    v)   m = getValue (Var v) m
parse (NOT    a)   m = complement (getValue a m)
parse (OR     a b) m = (getValue a m) .|. (getValue b m)
parse (AND    a b) m = (getValue a m) .&. (getValue b m)
parse (RSHIFT a i) m = shiftR (getValue a m) i
parse (LSHIFT a i) m = shiftL (getValue a m) i
  

parseToMap :: String -> M.Map String Circuit
parseToMap = foldl (\m (k,v) -> M.insert k v m) M.empty . map toCircuit . lines
    where
        toCircuit :: String -> (String, Circuit)
        toCircuit = go . words
            where go :: [String] -> (String, Circuit)
                  go [    a, "AND"    ,   b, "->", c] = let ( a',  b') = getVars (  a,   b) in (c, a' `AND`   b')
                  go [    a, "OR"     ,   b, "->", c] = let ( a',  b') = getVars (  a,   b) in (c, a' `OR`    b')
                  go [    a, "RSHIFT" , num, "->", c] = let ( a', I i) = getVars (  a, num) in (c, a' `RSHIFT` i)
                  go [    a, "LSHIFT" , num, "->", c] = let ( a', I i) = getVars (  a, num) in (c, a' `LSHIFT` i)
                  go ["NOT",         a,      "->", c] =                                        (c,   NOT (Var a))
                  go [  num,                 "->", c] = let ( i',   _) = getVars (num, num) in (c,            i')
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
  text <- readFile "lib/day07-test.txt"
  let m = parseToMap text
      l = nub [w | w <- (words text), all isAlpha w, w /= "NOT", w /= "OR", w /="RSHIFT", w /="LSHIFT", w /= "AND"]

  print l
  -- print (getValue (Var "a") m)