#lang racket

(require quickcheck)

(define (square x) (* x x))
(define (close-enough? x y)
  (< (abs (- x y)) 0.00001))

;; procedura sqrt znajduje pierwiastek kwadratowy
(quickcheck
 (property ([x arbitrary-real])
           (close-enough? x (square (sqrt x))))) ; eq nie zadiała


;; pierwiastek iloczynu jest iloczynem pierwiastków
;; nie działa -- close-enough? nie zdefiniowany dla liczb zespolonych
;(quickcheck
; (property ([x arbitrary-real]
;            [y arbitrary-real])
;           (close-enough? (sqrt (* x y)) (* (sqrt x) (sqrt y)))))

(define (close-enough-complex? x y)
  (< (magnitude (- x y)) 0.00001))

;; pierwiastek iloczynu jest iloczynem pierwiastków -- drugie podejście
;; też nie działa -- wyniki różnią się znakiem
(quickcheck
 (property ([x arbitrary-real]
            [y arbitrary-real])
           (close-enough-complex? (sqrt (* x y)) (* (sqrt x) (sqrt y)))))

;; pierwiastek iloczynu jest iloczynem pierwiastków -- trzecie podejście
(quickcheck
 (property ([x arbitrary-real]
            [y arbitrary-real])
           (==> (positive? x)
                (==> (positive? y)
                     (close-enough? (sqrt (* x y)) (* (sqrt x) (sqrt y)))))))

;; pierwiastek iloczynu jest iloczynem pierwiastków -- czwarte podejście
(quickcheck
 (property ([x (choose-real 0 1000)]
            [y (choose-real 0 1000)])
           (close-enough? (sqrt (* x y)) (* (sqrt x) (sqrt y)))))

;; procedura cons tworzy parę
(quickcheck
 (property ([x arbitrary-symbol]
            [y arbitrary-symbol])
           (and (eq? x (car (cons x y))) (eq? y (cdr (cons x y))))))

;; procedura map zachowuje długość
(quickcheck
 (property ([l (arbitrary-list arbitrary-symbol)]
            [p (arbitrary-procedure arbitrary-symbol arbitrary-symbol)])
           (eq? (length l) (length (map p l)))))

;; długość konkatenacji list to suma długości list wejściowych
(quickcheck
 (property ([l1 (arbitrary-list arbitrary-symbol)]
            [l2 (arbitrary-list arbitrary-symbol)])
           (eq? (length (append l1 l2)) (+ (length l1) (length l2)))))

;; rozdzielność append względem map
(quickcheck
 (property ([l1 (arbitrary-list arbitrary-symbol)]
            [l2 (arbitrary-list arbitrary-symbol)]
            [p (arbitrary-procedure arbitrary-symbol arbitrary-symbol)])
           (equal? (map p (append l1 l2)) (append (map p l1) (map p l2)))))

;; błędna implementacja map -- odwraca listę
;; podany kontrakt nie sprawdza kolejności
(define/contract (bad-map f xs)
  (parametric->/c [a b] (-> (-> a b) (listof a) (listof b)))
  (define (map-iter xs ys)
    (cond [(null? xs) ys]
          [else (map-iter (cdr xs) (cons (f (car xs)) ys))]))
  (map-iter xs '()))

;; błędna implementacja map nie ma własności rozdzielności względem append
(quickcheck
 (property ([l1 (arbitrary-list arbitrary-symbol)]
            [l2 (arbitrary-list arbitrary-symbol)]
            [p (arbitrary-procedure arbitrary-symbol arbitrary-symbol)])
           (equal? (bad-map p (append l1 l2)) (append (bad-map p l1) (bad-map p l2)))))
