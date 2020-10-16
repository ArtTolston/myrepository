#include <stdio.h>
#include <stdlib.h>

int NV;                 // Количество вершин в графе
int NE;                 // Количество ребер в графе

#define MAX_NODES 100  // Максимальное количество вершин
#define MAX_EDGES 10   // Максимальное количество ребер в графе

struct edge_t {
   int n1,n2;  // направление
   int w;      // вес ребра
} edges[MAX_EDGES];  // Ребра графа

int nodes[MAX_NODES];  // Вершины графа.  Значение - "верхняя вершина"

// Функция "сравнения" двух ребер, используемая для сортировки
int cmp(const void *a,const void *b){
    edge *c=(edge*)a, *d=(edge*)b;
   return c->w - d->w;
}

int last_n;

// Функция получает цвет вершины n-й по порядку.
// если nodes[n] < 0, то вершина n имеет цвет nodes[n]
// если nodes[n] >= 0, то вершина n имеет цвет такой же,
// как и вершина с номером nodes[n]
int getColor(int n){
   int c;
   if (nodes[n]<0)
      return nodes[last_n=n];
   c = getColor(nodes[n]);
   nodes[n] = last_n;
   return c;
}

int main(){
   int i;
   // Считываем вход
   scanf ("%d %d", &NV, &NE);
   for(i = 0; i < N; i++) nodes[i] = -1-i;

   for(i = 0; i < NE; i++)
      scanf("%d %d %d", &edges[i].n1, &edges[i].n2, &edges[i].w);

   // Алгоритм Крускала

   // Сортируем все ребра в порядке возрастания весов
   qsort(edges, NE, sizeof(edge_t), cmp);

   for(i = 0; i < NE; i++){ // пока не прошли все ребра
      int c2 = getColor(edges[i].n2);
      if ( getColor (edges[i].n1) != c2 ){
         // Если ребро соединяет вершины различных цветов-мы его добавляем
         // и перекрашиваем вершины
         nodes [last_n] = edges[i].n2;
         printf ("%d %d %d\n", edges[i].n1, edges[i].n2, edges[i].w);
      }
   }
   return 0;
}
