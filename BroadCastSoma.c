#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 100

int main()
{
    int numprocs,myid,x,inicio,fim;
    int data[MAXSIZE],i,somaparcial=0,soma;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    if(myid == 0) //mestre
    {
        for(i=0; i<MAXSIZE; i++)
            data[i] = 1;
    }

    //Comunicação Coletiva - Broadcast |  data = &data[0] - Um para todos
    MPI_Bcast(data,MAXSIZE,MPI_INT,0,MPI_COMM_WORLD);

    //Divisão dos dados
    x = MAXSIZE / numprocs;
    inicio = myid * x;
    fim = inicio + x;

    for(i=inicio; i<fim; i++)
        somaparcial = somaparcial + data[i];

    printf("Eu sou o ID = %d, minha soma = %d\n",myid,somaparcial);

    //Comunicação Coletiva - Reduce - Todos Para um
    MPI_Reduce(&somaparcial,&soma,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(myid == 0) //mestre   | Entrada e saida, nó mestre que faz
        printf("Soma total do vetor = %d\n",soma);

    MPI_Finalize();
    return 0;
}
