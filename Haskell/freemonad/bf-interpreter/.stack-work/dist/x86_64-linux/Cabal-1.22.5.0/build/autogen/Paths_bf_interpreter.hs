module Paths_bf_interpreter (
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

bindir     = "/home/rewrite/Documents/Personal-Repository/Haskell/freemonad/bf-interpreter/.stack-work/install/x86_64-linux/lts-6.10/7.10.3/bin"
libdir     = "/home/rewrite/Documents/Personal-Repository/Haskell/freemonad/bf-interpreter/.stack-work/install/x86_64-linux/lts-6.10/7.10.3/lib/x86_64-linux-ghc-7.10.3/bf-interpreter-0.1.0.0-HCx0KDm1WRU7KNL5TxB75Z"
datadir    = "/home/rewrite/Documents/Personal-Repository/Haskell/freemonad/bf-interpreter/.stack-work/install/x86_64-linux/lts-6.10/7.10.3/share/x86_64-linux-ghc-7.10.3/bf-interpreter-0.1.0.0"
libexecdir = "/home/rewrite/Documents/Personal-Repository/Haskell/freemonad/bf-interpreter/.stack-work/install/x86_64-linux/lts-6.10/7.10.3/libexec"
sysconfdir = "/home/rewrite/Documents/Personal-Repository/Haskell/freemonad/bf-interpreter/.stack-work/install/x86_64-linux/lts-6.10/7.10.3/etc"

getBinDir, getLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "bf_interpreter_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "bf_interpreter_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "bf_interpreter_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "bf_interpreter_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "bf_interpreter_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
