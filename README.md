Sistemas Distribuidos

Este repositório contém informações sobre Trabalhos Práticos da disciplina Sistemas Distribuídos da UFPR, em curso no 1o semestre de 2014.

Os programas desenvolvidos usam a biblioteca SMPL, de simulação de eventos em nodos.


Contém os seguintes arquivos:

makefile - compila todos os programas.
tp1_1.c - trabalho prático 1, tarefa 1: testa somente o proximo no anel.
tp1_2.c - tarefa 2: cada nodo sem falha executa testes sequencialmente ate encontrar um outro nodo sem falha.
tp1_3.c - tarefa 3: cada nodo mantem um vetor local state [0..N-1] e atualiza as entradas correspondentes ao testar.
tp1_4.c - tarefa 4:cada nodo ao testar um nodo sem falha, o testador obtem info sobre todos os nodos que nao testou.
tp1_adsd.c - implementação do algoritmo adaptive-DSD, com reliable broadcast de mensagens em novos eventos.



Logs de saída dos programas:
