module ListTransformations (dropItem, dropDouble) where 


-- deletes the item from the list
-- dropItem '/' "/home/i/test/"  -> "homeitest"
dropItem :: (Eq a) => a -> [a] -> [a]
dropItem i = foldr (\x y -> if x == i then y else x : y) []

-- cuts the list from the start to front until end and drops everything else
-- doubleDrop 2 3 "Haskell is fun!" -> "skell is fu"
dropDouble :: Int -> Int -> [a] -> [a]
dropDouble front end l = reverse (e f)
                        where f = drop front l
                              e f = drop end (reverse f)

