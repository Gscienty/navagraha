#include "humha_process.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int humha_process(const u_char * executor, const u_char ** args, humha_process_t * p)
{
    int pipe_stdin[2];
    int pipe_stdout[2];
    int flag;
    int ret;

    if ((ret = pipe(pipe_stdin)) != 0) {
        return -1;
    }
    p->in_opened = 1;
    p->in = pipe_stdin[1];
    p->peer_in = pipe_stdin[0];

    if ((ret = pipe(pipe_stdout)) != 0) {
        return -1;
    }
    p->out_opened = 1;
    p->peer_out = pipe_stdout[1];
    p->out = pipe_stdout[0];

    flag = fcntl(p->out, F_GETFL, 0);
    fcntl(p->out, F_SETFL, flag | O_NONBLOCK | O_CLOEXEC);

    p->pid = fork();
    if (p->pid < 0) {
        return p->pid;
    }

    if (p->pid == 0) {
        if (0 > dup2(p->peer_in, 0) || 0 > dup2(p->peer_out, 1)) {
            exit(127);
        }

        close(p->peer_in);
        close(p->peer_out);
        close(p->in);
        close(p->out);

        execv((const char *) executor, (char * const *) args);
    }

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
        close(p->peer_in);
        close(p->in);
        p->in_opened = 0;
    }

    return 0;
}

int humha_process_out_close(humha_process_t * p)
{
    if (p->out_opened) {
        close(p->out);
        close(p->peer_out);
        p->out_opened = 0;
    }

    return 0;
}
