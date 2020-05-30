#lang racket

(define (cube-root x)
  (define tolerance 0.0001)
  (define (good guess x)
    (if (< (abs (- (* guess guess guess) x)) tolerance) true false))
  (define (cube-root-iter guess x)
    (if (good guess x)
        guess
        (cube-root-iter (/ (+ (/ x (* guess guess)) (* 2 guess)) 3) x)))
  (cube-root-iter 1.0 x))


(provide cube-root)

(cube-root 8)
(cube-root -125)
(cube-root 10045600)
(cube-root 55524)