{-# LANGUAGE DeriveFunctor, RankNTypes #-}

module BFInterpreter where

import Control.Monad.Free
import Control.Monad        ((=<<))

import Text.ParserCombinators.Parsec.Combinator
import Text.ParserCombinators.Parsec.Char
import Text.Parsec

import Data.Char      (chr, ord)
import Prelude hiding (read)

data BF next = MoveRight       next  -- move pointer to the right             (>)
             | MoveLeft        next  -- move pointer to the left              (<)
             | Inc             next  -- increment cell at cur pos             (+)
             | Dec             next  -- decrement cell at cur pos             (-)
             | Write           next  -- output the data at cur pos            (.)
             | Read            next  -- accept byte input, store at cur. pos  (,)
             | While (BFF ())  next  -- if cur pos = 0 move to WhileEnd       ([)
    deriving (Functor, Show)

type BFF = Free BF

moveR :: BFF ()
moveR = liftF $ MoveRight ()

moveL ::BFF  ()
moveL = liftF $ MoveLeft ()

inc :: BFF ()
inc = liftF $ Inc ()

dec :: BFF ()
dec = liftF $ Dec ()

read :: BFF ()
read = liftF $ Read ()

write :: BFF ()
write = liftF $ Write ()

while :: BFF () -> BFF ()
while loop = liftF $ While loop ()

-- naive Tape implementation with two lists, this is the spot to improve performance

type Tape a = ([a], [a])

tape :: Tape Int
tape = ([], [])

moveRightT :: Tape Int -> Tape Int
moveRightT (ws, (x:xs)) = (ws ++ [x], xs)
moveRightT (ws,    xs)  = (ws ++ [0], xs)

moveLeftT :: Tape Int -> Tape Int
moveLeftT (ws, xs)
    | null ws   = (ws, 0:xs)
    | otherwise = let x = last ws in (ws, x:xs)

incT :: Tape Int -> Tape Int
incT (ws, (x:xs)) = (ws, x+1:xs)
incT (ws,     xs) = (ws,   1:xs)

decT :: Tape Int -> Tape Int
decT (ws, (x:xs)) = (ws,  x-1:xs)
decT (ws,     xs) = (ws, (-1):xs)

readT :: Tape Int -> IO (Tape Int)
readT tape = do 
        str <- getLine
        case str of
            []     -> return $ updateT tape 0
            (x:xs) -> return $ updateT tape (fromEnum x)
    where
        updateT :: Tape Int -> Int -> Tape Int
        updateT (ws, (x:xs)) elem = (ws, elem:xs)
        updateT (ws,    xs)  elem = (ws, elem:xs)

printT :: Tape Int -> IO (Tape Int)
printT t@(ws, (x:xs)) = putChar (chr x) >> return t
printT t@(ws,    xs)  = putChar (chr 0) >> return t

whileT :: BFF () -> Tape Int -> IO (Tape Int)
whileT bff tape = do
        let v = getValue tape
        case v of
            0 -> return tape
            _ -> runBFF bff tape >>= whileT bff
    where
        getValue :: Tape Int -> Int
        getValue (ws, (x:xs)) = x
        getValue (ws,    xs)  = 0


-- interpreter
--
runBFF :: BFF () -> Tape Int -> IO (Tape Int)
runBFF (Free (MoveRight  next)) t = runBFF next . moveRightT $ t
runBFF (Free (MoveLeft   next)) t = runBFF next . moveLeftT  $ t
runBFF (Free (Inc        next)) t = runBFF next . incT $ t
runBFF (Free (Dec        next)) t = runBFF next . decT $ t
runBFF (Free (Write      next)) t = printT t >>= runBFF next 
runBFF (Free (Read       next)) t = readT t  >>= runBFF next 
runBFF (Free (While loop next)) t = whileT loop t >>= runBFF next
runBFF (Pure _)                 t = return t


lexBF :: String -> BFF ()
lexBF ('>':xs) = moveR >> lexBF xs
lexBF ('<':xs) = moveL >> lexBF xs
lexBF ('+':xs) = inc   >> lexBF xs
lexBF ('-':xs) = dec   >> lexBF xs
lexBF (',':xs) = read  >> lexBF xs
lexBF ('.':xs) = write >> lexBF xs
lexBF ('[':xs) = let (loop, rest) = parseTill (xs,[]) 0
                 in while (lexBF loop) >> lexBF rest
    where
        parseTill :: (String, String) -> Int -> (String, String)
        parseTill (']':rest, acc) 0 = (reverse acc, rest)
        parseTill (']':rest, acc) n = parseTill (rest, ']':acc) (n-1)
        parseTill ('[':rest, acc) n = parseTill (rest, '[':acc) (n+1)
        parseTill (x  :rest, acc) n = parseTill (rest,   x:acc) n
        parseTill ([]      , acc) n = error ("unclosed ] - " ++ show n ++ ", rest: " ++ acc)

lexBF (_:xs)   = lexBF xs
lexBF []       = return ()


e1 = "[->+<]"

e1' :: BFF ()
e1' = do
    while $ do
        dec
        moveR
        inc
        moveL

{- 
-- lexer
--
lexer :: String -> Either ParseError (BFF ())
lexer = parse ((sequence_ <$> many pp) <* eof) ""

    where

        pp :: Parsec String () (BFF ())
        pp = choice [mRP, mLP, incP, decP, writeP, readP, whileP, otherwiseP]

        mRP :: Parsec String () (BFF ())
        mRP = char '>'  >> return moveR

        mLP :: Parsec String () (BFF ())
        mLP = char '<'  >> return moveL

        incP :: Parsec String () (BFF ())
        incP = char '+'  >> return inc

        decP :: Parsec String () (BFF ())
        decP = char '-'  >> return dec

        writeP :: Parsec String () (BFF ())
        writeP = char '.' >> return write

        readP :: Parsec String () (BFF ())
        readP = char ',' >> return read

        whileP :: Parsec String () (BFF ())
        whileP = between (char '[') (char ']') pp >>= return . while

        otherwiseP :: Parsec String () (BFF ())
        otherwiseP = noneOf "+" >> return (Pure ())

-}