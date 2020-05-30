#lang racket

(struct node (data l r) #:transparent)
(struct leaf ()         #:transparent)

(define (height t)
  (cond [(leaf? t) 0]
        [(node? t) (+ 1 (max (height (node-l t))
                             (height (node-r t))))]))

; Tego lepiej nie próbować:
; (define (size t)
;  (cond [(leaf? t) 0]
;        [(node? t) (+ 1 (size (third t))
;                        (size (fourth t)))]))

(define (height-pm t)
  (match t [(leaf) 0]
           [(node d l r) (+ 1 (max (height-pm l)
                                   (height-pm r)))]))
