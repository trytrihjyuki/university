#lang racket

;PRACA GRUPOWA MAURYCY BORKOWSKI MARCIN BADOWSKI PIOTREK PIESIAK FILIP KOMOROWSKI

(require racket/contract)

(provide (contract-out
          [with-labels  with-labels/c]
          [foldr-map  foldr-map/c]
          [pair-from  pair-from/c ]
          ))

(provide with-labels/c  foldr-map/c  pair-from/c)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define with-labels/c
    (parametric->/c [a b]
    (-> (-> a b) (listof a) (listof (cons/c b a)))))

(define (with-labels f xs)
    (parametric->/c [a b]
    (-> (-> a b) (listof a) (listof (list/c b a))))
  (define (labels-iter helpxs l) 
    (if (null? l)
        helpxs
        (labels-iter (append helpxs (list (list (f (car l)) (car l)))) (cdr l))))
  (labels-iter '() xs))

;(with-labels  number->string (list 1 2 3))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define foldr-map/c
  (parametric->/c [a b c]
                  (-> (-> a c (cons/c b c)) c (listof a) (cons/c (listof b) c))))  
  
(define (foldr-map f a xs)
  (parametric->/c [a b c]
                  (-> (-> a c (cons/c b c)) c (listof a) (cons/c (listof b) c)))
  (define (it a xs ys)
    (if (null? xs)
        (cons  ys a)
        (let[(p (f (car xs) a))]
          (it (cdr p)
              (cdr xs)
              (cons (car p) ys)))))
  (it a (reverse xs) null))

  
;(foldr-map (lambda(x a) (cons a (+ a x))) 0'(1 2 3))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define pair-from/c
  (parametric->/c [a b c]
                  (-> (-> a b) (-> a c) (-> a (cons/c b c)))))

(define (pair-from f g)
  (parametric->/c [a b c]
                  (-> (-> a b) (-> a c) (-> a (cons/c b c))))
  (lambda (x)
    (cons (f x) (g x))))

;(( pair-from (lambda(x) (+ x 1)) (lambda(x) (* x 2))) 2)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;