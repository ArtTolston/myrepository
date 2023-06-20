#include "secure_allocation_lib.h"

char tmpbuff[BUF_SIZE];
unsigned long tmppos = 0;
unsigned long tmpallocs = 0;

void* allocated_buf[BUF_SIZE];
void* freeing_buf[BUF_SIZE];

int allocated_buf_pos = 0;
int freeing_buf_pos = 0;

static void init()
{
    true_malloc     = dlsym(RTLD_NEXT, "malloc");
    true_free       = dlsym(RTLD_NEXT, "free");
    true_calloc     = dlsym(RTLD_NEXT, "calloc");
    true_realloc    = dlsym(RTLD_NEXT, "realloc");
    true_memalign   = dlsym(RTLD_NEXT, "memalign");

    if (!true_malloc || !true_free || !true_calloc || !true_realloc || !true_memalign)
    {
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
        exit(1);
    }
}

void *malloc(size_t size)
{
    static int initializing = 0;
    if (true_malloc == NULL)
    {
        if (!initializing)
        {
            initializing = 1;
            init();
            initializing = 0;

            fprintf(stdout, "allocated %lu bytes of temp memory in %lu chunks during initialization\n", tmppos, tmpallocs);
        }
        else
        {
            if (tmppos + size < sizeof(tmpbuff))
            {
                void *retptr = tmpbuff + tmppos;
                tmppos += size;
                ++tmpallocs;
                return retptr;
            }
            else
            {
                fprintf(stdout, "too much memory requested during initialisation - increase tmpbuff size\n");
                exit(1);
            }
        }
    }

    void *ptr = sec_malloc(size);
    return ptr;
}

void free(void *ptr)
{
   // something wrong if we call free before one of the allocators!
    //if (true_malloc == NULL)
    //    init();

    if (ptr >= (void*) tmpbuff && ptr <= (void*)(tmpbuff + tmppos))
        fprintf(stdout, "freeing temp memory\n");
    else
        sec_free(ptr);
}

void *realloc(void *ptr, size_t size)
{
    if (true_malloc == NULL)
    {
        void *nptr = malloc(size);
        if (nptr && ptr)
        {
            memmove(nptr, ptr, size);
            free(ptr);
        }
        return nptr;
    }

    void *nptr = true_realloc(ptr, size);
    return nptr;
}

void *calloc(size_t nmemb, size_t size)
{
    if (true_malloc == NULL)
    {
        void *ptr = malloc(nmemb*size);
        if (ptr)
            memset(ptr, 0, nmemb*size);
        return ptr;
    }

    void *ptr = true_calloc(nmemb, size);
    return ptr;
}

void *memalign(size_t blocksize, size_t bytes)
{
    void *ptr = true_memalign(blocksize, bytes);
    return ptr;
}


void* sec_malloc(size_t size)
{

    void *ptr = true_malloc(size);

    if(!memset(ptr, 0xDE, size)) {
        fprintf(stdout, "can't set memory to 0xDE");
    }

    if(allocated_buf_pos < BUF_SIZE) {
        allocated_buf[allocated_buf_pos] = ptr;
        allocated_buf_pos += 1;
    } else {
        fprintf(stdout, "allocated_buf size is exceeded");
    }
    return ptr;
}


void sec_free(void* ptr)
{
    fprintf(stdout, "here");
    true_free(ptr);

    if(freeing_buf_pos < BUF_SIZE) {
        freeing_buf[freeing_buf_pos] = ptr;
        freeing_buf_pos += 1;
    } else {
        fprintf(stdout, "freeing_buf size is exceeded");
    }

}


void sec_stats(void)
{
    for(int i = 0; i < allocated_buf_pos; i++) {
        if(find_in_buf(freeing_buf, freeing_buf_pos, allocated_buf[i])) {
            fprintf(stdout, "%d:память по адресу %p - освобождена\n", i, allocated_buf[i]);
        } else {
            fprintf(stdout, "%d:память по адресу %p - выделена\n", i, allocated_buf[i]);
        }
    }
}

void sec_emergency_clean(void)
{
    for(int i = 0; i < allocated_buf_pos; i++) {
        if( ! find_in_buf(freeing_buf, freeing_buf_pos, allocated_buf[i])) {
            sec_free(allocated_buf[i]);
        }
    }
}

int find_in_buf(void **buf, size_t buf_size, void *ptr)
{
    for(int i = 0; i < buf_size; i++) {
        if(buf[i] == ptr) {
            return 1;
        }
    }
    return 0;
}

