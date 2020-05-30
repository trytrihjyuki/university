#lang racket
;PRACA GRUPOWA Maurycy Borkowski, Piotrek Piesiak, Filip Komorowski, Marcin Badowski
(provide (struct-out complex) parse eval)

(struct complex (re im) #:transparent)

(define value?
  complex?)

;; Ponizej znajduje sie interpreter zwyklych wyrazen arytmetycznych.
;; Zadanie to zmodyfikowac go tak, by dzialal z liczbami zespolonymi.

(struct const (val)    #:transparent)
(struct binop (op l r) #:transparent)



(define (conjugate c)
  (complex (complex-re c) (- (complex-im c))))

(define (add c1 c2)
  (complex (+ (complex-re c1) (complex-re c2)) (+ (complex-im c1) (complex-im c2))))

(define (mult c1 c2)
  (complex (- (* (complex-re c1) (complex-re c2)) (* (complex-im c1) (complex-im c2))) (+ (* (complex-re c1) (complex-im c2)) (* (complex-im c1) (complex-re c2)))))

(define (sub c1 c2)
  (complex (- (complex-re c1) (complex-re c2)) (- (complex-im c1) (complex-im c2))))

(define (divReal c r)
  (complex (/ (complex-re c) r) (/ (complex-im c) r))) 

(define (div c1 c2)
  (divReal (mult c1 (conjugate c2)) (complex-re (mult c2 (conjugate c2)))))
  

(define (op->proc op)
  (match op ['+ add] ['- sub] ['* mult] ['/ div]))

(define (eval e)
  (match e
    [(complex re im) (complex re im)]
    [(binop op l r) ((op->proc op) (eval l) (eval r))]))

(define (parse q)
  (cond [(number? q) (complex  q  0)]
       [(equal? q 'i)  (complex  0  1)]
        [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
         (binop (first q) (parse (second q)) (parse (third q)))]))

;(eval (parse '(+ 1 (* 8 i))))
;(define elu (complex 3 6))
;(define wina (complex 1 3))
;(div elu wina)

;(eval (parse'(+ 3 (* i 8))))

;(value? '(+ (complex 3 1)))