module Paths_tutorial (
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

bindir     = "/home/rewrite/Documents/Personal-Repository/Haskell/Playground/tutorial/.stack-work/install/x86_64-linux/lts-3.8/7.10.2/bin"
libdir     = "/home/rewrite/Documents/Personal-Repository/Haskell/Playground/tutorial/.stack-work/install/x86_64-linux/lts-3.8/7.10.2/lib/x86_64-linux-ghc-7.10.2/tutorial-0.1.0.0-9N6eKth73jBDFdaJD3o8E8"
datadir    = "/home/rewrite/Documents/Personal-Repository/Haskell/Playground/tutorial/.stack-work/install/x86_64-linux/lts-3.8/7.10.2/share/x86_64-linux-ghc-7.10.2/tutorial-0.1.0.0"
libexecdir = "/home/rewrite/Documents/Personal-Repository/Haskell/Playground/tutorial/.stack-work/install/x86_64-linux/lts-3.8/7.10.2/libexec"
sysconfdir = "/home/rewrite/Documents/Personal-Repository/Haskell/Playground/tutorial/.stack-work/install/x86_64-linux/lts-3.8/7.10.2/etc"

getBinDir, getLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "tutorial_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "tutorial_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "tutorial_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "tutorial_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "tutorial_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
