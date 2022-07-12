#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int send_packets (int sockfd, char* ip, int ttl, pid_t pid);