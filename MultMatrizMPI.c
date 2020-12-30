#include <stdio.h>
#include <mpi.h>
#define DADOS 100

int main()
{
   int i,j,k,L,K,n1,n2;
   int n=2;

   int rank; //id
   int total;
   MPI_Status s;
   MPI_Init(NULL,NULL);

   MPI_Comm_size(MPI_COMM_WORLD,&total);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);

   if(rank == 0) //mestre
   {
      double A[n][n],B[n][n],C[n][n],x[n],x1[n];

      for(i=0; i<n; i++){       //Inicializando Valores Vetores
         for(j=0; j<n; j++){
            A[i][j]=1;
            B[i][j]=2;
         }
      }
      //-----------------------------------
      for(i=0; i<n; i++){
         for(j=0; j<n; j++)
            printf("%.1lf ",A[i][j]);
         printf("\n");
      }
      printf("\n");
      //-----------------------------------
      
      for(n1=0; n1<n; n1++){               //for para cada escravo
         for(i=0;i<n;i++)                  //for para enviar linha de A
            MPI_Send(&A[n1][i],n,MPI_DOUBLE,n1+1,DADOS,MPI_COMM_WORLD);
         MPI_Send(&B[0][0],n*n,MPI_DOUBLE,n1+1,DADOS,MPI_COMM_WORLD);
      }
      
      for(i=0;i<n;i++)  
         MPI_Recv(&C[i][0],n,MPI_DOUBLE,i+1,DADOS,MPI_COMM_WORLD,&s);

      //-----------------------------------
      for(i=0; i<n; i++){
         for(j=0; j<n; j++)
            printf("%.1lf ",C[i][j]);
         printf("\n");
      }
      //-----------------------------------
      
   }
   else{  
      double A[n];
      double B[n][n];
      double c1[n];
      for(k=0;k<n;k++)
         MPI_Recv(&A[k],n,MPI_DOUBLE,0,DADOS,MPI_COMM_WORLD,&s);

      MPI_Recv(&B[0][0],n*n,MPI_DOUBLE,0,DADOS,MPI_COMM_WORLD,&s);

      for(j=0; j<n; j++){
            c1[j]=0;
            for(k=0;k<n;k++)
               c1[j] = c1[j] + A[k]*B[k][j];
      }
         MPI_Send(&c1[0],n,MPI_DOUBLE,0,DADOS,MPI_COMM_WORLD);
   }
   MPI_Finalize();

return 0;
}

