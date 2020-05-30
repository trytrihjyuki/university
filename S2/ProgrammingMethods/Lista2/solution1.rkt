#lang racket
;10
(define (square x) (* x x))
(define tolerance 0.001)

(define (cont-frac num den)
  (define (iter a_n-1 a_n-2 b_n-1 b_n-2 f_n-1 n)
    (let* ((a_n (+ (* (den n) a_n-1) (* (num n) a_n-2)))
         (b_n (+ (* (den n) b_n-1) (* (num n) b_n-2)))
         (f_n (/ a_n b_n)))
      (if (< (abs (- f_n f_n-1)) tolerance)
          f_n
          (iter a_n a_n-1 b_n b_n-1 f_n (+ n 1)))))
  (iter 0 1 1 0 1 1))

;testy
(display "\ntesty:\n\ntest 1\n")
(/ 1 (+ 1 (cont-frac (lambda(i) (square (* 1 i))) (lambda(i) (+ (* 2.0 i) 1.0)))))
(display "\ntest 2\n")
(/ 4 (+ 1 (cont-frac (lambda(i) (square (* 4 i))) (lambda(i) (+ (* 2.0 i) 1.0)))))
(display "\ntest 3\n")
(/ 400 (+ 1 (cont-frac (lambda(i) (square (* 400 i))) (lambda(i) (+ (* 2.0 i) 1.0)))))
(display "\ntest 4\n")
(/ 12 (+ 1 (cont-frac (lambda(i) (square (* 12 i))) (lambda(i) (+ (* 2.0 i) 1.0)))))
