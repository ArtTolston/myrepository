#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct{
  int st;
  int fin;
  int i;
}event;

int greedy_alg(event* zvk, int num);

int main(){
  event *zvk;
  int num = 0;
  int i = 0, val = 0;

  printf("vvedite amount of zayvok\n");
  scanf("%d", &num);
  zvk = (event*)calloc(num, sizeof(event));

  printf("vvedite time nachala and end every zayvki\n");
  for(i = 0; i <= num - 1; i++){
    scanf("%d", &zvk[i].st);
    scanf("%d", &zvk[i].fin);
  }

  val = greedy_alg(zvk, num);
  printf("%d", val);
  return 0;
}



int greedy_alg(event* zvk, int num){
  int max_fin = 0, min_fin, min_st = 0;
  int count = 0, k = 0, val = 0;
  for(int i = 0; i <= num - 1; i++){
    zvk[i].i = 0;
    if(zvk[i].fin >= max_fin)
      max_fin = zvk[i].fin;
  }
  while(k++ <= num - 1){
    min_fin = max_fin;
    for(int i = 0; i <= num - 1; i++){
      if(zvk[i].fin <= min_fin && zvk[i].st >= min_st){
        min_fin = zvk[i].fin;
        val = i;
      }
    }
    zvk[val].i = 1;
    min_st = min_fin;
  }
  for(int i = 0; i <= num - 1; i++){
    count += zvk[i].i;
  }
  return count;
}
