#ifndef _NAVAGRAHA_HUMHA_PROCESS_H
#define _NAVAGRAHA_HUMHA_PROCESS_H

#include <sys/types.h>
#include <unistd.h>

typedef struct {
    pid_t pid;
    int in;
    int out;
} humha_process_t;

int humha_process(const char * cmd, humha_process_t * p);

int humha_process_wait(humha_process_t * p);

int humha_process_close(humha_process_t * p);

#endif
