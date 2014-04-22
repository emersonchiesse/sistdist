/*
 * tp1_adsd: programa que simula diagnostico em um sistema distribuido, usando implementacao
 * do algoritmo Adaptive-DSD e difusão confiável, com a bilbioteca smpl.
 *
 * Autor: Emerson Luiz Chiesse da Silva
 * Disciplina: Sistemas Distribuidos
 * Instituicao: UFPR
 * data da ultima atualizacao: 21 abr 2014
 */

# include <stdio.h>
# include <stdlib.h>
# include "smpl.h"

/* definicao de eventos */

#define test 	1
#define fault 	2
#define repair 	3

#define estado_indefinido 	-1
#define estado_semfalha	0
#define estado_comfalha	1

#define false 0
#define true 1

/* descritor do nodo */
#define MAX_NODES 20
typedef struct{
    int id;  /* identificador da "facility" SMPL */
    /* aqui são definidas as estruturas locais mantidas pelos nodos */
    int state[MAX_NODES];
    int testouSemFalha;  // indica se o nodo testou pelo menos um outro nodo sem falha; para contabilizacao de
    	// rodada de testes
} tnodo;

tnodo *nodo;

/* imprine uma sindrome, contida no nodo x, da estrutura de nodos n, com no N nodos. */
print_state (int x, tnodo n, int N)
{
	int i;
	for (i = 0; i < N; i++)
		printf ("n %d [%d]:%d \n", x, i, n.state[i]);

	printf ("\n");
}

/*
 * verifica_rodada_de_testes:
 * verifica na estrutura de nodos n, com N nodos, se uma rodada de testes foi concluida.
 * retorna true se terminou rodada; false se nao terminou
 * verifica os nodos sem falha e se o nodo testou algum nodo sem falha
 *
 * checa em todos os nodos sem falha se tal nodo testou algum outro nodo sem falha
 * caso tenha encerrado uma rodada, reinicia a contagem.
 */
int verifica_rodada_de_testes (tnodo *n, int N)
{
	int i;

	for (i = 0; i < N; i++)
	{
		/* se algum nodo estah sem falha e nao testou nodo sem falha,
		 * jah retorna false */
		if ((status(n[i].id) == 0) && (n[i].testouSemFalha == 0))
			return false;
	}

	/* se todos os nodos sem falha testaram algum outro nodo sem falha,
	 * terminou a rodada, e reinicia contagem
	 */

	for (i = 0; i < N; i++)
		n[i].testouSemFalha = 0;

	return true;
}

/*
 * checa_latencia:
 * verifica na estrutura de nodos n, com N nodos, se a latencia foi atingida.
 * (a latencia eh o numero de rodadas de testes em que todo o sistema possui o diagnostico)
 *
 * 1. conta quantos nodos sem falha.
 * 2.  se nao tem nodos sem falha, nao tem diagnostico
 * 3.  se tem apenas um nodo sem falha, ja possui o diagnostico
 *
 * procura o primeiro nodo sem falha, e compara o vetor state do proximo nodo sem falha
 * se todos os nodos sem falha possuem a mesma sindrome, o sistema estah diagnosticado
 * e retorna true
*/
int checa_latencia (tnodo *n, int N)
{
	int i, j, k, count = 0;

	// conta nodos sem falha
	for (i = 0; i < N; i++)
		if (status(n[i].id) == 0)
			count ++;

	printf ("%d nodos sem falha.\n", count);

	if (count == 0)
		return false; // nenhum nodo sem falha; todos falhos

	if (count == 1)  // apenas um nodo sem falha; terminou latencia
		return true;

	// mais q um nodo sem falha, checa se todos tem sindrome igual
	i = 0;
	// procura o primeiro nodo sem falha
	while ((status(n[i].id) != 0))
		i++;

	printf ("primeiro nodo sem falha: %d \n", i);
	j = i+1;

	// compara com os demais nodos sem falha. na primeira diferenca, sai fora. e a latencia
	// nao terminou. se todos forem iguais, terminou a latencia
	while (j < N)
	{
		while ((status(n[j].id) != 0))
			j++;

		printf ("outro nodo sem falha: %d \n", j);
		for (k = 0; k < N; k++)
		{
			if (n[i].state[k] != n[j].state[k])
				return false;
		}
		j++;
	}

	return true;
}

/*
 * envia_msg:
 * na estrutura de 'nodos', com N nodos, atualiza 'estado' do nodo 'testado', para outros nodos.
 * envia msg para todos os outros nodos, exceto de quem enviou ('testador').
 * incrementa o contador 'msg' com o numero de mensagens difundidas
 */
envia_msg (tnodo *nodos, int N, int testador, int testado, int estado, int *msg)
{
	int i;
	for (i = 0; i < N; i++)
	{
		if (testador != testado)
		{
			// se nodo sem falha, atualiza
			if ((status(nodos[i].id) == 0))
			{
				printf ("atualizando estado no nodo %d\n", i);
				if (estado == estado_semfalha)
					nodos [i].state[testador] = testado;
				else
					nodos [i].state[testado] = estado_comfalha;
				*msg = *msg + 1;
			}
		}
	}
}

