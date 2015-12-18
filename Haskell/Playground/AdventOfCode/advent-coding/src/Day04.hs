{-# LANGUAGE OverloadedStrings #-}

module Day04 where

import Data.Digest.Pure.MD5
import Data.ByteString.Lazy.Char8

input = pack "iwrupvqb"

-- Part 1

encodeMD5 i input = show $ md5 (input `append` (pack . show) i)

part1 = go 0 input
  where go n input
          | ('0':'0':'0':'0':'0':_) <- encodeMD5 n input = n
          | otherwise                                    = go (n+1) input


-- Part 2

part2 = go 0 input
  where go n input
          | ('0':'0':'0':'0':'0':'0':_) <- encodeMD5 n input = n
          | otherwise                                        = go (n+1) input