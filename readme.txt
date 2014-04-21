
/* #2 cada nodo sem falha executa testes sequencialmente ate encontrar um outro nodo sem falha*/

    /* #3 cada nodo mantem um vetor local state [0..N-1] e atualiza as entradas correspondentes
     * ao testar.
     * -1 desconhecido, 0 sem falha, 1 com falha*/

    /* #4: cada nodo ao testar um nodo sem falha, o testador obtem info sobre todos os nodos
     * que nao testou*/
     
     Você deve implementar o algoritmo Adaptive-DSD utilizando o SMPL. 
     Entretanto, a cada vez que um evento é detectado (nodo falho se recupera ou nodo sem-falha 
     fica falho) o testador dispara o envio da informação para os demais nodos utilizando o 
     algoritmo clássico da difusão confiável: todos os nodos enviam a mensagem para todos 
     os demais, exceto para aquele nodo de quem a recebeu. 
     Ao final de cada execução vc deve mostrar a latência de diagnóstico, 
     bem como o número de mensagens de disseminação de eventos. 
     No log, mostre cuidadosamente resultados para 1 (hum) evento, seguidos de resultados 
     para 2 e 3 eventos simultâneos. No relatório descreva cuidadosamente como foi 
     simulado o envio de mensagens e todas as outras decisões chave que tiveram que ser 
     tomadas na implementação do trabalho.