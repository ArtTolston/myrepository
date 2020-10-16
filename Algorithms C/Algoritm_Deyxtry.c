#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **a; // матрица св€зей
    int *d;  // минимальное рассто€ние
    int *v;  // посещенные вершины
    int temp;
    int minindex, min;
    int i, j;
    int N;
    printf ("Number of vertex:");
    scanf ("%d", &N);
    a = (int **)malloc(N * sizeof(int*));
    d = (int*)malloc(N * sizeof(int));
    v =(int*)malloc(N * sizeof(int));
    for (i = 0; i < N; i ++)
        a[i] = (int *)malloc(N * sizeof(int));
    // »нициализаци€ матрицы св€зей
    for (i = 0; i<N; i++)
    {
        a[i][i] = 0;
        for (j = i + 1; j<N; j++) {
            printf("Distance between %d - %d: ", i + 1, j + 1);
            scanf("%d", &temp);
            a[i][j] = temp;
            a[j][i] = temp;
        }
    }
    // ¬ывод матрицы св€зей
    for (i = 0; i<N; i++)
    {
        for (j = 0; j<N; j++)
            printf("%5d ", a[i][j]);
        printf("\n");
    }
    //»нициализаци€ вершин и рассто€ний
    for (i = 0; i<N; i++)
    {
        d[i] = 1000;
        v[i] = 1;
    }
    d[0] = 0;
    // Ўаг алгоритма
    do
    {
        minindex = 1000;
        min = 1000;
        for (i = 0; i<N; i++)
        {     // ≈сли вершину ещЄ не обошли и вес меньше min
            if ((v[i] == 1) && (d[i]<min))
            { // ѕереприсваиваем значени€
                min = d[i];
                minindex = i;
            }
        }
    // ƒобавл€ем найденный минимальный вес
    // к текущему весу вершины
    // и сравниваем с текущим минимальным весом вершины
        if (minindex != 1000)
        {
            for (i = 0; i<N; i++)
            {
                if (a[minindex][i] > 0)
                {
                    temp = min + a[minindex][i];
                    if (temp < d[i])
                        d[i] = temp;
                }
            }
            v[minindex] = 0;
        }
    }
    while (minindex < 1000);
  // ¬ывод кратчайших рассто€ний до вершин
    printf("\nShortest distances to vertices: \n");
    for (i = 0; i<N; i++)
        printf("%5d ", d[i]);

  // ¬осстановление пути
    int *ver; // массив посещенных вершин
    ver = (int*)malloc(N * sizeof(int));
    int end = N - 1;  // индекс конечной вершины = N - 1
    ver[0] = end + 1; // начальный элемент - конечна€ вершина
    for (i = 1; i < N; i ++)
        ver[i] = 0;
    int k = 1; // индекс предыдущей вершины
    int weight = d[end]; // вес конечной вершины

    while (end > 0) // пока не дошли до начальной вершины
    {
        for(i=0; i<N; i++) // просматриваем все вершины
        if (a[end][i] != 0)   // если св€зь есть
        {
            int temp = weight - a[end][i]; // определ€ем вес пути из предыдущей вершины
            if (temp == d[i])   // если вес совпал с рассчитанным
            {                   // значит из этой вершины и был переход
                weight = temp;  // сохран€ем новый вес
                end = i;        // сохран€ем предыдущую вершину
                ver[k] = i + 1; // и записываем ее в массив
                k++;
            }
        }
    }
    // ¬ывод пути (начальна€ вершина оказалась в конце массива из k элементов)
    printf("\nFinding the shortest path\n");
    for (i = k-1; i>=0; i--)
        printf("%3d ", ver[i]);
    getchar();
    getchar();
  return 0;
}
