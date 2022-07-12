#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/ip_icmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

struct response {
    char sender_ip[20];
    uint16_t ttl;
    double time_since_start;
    bool duplicated_ip;
};

int receive_packets(int sockfd, pid_t pid, int ttl, struct response *responses);

void print_responses(struct response *responses, int ttl, int num_of_responses);

bool check_final_ip(char* destination_ip, struct response *responses, int num_of_responses);