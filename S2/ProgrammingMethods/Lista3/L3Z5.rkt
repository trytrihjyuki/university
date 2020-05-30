#lang racket
(define (select-min l)
  (define (pom lista kandydat)
    (if (null? lista)
        kandydat
        (if (< (car lista) kandydat)
            (pom (cdr lista) (car lista))
            (pom (cdr lista) kandydat))))
  (let ([mini (pom l 100000000)])
    (define (pom2 pre suf)
      (if (= (car suf) mini)
          (append pre (cdr suf))
          (pom2 (append pre (list(car suf))) (cdr suf))))
    (cons (pom2 null l) mini)))

(define (select-sort lista)
  (define (pom l sorted)
    (if (null? l)
        sorted
        (pom  (car (select-min l)) (append sorted (list (cdr (select-min l)))))))
  (pom lista null))

(select-sort (list 7  6 11 22 2 997 24 69 5))