# Jesus Ramirez Delgado
# A01274723
# Evidenvia 1

import networkx as nx

def construct_nfa(expression, alphabet):
    operators = []
    operands = []
    states = 0

    for char in expression:
        if char in alphabet:
            # Crear un autómata del símbolo y colocarlo en la pila de operandos
            states += 1
            nfa = nx.DiGraph()
            nfa.add_edge(states - 1, states, label=char)
            operands.append(nfa)
        elif char == '(':
            # Agregar el paréntesis de apertura a la pila de operadores
            operators.append(char)
        elif char == ')':
            # Construir el autómata correspondiente y colocarlo en la pila de operandos
            while operators and operators[-1] != '(':
                process_operator(operators, operands)
            operators.pop()  # Remover el '('
        else:
            # Si C es un operador, manejar prioridades y construir autómatas
            while operators and get_priority(operators[-1]) >= get_priority(char):
                process_operator(operators, operands)
            operators.append(char)

    # Procesar el resto de operadores en la pila
    while operators:
        process_operator(operators, operands)

    return operands[0]

def get_priority(operator):
    priorities = {'*': 3, '.': 2, '|': 1}
    return priorities.get(operator, 0)

def process_operator(operators, operands):
    operator = operators.pop()
    if operator == '*':
        # Operador de cierre de Kleene (*)
        nfa_operand = operands.pop()
        nfa = nx.DiGraph()
        nfa.add_edge(1, 2, label='ε')
        nfa.add_edge(2, 2, label='ε')
        nfa.add_edge(1, 3, label='ε')
        nfa.add_edge(3, 2, label='ε')
        nfa.add_edge(3, 4, label='ε')
        nfa.add_edge(2, 4, label='ε')
        nfa.add_edge(4, 5, label='ε')
        nfa.add_edge(5, 6, label='ε')
        nfa.add_edge(6, 3, label='ε')
        nfa.add_edge(6, 5, label='ε')
        operands.append(nfa)
    elif operator in ['.', '|']:
        # Operadores de concatenación (.) y unión (|)
        nfa_operand2 = operands.pop()
        nfa_operand1 = operands.pop()
        nfa = nx.DiGraph()
        nfa.add_edges_from([(x[0], x[1], y) for x, y in nfa_operand1.edges.items()])
        nfa.add_edges_from([(x[0] + len(nfa_operand1), x[1] + len(nfa_operand1), y) for x, y in nfa_operand2.edges.items()])
        nfa.add_edge(0, 1, label='ε')
        nfa.add_edge(0, len(nfa_operand1) + 1, label='ε')
        nfa.add_edge(len(nfa_operand1), len(nfa.nodes), label='ε')
        nfa.add_edge(len(nfa_operand1) + len(nfa_operand2), len(nfa.nodes), label='ε')
        operands.append(nfa)

def print_nfa(nfa):
    print("NFA:")
    for state, neighbors in nfa.adjacency():
        transitions = [(neighbor, data['label']) for neighbor, data in neighbors.items()]
        print(f"{state} => {transitions}")
x%
def epsilon_closure(nfa, states):
    closure = set(states)
    stack = list(states)
    while stack:
        state = stack.pop()
        for neighbor in nfa[state]:
            label = nfa[state][neighbor].get('label')
            if label == 'ε' and neighbor not in closure:
                closure.add(neighbor)
                stack.append(neighbor)
    return closure

def move(nfa, states, symbol):
    moves = set()
    for state in states:
        for neighbor in nfa[state]:
            label = nfa[state][neighbor].get('label')
            if label == symbol:
                moves.add(neighbor)
    return moves

def convert_to_dfa(nfa, alphabet):
    dfa = nx.DiGraph()   # Inicializar el DFA como un grafo dirigido vacío
    dfa_states = []      # Lista para almacenar los estados del DFA
    start_state = epsilon_closure(nfa, [0])   # Calcular la cerradura epsilon del estado inicial del NFA
    dfa_states.append(tuple(sorted(start_state)))   # Agregar la cerradura epsilon como estado inicial del DFA
    dfa.add_node(0)   # Agregar el estado inicial del DFA al grafo

    queue = [start_state]   # Cola para procesar conjuntos de estados
    while queue:
        current_state = queue.pop(0)   # Obtener el próximo conjunto de estados de la cola
        for symbol in alphabet:
            new_state = epsilon_closure(nfa, move(nfa, current_state, symbol))   # Calcular la cerradura epsilon de los estados alcalzables por el símbolo
            if not new_state:
                continue   # Si el conjunto resultante es vacío, continuar con el siguiente símbolo

            if tuple(sorted(new_state)) not in dfa_states:
                # Si el conjunto de estados no se ha encontrado previamente, agregarlo al DFA y a la cola
                dfa_states.append(tuple(sorted(new_state)))
                queue.append(new_state)
                dfa.add_node(len(dfa_states) - 1)

            # Agregar una arista al DFA para representar la transición desde el estado actual al conjunto alcanzable por el símbolo
            dfa.add_edge(dfa_states.index(tuple(sorted(current_state))), dfa_states.index(tuple(sorted(new_state))), label=symbol)

    # Calcular los estados de aceptación del DFA
    accepting_states = [i for i, state in enumerate(dfa_states) if any(x in state for x in nfa.nodes())]

    return dfa, accepting_states   # Devolver el DFA resultante y los estados de aceptación


def print_dfa(dfa, accepting_states):
    print("\nDFA:")
    for state, neighbors in dfa.adjacency():
        transitions = [(neighbor, data['label']) for neighbor, data in neighbors.items()]
        print(f"{state} => {transitions}")

    print("Accepting states:", accepting_states)

def main():
    alphabet = input("Alphabet: ").strip()
    regex = input("RegEx: ").strip()
    nfa = construct_nfa(regex, alphabet)
    print("----RESULTS----")
    print("NFA:")
    print_nfa(nfa)

    dfa, accepting_states = convert_to_dfa(nfa, alphabet)
    print_dfa(dfa, accepting_states)

if __name__ == "__main__":
    main()