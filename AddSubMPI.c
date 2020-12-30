#include <stdio.h>
#include <mpi.h>
#define DADOS 100

int main()
{
    int rank; //id
    int total;
    int A,B,C,D;
    MPI_Status s;

    MPI_Init(NULL,NULL);

    MPI_Comm_size(MPI_COMM_WORLD,&total);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0) //mestre
    {
        printf("\nDigite o valor A: ");
        scanf("%d",&A);

        printf("\nDigite o valor B: ");
        scanf("%d",&B);

        printf("\nDigite o valor C: ");
        scanf("%d",&C);

        printf("\nDigite o valor D: ");
        scanf("%d",&D);

        MPI_Send(&A,1,MPI_INT,1,DADOS,MPI_COMM_WORLD);
        MPI_Send(&B,1,MPI_INT,1,DADOS,MPI_COMM_WORLD);

        MPI_Send(&C,1,MPI_INT,2,DADOS,MPI_COMM_WORLD);
        MPI_Send(&D,1,MPI_INT,2,DADOS,MPI_COMM_WORLD);

        MPI_Recv(&A,1,MPI_INT,1,DADOS,MPI_COMM_WORLD,&s);
        MPI_Recv(&C,1,MPI_INT,2,DADOS,MPI_COMM_WORLD,&s);

        total = A*C;

        printf("\nTotal = %d \n",total);
 }
    else if(rank == 1) //escravo
    {
        MPI_Recv(&A,1,MPI_INT,0,DADOS,MPI_COMM_WORLD,&s);
        MPI_Recv(&B,1,MPI_INT,0,DADOS,MPI_COMM_WORLD,&s);
        A = (A+B);
        MPI_Send(&A,1,MPI_INT,0,DADOS,MPI_COMM_WORLD);
    }
    else
   {
        MPI_Recv(&C,1,MPI_INT,0,DADOS,MPI_COMM_WORLD,&s);
        MPI_Recv(&D,1,MPI_INT,0,DADOS,MPI_COMM_WORLD,&s);
        C = (C-D);
        MPI_Send(&C,1,MPI_INT,0,DADOS,MPI_COMM_WORLD);
    }
    MPI_Finalize();

return 0;
}

