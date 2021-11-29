#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int n, p;
	double x;
	float a = 1.0, b = 4.0, sum = 0.0;
	int t = 50;
	float h;
	h = (b-a)/n;
	
		
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Status status;
    
    if(p==n-1)
    { 
        printf("\n proces %d \n", p);
        printf("a = %lf \n", a);
        printf("b = %lf \n", b);
        printf("h = %lf \n", h);

        sum = sum + (pow(a,2)/2);
        printf("wynik = %lf \n", sum);
        
        sum = sum + (pow(b,2)/2);
        printf("wynik = %lf \n", sum);

        x = b;
        
        MPI_Send(&sum, 1, MPI_DOUBLE, p - 1, t, MPI_COMM_WORLD);
        MPI_Send(&x, 1, MPI_DOUBLE, p - 1, t, MPI_COMM_WORLD);
    }
    else if((p<n-1)&&(p>0))
    { 
        MPI_Recv(&sum, 1, MPI_DOUBLE, p + 1, t, MPI_COMM_WORLD, &status);
        MPI_Recv(&x, 1, MPI_DOUBLE, p + 1, t, MPI_COMM_WORLD, &status);

        x = x - h;
        
        sum = sum + (pow(x,2));
    
        printf("\n proces %d\n", p);
        printf("wynik = %lf \n", sum);

        MPI_Send(&sum, 1, MPI_DOUBLE, p - 1, t, MPI_COMM_WORLD);
        MPI_Send(&x, 1, MPI_DOUBLE, p - 1, t, MPI_COMM_WORLD);
    }  
    else if(p==0)
	{ 
        MPI_Recv(&sum, 1, MPI_DOUBLE, p + 1, t, MPI_COMM_WORLD, &status);
        MPI_Recv(&x, 1, MPI_DOUBLE, p + 1, t, MPI_COMM_WORLD, &status);

        x = x - h;
        
        sum = sum + (pow(x,2));

        printf("\n proces %d\n", p);
        printf("wynik koncowy = %lf \n", sum * h);       
    }   
    
    MPI_Finalize();
    return 0;
} 