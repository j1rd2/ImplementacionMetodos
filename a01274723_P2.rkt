#lang racket

(define fahrenheit
         (lambda (f)
           (/ 9(* 5(- f 32)))))

(define roots
  (lambda(a b c)
    (/ 2 a(+ (- b)(sqrt(- (expt b 2)(* a c 4)))))))