module Opts2 where

import System.Console.GetOpt
import Data.Maybe ( fromMaybe )

data Options = Options
 { optVerbose     :: Bool
 , optShowVersion :: Bool
 , optOutput      :: Maybe FilePath
 , optInput       :: Maybe FilePath
 , optLibDirs     :: [FilePath]
 } deriving Show

defaultOptions    = Options
 { optVerbose     = False
 , optShowVersion = False
 , optOutput      = Nothing
 , optInput       = Nothing
 , optLibDirs     = []
 }

options :: [OptDescr (Options -> Options)]
options =
 [ Option ['v']     ["verbose"]
     (NoArg (\ opts -> opts { optVerbose = True }))
     "chatty output on stderr"
 , Option ['V','?'] ["version"]
     (NoArg (\ opts -> opts { optShowVersion = True }))
     "show version number"
 , Option ['o']     ["output"]
     (OptArg ((\ f opts -> opts { optOutput = Just f }) . fromMaybe "output")
             "FILE")
     "output FILE"
 , Option ['c']     []
     (OptArg ((\ f opts -> opts { optInput = Just f }) . fromMaybe "input")
             "FILE")
     "input FILE"
 , Option ['L']     ["libdir"]
     (ReqArg (\ d opts -> opts { optLibDirs = optLibDirs opts ++ [d] }) "DIR")
     "library directory"
 ]

compilerOpts :: [String] -> IO (Options, [String])
compilerOpts argv =
   case getOpt Permute options argv of
      (o,n,[]  ) -> return (foldl (flip id) defaultOptions o, n)
      (_,_,errs) -> ioError (userError (concat errs ++ usageInfo header options))
  where header = "Usage: ic [OPTION...] files..."