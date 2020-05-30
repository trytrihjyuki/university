#lang racket

(define (node data l r) (list 'node data l r))
(define (node? t) (and (pair? t) (eq? (car t) 'node)))
(define (node-data t) (second t))
(define (node-l t) (third t))
(define (node-r t) (fourth t))

(define (leaf) (list 'leaf))
(define (leaf? t) (and (pair? t) (eq? (car t) 'leaf)))

(define (height t)
  (cond [(leaf? t) 0]
        [(node? t) (+ 1 (max (height (node-l t))
                             (height (node-r t))))]))

(define (size t)
  (cond [(leaf? t) 0]
        [(node? t) (+ 1 (size (third t))
                        (size (fourth t)))]))