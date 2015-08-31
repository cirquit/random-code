module ListTransformations (dropItem, dropFromBothEnds, crtSubListsBy, dropLastUntil) where 

import Data.List (foldl')

-- deletes the item from the list
-- dropItem '/' "/home/i/test/"  -> "homeitest"
dropItem :: (Eq a) => a -> [a] -> [a]
dropItem i = foldr (\x y -> if x == i then y else x : y) []




-- cuts the list from the start to front until end and drops everything else
-- doubleDrop 2 3 "Haskell is fun!" -> "skell is fu"
dropFromBothEnds :: Int -> Int -> [a] -> [a]
dropFromBothEnds front end l = reverse (e f)
                        where f = drop front l
                              e l' = drop end (reverse l')

-- drops the last item from a filepath
-- dropLastFile "/home/i/test/dir/item.hs" -> "/home/i/test/dir/"
dropLastFile :: String -> String
dropLastFile l = reverse $ dropWhile (/= '/') (reverse l)


-- creates sublists by a char seperator 
-- crtSubListsBy '/' "/home/i/test/dir/item.hs" -> ["",  "/", "home", "/" "i", "/" "test", "/" "dir", "/" "item.hs"]
crtSubListsBy :: Char -> String -> [String]
crtSubListsBy c l = case span (/=c) l of
                        (a, []) -> [a]
                        (a, b) -> [a] ++ [c:[]] ++  crtSubListsBy c (tail b)


-- drops until the last element matches
-- dropLastUntil "dir" '/' "/home/i/test/dir/item.hs" -> "/home/i/test/dir"
dropLastUntil :: String -> Char -> String -> String
dropLastUntil word sep l = concat $ reverse (dropWord word subList)
                                where subList = reverse $ crtSubListsBy sep l
                                      dropWord _ [] = []
                                      dropWord word xx@(x:xs)
                                        | word == x = xx
                                        | otherwise = dropWord word xs







