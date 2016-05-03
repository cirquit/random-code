module Paths_advent_coding (
    version,
    getBinDir, getLibDir, getDataDir, getLibexecDir,
    getDataFileName, getSysconfDir
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
catchIO = Exception.catch

version :: Version
version = Version [0,1,0,0] []
bindir, libdir, datadir, libexecdir, sysconfdir :: FilePath

bindir     = "/home/rewrite/Documents/Personal-Repository/Haskell/Playground/AdventOfCode/advent-coding/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/bin"
libdir     = "/home/rewrite/Documents/Personal-Repository/Haskell/Playground/AdventOfCode/advent-coding/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/lib/x86_64-linux-ghc-7.10.2/advent-coding-0.1.0.0-50qzlX786zH5MCh4a2QQrZ"
datadir    = "/home/rewrite/Documents/Personal-Repository/Haskell/Playground/AdventOfCode/advent-coding/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/share/x86_64-linux-ghc-7.10.2/advent-coding-0.1.0.0"
libexecdir = "/home/rewrite/Documents/Personal-Repository/Haskell/Playground/AdventOfCode/advent-coding/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/libexec"
sysconfdir = "/home/rewrite/Documents/Personal-Repository/Haskell/Playground/AdventOfCode/advent-coding/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/etc"

getBinDir, getLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "advent_coding_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "advent_coding_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "advent_coding_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "advent_coding_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "advent_coding_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
