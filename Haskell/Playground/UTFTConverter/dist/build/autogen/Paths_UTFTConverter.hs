module Paths_UTFTConverter (
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
version = Version {versionBranch = [0,1,0,0], versionTags = []}
bindir, libdir, datadir, libexecdir, sysconfdir :: FilePath

bindir     = "/home/rewrite/.cabal/bin"
libdir     = "/home/rewrite/.cabal/lib/x86_64-linux-ghc-7.8.3/UTFTConverter-0.1.0.0"
datadir    = "/home/rewrite/.cabal/share/x86_64-linux-ghc-7.8.3/UTFTConverter-0.1.0.0"
libexecdir = "/home/rewrite/.cabal/libexec"
sysconfdir = "/home/rewrite/.cabal/etc"

getBinDir, getLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "UTFTConverter_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "UTFTConverter_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "UTFTConverter_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "UTFTConverter_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "UTFTConverter_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
