#lang racket

(struct const (val)    #:transparent)
(struct binop (op l r) #:transparent)

(define (rpn-expr? e)
  (and (list? e)
       (pair? e)
       (andmap (lambda (x) (or (number? x) (member x '(+ - * /))))
               e)))

(struct stack (xs))

(define empty-stack (stack null))
(define (empty-stack? s) (null? (stack-xs s)))
(define (top s) (car (stack-xs s)))
(define (push a s) (stack (cons a (stack-xs s))))
(define (pop s) (stack (cdr (stack-xs s))))

(define (op->proc op)
  (match op ['+ +] ['- -] ['* *] ['/ /]))

(define (eval-am e s)
  (cond [(null? e)
         (top s)]
        [(number? (car e))
         (eval-am (cdr e) (push (car e) s))]
        [(symbol? (car e))
         (eval-am (cdr e)
                  (push ((op->proc (car e)) (top s) (top (pop s)))
                        (pop (pop s))))]))

(define (eval-rpn e) (eval-am e empty-stack))

(define (arith->rpn e)
  (match e
    [(const n) (list n)]
    [(binop op l r) (append (arith->rpn l)
                            (arith->rpn r)
                            (list op))]))

(define 2+2*2 (binop '+ (const 2)
                        (binop '* (const 2)
                                  (const 2))))