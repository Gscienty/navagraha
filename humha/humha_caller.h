#ifndef _HUMHA_CALLER_H
#define _HUMHA_CALLER_H


typedef struct humha_caller_chain_s humha_caller_chain_t;
struct humha_caller_chain_s {
    humha_caller_chain_t * next;
    int size;
    int used_size;

    char buf_ptr[0];
};

int humha_caller(int out_fd, char * hostname);

#endif
