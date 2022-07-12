// Maurycy Borkowski 317057
#include "send.h"

u_int16_t compute_icmp_checksum (const void *buff, int length)
{
    u_int32_t sum;
    const u_int16_t* ptr = buff;
    assert (length % 2 == 0);
    for (sum = 0; length > 0; length -= 2)
        sum += *ptr++;
    sum = (sum >> 16) + (sum & 0xffff);
    return (u_int16_t)(~(sum + (sum >> 16)));
}

int send_packets (int sockfd, char* ip, int ttl, pid_t pid)
{
    struct icmp header;
    header.icmp_type = ICMP_ECHO;
    header.icmp_code = 0;
    header.icmp_hun.ih_idseq.icd_id = pid;
    header.icmp_hun.ih_idseq.icd_seq = ttl;
    header.icmp_cksum = 0;
    header.icmp_cksum = compute_icmp_checksum ((u_int16_t*)&header, sizeof(header));

    struct sockaddr_in recipient;
    bzero (&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;
    if (inet_pton(AF_INET, ip, &recipient.sin_addr) <= 0)
    {
        fprintf(stderr, "inet_pton() error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int)) < 0)
    {
        fprintf(stderr, "setsockopt() error: %s\n", strerror(errno)); 
        return EXIT_FAILURE;
    }

    for (int i=0; i<3; i++)
    {
        ssize_t bytes_sent = sendto (sockfd, &header, sizeof(header), 0, (struct sockaddr*)&recipient, sizeof(recipient));
        if (bytes_sent < 0)
        {
            fprintf(stderr, "sendto() error: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
