# include <stdio.h>
# include <stdlib.h>
# include "smpl.h"

/* eventos */

#define test 	1
#define fault 	2
#define repair 	3

#define estado_indefinido 	-1
#define estado_semfalha		0
#define estado_comfalha		1

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
    token, event, r, i, j;
    static char fa_name[5];

    if (argc != 2){
        puts("Uso correto: <tempo> <num-nodos>");
        exit(1);
    }

    N= atoi(argv[1]);
    smpl (0, "smpl");
    reset ();
    stream(1);

    /*inicialização*/
    nodo = (tnodo*)malloc(sizeof(tnodo)*N);
    for (i=0; i<N; i++){
        memset(fa_name,'\0', 5);
        sprintf(fa_name,"%d", i);
        nodo[i].id=facility (fa_name, 1);

        /* aqui inicializa variaveis locais y */
        for (j=0; j<N; j++)
        	nodo[i].state[j] = estado_indefinido;
    }

    /* escalonamento de eventos */
    for (i=0; i<N; i++)
        schedule (test,30.0,i);
    schedule (fault, 31.0, 0);
    schedule (repair, 61.0, 0);

    /* #3 cada nodo mantem um vetor local state [0..N-1] e atualiza as entradas correspondentes
     * ao testar.
     * -1 desconhecido, 0 sem falha, 1 com falha*/
    while (time() < 180.0){
        cause (&event, &token);
        switch (event){
        case test:
            if (status(nodo[token].id) != 0) break;
            printf("o nodo %d vai testar no tempo %5.1f\n", token, time());

            /* testa o proximo */
            i = (token+1)%N;
            do
            {
            	printf ("testando o nodo %d: ", i);
				if (status(nodo[i].id)==0)
				{
					printf ("sem falha. fim dos testes para do nodo %d.\n", token);
					nodo[token].state[i] = estado_semfalha;
					break;
				}
				else
				{
					printf ("com falha.\n");
					nodo[token].state[i] = estado_comfalha;
				}

            	i++;
            } while (i < token);

            print_state (nodo[token], N);
            schedule (test, 30.0, token);

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
            printf("O nodo %d recuperou no tempo %5.1f\n", token, time());
            release(nodo[token].id,token);
            schedule (test, 30.0, token);
            break;
        }
    }
}
		


