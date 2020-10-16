#include<stdio.h>
#include<malloc.h>

int main() {
  int **m;
  int *v, *d;
  int n = 0, count = 0, index = 1, check = 1;

  printf("vvedite razmernost matrizhy: ");
  scanf("%d", &n);
  m = (int**)malloc(n * sizeof(int*));
  v = (int*)malloc(n * sizeof(int));
  d = (int*)malloc(n * sizeof(int));

  for(int i = 1; i <= n; i++) {
    if(i == 1)
      printf("  %d", i);
    else
      printf(" %d", i);
  }
  printf("\n");
  for(int i = 1; i <= n; i++) {
    m[i] = (int*)malloc(n * sizeof(int));
    printf("%d ", i);
    d[i] = 0;
    v[i] = 0;
    for(int k = 1; k <= n; k++) {
      scanf("%d", &m[i][k]);
    }
  }
  for(int counter = 1; counter <= n; counter++) {
    check = index;
    for(int k = 1; k <= n; k++) {
      for(int i = 1; i <= n; i++) {
        if(m[i][k] == 0 || v[i] == 1)
          count++;
        }
      if(count >= n) {
        v[k] = 1;
        d[index] = k;
        index++;
        continue;
      }
      count = 0;
    }
    if(index == check) {
      printf("Cycle in the graph");
      exit(1);
    }
  }
  printf("\n-------------------------------\n");
  for(int i = 1; i <= n; i++) {
    if(i == 1)
      printf("  %d", d[i]);
    else
      printf(" %d", d[i]);
  }
  printf("\n");
  for(int i = 1; i <= n; i++) {
    printf("%d ", d[i]);
    for(int k = 1; k <= n; k++) {
      printf("%d ", m[i][k]);
    }
    printf("\n");
  }

}
