#include<stdio.h>
#include<stdlib.h>
#define N 20

//поиск минимальных расстояний от вершины 0 до других вершин
// min поиск минимального элемента в массиве с возврахением его индекса
// алгоритм дейкстры. Заключается в последновательной проверке и уменьшении длин от нужной вершины до всех остальных
int min(int* way , int* v , int n, int nv) {
  int count = 0, min = 1000, index = 0;
  while(count <= nv - 1) {
    if((way[count] != 1000) && (way[count] <= min) && (way[count] != 0 )&& (v[count] == 1)) {
      min = way[count];
      index = count;
    }
    count++;
  }
  return index;
}


int main() {
  int i = 0, k = 0, n = 0, count = 0, ves = 0, nv = 0;
  int arr[N][N] = {};
  int way[N] = {};
  int v[N] = {};


  printf("vvedite kolichestvo reber\n");
  scanf("%d", &n);
  printf("vvedite kolichestvo vershin\n");
  scanf("%d", &nv);
  printf("vvedite nomer 2x vershin i ves rebra\n");
  printf("first second ves\n");
  while(count <= n - 1) {
    scanf("%d %d %d", &i , &k , &ves);
    arr[i][k] = ves;
    arr[k][i] = ves;
    count++;
  }
  for(count = 1; count <= nv - 1; count++) {
    way[count] = 1000;
    v[count] = 1;
    if(arr[0][count] != 0)
      way[count] = arr[0][count];
  }

  for(count = 0; count <= nv - 1; count++) {
    i = min(way, v, n, nv);
    v[i] = 0;
    for(k = 0; k <= nv - 1; k++) {
      if((arr[i][k] + way[i] < way[k] )&& arr[i][k] != 1000 && arr[i][k] != 0) {
        way[k] = arr[i][k] + way[i];
      }
    }
  }
  for(count = 0; count <= nv - 1; count++)
    printf("%d ", way[count]);
}
