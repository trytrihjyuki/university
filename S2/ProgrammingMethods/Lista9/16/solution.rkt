#lang racket
;PRACA GRUPOWA: MAURYCY BORKOWSKI, MARCIN BADOWSKI, FILIP KOMOROWSKI, PIOTREK PIESIAK
(provide lcons lnull lnull? lcar lcdr)
(define (cycle xs)
  (define (list->mlist xs)
    (cond [(null? xs) null]
          [else (mcons (car xs) (list->mlist (cdr xs)))]))
  (define (first-to-last! mxs)
    (define (aux mys)
      (cond [(null? mys) (error "Can't cycle empty list")]
            [(and (mpair? mys) (null? (mcdr mys)))
             (set-mcdr! mys mxs)]
            [else (aux (mcdr mys))]))
    (aux mxs))
  (let ([mxs (list->mlist xs)])
    (begin (first-to-last! mxs)
           mxs)))

(define (mtake n mxs)
  (cond [(= n 0) null]
        [(null? mxs) null]
        [else (cons (mcar mxs) (mtake (- n 1) (mcdr mxs)))]))

(define (test)
  (mtake 15 (cycle '(0 1 2 3))))


(define(from n)
  (lcons n (lambda() (from (+ n 1)))))

(define lnull  null)
(define lnull? null?)
(define (lcons x f) (mcons x (mcons f lnull)))
(define (lcar xs) (mcar xs))
(define (lcdr xs) (if (lnull? (mcdr (mcdr xs)))
                      (let ([v ((mcar (mcdr xs)))])
                        ;(begin
                        (set-mcdr! (mcdr xs) v)
                         v);)
                        (mcdr (mcdr xs)))) 

 
(define nats 
  (from 0))

(define(lnth n xs)
  (cond[(= n 0) (lcar xs)]
       [else(lnth (- n 1) (lcdr xs))]))

(lnth 5 nats)


(define(lfilter p xs)
  (cond[(lnull? xs) lnull]
       [(p (lcar xs)) (lcons (lcar xs)
                             (lambda() (lfilter p (lcdr xs))))]
       [else(lfilter p (lcdr xs))]))

(define(prime? n)
  (define(factors i)
    (cond[(>= i n) (list n)]
         [(= (modulo n i) 0) (cons i (factors  (+ i 1)))]
         [else(factors  (+ i 1))]))
  (= (length (factors  1)) 2)); lista  wszystkich  liczb  pierwszych

(define primes (lfilter  prime? (from 2)))

;(time (lnth 1000 primes))

;(time (lnth 1001 primes))
;(time (lnth 1000 primes))


