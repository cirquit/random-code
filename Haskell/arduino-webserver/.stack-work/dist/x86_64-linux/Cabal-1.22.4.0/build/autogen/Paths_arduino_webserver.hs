module Paths_arduino_webserver (
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

bindir     = "/home/rewrite/Documents/Personal-Repository/Haskell/arduino-webserver/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/bin"
libdir     = "/home/rewrite/Documents/Personal-Repository/Haskell/arduino-webserver/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/lib/x86_64-linux-ghc-7.10.2/arduino-webserver-0.1.0.0-1uSC0RWgU5TDTHA72qz9Jz"
datadir    = "/home/rewrite/Documents/Personal-Repository/Haskell/arduino-webserver/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/share/x86_64-linux-ghc-7.10.2/arduino-webserver-0.1.0.0"
libexecdir = "/home/rewrite/Documents/Personal-Repository/Haskell/arduino-webserver/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/libexec"
sysconfdir = "/home/rewrite/Documents/Personal-Repository/Haskell/arduino-webserver/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/etc"

getBinDir, getLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "arduino_webserver_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "arduino_webserver_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "arduino_webserver_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "arduino_webserver_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "arduino_webserver_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
