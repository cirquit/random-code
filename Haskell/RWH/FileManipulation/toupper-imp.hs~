import System.IO
import Data.Char (toUpper)

-- for Windows use openBinaryFile (better portability)
-- for Linux openFile and openBinaryFile perform the same action


main :: IO()
main = do
	inH <- openFile "input.txt" ReadMode
	hPrint stdout "input.txt has been read"
	outH <- openFile "output.txt" WriteMode
	mainloop inH outH
	hClose inH
	hClose outH
	print "output.txt has been modified"
	
	
mainloop :: Handle -> Handle -> IO()
mainloop inH outH =
	do inEOF <- hIsEOF inH
	   if inEOF then return ()
	     else do inputStr <- hGetLine inH
		     position <- hTell inH
		     hPutStrLn outH ((map toUpper inputStr) ++ show (position))
	  	     mainloop inH outH
		     
		     

-- getLine = hGetLine stdin
-- putStrLn = hPutStrLn stdout
-- print = hPrint stdout
