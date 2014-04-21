# include <stdio.h>
# include <stdlib.h>
# include "smpl.h"

/* eventos */

#define test 	1
#define fault 	2
#define repair 	3

#define estado_indefinido 	-1
#define estado_semfalha	0
#define estado_comfalha	1

/* descritor do nodo */
#define MAX_NODES 20
typedef struct{
    int id;  /* identificador da "facility" SMPL */
    /* aqui são definidas as estruturas locais mantidas pelos nodos */
    int state[MAX_NODES];
} tnodo;

tnodo *nodo;

print_state (tnodo n, int N)
{
	int i;
	for (i = 0; i < N; i++)
		printf ("state[%d]:%d ", i, n.state[i]);

	printf ("\n");
}


main ( int argc, char *argv[]){
    static int N,  /* numero de nodos */
    token, event, r, i, j, k;
    static char fa_name[5];
    int nodos_falhos[MAX_NODES];


    if (argc < 2){
        printf ("Uso correto: %s <tempo_total> <num-nodos> <nodo falhos\n\n", argv[0]);
        exit(1);
    }

    N= atoi(argv[1]);
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
        for (j=0; j<N; j++)
            nodo[i].state[j] = estado_indefinido;
    }

    /* escalonamento de eventos */
    /* intervalo de testes para os nodos*/
    for (i=0; i<N; i++)
        schedule (test,30.0,i);

    /* adiciona eventos de falhas e retorno */
    schedule (fault, 31.0, 0);
    schedule (repair, 61.0, 0);

    /* #4 cada nodo ao testar um nodo sem falha, o testador obtem info sobre todos os nodos
     * que nao testou*/
    while (time() < 180.0){
        cause (&event,&token);
        switch (event){
        case test:
            if (status(nodo[token].id)!=0) break;
            printf("t(%5.1f): testando o nodo %d \n", time(), token);

            /* testa ate o proximo sem falha*/
            i = token;
            j = i;
            do
            {
            	j = (j+1) % N;
            	printf ("testando o nodo %d: ", j);
				if (status(nodo[j].id)==0) /* se o nodo sem falha, sai do loop*/
				{
					printf ("sem falha.\n");
					nodo[token].state[j] = estado_semfalha;

					nodo[i].state[i] = j;

					break; // sai do loop
				}
				else
				{
					printf ("com falha.\n");
					nodo[token].state[j] = estado_comfalha;
				}

            } while (j < token); // encerra se chegou ao mesmo nodo

            /* recupera o estado de todos os outros testes feitos pelo nodo testado j*/

			for (k = j; k < i-1; k++)
				nodo[i].state[k] = nodo[j].state[k];

			print_state (nodo[i], N);

            schedule (test,30.0,token);

            break;

        case fault:
            r = request(nodo[token].id,token,0);
            if (r!=0){
                puts("Nao foi possível falhar o nodo...");
                exit(1);
            }
            printf("O nodo %d falhou no tempo %5.1f\n", token, time());
            break;

        case repair:
            printf("O nodo %d  recuperou no tempo %5.1f\n",token,  time());
            release(nodo[token].id,token);
            schedule (test, 30.0, token);
            break;
        }
    }
}
		


