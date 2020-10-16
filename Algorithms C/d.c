#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
  char *a, *s;
  scanf("%s", a);
  s = (char*)malloc(strlen(a) + 1);
  strcpy(s, a);
  printf("%s", s);
}
