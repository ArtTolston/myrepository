#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct node{
  int age;
  int height;
  char *name;
  struct node* left;
  struct node* right;
}node;

node* tree(char *s, node* node, int age);
char* stralloc(char* s);
void treeprint(node* root);
node* Rrotate(node *root);
node* Lrotate(node *root);
node* Big_Rrotate(node *root);
node* Big_Lrotate(node *root);
int Rdef(node* root);
int Ldef(node* root);


int main() {
  node *root = NULL;
  char *s;
  int age = 0;

  do {
    scanf("%s %d", s, &age);
    root = tree(s, root, age);
  } while(age != 1);
  treeprint(root);
  return 0;
}


node* tree(char *s, node* root, int age)
{
  int left = 0, right =0, extrleft = 0, extrright = 0;
  if(root == NULL)
  {
    root = (node*)malloc(sizeof(node));
    root -> name = stralloc(s);
    root -> age = age;
    root -> height = 0;
    root -> left = NULL;
    root -> right = NULL;
    printf("yeah\n");
  }
  else{
    if(root -> age < age){
      root -> right = tree(s, root -> right, age);
    }
    else {
      root -> left = tree(s, root -> left, age);
    }
    do {
      left = Ldef(root);
      right = Rdef(root);
      printf(" left %d right %d", left, right);
      if(right - left >= 2) {
        extrright = Rdef(root -> right);
        extrleft = Ldef(root -> right);
        if(extrright - extrleft >= 0)
          root = Lrotate(root);
        else
          root = Big_Lrotate(root);
        extrleft = 0;
        extrright = 0;
      }
      if(left - right >= 2) {
        extrright = Rdef(root -> left);
        extrleft = Ldef(root -> left);
        if(extrleft - extrright >= 0)
          root = Rrotate(root);
        else
          root = Big_Rrotate(root);
        extrleft = 0;
        extrright = 0;
      }
    } while(left - right >= 2 || right - left >= 2);
    root -> height =(left > right ) ? (left + 1) : (right + 1);
    printf(" height root %d \n", root -> height);
  }
  return root;
}

char* stralloc(char* s)
{
  char* a = (char*)malloc(strlen(s) + 1);
  if(a != NULL)
  {
    strcpy(a, s);
  }
  return a;
}

node* Rrotate(node* root) {
  int left = 0, right = 0;
  node* a = root -> left;
  root -> left = a -> right;
  a -> right = root;
  root = a;
  left = Ldef(root -> right);
  right = Rdef(root -> right);
  root -> right -> height = left > right ? (left + 1) : (right + 1);

  return root;
}

node* Lrotate(node* root) {
  int left = 0, right = 0;
  node* a = root -> right;
  root -> right = a -> left;
  a -> left = root;
  root = a;
  left = Ldef(root -> left);
  right = Rdef(root -> left);
  root -> left -> height = left > right ? (left + 1) : (right + 1);
  return root;
}


node* Big_Rrotate(node *root) {
  root -> left = Lrotate(root -> left);
  root = Rrotate(root);
  return root;
}
node* Big_Lrotate(node *root) {
  root -> right = Rrotate(root -> right);
  root = Lrotate(root);
  return root;
}

void treeprint(node* root) {
  if(root != NULL){
    printf("%s %d\n", root -> name, root -> age);
    treeprint(root -> left);
    treeprint(root -> right);
  }
}
int Ldef(node* root) {
  int left = 1;
  if(root -> left != NULL)
    left = root -> left -> height;
  else
    left = -1;
  return left;
}

int Rdef(node* root) {
  int right = 1;
  if(root -> right != NULL)
    right = root -> right -> height;
  else
    right = -1;
  return right;
}
