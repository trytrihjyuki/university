#lang racket



;3
(define (btree? t)
  (or (eq? t 'leaf)
      (and(list? t)
         (= 4 (length t))
         (eq? (car t) 'node)
         (btree? (caddr t))
         (btree? (cadddr t)))))

(define (leaf? t)
  (eq? t 'leaf))

(define (node-elem h)
  (second h))

(define (node-left h)
  (third h))

(define (node-right h)
  (fourth h))

(define (flatten t)
  (define (flat t acc)
    (if (leaf? t)
        acc
        (flat (node-left t) (cons (node-elem t) (flat (node-right t) acc)))))
  (flat t null))


(flatten '(node a (node b (node c leaf leaf) leaf) (node d leaf leaf)))
       

