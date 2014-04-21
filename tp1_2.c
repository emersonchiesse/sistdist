# include <stdio.h>
# include <stdlib.h>
# include "smpl.h"

/* neste programa cada nodo conta seu tempo */

/*................eventos..............*/

#define test 1
#define fault 2
#define repair 3

/* descritor do nodo */

typedef struct{
    int id;  /* identificador da "facility" SMPL */
    /* aqui são definidas as estruturas locais mantidas pelos nodos */
    int state[];
} Tnodo;

Tnodo *nodo;

main ( int argc, char *argv[]){
    static int N,  /* numero de nodos */
    token, event, r, i;
    static char fa_name[5];

    if (argc != 2){
        puts("Uso correto: <tempo> <num-nodos>");
        exit(1);
    }

    N= atoi(argv[1]);
    smpl (0, "Um Exemplo de Simulação");
    reset ();
    stream(1);

    /*inicialização*/
    nodo = (Tnodo*)malloc(sizeof(Tnodo)*N);
    for (i=0; i<N; i++){
        memset(fa_name,'\0',5);
        sprintf(fa_name,"%d",i);
        nodo[i].id=facility (fa_name,1);
        /* aqui inicializa variaveis locais y */
    }

    /* escalonamentode eventos */
    for (i=0; i<N; i++)
        schedule (test,30.0,i);
    schedule (fault, 31.0, 0);
    schedule (repair, 61.0, 0);

    /* #2 cada nodo sem falha executa testes sequencialmente ate encontrar um outro nodo sem falha*/
    while (time() < 180.0){
        cause (&event,&token);
        switch (event){
        case test:
            if (status(nodo[token].id)!=0) break;
            printf("o nodo %d vai testar no tempo %5.1f\n", token, time());

            /* testa o proximo até o anterior*/
            i = (token+1)%N;
            do
            {
            	printf ("testando o nodo %d: ", i);
				if (status(nodo[i].id)==0)
				{
					printf ("sem falha.\n");
					break;
				}
				else
				{
					printf ("com falha.\n");
				}

            	i++;
            } while (i < token);


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
		


