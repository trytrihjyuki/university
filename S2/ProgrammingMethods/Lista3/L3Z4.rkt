#lang racket
(define (insert xs n)
  (define (iter pre suf)
    (if (null? suf)
      (append pre (list n))
      (if (>= (car suf) n)
          (append  pre (list n) suf)
          (iter (append pre (list (car suf))) (cdr suf)))))
    (iter null xs))

(insert (list 1 2 4 5) 3)

(define (sortuj xs)
  (define (pomocnicza sorted l)
    (if (null? l)
        sorted
        (pomocnicza (insert sorted (car l)) (cdr l))))
  (pomocnicza null xs))

(sortuj (list 1  6 11 22 997 24 69 5))