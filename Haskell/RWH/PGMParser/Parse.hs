module Parse where

import qualified Data.ByteString.Lazy.Char8 as L8
import qualified Data.ByteString.Lazy as L
import Data.Char (isSpace, chr, ord, isDigit)
import Data.Int (Int64(..))
import Data.Word (Word8(..))
import Data.Functor ((<$>))

data ParseState = ParseState { string :: L.ByteString, offset :: Int64 }
        deriving (Show)


data GreyMap = GreyMap {greyWidth, greyHeight, greyMax :: Int, greyData :: L.ByteString}
        deriving (Eq)

instance Show GreyMap where
        show (GreyMap w h m _) = "GreyMap" ++ show w ++ "x" ++ show h ++ " " ++ show m


newtype Parse a = Parse { runParse :: ParseState -> Either String (a, ParseState) }

simpleParse :: ParseState -> (a, ParseState)
simpleParse = undefined

betterParse :: ParseState -> Either String (a, ParseState)
betterParse = undefined

identity :: a -> Parse a
identity a = Parse (\s -> Right (a,s))

parse :: Parse a -> L.ByteString -> Either String a
parse parser initState = case runParse parser (ParseState initState 0) of
                                Left err           -> Left err
                                Right (result, _ ) -> Right result

modifyOffset :: ParseState -> Int64 -> ParseState
modifyOffset initState newOffset = initState {offset = newOffset}

-- before = ParseState (L8.pack "foo") 0
-- after = modifyOffset before 3

parseByte :: Parse Word8
parseByte = getState ==> \initState ->
            case L.uncons (string initState) of
                Nothing -> bail "no more input"
                Just (byte, remainder) ->
                   putState newState ==> \_ ->
                   identity byte
                  where newState = initState {string = remainder, offset = newOffset}
                        newOffset = offset initState+1

-- L.uncons <==> safe head for ByteString - packed in Maybe
getState :: Parse ParseState
getState = Parse (\s -> Right (s, s))

putState :: ParseState -> Parse ()
putState s = Parse (\_ -> Right ((), s))

bail :: String -> Parse a
bail err = Parse $ \s -> Left $
             "byte offset " ++ show (offset s) ++ ": " ++ err   


(==>) :: Parse a -> (a -> Parse b) -> Parse b
firstParser ==> secondParser = Parse chainedParser
        where chainedParser initState = 
                case runParse firstParser initState of
                        Left errMessage -> 
                                Left errMessage
                        Right (firstResult, newState) ->
                                runParse (secondParser firstResult) newState

instance Functor Parse where
        fmap f parser = parser ==> \result ->
                        identity (f result)

w2c :: Word8 -> Char
w2c = chr . fromIntegral

parseChar :: Parse Char
parseChar = w2c <$> parseByte

peekByte :: Parse (Maybe Word8)
peekByte = (fmap fst . L.uncons . string) <$> getState

peekChar :: Parse (Maybe Char)
peekChar = fmap w2c <$> peekByte

parseWhile :: (Word8 -> Bool) -> Parse [Word8]
parseWhile p = (fmap p <$> peekByte) ==> \mp ->
                if mp == Just True
                then parseByte ==> \b ->
                     (b:) <$> parseWhile p
                else identity []

parseWhileVerbose :: (Word8 -> Bool) -> Parse [Word8]
parseWhileVerbose p =
        peekByte ==> \mc ->
        case mc of
         Nothing -> identity []
         Just c | p c -> 
                        parseByte ==> \b ->
                        parseWhileVerbose p ==> \bs -> 
                        identity (b:bs)
                | otherwise ->
                        identity []

parseRawPGM =
        parseWhileWith w2c notWhite ==> \header -> skipSpaces   ==>&
        assert (header == "P5") "invalid raw header"            ==>&
        parseNat ==> \width -> skipSpaces                       ==>&
        parseNat ==> \height -> skipSpaces                      ==>&
        parseNat ==> \maxGrey ->
        parseByte ==>&
        parseBytes (width * height) ==> \bitmap ->
        identity (GreyMap width height maxGrey bitmap)
       where notWhite = (`notElem` "\r\n\t")

parseWhileWith :: (Word8 -> a) -> (a -> Bool) -> Parse [a]
parseWhileWith f p = fmap f <$> parseWhile (p . f)

parseNat :: Parse Int
parseNat = parseWhileWith w2c isDigit ==> \digits ->
           if null digits 
           then bail "no more digits"
           else let n = read digits
                in if n < 0
                        then bail "integer overflow"
                        else identity n

(==>&) :: Parse a -> Parse b -> Parse b
p ==>& f = p ==> \_ -> f

skipSpaces :: Parse()
skipSpaces = parseWhileWith w2c isSpace ==>& identity ()


assert :: Bool -> String -> Parse ()
assert True _ = identity ()
assert False err = bail err


parseBytes :: Int -> Parse L.ByteString
parseBytes n = 
        getState ==> \st ->
        let n' = fromIntegral n
            (h,t) = L.splitAt n' (string st)
            st' = st {offset = offset st + L.length h, string = t}
        in putState st' ==>&
                assert (L.length h == n') "end of output" ==>&
                identity h
















