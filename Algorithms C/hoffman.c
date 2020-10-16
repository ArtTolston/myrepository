#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct node {
  int freq;
  char code[16];
  char ltr;
  struct node* left;
  struct node* right;
} node;

int search(node* mass, char c, int i);
void sort(node* mass, int i);
node* tree_building(node *ptr[], int i);
void vstavka(node* tmp, node* ptr[], int n);
void treeprint(node* root);
void makeCode(node* root);
int find(node* mass, char c, int i);
void deCode(node* root);

int main() {
  node *ptr[100] = {}, *root = NULL;
  FILE *f1, *f2;
  char c, bite = 0;
  char str[9] = {};
  node mass[100] = {};
  int i = 0, count = 0, last_bit = 0, num = 0;
  float pressure = 0, pres1 = 0, pres2 = 0;


  f1 = fopen("data.txt", "r");

  while((c = getc(f1)) != EOF) {
    i = search(mass, c, i);
    pres1++;
  }
  // i на одну больше чем номер в массиве
  sort(mass, i);

  for(int k = 0; k <= i; k++)
    ptr[k] = &mass[k];

    while(count < i) {
    printf("%s %c ", mass[count].code, mass[count].ltr);
    count++;
  }
  count = 0;

  printf("\n------------------------------------------\n");

  root = tree_building(ptr, i);
  printf("\n------------------------------------------\n");

  makeCode(root);  // налево 1 направо 0

  treeprint(root);

  f2 = fopen("compressor.txt", "w");
  fclose(f1);

  f1 = fopen("data.txt", "r");

  while((c = getc(f1)) != EOF) {
    count = find(mass, c, i);
    fputs(mass[count].code, f2);
  }
  fclose(f2);
  fclose(f1);
  f2 = fopen("compressor.txt", "r");
  f1 = fopen("arhive.bin", "wb");

  while(fgets(str, 9, f2) != NULL) {
    for(int i = 0; i <= 7; i++) {
      if(str[i] != '\0') {
        if(str[i] == '1')
          bite = bite | (1 << i);
      }
      else {
        last_bit = i;
        break;
      }
    }
    putc(bite ,f1);
    pres2++;
    num++;
    bite = 0;
  }

  fclose(f1);
  fclose(f2);

  f1 = fopen("arhive.bin", "rb");
  f2 = fopen("compressor2.txt", "w");
  while((c = getc(f1)) != EOF) {
    bite = 0;
    if(num == 1) {
      for(int k = 0; k < last_bit; k++) {
        bite = c & (1 << k);
        if(bite)
          putc('1', f2);
        else
          putc('0', f2);
      }
      bite = 0;
    }
    else {
      for(int i = 0; i <= 7; i++) {
          bite = c & (1 << i);
          if(bite)
            putc('1', f2);
          else
            putc('0', f2);
      }
    }
    num--;
  }
  fclose(f1);
  fclose(f2);

  deCode(root);

  pressure = (1 - pres2 / pres1) * 100;


  printf("extent of compression: %%%4.1f", pressure);
   return 0;
}




void makeCode(node* root) {
  if(root -> left) {
    strcpy(root -> left -> code, root -> code);
    strcat(root -> left -> code, "1");
    makeCode(root -> left);
  }
  if(root -> right) {
    strcpy(root -> right -> code, root -> code);
    strcat(root -> right -> code, "0");
    makeCode(root -> right);
  }
}

void deCode(node* root) {
  FILE *fp = fopen("compressor2.txt", "r");
  FILE *f3 = fopen("data2.txt", "w");
  node* start = root;
  char c;
  while((c = getc(fp)) != EOF) {
    if(c == '1') {
      root = root -> left;
      if((root -> left == NULL) && (root -> right == NULL)) {
        putc(root -> ltr, f3);
        root = start;
      }
    }
    else {
      root = root -> right;
      if((root -> left == NULL) && (root -> right == NULL)) {
        putc(root -> ltr, f3);
        root = start;
      }
    }
  }
  fclose(fp);
  fclose(f3);
}


node* tree_building(node *ptr[], int n) {
  node *tmp = (node*)malloc(sizeof(node));
  tmp -> freq = ptr[n - 1] -> freq + ptr[n - 2] -> freq;
  tmp -> left = ptr[n - 2];
  tmp -> right = ptr[n - 1];
  tmp -> ltr = '%';
  tmp -> code[0] = 0;
  if(n == 2)
    return tmp;
  else {
    vstavka(tmp, ptr, n);
    for(int i = 0; i <= n - 1; i++) {
      printf("%d%c ", ptr[i] -> freq, ptr[i] -> ltr);
    }
    tree_building(ptr, n - 1);
  }

}

int find(node* mass, char c, int n) {
  for(int i = 0; i < n; i++) {
    if(mass[i].ltr == c)
      return i;
  }
}

void vstavka(node* tmp, node* ptr[], int n) {
  int i = 0;
  printf("     %d%c\n", tmp ->freq, tmp ->ltr );
  while(ptr[i] -> freq > tmp -> freq)
    i++;
  while(n >= i) {
    if(n  == i)
      ptr[i] = tmp;
    else
      ptr[n] = ptr[n - 1];
    n--;
  }
}


void treeprint(node* root) {
  if(root != NULL){
    if(root -> left == NULL && root ->right == NULL)
      printf("%c %s\n", root -> ltr, root -> code);
    treeprint(root -> left);
    treeprint(root -> right);
  }
}

int search(node* mass, char c, int n) {
  int i = 0;
  while(i <= n) {
    if(mass[i].ltr == c) {
      mass[i].freq++;
      return n;
    }
    i++;
  }
  if(i > n) {
    mass[n].ltr = c;
    mass[n].freq = 1;
    return n + 1;
  }
}

void sort(node* mass, int n) {
  node t;
  for(int k = 0; k <= n - 1; k++) {
    for(int i = k; i <= n - 1; i++) {
      if(mass[k].freq <= mass[i].freq){
        t = mass[i];
        mass[i] = mass[k];
        mass[k] = t;
      }
    }
  }
}