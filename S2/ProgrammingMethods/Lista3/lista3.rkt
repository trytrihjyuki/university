#lang racket

(define (make-point x y) (cons x y))
(define (point? p) (pair? p))

(define (make-vect point1 point2)(cons point1 point2))

(define (vect? x)
  (if (and (pair? (car x)) (pair? (cdr x)))
      1
      0))

(define (vect-begin v) (car v))
(define (vect-end v) (cdr v))

;(define siema (make-vect ) (point 3 4)))
;(vect? siema)


;zadanie 3
(define lista (list 1 2 3 420 997))


(define (last-item l)
  (if (pair? (cdr l))
      (last-item (cdr l))
      (car l)))

(last-item lista) 

(define (reverse-r lista)
  (if (null? lista)
      null
      (append (reverse-r (cdr lista))(list (car lista)))))

(define (compose f g)
  (lambda (x) (f (g x))))
(define (reapeted p n)
  (if (> n 1)
      (compose (reapeted p (- n 1)) p)
      p))

(define (reverse-iter lista)
  (define (iter l1 l-result)
    (if (null? l1)
        l-result
        (iter (cdr l1)(cons (car l1) l-result))))
  (iter lista null))

(reverse-r lista)
(reverse-r (list 1 2 3 4 5))
(reverse-iter lista)
(reverse-iter (list 1 2 3 4 5))

;4


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

;5

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
;8
(define (split lista1)
  (define (split-iter pref suf)
    (if (>= (length pref) (/ (length lista1) 2))
        (cons pref suf)
        (split-iter (append pref (list (car suf) )) (cdr suf))))
  (split-iter null lista1))


(define (merge lista1 lista2)
  (define (merge-helper l1 l2 result)
    (cond
         ((and (null? l1) (null? l2))
            result)
          ((null? l1)
            (merge-helper l1 null (append result l2)))
          ((null? l2)
            (merge-helper null l2 (append result l1)))
          ((<= (car l1) (car l2))
           (merge-helper (cdr l1) l2 (append result (list(car l1)))) )
          (else
           (merge-helper l1 (cdr l2) (append result (list(car l2)))) )
          )
    )
  (merge-helper lista1 lista2 null))
          



(define (merge-sort lista)
  (define temporary (split lista))
  (if (= (length lista) 1)
      lista
      (merge (merge-sort (car temporary)) (merge-sort (cdr temporary)))))

;9

(define (partition n xs)
  (define (pom lista small big)
    (if (null? lista)
        (cons small big)
        (if (<= (car lista) n)
            (pom (cdr lista) (append small (list (car lista))) big)
            (pom (cdr lista) small (append big (list (car lista)))))))
  (pom xs null null))

(define (quicksort l)
  (if (null? l)
      l
      (append (append (quicksort (car (partition (car l) (cdr l)))) (list (car l))) (quicksort (cdr (partition (car l) (cdr l)))))))
      


(quicksort (list 7  6 11 22 2 997 24 69 5))     
(partition (car (list 7 6 2 5)) (list 7 6 2 5))
(quicksort (list 7 6 2 5))

;TESTY
