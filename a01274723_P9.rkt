#lang racket

; Jesus Ramirez Delgado
; A01274723
; Programacion 9

; Ejercicio 1

; (define (sumatoria datos)
;  (if (null? datos)
;      0
;      (+ (car datos) sumatoria (cdr datos))))

(define (sumatoria datos)
  (sumatoria-ayuda datos 0)) ; Llama funcion auxiliar

(define sumatoria-ayuda ; Funcion auxiliar
  (lambda (datos acc)
    (if (null? datos)
        acc
        (sumatoria-ayuda (cdr datos) (+ (car datos) acc)))))

; Ejercicio 2

; (define (incrementa datos)
;   (if (null? datos)
;      0
;      (cons (+ 1 (car datos))(incrementa (cdr datos)))))

(define (incrementa datos) 
  (incrementa-ayuda datos '())) ; Llama funcion auxiliar

(define incrementa-ayuda ; Funcion auxiliar 
  (lambda (datos acc)
    (if (null? datos)
        (reverse acc)
        (incrementa-ayuda (cdr datos) (cons (+ 1 (car datos)) acc)))))



