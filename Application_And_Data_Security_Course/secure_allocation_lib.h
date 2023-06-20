#define _GNU_SOURCE
#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024


static void * (*true_calloc)(size_t nmemb, size_t size);
static void * (*true_malloc)(size_t size);
static void   (*true_free)(void *ptr);
static void * (*true_realloc)(void *ptr, size_t size);
static void * (*true_memalign)(size_t blocksize, size_t bytes);


void* sec_malloc(size_t size);
void sec_free(void* ptr);
void sec_stats(void);
void sec_emergency_clean(void);
int find_in_buf(void **buf, size_t buf_size, void *ptr);


static void init();
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nmemb, size_t size);
void *memalign(size_t blocksize, size_t bytes);

void *memset(void*,int,size_t);
void *memmove(void *to, const void *from, size_t size);