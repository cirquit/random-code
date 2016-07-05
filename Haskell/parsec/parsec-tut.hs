-- https://mrkkrp.github.io/megaparsec/tutorials/parsing-simple-imperative-language.html

module ParseWhile where

import           Control.Monad               (void)
import           Text.Megaparsec
import           Text.Megaparsec.Expr
import           Text.Megaparsec.String
import qualified Text.Megaparsec.Lexer as L


data BExpr = BoolConst Bool
           | Not BExpr
           | BBinary BBinOp BExpr BExpr
           | RBinary RBinOp AExpr AExpr
    deriving Show

data BBinOp = And | Or
    deriving Show

data RBinOp = Greater | Less
    deriving Show

data AExpr = Var String
           | IntConst Integer
           | Neg AExpr
           | ABinary ABinOp AExpr AExpr
    deriving Show

data ABinOp = Add
            | Substract
            | Multiply
            | Divide
    deriving Show

data Stmt = Seq [Stmt]
          | Assign String AExpr
          | If BExpr Stmt Stmt
          | While BExpr Stmt
          | Skip
    deriving Show


sc :: Parser ()
sc = L.space (void spaceChar) lineCmnt blockCmnt
    where
        lineCmnt  = L.skipLineComment "//"
        blockCmnt = L.skipBlockComment "/*" "*/"

lexeme :: Parser a -> Parser a
lexeme = L.lexeme sc

symbol :: String -> Parser String
symbol = L.symbol sc

parens :: Parser a -> Parser a
parens = between (symbol "(") (symbol ")")

integer :: Parser Integer
integer = lexeme L.integer

semi :: Parser String
semi = symbol ";"


rws :: [String]
rws = ["if", "then", "else", "while", "do", "skip"
      , "true", "false" , "not", "and", "or"]

rword :: String -> Parser ()
rword w = string w *> notFollowedBy alphaNumChar *> sc

identifier :: Parser String
identifier = lexeme (p >>= check)
    where
        p       = (:) <$> letterChar <*> many alphaNumChar
        check x
            | x `elem` rws = fail $ "keyword " ++ show x ++ " cannot be an identifier"
            | otherwise    = return x


whileParser :: Parser Stmt
whileParser = sc *> stmt <* eof

stmt :: Parser Stmt
stmt = parens stmt <|> stmtSeq

stmtSeq :: Parser Stmt
stmtSeq = f <$> sepBy1 stmt' semi
    where
        f [x] = x
        f l   = Seq l


stmt' :: Parser Stmt
stmt' = ifStmt
    <|> whileStmt
    <|> skipStmt
    <|> assignStmt

ifStmt :: Parser Stmt
ifStmt = do
    rword "if"
    cond <- bExpr
    rword "then"
    thenStmt <- stmt
    rword "else"
    elseStmt <- stmt
    return $ If cond thenStmt elseStmt

whileStmt :: Parser Stmt
whileStmt = do
    rword "while"
    cond <- bExpr
    rword "do"
    whileStmt <- stmt
    return $ While cond whileStmt

assignStmt :: Parser Stmt
assignStmt = do
    var <- identifier
    void $ symbol ":="
    expr <- aExpr
    return $ Assign var expr

skipStmt :: Parser Stmt
skipStmt = Skip <$ rword "skip"

relation :: Parser RBinOp
relation = (symbol ">" *> pure Greater)
       <|> (symbol "<" *> pure Less)

aExpr :: Parser AExpr
aExpr = makeExprParser aTerm aOperators

bExpr :: Parser BExpr
bExpr = makeExprParser bTerm bOperators

rExpr :: Parser BExpr
rExpr = do
    a1 <- aExpr
    op <- relation
    a2 <- aExpr
    return $ RBinary op a1 a2

aOperators :: [[Operator Parser AExpr]]
aOperators =
    [ [ Prefix $ (symbol "-") *> pure  Neg                ]
    , [ InfixL $ (symbol "*") *> pure (ABinary Multiply)
      , InfixL $ (symbol "/") *> pure (ABinary Divide)    ]
    , [ InfixL $ (symbol "+") *> pure (ABinary Add)
      , InfixL $ (symbol "-") *> pure (ABinary Substract) ]
    ]


bOperators :: [[Operator Parser BExpr]]
bOperators =
    [ [ Prefix $ (rword "not") *> pure   Not         ]
    , [ InfixL $ (rword "and") *> pure (BBinary And) 
      , InfixL $ (rword "or")  *> pure (BBinary Or)  ]
    ]

aTerm :: Parser AExpr
aTerm = parens aExpr
    <|> (Var      <$> identifier)
    <|> (IntConst <$> integer)


bTerm :: Parser BExpr
bTerm = parens bExpr
    <|> (rword "true"  *> pure (BoolConst True))
    <|> (rword "false" *> pure (BoolConst False))
    <|> rExpr


-- parseTest 
prog1 = "z := 1; while (x>0) do (x := z * y; z := z - 1)"