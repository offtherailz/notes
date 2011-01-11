mysum :: Num a => [a] -> a
mysum [] = 0
mysum (x:xs) = x + mysum xs
