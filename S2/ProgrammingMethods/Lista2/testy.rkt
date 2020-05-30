#lang racket

(define (sum term a next b)
  (if (> a b)
      0
      (+ (term a)
         (sum term (next a) next b))))


(define (cube x) (* x x x))

(define (inc n) (+ n 1))
(define (sume-cubes a b)
  (sum cube a inc b))

(sume-cubes 1 10)