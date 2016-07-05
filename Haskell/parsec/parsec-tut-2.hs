-- https://mrkkrp.github.io/megaparsec/tutorials/fun-with-the-recovery-feature.html

{-# LANGUAGE FlexibleContexts #-}

module Main where

import           Control.Applicative         (empty)
import           Control.Monad               (void)
import           Text.Megaparsec
import           Text.Megaparsec.String
import           Text.Megaparsec.Expr
import qualified Text.Megaparsec.Lexer as L

import Control.Monad.Trans.Maybe


type Program = [Equation]

data Equation = Equation String Expr
    deriving (Eq, Show)

data Expr = Value          Double
          | Reference      String
          | Negation       Expr
          | Addition       Expr Expr
          | Substraction   Expr Expr
          | Multiplication Expr Expr
          | Division       Expr Expr
    deriving (Eq, Show)

lineComment :: Parser ()
lineComment = L.skipLineComment "#"

scn :: Parser ()
scn = L.space (void spaceChar) lineComment empty

sc :: Parser ()
sc = L.space (void $ oneOf " \t") lineComment empty

lexeme :: Parser a -> Parser a
lexeme = L.lexeme sc

symbol :: String -> Parser String
symbol = L.symbol sc



