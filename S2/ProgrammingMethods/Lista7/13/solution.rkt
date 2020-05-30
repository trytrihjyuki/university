#lang racket
;PRACA GRUPOWA MAURYCY BROWKOSKI MARCIN BADOWSKI
; --------- ;
; Wyrazenia ;
; --------- ;

(struct const    (val)      #:transparent)
(struct binop    (op l r)   #:transparent)
(struct var-expr (id)       #:transparent)
(struct var-dead (id)       #:transparent)
(struct let-expr (id e1 e2) #:transparent)

(define (expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [(var-expr x) (symbol? x)]
    [(var-dead x) (symbol? x)]
    [(let-expr x e1 e2) (and (symbol? x) (expr? e1) (expr? e2))]
    [_ false]))

(define (parse q)
  (cond
    [(number? q) (const q)]
    [(symbol? q) (var-expr q)]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'let))
     (let-expr (first (second q))
               (parse (second (second q)))
               (parse (third q)))]
    [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
     (binop (first q)
            (parse (second q))
            (parse (third q)))]))

; ---------------------------------- ;
; Wyszukaj ostatnie uzycie zmiennych ;
; ---------------------------------- ;


(provide (struct-out const) (struct-out binop) (struct-out var-expr) (struct-out let-expr) (struct-out var-dead) find-dead-vars find-var kill-var)


(define (find-var var e)
  (match e
    [(const n) #f]
    [(binop op l r) (or (find-var var l) (find-var var r))]
    [(var-expr x) (eq? x var)]
    [(var-dead x) #f]
    [(let-expr x e1 e2) (if (eq? x var)
                            (find-var var e1)
                            (or (find-var var e1) (find-var var e2)))]))

(define (kill-var var ex)
  (match ex
    [(const n) (const n)]
    [(binop op l r)
     (cond
       [(find-var var r) (binop op l (kill-var var r))]
       [(find-var var l) (binop op (kill-var var l) r)]
       [else (binop op l r)])]
    [(let-expr x e1 e2) (if (eq? x var)
                            (let-expr x (kill-var var e1) e2)
                            (cond
                              [(find-var var e2) (let-expr x e1 (kill-var var e2))]
                              [(find-var var e1) (let-expr x (kill-var var e1) e2)]
                              [else (let-expr x e1 e2)]))]
    [(var-expr x)
     (if (eq?  x var)
         (var-dead x)
         (var-expr x))]
    [(var-dead x) (var-dead x)]))

(define (find-dead-vars e)
  (match e
    [(const n) (const n)]
    [(binop op l r) (binop op (find-dead-vars l) (find-dead-vars r))]
    [(var-expr x) (var-expr x)]
    [(var-dead x) (var-dead x)]
    [(let-expr x e1 e2) (let-expr x (find-dead-vars e1) (find-dead-vars (kill-var x e2)))]
    [_  e]))

