#lang racket
(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))

(define (concatMap proc seq)
  (accumulate append null (map proc seq)))

(define (from-to low high)
  (if (> low high)
      null
      (cons low (from-to (+ 1 low) high))))

(concatMap  (list (list 1 2 3 4) (list 1 2 3 4) (list 1 2 3 4)))