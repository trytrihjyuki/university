#lang racket
(define (compose f g)
  (lambda (x) (f (g x))))

(define (reapeted p n)
  (if (> n 1)
      (compose (reapeted p (- n 1)) p)
      p))

(define (close-to? x y)
  (< (abs (- x y)) 0.001))

(define (average x y)
  (/ (+ x y) 2))

(define (average-damp f)
  (lambda (x)
    (average x (f x))))

(define (fixed-point s f)
  ;(display s)
  ;(display "\n")
  (if (close-to? s (f s))
      s
      (fixed-point (f s) f)))
;(display "\nzad.9\n")
;Moja funkcja poprawna
(define (nth-root n x)
  (fixed-point 1.0 ((reapeted average-damp (- (/ n 2) 1)) (lambda (y) (/ x (expt y (- n 1)))))))

(provide nth-root)

;(display "\ntesty poprawnej funkcji:\n")
;(nth-root 10 1024)
;(nth-root 3 125)
;(nth-root 5 7776)
;(nth-root 5 16807)
;(nth-root 15 14348907)
;(nth-root 10 10000000000)
;(nth-root 16 65536)
;Nie poprawna funkcja tj. z jedną liczbą tłumień mniej
(define (nth-root-bad n x)
  (fixed-point 1.0 ((reapeted average-damp (- (/ n 2) 2)) (lambda (y) (/ x (expt y (- n 1)))))))

;(display "\ntesty NIE poprawnej funkcji, zapętlają się:\n")
;(nth-root-bad 10 1024)
;(nth-root-bad 3 125)
;(nth-root-bad 15 14348907)
;(nth-root-bad 16 65536)
;(nth-root 10 10000000000)
;(nth-root-bad 5 16807)
;(nth-root-bad 16 65536)
;(nth-root-bad 5 7776)