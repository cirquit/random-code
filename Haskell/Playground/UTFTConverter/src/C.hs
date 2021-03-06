module C (toCFile, Platform(..)) where

import Data.Time (UTCTime)
import RGB565    (to4Hex)

data Platform = AVR
              | ARM
              | PIC32
  deriving (Eq, Show)

toCFile :: [String] -> String -> (Int, Int) -> UTCTime -> Platform -> String
toCFile content name (w, h) time platform =
  let clength  = show (length content)
      memusage = show (length content * 2)
      include  | platform == AVR = "\n#include <avr/pgmspace.h>\n"
               | otherwise       = ""
      arrname  | platform == AVR = "const unsigned short " ++ name ++ '[' : clength ++ "] PROGMEM={\n"
               | otherwise       = "const unsigned short " ++ name ++ '[' : clength ++ "] ={\n"
  in
  "// Generated by   : Converter v0.1\n"                               ++
  "// Generated from : " ++ name      ++ ".jpg\n"                      ++
  "// Time generated : " ++ show time ++ "\n"                          ++
  "// Image Size     : " ++ show w ++ 'x' : show h ++ " pixels\n"      ++
  "// Memory usage   : " ++ memusage  ++ " bytes\n"                    ++
  include                                                              ++
  "\n"                                                                 ++
  arrname                                                              ++
  toCArray content 1

toCArray :: [String] -> Int -> String
toCArray []     _ = "};"
toCArray (x:xs) n = printHex x ++ com ++ toCArray xs (n+1)
  where com | n `mod` 16 == 0 = printCom n
            | otherwise       = ""

printHex :: String -> String
printHex hx = '0':'x': hx ++ ", "

printCom :: Int -> String
printCom n = ' ':' ':'/':'/':' ':'0':'x': to4Hex n ++ ' ':'(': show n ++ ") pixels\n"
