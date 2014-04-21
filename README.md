SISTEMAS DISTRIBUÍDOS

Este repositório contém informações sobre Trabalhos Práticos da disciplina CI721 - Sistemas Distribuídos, na UFPR, em curso no 1o semestre de 2014.


Os programas desenvolvidos usam a biblioteca SMPL, de simulação de eventos em nodos.


---------------------

Contém os seguintes arquivos:


makefile - compila todos os programas.

tp1_1.c - trabalho prático 1, tarefa 1: testa somente o proximo no anel.

tp1_2.c - tarefa 2: cada nodo sem falha executa testes sequencialmente ate encontrar um outro nodo sem falha.

tp1_3.c - tarefa 3: cada nodo mantem um vetor local state [0..N-1] e atualiza as entradas correspondentes ao testar.

tp1_4.c - tarefa 4:cada nodo ao testar um nodo sem falha, o testador obtem info sobre todos os nodos que nao testou.

tp1_adsd.c - implementação do algoritmo adaptive-DSD, com reliable broadcast de mensagens em novos eventos.

smpl.h e smpl.c: biblioteca de simulação SMPL


Para compilar todos os programas, basta baixar todos os arquivos e executar:

caso use o git, use:

git clone https://github.com/emersonchiesse/sistdist


Para compilar:

make

-----------------------

Para executar os programas:


tp1_adsd, use a seguinte sintaxe:

./tp1_adsd {tempo_execucao} {num_nodos} {lista de nodos falhos}

onde:

{tempo_execucao}: tempo total de simulacao. 

{num_nodos}: numero total de nodos existentes no sistema simulado

{lista de nodos falhos}: indique os IDs de nodos e em que momento o nodo falha, no formato {nodo1 tempo1 nodo 2 tempo2 ... nodon tempon}


Por exemplo: ./tp1_adsd 200 8 1 10 4 10 5 10 

o sistema executará 200 unidades de tempo, com 8 nodos, e o nodo 1 falha no momento 10, o nodo 1 falha no tempo 10, e o nodo 5 falha no tempo 10.


--------------------

CONSIDERAÇÕES SOBRE O TP1_ADSD


. não foi implementado tratamento de erros na inserção dos parâmetros na execução do programa, ou seja, todos os parêmetros devem ser inseridos corretamente, caso contrário, poderão ocorrer falha na execução.


. A implementação do algoritmo adaptive-DSD possui as seguintes funções principais:


verifica_rodada_de_testes: contabiliza as rodadas de testes, e incrementa a variável 'rodadas'.


checa_latencia: verifica se o sistema terminou um diagnóstico completo.


----------------------

Logs de saída dos programa tp1_adsd.c:


