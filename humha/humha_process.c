#include "humha_process.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int humha_process(const u_char * executor, const u_char ** args, humha_process_t * p)
{
    pid_t pid;
    int pipe_stdin[2];
    int pipe_stdout[2];
    int flag;

    if (pipe(pipe_stdin) != 0) {
        return -1;
    }
    if (pipe(pipe_stdout) != 0) {
        return -1;
    }

    pid = fork();
    if (pid < 0) {
        return pid;
    }

    if (pid == 0) {
        close(pipe_stdin[1]);
        dup2(pipe_stdin[0], 0);
        close(pipe_stdout[0]);
        dup2(pipe_stdout[1], 1);
        execv((const char *) executor, (char * const *) args);
        exit(127);
    }

    p->pid = pid;
    p->in_opened = 1;
    p->in = pipe_stdin[1];
    p->out_opened = 1;
    p->out = pipe_stdout[0];

    flag = fcntl(p->out, F_GETFL, 0);
    fcntl(p->out, F_SETFL, flag | O_NONBLOCK);

    return 0;
}

int humha_process_wait(humha_process_t * p)
{
    int status = 0;
    pid_t pid;

    do {
        pid = waitpid(p->pid, &status, 0);
    } while(pid == -1);

    return status;
}

int humha_process_close(humha_process_t * p)
{
    humha_process_in_close(p);
    humha_process_out_close(p);

    return 0;
}

int humha_process_kill(humha_process_t * p)
{
    kill(p->pid, SIGHUP);

    return 0;
}

int humha_process_in_close(humha_process_t * p)
{
    if (p->in_opened) {
        close(p->in);
        p->in_opened = 0;
    }

    return 0;
}

int humha_process_out_close(humha_process_t * p)
{
    if (p->out_opened) {
        close(p->out);
        p->out_opened = 0;
    }

    return 0;
}
