module Paths_gtk_example (
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

bindir     = "/home/rewrite/Documents/Personal-Repository/Haskell/GTK-Examples/gtk-example/.stack-work/install/x86_64-linux/lts-3.8/7.10.2/bin"
libdir     = "/home/rewrite/Documents/Personal-Repository/Haskell/GTK-Examples/gtk-example/.stack-work/install/x86_64-linux/lts-3.8/7.10.2/lib/x86_64-linux-ghc-7.10.2/gtk-example-0.1.0.0-AUWIBzJXet26kpB30IUuit"
datadir    = "/home/rewrite/Documents/Personal-Repository/Haskell/GTK-Examples/gtk-example/.stack-work/install/x86_64-linux/lts-3.8/7.10.2/share/x86_64-linux-ghc-7.10.2/gtk-example-0.1.0.0"
libexecdir = "/home/rewrite/Documents/Personal-Repository/Haskell/GTK-Examples/gtk-example/.stack-work/install/x86_64-linux/lts-3.8/7.10.2/libexec"
sysconfdir = "/home/rewrite/Documents/Personal-Repository/Haskell/GTK-Examples/gtk-example/.stack-work/install/x86_64-linux/lts-3.8/7.10.2/etc"

getBinDir, getLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "gtk_example_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "gtk_example_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "gtk_example_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "gtk_example_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "gtk_example_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
