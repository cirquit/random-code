module GlobRegex (globToRegex, matchesGlob, matchesGlobCs) where

import Data.Char (toUpper)
import Data.List (isInfixOf)
import Text.Regex.Posix ((=~)) -- possible Outputs:
                             -- String / Int / (Int,Int) / getAllTextMatches $ ".." =~ "" :: [String]

type GlobError = String


-- anchoring to ensure that the matching starts at the beginnung (^) and finishes at the end ($)
globToRegex :: String -> Either GlobError String
globToRegex cs = case internal of
                        Left error -> Left error
                        Right value -> Right ('^' : value ++ "$")
                 where internal = globToRegex' cs


-- translation
globToRegex' :: String -> Either GlobError String
globToRegex' "" = Right ""
globToRegex' ('*':cs) = prepend ".*" (globToRegex' cs)
globToRegex' ('?':cs) = prepend "."  (globToRegex' cs)
globToRegex' ('[':'!':c:cs) = prepend ("[^" ++ [c])  (charClass cs)
globToRegex' ('[':c:cs) = prepend ('[' : [c])  (charClass cs)
globToRegex' ('[':_) = Left "undefined character class"
globToRegex' (c:cs) = prepend (escape c) (globToRegex' cs)

-- ensuring that the regex engine doesn't interpret some chars as a regex
escape :: Char -> String
escape c | c `elem` regexChars = '\\' : [c]
         | otherwise = [c]
        where regexChars = "\\+()^$.{}]|"


-- checks if it ends properly with ']'
charClass :: String -> Either GlobError String
charClass (']':cs) = prepend "]" (globToRegex' cs)
charClass (c:cs) = prepend [c] (charClass cs)
charClass [] = Left "undefined character class"


--helper to forward the error and lose every other input
prepend :: String -> Either GlobError String -> Either GlobError String
prepend prefix (Left error) = Left error
prepend prefix (Right string) = Right (prefix ++ string)
                                        

-- if the pattern is wrong, it doesn't match at all
matchesGlob :: FilePath -> String -> Bool
name `matchesGlob` pat = case globToRegex pat of
                                Left error -> False                                
                                Right regex -> turnToUpperCase name =~ turnToUpperCase regex
                                               where turnToUpperCase = foldr (\x y -> toUpper x : y) []

-- case sensitive
matchesGlobCs :: FilePath -> String -> Bool
name `matchesGlobCs` pat = case globToRegex pat of
                                Left error -> False                                
                                Right regex -> name =~ regex

-- ###############################################################--
-- My glob pattern matcher --

globMatch :: FilePath -> String -> Bool
globMatch cs "" = null cs
globMatch (c:cs) ('?':xs) = globMatch cs xs
globMatch cs ('*':xs) = matchStar cs xs
globMatch cs ('[':xs) = matchCharClass cs xs
globMatch (c:cs) (x:xs) = (c == x) && globMatch cs xs
globMatch "" _ = False


matchCharClass :: FilePath -> String -> Bool
matchCharClass _ pat | ']' `notElem` pat = False                -- if the bracket is not closed, return false
matchCharClass (c:cs) ('!':xs) = (c `notElem` (getCharClass xs)) && globMatch cs (afterCharClass xs)
matchCharClass (c:cs) xs = (c `elem` (getCharClass xs)) && globMatch cs (afterCharClass xs)


-- everything before ']'
getCharClass :: String -> String
getCharClass pat = takeWhile (/= ']') pat

-- everything after the first ']'
afterCharClass :: String -> String
afterCharClass pat = tail $ dropWhile (/= ']') pat

matchStar :: FilePath -> String -> Bool
matchStar "" pat = globMatch "" pat
matchStar cs pat = globMatch cs pat || matchStar (tail cs) pat















