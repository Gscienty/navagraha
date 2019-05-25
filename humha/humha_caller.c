#include "humha_caller.h"
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

static int humha_remote_fd(char * hostname)
{
    struct sockaddr_in peer_sock;
    struct hostent * host = gethostbyname(hostname);
    char * peer_ip_str = NULL;
    int retfd = 0;
    if (host == NULL) {
        return 0;
    }
    peer_ip_str = inet_ntoa(*(struct in_addr *) (host->h_addr_list[0]));
    peer_sock.sin_family = AF_INET;
    peer_sock.sin_port = htons(80);
    peer_sock.sin_addr.s_addr = inet_addr(peer_ip_str);

    retfd = socket(AF_INET, SOCK_STREAM, 0);
    
    connect(retfd, (struct sockaddr *) &peer_sock, sizeof(struct sockaddr_in));

    return retfd;
}

static humha_caller_chain_t * humha_caller_chain_alloc(int size)
{
    humha_caller_chain_t * ret = (humha_caller_chain_t *) malloc(sizeof(humha_caller_chain_t) + size);
    if (ret == NULL) {
        return NULL;
    }
    ret->next = NULL;
    ret->size = size;
    ret->used_size = 0;

    return ret;
}

static humha_caller_chain_t * humha_caller_chain_set(humha_caller_chain_t * chain, char * seg)
{
    int seg_size = strlen(seg);
    int remain_size = chain->size - chain->used_size;

    if (remain_size >= seg_size) {
        memcpy(chain->buf_ptr + chain->used_size, seg, seg_size);
        chain->used_size += seg_size;
    }
    else {
        memcpy(chain->buf_ptr + chain->used_size, seg, remain_size);
        chain->next = humha_caller_chain_alloc(512 > seg_size - remain_size ? 512 : seg_size - remain_size);
        chain = chain->next;
        memcpy(chain->buf_ptr, seg + (seg_size - remain_size), seg_size - remain_size);
    }

    return chain;
}

static humha_caller_chain_t * humha_caller_chain_set_int(humha_caller_chain_t * chain, int val)
{
    char val_str[32];
    int val_str_used = 0;
    if (val == 0) {
        if (chain->size - chain->used_size < 1) {
            chain->next = humha_caller_chain_alloc(512);
            chain = chain->next;
        }
        chain->used_size = 1;
        chain->buf_ptr[0] = '0';
    }
    else {
        while (val != 0) {
            val_str[val_str_used++] = (val % 10) + '0';
            val /= 10;
        }

        while (val_str_used != 0) {
            if (chain->size - chain->used_size < 1) {
                chain->next = humha_caller_chain_alloc(512);
                chain = chain->next;
            }
            chain->buf_ptr[chain->used_size++] = val_str[--val_str_used];
        }
    }

    return chain;
}

int humha_caller(int out_fd, char * hostname)
{
    int remote_fd = humha_remote_fd(hostname);
    humha_caller_chain_t * head = humha_caller_chain_alloc(512);
    humha_caller_chain_t * payload = humha_caller_chain_alloc(512);
    int payload_size = 0;
    humha_caller_chain_t * cur = NULL;
    int yield_size = 0;

    cur = payload;
    while ((yield_size = read(out_fd, cur->buf_ptr + cur->used_size, cur->size - cur->used_size)) > 0) {
        payload_size += yield_size;

        if (yield_size + cur->used_size >= cur->size) {
            cur->next = humha_caller_chain_alloc(512);
            cur = cur->next;
        }
    }

    cur = humha_caller_chain_set(head, "POST / HTTP/1.1");
    cur = humha_caller_chain_set(cur, "\r\n");
    cur = humha_caller_chain_set(cur, "host: ");
    cur = humha_caller_chain_set(cur, hostname);
    cur = humha_caller_chain_set(cur, "\r\n");
    cur = humha_caller_chain_set(cur, "Content-Length: ");
    cur = humha_caller_chain_set_int(cur, payload_size);
    cur = humha_caller_chain_set(cur, "\r\n");
    cur = humha_caller_chain_set(cur, "Content-Type: application/octent-stream");
    cur = humha_caller_chain_set(cur, "\r\n");
    cur = humha_caller_chain_set(cur, "\r\n");
    cur->next = payload;


    // TODO call send remote
    //
    // TODO free chain

    close(remote_fd);
    return 0;
}
