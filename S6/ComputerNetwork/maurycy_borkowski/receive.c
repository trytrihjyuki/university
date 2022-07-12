// Maurycy Borkowski 317057
#include "receive.h"

void get_id_and_seq (struct icmp* icmp_header, uint16_t *id, uint16_t *seq)
{
    if (icmp_header->icmp_type == ICMP_TIME_EXCEEDED)
        icmp_header++; // We need to skip 8 bits
    *id = icmp_header->icmp_id;
    *seq = icmp_header->icmp_seq;
}

double calculate_rtt(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec)/1000.0;
}

int receive_packets(int sockfd, pid_t pid, int ttl, struct response *responses)
{
    fd_set descriptors;
    FD_ZERO (&descriptors);
    FD_SET (sockfd, &descriptors);

    struct timeval tv; tv.tv_sec = 1; tv.tv_usec = 0; // We wait one second until any packet is received
    struct timeval start; gettimeofday(&start, 0);
    struct timeval end;

    int received_packets = 0;
    while (received_packets < 3)
    {
        int ready = select(sockfd+1, &descriptors, NULL,NULL, &tv);
        if (ready < 0)
        {
            fprintf(stderr, "select() error: %s\n", strerror(errno));
            return -1;
        }
        if (ready == 0)
            return received_packets;

        struct sockaddr_in sender; 
        socklen_t sender_len = sizeof(sender);
        uint8_t buffer[IP_MAXPACKET];
        uint16_t id, seq;

        ssize_t packet_len = recvfrom (sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
        if (packet_len < 0) 
        {
            fprintf(stderr, "recvfrom() error: %s\n", strerror(errno));
            return -1;
        }

        char sender_ip_str[20];
        if (inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str)) == NULL)
        {
            fprintf(stderr, "inet_ntop() error: %s\n", strerror(errno));
            return -1;
        }

        struct ip*  ip_header = (struct ip*) buffer;
        ssize_t ip_header_len = 4 * ip_header->ip_hl;
        struct icmp* icmp_header = (struct icmp*) (buffer + ip_header_len);

        if (icmp_header->icmp_type != ICMP_TIME_EXCEEDED && icmp_header->icmp_type != ICMP_ECHOREPLY)
            continue;

        get_id_and_seq(icmp_header, &id, &seq);

        if (id == pid && seq == ttl)
        {
            struct response res;
            gettimeofday(&end, 0);
            bool duplicate_ip = false;
            for (int i=0; i<received_packets; i++)
            {
                if (!strcmp(responses[i].sender_ip, sender_ip_str))
                        duplicate_ip = true;
            }
            res.duplicated_ip = duplicate_ip;
            res.ttl = seq;
            res.time_since_start = calculate_rtt(start, end);
            memcpy(res.sender_ip, sender_ip_str, 20);
            memcpy(responses + received_packets, &res, sizeof(res));
            received_packets++;
        }
    }
    return received_packets;
}

bool check_final_ip(char* destination_ip, struct response *responses, int num_of_responses)
{
    for (int i=0; i<num_of_responses; i++)
    {
        if (!strcmp(responses[i].sender_ip, destination_ip))
            return true;
    }
    return false;
}

void print_responses(struct response *responses, int ttl, int num_of_responses)
{
    printf("\n%d. ", ttl);

    if (num_of_responses == 0) // No packets received
    {
        printf("*\n");
        return;
    }
    double rtt = 0.0;
    for (int i=0; i<num_of_responses; i++)
    {
        assert (responses[i].ttl == ttl);
        if (!responses[i].duplicated_ip)
            printf("%s ", responses[i].sender_ip);
        rtt += responses[i].time_since_start;
    }
    if (num_of_responses < 3)
        printf("???\n");
    else
        printf("%.0lfms\n", rtt/3.0);
}