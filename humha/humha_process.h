#ifndef _NAVAGRAHA_HUMHA_PROCESS_H
#define _NAVAGRAHA_HUMHA_PROCESS_H

#include <sys/types.h>
#include <unistd.h>

typedef struct {
    pid_t pid;
    int in_opened;
    int in;
    int peer_in;
    int out_opened;
    int out;
    int peer_out;
} humha_process_t;

int humha_process(const u_char * executor, const u_char ** args, humha_process_t * p);

int humha_process_wait(humha_process_t * p);

int humha_process_in_close(humha_process_t * p);

int humha_process_out_close(humha_process_t * p);

int humha_process_close(humha_process_t * p);

int humha_process_kill(humha_process_t * p);

#endif
