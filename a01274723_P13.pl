% Jesus Ramirez Delgado
% A01274723
% Programacion 13

% Casos base para calcular la potencia de un número.
pow(_, 0, 1). % Cualquier número elevado a la potencia 0 es igual a 1.
% Regla recursiva para calcular la potencia de un número.
pow(A, B, Res) :-
    B > 0, % B debe ser positivo.
    B1 is B - 1,
    pow(A, B1, Res1),
    Res is A * Res1.

% Casos base para la secuencia de Fibonacci.
fibonacci(0, 0).
fibonacci(1, 1). 
% Regla recursiva para calcular el N-ésimo elemento de la secuencia de Fibonacci.
fibonacci(N, X) :-
    N > 1, % N debe ser mayor que 1 para calcular elementos de la secuencia.
    N1 is N - 1, 
    fibonacci(N1, X1),
    N2 is N - 2,
    fibonacci(N2, X2),
    X is X1 + X2.