main ( int argc, char *argv[]){
    static int N,  /* numero de nodos */
    token, event, r, i, j, k;
    int tempo;
    static char fa_name[5];
    int rodadas = 0;     // numero de rodadas de testes
    int mensagens = 0;   // numero de mensagens de broadcast
    int encerra = false; // indicacao para encerrar o programa

    if (argc < 2){
        printf ("Uso correto: %s <tempo_total> <num-nodos> <nodo falho 1> <tempo da falha 1> <nodo falho 2> <tempo da falha 2> ...\n\n", argv[0]);
        exit(1);
    }

    N = atoi(argv[2]);
    tempo = atoi(argv[1]);

    printf ("Implementacao do algoritmo Adaptive-DSD.\n");
    printf ("executando sistema de %d nodos\n", N);
    printf ("\n");

    smpl (0, "implementacao de A-DSD");
    reset ();
    stream(1);

    /*inicialização dos nodos*/
    nodo = (tnodo*) malloc (sizeof (tnodo)*N);
    for (i=0; i<N; i++){
        memset(fa_name,'\0',5);
        sprintf(fa_name,"%d",i);
        nodo[i].id=facility (fa_name,1);

        /* inicialização de outras variaveis do nodo */
        /* estado */
        for (j=0; j<N; j++)
            nodo[i].state[j] = estado_indefinido;

        // contabilizacao de rodadas
        nodo[i].testouSemFalha = 0;
    }

    /* escalonamento de eventos */
    /* intervalo de testes para os nodos*/
    for (i=0; i<N; i++)
        schedule (test,30.0,i);

    /* adiciona eventos de falhas e retorno */
    for (i=3; i< argc; i=i+2)
    {
    	printf ("adicionando nodo falho %s no tempo %s\n", argv[i], argv[i+1]);
    	schedule (fault, atof (argv[i+1]), atoi (argv [i]));
    }
    //schedule (fault, 31.0, 0);
    //schedule (repair, 61.0, 0);

    printf ("\nInicio de execucao!\n");
    printf ("----------------------\n");

    encerra = false;
    /* #4 cada nodo ao testar um nodo sem falha, o testador obtem info sobre todos os nodos
     * que nao testou*/
    while ((time() < tempo) && (!encerra)){
        cause (&event,&token);
        switch (event){
        case test:
        	// se nodo com falha, interrompe
            if (status(nodo[token].id)!=0) break;

            printf ("----------------------------\n");
            printf("t(%5.1f): testes do nodo %d \n", time(), token);

            /* testa ate o proximo sem falha*/
            i = token;
            j = i;
            int fim = false;
            do
            {
            	j = (j+1) % N;
            	printf ("\ntestando o nodo %d:. seu estado anterior era: %d. ", j, nodo[token].state[j]);

				if (status(nodo[j].id)==0) /* se nodo j sem falha, sai do loop*/
				{
					printf ("agora sem falha. encerra testes de outros nodos.\n");

					nodo[token].testouSemFalha = 1; // para contabilizar rodada de testes

					fim = true; //sinaliza para interromper o loop
					/* obtem state [j] para state do nodo [i] */

					if (nodo[token].state[j] != 0) // mudou o estado, estava falho
					{
						// envia msg para todos os outros nodos
						printf ("mudou estado do nodo. enviando mensagens para outros nodos sem falha...\n");
						envia_msg (nodo, N, token, j, estado_semfalha, &mensagens);
						printf ("enviou %d mensagens\n", mensagens);
					}
				}
				else
				{
					printf ("agora com falha.\n");
					if (nodo[token].state[token] != j) // mudou o estado, estava sem falha
					{
						// envia msg para todos os outros nodos
						printf ("mudou estado do nodo. enviando mensagens para outros nodos sem falha...\n");
						envia_msg (nodo, N, token, j, estado_comfalha, &mensagens);
						printf ("enviou %d mensagens\n", mensagens);
					}
				}



            } while (!fim); // encerra se chegou ao mesmo nodo

            printf ("recuperando state de %d\n", j);
            nodo[i].state[i] = j;

            /* recupera o estado de todos os outros testes feitos pelo nodo testado j*/
			for (k = 0; k < N; k++)
				if (k != i)
					nodo[i].state[k] = nodo[j].state[k];

			print_state (i, nodo[i], N);

			if (verifica_rodada_de_testes (nodo, N))
			{
				rodadas ++;
				printf ("terminou rodada %d\n", rodadas);

				if (checa_latencia (nodo, N))
				{
					printf ("terminou diag, com latencia de %d rodadas e %d mensagens.\n\n", rodadas, mensagens);
					encerra = true;
				}
				else
					printf ("nao terminou diag.\n\n");
			}
			else
				printf ("nao terminou rodada de testes.\n");

            schedule (test, 30.0, token);

            break;

        case fault:
            r = request(nodo[token].id, token, 0);
            if (r!=0){
                puts("Nao foi possível falhar o nodo...");
                exit(1);
            }
            printf("O nodo %d falhou no tempo %5.1f\n", token, time());
            break;

        case repair:
            printf("O nodo %d  recuperou no tempo %5.1f\n", token,  time());
            release(nodo[token].id, token);
            schedule (test, 30.0, token);
            break;
        }
    }
}
		


