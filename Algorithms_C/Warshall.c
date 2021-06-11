#include<stdio.h>
#include<malloc.h>

int main() {
  int **matrix;
  int n = 0;
  printf("Vvedite razmernost matrizhy\n");
  scanf("%d", &n);
  matrix = (int**)malloc(n * sizeof(int*));
  for(int i = 0; i < n; i++) {
    matrix[i] = (int*)malloc(n * sizeof(int));
    for(int k = 0; k < n; k++) {
      scanf("%d", &matrix[i][k]);
    }
  }

  for(int i = 0; i < n; i++) {
    for(int k = 0; k < n; k++) {
      if(i != k && matrix[i][k] != 0) {
        for(int count = 0; count < n; count++) {
          matrix[i][count] = matrix[i][count] | matrix[k][count];
        }
      }
    }
  }

printf("\n\n");

  for(int i = 0; i < n; i++) {
    for(int k = 0; k < n; k++) {
      printf("%d ", matrix[i][k]);
    }
  printf("\n");
  }
  for(int i = 0; i < n; i++) {
    free(matrix[i]);
  }
  free(matrix);
}
