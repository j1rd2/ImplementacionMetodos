#lang racket

; Jesus Ramirez Delgado
; A01274723A
; Evidencia 2

; Función que determina si una cadena de entrada es aceptada por el autómata

(define (acepta? automata cadena)
  
  ; Extraer componentes del autómata
  (define estados (first automata))
  (define alfabeto (second automata))
  (define transiciones (third automata))
  (define estado-inicial (fourth automata))
  (define estados-finales (fifth automata))

 ; Función que determina el próximo estado
(define (proximo-estado estado simbolo transiciones)
  (cond
    [(null? transiciones) #f] ; si no quedan transiciones para revisar, devuelve falso
    [(and (equal? (first (car transiciones)) estado) 
          (equal? (second (car transiciones)) simbolo))
     (third (car transiciones))] ; si la transición actual coincide, devuelve el próximo estado
    [else
     (proximo-estado estado simbolo (cdr transiciones))])) ; si no, avanza a la siguiente transición


  ; Función auxiliar para procesar la cadena de entrada
  (define (procesa-cadena estado cadena)
    (if (null? cadena)
    (not (eq? #f (member estado estados-finales)))
        (let ([prox-estado (proximo-estado estado (car cadena) transiciones)])
          (if prox-estado
              (procesa-cadena prox-estado (cdr cadena))
              #f))))

  ; Llamar a la función auxiliar con el estado inicial y la cadena de entrada
  (procesa-cadena estado-inicial cadena))

; Función para procesar múltiples cadenas de entrada
(define (valida-cadenas automata cadenas)
  (map (lambda (cadena) (acepta? automata cadena)) cadenas))

; Ejemplo de uso
(define automata '((0 1 2 3 4) 
                   (a b) 
                   ((0 a 1) (0 b 2) (1 a 1) (1 b 3) (2 b 2) (2 a 1) (3 a 1) (3 b 4) (4 a 1) (4 b 2))
                   0 
                   (4)))

(define automata2 '((0 1 2) 
                           (0 1) 
                           ((0 0 1) (0 1 0) (1 0 1) (1 1 2) (2 0 1) (2 1 0))
                           0 
                           (2)))


(define entradas '((a b a b a a b b) 
                  (a a a a a a b) 
                  (a b a b a b b) 
                  (a b)
                  (a b a b a a b b)))

(define entradas2 '((1 0 1) 
                    (1 0 0 1) 
                     (1 1 1) 
                     (0 0 0 0)))


(display (valida-cadenas automata entradas))

(display (valida-cadenas automata2 entradas2))

