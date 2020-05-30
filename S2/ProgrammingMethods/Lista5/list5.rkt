#lang racket

(require "props.rkt")
(provide falsifiable-cnf?)

(define (to-nnf f)
  (cond
   [(var? f)  (lit-pos f)]
   [(neg? f)  (to-nnf-neg (neg-subf f))]
   [(conj? f) (conj (to-nnf (conj-left f))
                    (to-nnf (conj-right f)))]
   [(disj? f) (disj (to-nnf (disj-left f))
                    (to-nnf (disj-right f)))]))

(define (to-nnf-neg f)
  (cond
   [(var? f)  (lit-neg f)]
   [(neg? f)  (to-nnf f)]
   [(conj? f) (disj (to-nnf-neg (conj-left f))
                    (to-nnf-neg (conj-right f)))]
   [(disj? f) (conj (to-nnf-neg (disj-left f))
                    (to-nnf-neg (disj-right f)))]))

(define (lit? f)
  (or (var? f)
      (and (neg? f)
           (var? (neg-subf f)))))

(define (lit-pos v)
  v)

(define (lit-neg v)
  (neg v))

(define (lit-var l)
  (if (var? l)
      l
      (neg-subf l)))

(define (lit-pos? l)
  (var? l))

(define (mk-cnf xss)
  (cons 'cnf xss))

(define (clause? f)
  (and (list? f)
       (andmap lit? f)))

(define (cnf? f)
  (and (pair? f)
       (eq? 'cnf (car f))
       (list? (cdr f))
       (andmap clause? (cdr f))))

(define (to-cnf f)
  (define (join xss yss)
    (apply append (map (lambda (xs) (map (lambda (ys) (append xs ys)) yss)) xss)))
  (define (go f)
    (cond
     [(lit? f)  (list (list f))]
     [(conj? f) (append (go (conj-left f))
                        (go (conj-right f)))]
     [(disj? f) (join (go (disj-left f))
                      (go (disj-right f)))]))
  (mk-cnf (go f)))

(define (falsifiable-cnf? f)
  (error "TODO: Uzupelnij tutaj"))





(define (falsifable-cnf? f)
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
        [(list? (falsifable-cnf? (conj-left g))) (remove-duplicates (falsifable-cnf? (conj-left g)))]
        [(list? (falsifable-cnf? (conj-right g))) (remove-duplicates (falsifable-cnf? (conj-right g)))]
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


(display "Test dla formuly: ")(display lol)(display " po przeksztalceniu: ")(falsifable-cnf? lol)
(display "Test dla formuly: ")(display k)(display " po przeksztalceniu: ")(falsifable-cnf? k)
(display "Test dla formuly: ")(display tescior)(display " po przeksztalceniu: ")(falsifable-cnf? tescior)
(display "Test dla formuly: ")(display tescior2)(display " po przeksztalceniu: ")(falsifable-cnf? tescior2)
(display "Test dla formuly: ")(display test)(display " po przeksztalceniu: ")(falsifable-cnf? test)
(display "Test dla formuly: ")(display f)(display " po przeksztalceniu: ")(falsifable-cnf? f)
(display "Test dla formuly: ")(display f1)(display " po przeksztalceniu: ")(falsifable-cnf? f1)
(display "Test dla formuly: ")(display czyzby)(display " po przeksztalceniu: ")(falsifable-cnf? czyzby)
(display "Test dla formuly: ")(display tescior3)(display " po przeksztalceniu: ")(falsifable-cnf? tescior3)
(display "Test dla formuly: ")(display tescior4)(display " po przeksztalceniu: ")(falsifable-cnf? tescior4)

  

              