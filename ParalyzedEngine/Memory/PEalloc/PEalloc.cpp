#include "PEalloc.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
void * PE_malloc(size_t size){
    void * pt = pe_malloc(size);
    if(UNLIKELY(!pt && size)){
        return NULL;
    }
    //printf("allocated %i bytes\n",size);
    return pt;
}