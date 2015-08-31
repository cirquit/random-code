-- remove rename write

import qualified System.Directory as Dir
import System.IO
-- for Windows use openBinaryFile (better portability)
-- for Linux openFile and openBinaryFile perform the same action

appTxt :: String -> String
appTxt [] = ".txt"
appTxt x = x ++ ".txt"


-- currentDirectory Path
curDir :: String -> IO (FilePath)
curDir x = case x of
		"curDir" -> Dir.getCurrentDirectory
		_	 -> return (crtDir x)

-- check for spaces in the directory path
crtDir :: String -> String
crtDir list = if (head list) == ' ' then checkLast (addSlash list) else checkLast (addSlash ('/':list))
	     	 where addSlash l = foldr (\y x -> if y == ' ' then '/':x else y:x) [] l
		       checkLast l = if (last l) == '/' then take ((length l) - 1) l
					 else l

removeFile :: FilePath -> FilePath -> IO()
removeFile dir file = do ndir <- curDir dir 
			 fex <- exists file
			 case fex of
				True ->  Dir.removeFile (appTxt file) >> putStrLn "File deleted!"
				False -> putStrLn "File doesn't exist, please try again!"


console :: IO ()
console = do
		putStrLn "Hello to Remove-Rename-Create!"
		putStrLn "Choose what you want to do!"
		putStrLn "1. Remove: <dir> <filename>"
		putStrLn "2. Rename: <dir> <oldFilename> <newFilename>"
		putStrLn "3. Create: <dir> <filename>"
		putStrLn "4. Create: <dir>"
		putStrLn "<dir> = home i isenko Desktop <==> /home/i/isenko/Desktop"
		putStrLn "<dir> = curDir <==> currentDirectory"
		putStrLn "<filename> = yourname <==> yourname.txt"
		putStrLn "Parsing input now:"



exists :: FilePath -> IO(Bool)
exists file = Dir.getCurrentDirectory >>= \curDir -> Dir.getDirectoryContents curDir >>= \contents -> case (appTxt file) `elem` contents of
												True -> return True
												False -> return False

