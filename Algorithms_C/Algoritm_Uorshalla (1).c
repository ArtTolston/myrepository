#include<stdio.h>
#include<stdlib.h>

int main()
{
    int i, j, k;
    int n;
    int **matrix;
    printf ("number of vertices:");
    scanf ("%d", &n);
    matrix = (int**)malloc(n * sizeof(int *));

    for (i = 0; i < n; i ++)
        matrix[i] = (int *)malloc(n * sizeof(int));
    printf ("Matrix:\n");
    for (i = 0; i < n; i ++)
        for (j = 0; j < n; j ++)
            scanf ("%d", &matrix[i][j]);
    for (i = 0; i < n; i ++)
        for (j = 0; j < n; j ++) {
            if ((i != j) && (matrix[i][j] != 0))
                for (k = 0; k < n; k ++)
                    matrix[i][k] = matrix[i][k] | matrix[j][k];
        }
    for (i = 0; i < n; i ++) {
        for (j = 0; j < n; j ++)
            printf ("%d ", matrix[i][j]);
        printf ("\n");
    }
    for (i = 0; i < n; i ++)
        free (matrix[i]);
    free (matrix);
    return 0;
}
