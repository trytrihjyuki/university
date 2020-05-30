#lang racket

( define ( var? t )
   ( symbol? t ) )
( define ( neg? t )
   ( and ( list? t )
         (= 2 ( length t ) )
         ( eq? 'neg ( car t ) ) ) )
( define ( conj? t )
   ( and ( list? t )
         (= 3 ( length t ) )
         ( eq? 'conj ( car t ) ) ) )
( define ( disj? t )
   ( and ( list? t )
         (= 3 ( length t ) )
         ( eq? 'disj ( car t ) ) ) )

(define (neg f)
  (list 'neg f))

(define (conj f1 f2)
  (list 'conj f1 f2))

(define (disj f1 f2)
  (list 'disj f1 f2))

(define (neg-subf f)
  (second f))

(define (conj-left f)
  (second f))

(define (conj-right f)
  (third f))

(define (disj-left f)
  (second f))

(define (disj-right f)
  (third f))


(define (literal? f)
  (or (var? f)
      (and (neg? f) (var? (neg-subf f)))))


(define (clause? x)
  (cond [(conj? x) #f]
        [(literal? x) #t]
        [else (and (clause? (disj-left x)) (clause? (disj-right x)))]))

(define (convert-to-nnf f)
  (define (convert-neg g)
    (cond [(var? g) (neg g)]
          [(neg? g) (convert-to-nnf (neg-subf g))]
          [(conj? g) (disj (convert-neg (conj-left g))
                           (convert-neg (conj-right g)))]
          [(disj? g) (conj (convert-neg (disj-left g))
                           (convert-neg (disj-right g)))]))
  
  (cond [(var? f) f]
        [(neg? f) (convert-neg (neg-subf f))]
        [(conj? f) (conj (convert-to-nnf (conj-left f))
                         (convert-to-nnf (conj-right f)))]
        [(disj? f) (disj (convert-to-nnf (disj-left f))
                         (convert-to-nnf (disj-right f)))]))

(define (convert-to-cnf f)
  (cond [(clause? f) f]
        [(conj? f) (conj (convert-to-cnf (conj-left f))
                         (convert-to-cnf (conj-right f)))]
        [(disj? f) (cond [(conj? (disj-right f))
                          (conj
                           (convert-to-cnf (disj
                                            (convert-to-cnf (disj-left f))
                                            (convert-to-cnf (conj-left (disj-right f)))))
                           (convert-to-cnf (disj
                                            (convert-to-cnf (disj-left f))
                                            (convert-to-cnf (conj-right (disj-right f))))))]
                         [(conj? (disj-left f))
                          (conj
                           (convert-to-cnf (disj
                                            (convert-to-cnf (conj-left (disj-left f)))
                                            (convert-to-cnf (disj-right f))))
                           (convert-to-cnf (disj
                                            (convert-to-cnf (conj-right (disj-left f)))
                                            (convert-to-cnf (disj-right f)))))]
                         [(or (disj? (disj-left f)) (disj? (disj-right f)))
                          (convert-to-cnf (disj (convert-to-cnf (disj-right f)) (convert-to-cnf (disj-left f))))])]))


(define (falsifiable-cnf? f)
  (define g (convert-to-cnf (convert-to-nnf f)))
  (define (find-neg c val)
    (cond
      [(disj? c) (or
                  (find-neg (disj-left c) val)
                  (find-neg (disj-right c) val))]
      [(var? c) (if (and (neg? val) (eq? c (neg-subf val)))
                    #t
                    #f)]
      [(neg? c) (if (and (var? val) (eq? (neg-subf c) val))
                    #t
                    #f)]
      [else #f]
      )
    )
  (define (falsifable-clause? c c-og)
    (cond
      [(disj? c) (or (falsifable-clause? (disj-left c) c-og) (falsifable-clause? (disj-right c) c-og))]
      [else (find-neg c-og c)]
      )
    )
  (define (get-val c)
    (cond
      [(disj? c) (append (get-val (disj-left c)) (get-val (disj-right c)))]
      [(if (var? c)
           (list (cons c #f))
           (list (cons (neg-subf c) #t))
      )]))
  (if (clause? g)
      (if (not (falsifable-clause? g g))
          (get-val g)
          #f)
      (cond
        [(list? (falsifiable-cnf? (conj-left g))) (remove-duplicates (falsifiable-cnf? (conj-left g)))]
        [(list? (falsifiable-cnf? (conj-right g))) (remove-duplicates (falsifiable-cnf? (conj-right g)))]
        [else #f])))
          

(define lol (disj (neg 'm) (conj 'p 'q)))
(define k (convert-to-nnf '(neg (disj (neg p) (conj q r)))))
(define tescior (conj (disj 'p 'q) (conj (neg 'p) (disj (neg 'q) 'r))))
(define tescior2 (disj (disj 'p (conj 'p 'r)) (disj 'q 's)))
(define test (disj (conj 'p 'm) (conj 'r 'q)))
(define f (disj (conj 'p 'm) 'r))
(define f1 (disj 'r (conj 'p 'm)))
(define czyzby (disj 'p (conj 'p 'r)))
(define czyzby2 (disj (conj (disj 'p 'p) (disj 'p 'r)) (disj 'p 's)))

(define tescior3 (disj 'p (neg 'p)))
(define tescior4 (conj (disj 'q (disj 'p (disj (neg 'p) (neg 'q)))) (disj 'r (neg 'r))))


(display "Test dla formuly: ")(display lol)(display " po przeksztalceniu: ")(falsifiable-cnf? lol)
(display "Test dla formuly: ")(display k)(display " po przeksztalceniu: ")(falsifiable-cnf? k)
(display "Test dla formuly: ")(display tescior)(display " po przeksztalceniu: ")(falsifiable-cnf? tescior)
(display "Test dla formuly: ")(display tescior2)(display " po przeksztalceniu: ")(falsifiable-cnf? tescior2)
(display "Test dla formuly: ")(display test)(display " po przeksztalceniu: ")(falsifiable-cnf? test)
(display "Test dla formuly: ")(display f)(display " po przeksztalceniu: ")(falsifiable-cnf? f)
(display "Test dla formuly: ")(display f1)(display " po przeksztalceniu: ")(falsifiable-cnf? f1)
(display "Test dla formuly: ")(display czyzby)(display " po przeksztalceniu: ")(falsifiable-cnf? czyzby)
(display "Test dla formuly: ")(display tescior3)(display " po przeksztalceniu: ")(falsifiable-cnf? tescior3)
(display "Test dla formuly: ")(display tescior4)(display " po przeksztalceniu: ")(falsifiable-cnf? tescior4)

(provide falsifiable-cnf?)
(provide convert-to-cnf)
(provide convert-to-nnf)

              