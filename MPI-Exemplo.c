#include <stdio.h>
#include <mpi.h>
#define DADOS 100

int main()
{
    int rank; //id
    int total;
    int info;
    MPI_Status s;

    MPI_Init(NULL,NULL);

    MPI_Comm_size(MPI_COMM_WORLD,&total);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0) //mestre
    {
        printf("Digite um valor: ");
        scanf("%d",&info);
        printf("Rank: %d - Enviando dado para o escravo...\n",rank);

        MPI_Send(&info,1,MPI_INT,1,DADOS,MPI_COMM_WORLD);
    }
    else //escravo
    {
        MPI_Recv(&info,1,MPI_INT,0,DADOS,MPI_COMM_WORLD,&s);
        printf("Eu sou o rank %d recebi o dado do mestre... %d \n", rank$
    }

    MPI_Finalize();

return 0;
}
