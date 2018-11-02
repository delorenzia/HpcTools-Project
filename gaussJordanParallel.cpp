#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, j, k;
    double **a, akk, aik;
    
    n = 2048;

    a= (double**) malloc(n*sizeof(double*));
#pragma omp parallel shared(a)
{
  #pragma omp for private(i) 
    for(i=0;i<n;i++) a[i]= (double*) malloc((n+1)*sizeof(double));

  #pragma omp for private (i, j)  
    for(i=0;i<n;i++) for(j=0;j<n;j++) {a[i][j] = rand()%100+1;}

  #pragma omp for private (i)
    for(i=0;i<n;i++) {a[i][n] = rand()%100+1;}   
}
/* algorithme de Gauss-Jordan */

    for(k=0;k<n;k++)
    {
        akk=a[k][k];
        for(j=k;j<n+1;j++) a[k][j]=a[k][j]/akk;
        for(i=0;i<n;i++){aik=a[i][k]; if(i!=k) for(j=k;j<n+1;j++) a[i][j]=a[i][j]-aik*a[k][j];}
    }
    /* desallocations */
    for(i=0;i<n+1;i++) free(a[i]);
    free(a);
    return 0;
}


