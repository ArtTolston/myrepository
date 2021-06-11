#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

int main()
{
    int n, i, k, j, status;
    printf("Vvedite razmernost matrizy\n");
    scanf("%d", &n);
    int **gr = (int**)calloc(n, sizeof(int*));
    for(i = 0; i < n; i++)
    {
        gr[i] = (int*)calloc(n, sizeof(int));
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            scanf("%d", &gr[i][j]);
    }
    int *sortir = (int*)calloc(n, sizeof(int));
    i = 0;
    while(i < n)
    {
        for(j = 0; j < n; j++)
        {
            status = 0;
            for(k = 0; k < n && status == 0; k++)
            {
                 if(gr[k][j] == 1)
                     status = 1;
            }
            if(status == 0) {
                 sortir[j] = i;
                 for(k = 0;k < n; k++)
                     gr[j][k] = 0;
                 gr[j][j] = 1;
                 i++;
            }
        }
    }
    for(i = 0; i < n; i++)
        printf("%d ", sortir[i]);
    return 0;
}
