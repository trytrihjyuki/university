#lang racket

;PRACA GRUPOWA Filip Komorowski, Maurycy Borkowski, Marcin Badowski, Piotr Piesiak

(require "graph.rkt")
(provide bag-stack@ bag-fifo@)

;; struktura danych - stos
(define-unit bag-stack@
  (import)
  (export bag^)
  
  ;; TODO: zaimplementuj
  (define (bag? b)
    (and (list? b)
         (eq? (length b) 2)
         (eq? (first b) 'bag-stack)))

  (define empty-bag (list 'bag-stack '()))

  (define (bag-empty? b)
    (equal? b empty-bag))

  (define (bag-insert b v)
    (if (bag-empty? b)
        (list 'bag-stack (list v))
    (list (first b) (cons v (second b)))))
  
  (define (bag-peek b)
    (car (second b)))

  (define (bag-remove b)
    (if (null? (second b))
        empty-bag
    (list (first b) (cdr (second b)))))
)

;; struktura danych - kolejka FIFO
(define-unit bag-fifo@
  (import)
  (export bag^)
  
  ;; TODO: zaimplementuj

  ;Kolejka -> ('label input output)
  
  (define (bag? b)
    (and (list? b)
         (eq? (length b) 3)
         (eq? (first b) 'bag-fifo)))

  (define (bag-empty? b)
    (equal? b empty-bag))
  
  (define empty-bag (list 'bag-fifo '() '()))

  (define (bag-peek b)
    (car (third b)))

  (define (new-queue input output)
    (if (null? output)
        (list 'bag-fifo '() (reverse input))
        (list 'bag-fifo input output)))
        
   (define (bag-remove b)
     (if (eq? b empty-bag)
         empty-bag
         (if (null? (third b))
               (bag-remove (new-queue '() (reverse (second b))))
               (new-queue (second b) (cdr (third b))))))

  (define (bag-insert b v)
    (new-queue (cons v (second b)) (third b))) 
)

;; otwarcie komponentów stosu i kolejki

(define-values/invoke-unit bag-stack@
  (import)
  (export (prefix stack: bag^)))

(define-values/invoke-unit bag-fifo@
  (import)
  (export (prefix fifo: bag^)))

;; testy w Quickchecku
(require quickcheck)

;; testy kolejek i stosów
(define-unit bag-tests@
  (import bag^)
  (export)
  
  ;; test przykładowy: jeśli do pustej struktury dodamy element
  ;; i od razu go usuniemy, wynikowa struktura jest pusta
  (quickcheck
   (property ([s arbitrary-symbol])
             (bag-empty? (bag-remove (bag-insert empty-bag s)))))
  ;; TODO: napisz inne własności do sprawdzenia!
  
  ;Czy to dodamy do pustego baga to to samo co bag-peek
  (quickcheck
   (property ([s arbitrary-symbol])
             (equal? s (bag-peek (bag-insert empty-bag s)))))
  
)

(define-unit stack-tests@
  (import bag^)
  (export)

  (quickcheck
   (property ([a arbitrary-symbol]
             [b arbitrary-symbol])
            (eq? (bag-peek (bag-insert (bag-insert empty-bag a) b) ) b)))
  
  (quickcheck
   (property ([l (arbitrary-list arbitrary-symbol)]
          	[s arbitrary-symbol])
         	(eq? s (bag-peek (bag-insert (list 'bag-stack l) s)))))
  
  (quickcheck ;Czy w stacku elementy są odwrotnie jak na liście
   (property ([l (arbitrary-list arbitrary-symbol)])
         	(==> (not (empty? l))
              	(let ([b (foldl (lambda (x s) (bag-insert s x)) empty-bag l)])
                	(define (check-contain bg xs)
                  	(if (or (bag-empty? bg) (empty? xs))
                      	(and (bag-empty? bg) (empty? xs))
                      	(and (equal? (bag-peek bg) (car xs)) (check-contain (bag-remove bg) (cdr xs)))))
                	(check-contain b (reverse l))
                	))))

   
)
(define-unit queue-tests@
  (import bag^)
  (export)

  (quickcheck
   (property ([a arbitrary-symbol]
             [b arbitrary-symbol])
            (eq? (bag-peek (bag-insert (bag-insert empty-bag a) b) ) a)))

  (quickcheck ;Czy w stacku elementy są odwrotnie jak na liście
   (property ([l (arbitrary-list arbitrary-symbol)])
         	(==> (not (empty? l))
              	(let ([b (foldl (lambda (x s) (bag-insert s x)) empty-bag l)])
                	(define (check-contain bg xs)
                  	(if (or (bag-empty? bg) (empty? xs))
                      	(and (bag-empty? bg) (empty? xs))
                      	(and (equal? (bag-peek bg) (car xs)) (check-contain (bag-remove bg) (cdr xs)))))
                	(check-contain b l)
                	))))
   
)

;; uruchomienie testów dla obu struktur danych

(invoke-unit bag-tests@ (import (prefix stack: bag^)))
(invoke-unit bag-tests@ (import (prefix fifo: bag^)))
(invoke-unit stack-tests@ (import (prefix stack: bag^)))
(invoke-unit queue-tests@ (import (prefix fifo: bag^)))

;; TODO: napisz też testy własności, które zachodzą tylko dla jednej
;; z dwóch zaimplementowanych struktur danych



;; otwarcie komponentu grafu
(define-values/invoke-unit/infer simple-graph@)

;; otwarcie komponentów przeszukiwania 
;; w głąb i wszerz
(define-values/invoke-unit graph-search@
  (import graph^ (prefix stack: bag^))
  (export (prefix dfs: graph-search^)))

(define-values/invoke-unit graph-search@
  (import graph^ (prefix fifo: bag^))
  (export (prefix bfs: graph-search^)))

;; graf testowy
(define test-graph
  (graph
   (list 1 2 3 4)
   (list (edge 1 3)
         (edge 1 2)
         (edge 2 4))))
;; TODO: napisz inne testowe grafy

(define test-graph2
  (graph
   (list 1 2 3 4 5 6)
   (list (edge 1 2)
     	(edge 1 3)
     	(edge 1 4)
     	(edge 2 5)
     	(edge 4 6))))

(define test-graph3
  (graph
   (list 'w 2)
   (list (edge 'w 2))))

;; uruchomienie przeszukiwania na przykładowym grafie
(bfs:search test-graph 1)
(dfs:search test-graph 1)
;; TODO: uruchom przeszukiwanie na swoich przykładowych grafach
(bfs:search test-graph2 1)
(dfs:search test-graph2 1)
(bfs:search test-graph3 'w)
(dfs:search test-graph3 'w)