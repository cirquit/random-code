module Glob (namesMatching) where

import System.Directory (doesDirectoryExist, doesFileExist, getCurrentDirectory, getDirectoryContents)
import System.FilePath (dropTrailingPathSeparator, splitFileName, (</>))

import Control.Exception (handle)
import Control.Monad (forM)
import GlobRegex (matchesGlob, matchesGlobCs)

import System.Info (os)
import System.Posix.Files (fileExist)

isPattern :: String -> Bool
isPattern = any (`elem` "[*?")

namesMatching :: String -> IO[String]
namesMatching pat
        | not (isPattern pat) = do
               exists <- fileExist pat
               return (if exists then [pat] else [])
        | otherwise = do
              case splitFileName pat of
                   ("", baseName) -> do
                              curDir <- getCurrentDirectory
                              listMatches curDir baseName
                   (dirName, baseName) -> do
                              dirs <- if isPattern dirName 
                                         then namesMatching (dropTrailingPathSeparator dirName)
                                         else return [dirName]
                              let listDir = if isPattern baseName
                                               then listMatches
                                               else listPlain
                              pathNames <- forM dirs $ \dir -> do
                                                  baseNames <- listDir dir baseName
                                                  return (map (dir </>) baseNames)
                              return (concat pathNames)


-- returns all files matching the glob pattern in a directory (Windows not cs / otherwise cs)
listMatches :: FilePath -> String -> IO [String]
listMatches dirName pat = do
                            dirName' <- if null dirName
                                        then getCurrentDirectory
                                        else return dirName
                            names <- getDirectoryContents dirName' -- not exceptoion handling (p. 208)
                            let names' = if isHidden pat
                                         then filter isHidden names
                                         else filter (not . isHidden) names
                            if os == "windows" then return (filter (`matchesGlob` pat) names')
                            else return (filter (`matchesGlobCs` pat) names')


isHidden :: String -> Bool
isHidden ('.':_) = True
isHidden _ = False

listPlain :: FilePath -> String -> IO [String]
listPlain dirName baseName = do
                                exists <- if null baseName
                                          then doesDirectoryExist dirName
                                          else fileExist (dirName </> baseName)
                                return (if exists then [baseName] else [])


-- checking for directory OR file (already imported with fileExist from System.Posix.Files)
{-doesNameExist :: FilePath -> IO Bool
doesNameExist name = do
                        fileExists <- doesFileExist name
                        if fileExists 
                        then return True
                        else doesDirectoryExist name
-}
































