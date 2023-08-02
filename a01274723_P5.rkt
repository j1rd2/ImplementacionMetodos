#lang racket

; Jesus Ramirez Delgado
; A01274723
; Programacion 5

 (define list1 '(1 4 -3 2 -5 -7 5 9 5 3 5))

(define how-many-positives
  (lambda (n)
    (cond ((null? n)0)
          ((>(car n) 0)
           (+ 1 (how-many-positives(cdr n))))
          (else (how-many-positives(cdr n))))))


(define find
  (lambda (lst b)
  (cond ((null? lst) 0)
        ((= (car lst) b)
         (+ 1 (find (cdr lst) b)))
        (else (find (cdr lst) b)))))