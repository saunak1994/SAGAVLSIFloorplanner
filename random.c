

#include <stdio.h>
#include <math.h>
#include <stdlib.h>





random_int(low,high)
int low,high;                                   
{
        int rand();
        int i,j,r;                                      

        i = RAND_MAX / (high-low+1);
        i *= (high-low+1);
        while ((j = rand()) >=i) continue;
        r = (j % (high-low+1)) + low;
/*printf("rand=%d RAND_MAX=%d \n",r,RAND_MAX);*/
/*printf("rand=%d low=%d high=%d \n",r,low,high);*/
        if ((r < low) || (r > high))
                printf("Error: random integer %d out of range [%d,%d]\n",
                        r,low,high);

        return(r);
}


random_permutation(a,n)
int a[];
int n;
{
        int i;

        for (i=n; i>1; i--) 
                swap(&a[i-1],&a[random_int(0,i-1)]);
}

swap(a,b)
int *a,*b;
{
        int x;

        x = *a;
        *a = *b;
        *b = x;
}


double random_float(float low,float high)
{
	return rand()/(RAND_MAX - 1.0) ;
}
