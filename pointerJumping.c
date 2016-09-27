#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <time.h>


void main()
{
    int i,query,V,noOfThreads;
    double start_t,end_t;
    int *parent,*child;
    struct timeval tv;

    printf("Enter number of vertices in the forest\n");
    scanf("%d",&V);
    noOfThreads=2;
    omp_set_num_threads(noOfThreads);

    parent = (int *)malloc(V*sizeof(int));
    child = (int *)malloc(V*sizeof(int));
    for(i=0;i<V;i++)
    {
        printf("parent of %d-th vertex\n",i);
        scanf("%d",&parent[i]);
    }

    printf("\nVertex whose root you want to know and enter -1 if you want to exit search \n");
    scanf("%d",&query);	
        
    while(query!=-1){

        gettimeofday(&tv, 0);
        start_t = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;

        while(100)
        {
	    
	    #pragma omp parallel for
            for(i=0;i<V;i++)
            {
            child[i]=parent[parent[i]];
            }

            if(parent[query]==child[query])
                break;
          
	    #pragma omp parallel for
            for(i=0;i<V;i++)
            {
                parent[i]=child[i];
            }

        }
        gettimeofday(&tv, 0);
        end_t = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
        printf("root of %d vertex is %d  ",query,parent[query]);
        printf("and time taken is: %f ",end_t - start_t);
	
	printf("\nVertex whose root you want to know \n");
    	scanf("%d",&query);
    }
}
