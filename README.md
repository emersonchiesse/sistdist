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

adsd.log - log de execução do adsptive-DSD para um evento de falha.

adsd2.log - log de execução do adsptive-DSD para dois eventos de falha.

adsd3.log - log de execução do adsptive-DSD para tres eventos de falha.


Para compilar todos os programas, basta baixar todos os arquivos e executar o make:

caso use o git, use:

git clone https://github.com/emersonchiesse/sistdist


Para compilar, execute:

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

CONSIDERAÇÕES SOBRE O TRABALHO PRATICO #1 - PROGRAMA TP1_ADSD

Enunciado:
"implementar o algoritmo Adaptive-DSD utilizando o SMPL. 
     Entretanto, a cada vez que um evento é detectado (nodo falho se recupera ou nodo sem-falha 
     fica falho) o testador dispara o envio da informação para os demais nodos utilizando o 
     algoritmo clássico da difusão confiável: todos os nodos enviam a mensagem para todos 
     os demais, exceto para aquele nodo de quem a recebeu. 
     Ao final de cada execução vc deve mostrar a latência de diagnóstico, 
     bem como o número de mensagens de disseminação de eventos. 
     No log, mostre cuidadosamente resultados para 1 (hum) evento, seguidos de resultados 
     para 2 e 3 eventos simultâneos. No relatório descreva cuidadosamente como foi 
     simulado o envio de mensagens e todas as outras decisões chave que tiveram que ser 
     tomadas na implementação do trabalho."
     

Detalhes da implementação:

. nesta versão, o programa aceita varios parâmetros, indicando o numero total de nodos do sistema e quais nodos estão 
  falhos em determinado momento. Do mesmo modo, no futuro poderá ser implementada a indicação de recuperação de 
  determinados nodos em certo momento, simulando mais situações para validação do algoritmo.

. não foi implementado tratamento completo de erros na inserção dos parâmetros na execução do programa, ou seja, 
  todos os parâmetros devem ser inseridos corretamente, caso contrário, ocorrerá falha na execução, pois não é foco
  da tarefa e dispensa trabalho fora do contexto.


. A implementação do algoritmo adaptive-DSD possui as seguintes funções principais:


verifica_rodada_de_testes: contabiliza as rodadas de testes, e incrementa a variável 'rodadas'.


checa_latencia: verifica se o sistema terminou um diagnóstico completo.


envia_msg: implementa a difusao confiavel. Envia "mensagens" a todos os nodos, atualizando o novo 
  estado de determinado nodo para todos os demais nodos. O envio de mensagens foi 
  implementado nesta função, que internamente atualiza o vetor state do nodo destino,
  e contabiliza esta atualização como sendo uma mensagem.
 

----------------------

Os Logs de saída dos programa tp1_adsd.c, para cada caso, sao: 

. um evento: adsd1.log
https://github.com/emersonchiesse/sistdist/blob/master/adsd.log
  
  sistema de 8 nodos, com o nodo 3 falho.

  Executado com a linha de execucao ./tp1_adsd 200 8 5 10 > adsd.log
  

. dois eventos: adsd2.log
  
  sistema de 8 nodos, com os nodos falhos 3 e  5.

  Executado com a linha de execucao ./tp1_adsd 200 8 3 10 5 10 > adsd2.log


. tres eventos: adsd3.log. 

  sistema de 8 nodos, com os nodos falhos 3, 5 e 6.

  Executado com a linha de execucao ./tp1_adsd 200 8 3 10 5 10 6 10 > adsd3.log




