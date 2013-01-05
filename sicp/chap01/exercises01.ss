(define (square n)
  (* n n))

(define (square-sum-larger a b c)
  (cond
    ((and (>= a b) (>= b c) (+ (square a) (square b))))
    ((and (>= a b) (>= c b) (+ (square a) (square c))))
    ((and (>= b a) (>= c b) (+ (square b) (square c))))
    ((and (>= b a) (>= a c) (+ (square b) (square a))))
    ((and (>= b a) (>= c a) (+ (square b) (square c))))))
