myprod :: Num a => [a] -> a
myprod [] = 1
myprod (x:xs) = x * myprod xs
