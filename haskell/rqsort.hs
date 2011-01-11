rqsort :: Ord a => [a] -> [a]
rqsort [] = []
rqsort (x:xs) = rqsort larger ++ [x] ++ rqsort smaller
    where
    smaller = [a| a <- xs, a <= x]
    larger = [a| a <- xs, a > x]
