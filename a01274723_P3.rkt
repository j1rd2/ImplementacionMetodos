#lang racket

; Jesus Ramirez Delgado
; A01274723
; Programacion 3

(define sign
  (lambda (n)
         (cond ((< n 0) -1)
               ((> n 0) 1)
               (else 0))))

(define BMI
  (lambda (w h)
    (let ((bmi (/ w (expt h 2))))
    (cond ((< bmi 20) 'UNDERWEIGHT)
          ((and (>= bmi 20) (< bmi 25)) 'NORMAL)
          ((and (>= bmi 25) (< bmi 30)) 'OBESEL1)
          ((and (>= bmi 30) (< bmi 40)) 'OBESEL2)
          (else 'OBESEL3)))))
  