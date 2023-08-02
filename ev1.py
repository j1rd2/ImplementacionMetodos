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

def main():
    alphabet = input("Alphabet: ").strip()
    regex = input("RegEx: ").strip()
    nfa = construct_nfa(regex, alphabet)
    print("----RESULTS----")
    print("INPUT:")
    print(regex)
    print_nfa(nfa)

if __name__ == "__main__":
    main()
