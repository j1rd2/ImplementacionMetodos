#lang racket

; Jesus Ramirez Delgado
; A01274723
; Programacion 6

; Listas para ejercicios

(define list1 '(1 2 3 4 2 5 1 3))
(define list2 '(1 -6 3 -2 -1 1 9))
(define list3 '(A B C D E F))
(define list4 '(A 5 Z 1 -7 D 9))
(define dot1 '(1 4 3))
(define dot2 '(2 9 7))

; Ejercicio 1

(define duplicate
  (lambda (lst) 
    (cond ((null? lst) '()) ; Caso base
          (else (cons (car lst)(cons (car lst) (duplicate (cdr lst)))))))) ; Construye una lista con el primer elemento y lo hace recursivamente

; Ejercicio 2

(define positives
  (lambda (lst)
  (cond ((null? lst) '()) ; Caso base
        ((> (car lst) 0) ; Si el primer elemento es mayor que 0
        (cons (car lst) (positives(cdr lst)))) ; Construye una lista y lo hace recursivamente
       (else (positives (cdr lst)))))) ; Si no es mayor que 0 el primer elemento va a los siguientes

; Ejercicio 3

(define symbol
  (lambda (lst)
    (cond ((null? lst) #t) ; Caso base
          ((symbol? (car lst))(symbol (cdr lst))) ; Con simbol? corroboramos que haya un simbolo
          (else #f)))) ; Si no hay retorna falso
                              
           
; Ejercicio 4

(define swapper
  (lambda (a b lst)
    (cond ((null? lst) '()) ; Caso base                                 
        ((eq? (car lst) a) (cons b (swapper a b (cdr lst)))) ; Si el primer elemento es igual a a, se agrega b en una nueva lista, despues se "llama" la funcion recursivamente
        ((eq? (car lst) b) (cons a (swapper a b (cdr lst)))) ; Mismo paso anterior pero ahora con b
        (else (cons (car lst) (swapper a b (cdr lst)))))))  ; Si no coinciden, se crea una nueva lista con el priomer elemento


; Ejercicio 5

(define dot-product
  (lambda (lst1 lst2)
    (cond ((null? lst1) 0) ; Caso base
          ((null? lst2) 0) ; Caso base
          (else (+ (*(car lst1)(car lst2))(dot-product (cdr lst1) (cdr lst2))))))) ; Operacion producto punto y lo hace recursivamente "llamandose"



