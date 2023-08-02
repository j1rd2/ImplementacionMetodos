% Jesus Ramirez Delgado
% A01274723
% Programacion 14

% Ejercicio 1

how_many_positives([], 0). % Lista vacía.

how_many_positives([H|T], N) :- % Caso base numero positivo.
    H > 0,
    how_many_positives(T, N1),
    N is N1 + 1.

how_many_positives([H|T], N) :- % Caso base numero negativo.
    H =< 0,
    how_many_positives(T, N).

how_many_positives(Lst, N) :- % Recursion llama a la funcion.
    how_many_positives(Lst, 0, N).

% Ejercicio 2

count(_, [], 0). % Caso base: lista vacía.

count(B, [B|T], N) :- % Caso base: primer elemento igual a B.
    count(B, T, N1),
    N is N1 + 1.

count(B, [H|T], N) :- % Caso base: primer elemento diferente a B.
    H \= B,
    count(B, T, N).

count(B, Lst, N) :- % Recursividad.
    count(B, Lst, 0, N).

% Ejercicio 3

duplicateo([], []). % Caso base: lista vacía.

duplicateo([H|T], [H, H|T2]) :- % Caso recursivo.
    duplicateo(T, T2).

% Ejercicio 4

% Caso base: lista vacía.
positives([], []).

positives([H|T], [H|T2]) :-  % Si el primer elemento H de la lista es positivo
    H > 0,                  % Si H es mayor que 0
    positives(T, T2). 

positives([H|T], T2) :- % Si el primer elemento H de la lista no es positivo
    H =< 0,          % Si H es menor que 0
    positives(T, T2).

% Ejercicio 5

dotProduct([], [], 0). % Caso base: ambas listas vacías.

dotProduct([H1|T1], [H2|T2], Result) :- % Recursividad, listas no vacías.
    dotProduct(T1, T2, Res1),
    Result is H1 * H2 + Res1.
