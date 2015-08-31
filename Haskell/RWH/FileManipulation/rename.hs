-- rename.hs

import System.Directory

-- for Windows use openBinaryFile (better portability)
-- for Linux openFile and openBinaryFile perform the same action
appTxt :: String -> String
appTxt [] = ".txt"
appTxt x = x ++ ".txt"


main :: IO()
main = do
	putStrLn "Please tell me what file to rename" >>
	 getLine >>= \oldF -> putStrLn "Please tell me how to rename" >>
	 getLine >>= \newF -> getCurrentDirectory >>= \curDir -> getDirectoryContents curDir >>=
	 \contents -> case (appTxt oldF) `elem` contents of
			True ->  renameFile (appTxt oldF) (appTxt newF)
			False -> putStrLn $ "The file named " ++ oldF ++" doesn't exist!"

