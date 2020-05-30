#lang racket

; --------------------- ;
; Składnia abstrakcyjna ;
; --------------------- ;

(struct const (val)    #:transparent)
(struct binop (op l r) #:transparent)

; 2 + 2 * 2
(define 2+2*2 (binop '+ (const 2)
                        (binop '* (const 2)
                                  (const 2))))

; Co to są wyrażenia?
(define (expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]))

; ---- ;
; Stos ;
; ---- ;

(struct stack (xs))

(define empty-stack (stack null))
(define (empty-stack? s) (null? (stack-xs s)))
(define (top s) (car (stack-xs s)))
(define (push a s) (stack (cons a (stack-xs s))))
(define (pop s) (stack (cdr (stack-xs s))))

; ------------------------------------ ;
; Ewaluacja przez maszynę abstrakcyjną ;
; ------------------------------------ ;

; Co to są wartości?
(define (value? v)
  (number? v))

(define (op->proc op)
  (match op ['+ +] ['- -] ['* *] ['/ /]))

; Ramki do wstawiania na stos
(struct frame-l (op e))
(struct frame-r (op v))

; Eval-Apply Ying-Yang
(define (eval-am e s)
  (match e
    [(const n) (apply n s)]
    [(binop op l r) (eval-am l (push (frame-l op r) s))]))

(define (apply v s)
  (if (empty-stack? s) v
      (match (top s)
        [(frame-l op r) (eval-am r (push (frame-r op v) (pop s)))]
        [(frame-r op w) (apply ((op->proc op) w v) (pop s))])))

(define (eval e) (eval-am e empty-stack))
