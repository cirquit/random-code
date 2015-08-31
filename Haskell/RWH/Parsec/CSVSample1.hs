module CSVSample1 where

import Text.ParserCombinators.Parsec
import Text.Parsec (ParseError)
import Text.Parsec.String
import Text.Parsec.Combinator (many1, choice, chainl1)
import Control.Monad (void)
import Data.Char (isLetter, isDigit)
{-
csvFile :: GenParser Char st [[String]]
csvFile = do string "<title>"
             result <- many line
             eof
             return result

line :: GenParser Char st [String]
line = do result <- cells
          try (string "</title>") <|> string "\n"
          return result

cells :: GenParser Char st [String]
cells = do first <- cellContent
           next <- remainingCells
           return $ first:next

remainingCells :: GenParser Char st [String]
remainingCells = (char ',' >> cells) <|> (return [])

cellContent :: GenParser Char st String
cellContent = many (noneOf ",\n")

eol :: GenParser Char st Char
eol = char '\n'

parseCSV :: String -> Either ParseError [[String]]
parseCSV input = parse csvFile "(unknown)" input



type GEN st a = GenParser Char st a

-}

{-rssFeed :: GEN st [[String]]
rssFeed = do 
             result <- many titles
             eof
             return result

titles :: GEN st [String]
titles = do 
            result <- singleTitle
            eot
            return result

singleTitle :: GEN st [String]
singleTitle = do 
                    first <- firstWord
                    rest  <- restWords
                    return $ first:rest

firstWord :: GEN st String
firstWord = many (noneOf " Q<")

restWords :: GEN st [String]
restWords = (char 'Q' >> titles) <|> (return [])

eot :: GEN st Char
eot = char '\n'

parseCSV :: String -> Either ParseError [[String]]
parseCSV input = parse rssFeed "" input-}





-- v0.3
{-
whitespace :: Parser ()
whitespace = void $ many $ oneOf $ " \n\t"++['a'..'z']++['A'..'Z']++"!§$%&/()=?{[]}¸'*+#-.,;:_"

lexeme :: Parser a -> Parser a
lexeme p = do
           x <- p
           whitespace
           return x

{-parensW :: Parser String
parensW = do
            whitespace
            void $ string "<title>"
            e <- many1 letter
            void $ string "</title>"
            whitespace
            return e-}

parensW :: Parser String
parensW = do
            manyTill anyChar (string "<title>")
            void $ string "<title>"
            e <- many1 letter
            void $ string "</title>"
            return e


regParse x y = parse x "" y




csvFile :: Parser [String]
csvFile = do result <- many parensW
             eof
             return result











parseCSV input = parse line' "" input




line' = sepBy text (string "title")

text = many (noneOf "<>\n\r")








-}

{-main = do
          c <- getContents
          case parseCSV c of
                Left e -> putStrLn "Error parsing input:" >> print e
                Right r -> mapM_ print r





-}














-- v0.1

csvFile' = endBy line' eol'

line' = sepBy cell' (char ',')

cell' = many (noneOf ",\n\r")

eol' =  try (string "\n\r") 
    <|> try (string "\r\n") 
    <|> string "\n" 
    <|> string "\r"
    <?> "Couldn't find EOL"


parseCSV' :: String -> Either ParseError [[String]]
parseCSV' input = parse csvFile' "(unknown)" input

main = do
          c <- getContents
          case parseCSV' c of
                Left e -> putStrLn "Error parsing input:" >> print e
                Right r -> mapM_ print r

