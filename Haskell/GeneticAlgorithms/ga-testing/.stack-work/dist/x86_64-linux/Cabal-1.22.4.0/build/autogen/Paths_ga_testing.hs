module Paths_ga_testing (
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

bindir     = "/home/rewrite/Documents/Personal-Repository/Haskell/GeneticAlgorithms/ga-testing/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/bin"
libdir     = "/home/rewrite/Documents/Personal-Repository/Haskell/GeneticAlgorithms/ga-testing/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/lib/x86_64-linux-ghc-7.10.2/ga-testing-0.1.0.0-4DnI6VdIzDxHQbITIsniTE"
datadir    = "/home/rewrite/Documents/Personal-Repository/Haskell/GeneticAlgorithms/ga-testing/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/share/x86_64-linux-ghc-7.10.2/ga-testing-0.1.0.0"
libexecdir = "/home/rewrite/Documents/Personal-Repository/Haskell/GeneticAlgorithms/ga-testing/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/libexec"
sysconfdir = "/home/rewrite/Documents/Personal-Repository/Haskell/GeneticAlgorithms/ga-testing/.stack-work/install/x86_64-linux/lts-3.14/7.10.2/etc"

getBinDir, getLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "ga_testing_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "ga_testing_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "ga_testing_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "ga_testing_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "ga_testing_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
