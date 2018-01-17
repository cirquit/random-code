{-# LANGUAGE CPP #-}
{-# OPTIONS_GHC -fno-warn-missing-import-lists #-}
{-# OPTIONS_GHC -fno-warn-implicit-prelude #-}
module Paths_svg_loading (
    version,
    getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir,
    getDataFileName, getSysconfDir
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

#if defined(VERSION_base)

#if MIN_VERSION_base(4,0,0)
catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
#else
catchIO :: IO a -> (Exception.Exception -> IO a) -> IO a
#endif

#else
catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
#endif
catchIO = Exception.catch

version :: Version
version = Version [0,1,0,0] []
bindir, libdir, dynlibdir, datadir, libexecdir, sysconfdir :: FilePath

bindir     = "/home/rewrite/Documents/github-repos/random-code/Haskell/svg-loading/.stack-work/install/x86_64-linux-nopie/lts-9.0/8.0.2/bin"
libdir     = "/home/rewrite/Documents/github-repos/random-code/Haskell/svg-loading/.stack-work/install/x86_64-linux-nopie/lts-9.0/8.0.2/lib/x86_64-linux-ghc-8.0.2/svg-loading-0.1.0.0-8ezZ6UvT4zy52o8uNEaUV2"
dynlibdir  = "/home/rewrite/Documents/github-repos/random-code/Haskell/svg-loading/.stack-work/install/x86_64-linux-nopie/lts-9.0/8.0.2/lib/x86_64-linux-ghc-8.0.2"
datadir    = "/home/rewrite/Documents/github-repos/random-code/Haskell/svg-loading/.stack-work/install/x86_64-linux-nopie/lts-9.0/8.0.2/share/x86_64-linux-ghc-8.0.2/svg-loading-0.1.0.0"
libexecdir = "/home/rewrite/Documents/github-repos/random-code/Haskell/svg-loading/.stack-work/install/x86_64-linux-nopie/lts-9.0/8.0.2/libexec"
sysconfdir = "/home/rewrite/Documents/github-repos/random-code/Haskell/svg-loading/.stack-work/install/x86_64-linux-nopie/lts-9.0/8.0.2/etc"

getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "svg_loading_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "svg_loading_libdir") (\_ -> return libdir)
getDynLibDir = catchIO (getEnv "svg_loading_dynlibdir") (\_ -> return dynlibdir)
getDataDir = catchIO (getEnv "svg_loading_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "svg_loading_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "svg_loading_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
