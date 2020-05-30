#lang racket

(define (inc x) (+ x 1))
(define (square x) (* x x))

;4
(define (compose f g)
  (lambda (x) (f (g x))))

((compose square inc) 2)
((compose inc square) 2)

;3

(define (reapeted p n)
  (if (> n 1)
      (compose (reapeted p (- n 1)) p)
      p))

((reapeted inc 4) 5)

;4

(define (pi-sum a b)
  (if (> a b)
      0
      (+ (/ 1.0 (* a (+ a 2)))
         (pi-sum (+ a 4) b))))

(define (pi-sum-iter a b)
  (define (iter sum a)
    (if (> a b)
        sum
        (iter (+ sum (/ 1.0 (* a (+ a 2)))) (+ a 4))))
  (iter 0 a))

(* 8 (pi-sum 1 10000))
(* 8 (pi-sum-iter 1 10000))

;6

(define (cont-frac num den k)
  (if (= k 0)
      0
      (/ (num 1) (+ (den 1) (cont-frac (compose num inc) (compose den inc) (- k 1))))))

(define (cont-frac-iter num den k)
  (define (iter lvl val)
    (if (= lvl 0)
        val
        (iter (- lvl 1) (/ (num lvl) (+ (den k) val)))))
  (iter k 0))

(cont-frac (lambda(i) 1.0) (lambda(i) 1.0) 1000)
(cont-frac-iter (lambda(i) 1.0) (lambda(i) 1.0) 1000)

;7
(display "\n7.\n\n")

(+ 3 (cont-frac (lambda(i) (square (- (* 2.0 i) 1.0))) (lambda(i) 6.0) 1000))
(+ 3 (cont-frac-iter (lambda(i) (square (- (* 2.0 i) 1.0))) (lambda(i) 6.0) 1000))

;8
(display "\n8.\n\n")
(define (atan-cf x k)
  (/ x (+ 1 (cont-frac (lambda(i) (square (* x i))) (lambda(i) (+ (* 2.0 i) 1.0)) k))))
  
(atan-cf 1 1000)  
(atan 1)

;9
(display "\n9.\n\n")
(define (build n d b)
  (/ n (+ d b)))

(define (reapeted-build k n d b)
  b((reapeted (lambda(i) (build n d i)) k) b))

(reapeted-build 1000 1.0 1.0 1.0)

;10

(define (cont-frac2 num den tolerance)
  (define (iter a_n-1 a_n-2 b_n-1 b_n-2 f_n-1 n)
    (let* ((a_n (+ (* (den n) a_n-1) (* (num n) a_n-2)))
         (b_n (+ (* (den n) b_n-1) (* (num n) b_n-2)))
         (f_n (/ a_n b_n)))
      (if (< (abs (- f_n f_n-1)) tolerance)
          f_n
          (iter a_n a_n-1 b_n b_n-1 f_n (+ n 1)))))
  (iter 0 1 1 0 1 1))

;testy
;(display "\ntesty:\n\ntest 1\n")
;(/ 1 (+ 1 (cont-frac (lambda(i) (square (* 1 i))) (lambda(i) (+ (* 2.0 i) 1.0)) 1000)))
;(/ 1 (+ 1 (cont-frac2 (lambda(i) (square (* 1 i))) (lambda(i) (+ (* 2.0 i) 1.0)) 0.000001)))
;(display "\ntest 2\n")
;(/ 4 (+ 1 (cont-frac (lambda(i) (square (* 4 i))) (lambda(i) (+ (* 2.0 i) 1.0)) 1000)))
;(/ 4 (+ 1 (cont-frac2 (lambda(i) (square (* 4 i))) (lambda(i) (+ (* 2.0 i) 1.0)) 0.000001)))
;(display "\ntest 3\n")
;(/ 21 (+ 1 (cont-frac (lambda(i) (square (* 21 i))) (lambda(i) (+ (* 2.0 i) 1.0)) 1000)))
;(/ 21 (+ 1 (cont-frac2 (lambda(i) (square (* 21 i))) (lambda(i) (+ (* 2.0 i) 1.0)) 0.01)))
;(display "\ntest 4\n")
;(/ 12 (+ 1 (cont-frac (lambda(i) (square (* 12 i))) (lambda(i) (+ (* 2.0 i) 1.0)) 1000)))
;(/ 12 (+ 1 (cont-frac2 (lambda(i) (square (* 12 i))) (lambda(i) (+ (* 2.0 i) 1.0)) 0.01)))

;11
;Funkcje z wykładu
(define (close-to? x y)
  (< (abs (- x y)) 0.00001))

(define (average x y)
  (/ (+ x y) 2))

(define (average-damp f)
  (lambda (x)
    (average x (f x))))

(define (fixed-point s f)
  ;(display s)
  ;(display "\n")
  (if (close-to? s (f s))
      s
      (fixed-point (f s) f)))
(display "\nzad.9\n")
;Moja funkcja poprawna
(define (nth-root n x)
  (fixed-point 1.0 ((reapeted average-damp (- (/ n 2) 1)) (lambda (y) (/ x (expt y (- n 1)))))))

(display "\ntesty poprawnej funkcji:\n")
(nth-root 10 1024)
(nth-root 3 125)
(nth-root 5 7776)
(nth-root 5 16807)
(nth-root 15 14348907)
(nth-root 10 10000000000)
(nth-root 16 65536)
;Nie poprawna funkcja tj. z jedną liczbą tłumień mniej
(define (nth-root-bad n x)
  (fixed-point 1.0 ((reapeted average-damp (- (/ n 2) 2)) (lambda (y) (/ x (expt y (- n 1)))))))

(display "\ntesty NIE poprawnej funkcji, zapętlają się:\n")
(nth-root-bad 10 1024)
(nth-root-bad 3 125)
(nth-root-bad 15 14348907)
(nth-root-bad 16 65536)
(nth-root 10 10000000000)
(nth-root-bad 5 16807)
(nth-root-bad 16 65536)
(nth-root-bad 5 7776)