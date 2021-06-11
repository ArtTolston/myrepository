#include <stdio.h>
#define N 20

int min(int d[], int n, int v[]) {
  int min = 1000, index = 0;
  for(int i = 0; i <= n - 1; i++) {
    if(d[i] <= min && v[i] == 0) {
      min = d[i];
      index = i;
    }
  }
  return index;
}

int main() {
  int arr[N][N] = {};
  int d[N] = {};
  int n = 0, sum = 0, i = 0, k = 0, index = 1000;
  int v[N] = {};
  printf("Vvedite kolichestvo vershin\n");
  scanf("%d", &n);
  printf("Vvedite matrizhy smezhnosti\n");
  for(int i = 0; i <= n - 1; i++) {
    d[i] = 1000;
    v[i] = 0;
    for(int k = 0; k <= n - 1; k++) {
      scanf("%d", &arr[i][k]);
      if(arr[i][k] == 0)
        arr[i][k] = 1000;
    }
  }
  i = 0;
  for(int count = 0; count <= n - 1; count++) {
    for(k = 0; k <= n - 1; k++) {
      v[i] = 1;
      if(arr[i][k] != 1000 && arr[i][k] < d[k] && v[k] == 0) {
        d[k] = arr[i][k];
      }
    }
    i = min(d, n, v);
    sum += d[i];
  }
  printf("dlina ostovnogo dereva: %d", sum - 1000);
}
