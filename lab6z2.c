#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int n, p, t = 50;
	float pi = 0.0, sum = 0.0; 


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Status status;
   
    if((p<n)&&(p>0))
    {
        MPI_Recv(&pi, 1, MPI_INT, p-1, t, MPI_COMM_WORLD, &status);
        sum = (pow(-1.0, p))/(2*p+1);
        pi = pi + sum;
        printf("n = %d pi = %f \n", p, pi*4);
        
        if(p!=n-1)
        { 
            MPI_Send(&pi, 1, MPI_INT ,p+1 ,t, MPI_COMM_WORLD);
        }   
    }      
    else if(p==0)
    {
        sum = (pow(-1.0, p))/(2*p+1);
        pi = pi + sum;
        printf("n = %d pi = %f \n", p, pi*4);
        MPI_Send(&pi, 1, MPI_INT ,p+1 ,t, MPI_COMM_WORLD);
        MPI_Send(&pi, 1, MPI_INT ,p+1 ,t, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}