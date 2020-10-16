#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>  //считать в массив интов значения из строки сразу
#include<string.h>
#define N 20

typedef struct{
  int v1, v2;
  int ves;
  int n;
}rebra;

int compare(const void *x1, const void *x2){
  rebra *a1 = (rebra*)x1, *a2 = (rebra*)x2;
  return a1 -> ves - a2 -> ves;
}

int check_color(rebra* rebro, int num_e, int i, int v1, int v2){
  int k = 0, color = -1, color2 = -2;
  for(k = 0; k <= num_e - 1; k++){
    if((rebro[k].v1 == v1 || rebro[k].v2 == v1)&&(rebro[k].n != 0)&&(i != k) ){
       color = rebro[k].n;
    }
    else if((rebro[k].v1 == v2 || rebro[k].v2 == v2)&&(rebro[k].n != 0)&&(i != k) ){
      color2 = rebro[k].n;
    }
    if(color == color2)
      return 0;
  }
  return 1;
}

void pereschet(rebra rebro[], int n, int i, int num_e){
  for(int k = 0; k <= num_e - 1; k++){
    if(rebro[k].n == 0)
      continue;
    if((rebro[k].v2 == rebro[i].v1 || rebro[k].v1 == rebro[i].v1)&&(i != k)&&(rebro[k].n != n) ){
      rebro[k].n = n;
      pereschet(rebro, n, k, num_e);
    }
    else if((rebro[k].v2 == rebro[i].v2 || rebro[k].v1 == rebro[i].v2)&&(i != k)&&(rebro[k].n != n) ){
      rebro[k].n = n;
      pereschet(rebro, n, k, num_e);
    }
  }
}

int kraskala(rebra rebro[], int num_e){
  int i = 0, n = 1, sum = 0;
  for(i = 0; i <= num_e - 1; i++){
    if(check_color(rebro, num_e, i, rebro[i].v1, rebro[i].v2)){
      rebro[i].n = n;
      sum += rebro[i].ves;
      pereschet(rebro, n, i, num_e);
    }
    n++;
  }
  return sum;
}

//check_color проверка на разность цветов на концах ребра
// pereschet закрашиваем все соединенные ребра одним цветом(номер n)
//qsort сортирует все ребра по весу

int main() {
  int ne, i = 0, sum = 0;
  rebra rebro[N] = {};
  printf("Vvedite kolichestvo reber\n");
  scanf("%d", &ne);
  printf("Vvedite vershiny i ves\n");
  printf("first second ves\n");
  for(i = 0; i <= ne - 1; i++){
    scanf("%d %d %d", &rebro[i].v1, &rebro[i].v2, &rebro[i].ves);
  }
  qsort(rebro, ne, sizeof(rebra), compare);
  sum = kraskala(rebro, ne);
  printf("%d", sum);
}
