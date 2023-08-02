#lang racket

; Jesus Ramirez Delgado
; A01274723
; Programacion 4

(define factorial
  (lambda (n)
  (if (<= n 1)
      1
      (* n (factorial (- n 1))))))


(define pow
  (lambda (n x)
    (if (= x 0)
    1
    (* n (pow n(- x 1))))))

(define fib
  (lambda (n)
    (cond ((= n 0)0)
          ((= n 1)1)
          (else (+(fib(- n 1))(fib(- n 2)))))))
                  