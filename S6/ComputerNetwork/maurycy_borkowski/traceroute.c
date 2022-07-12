// Maurycy Borkowski 317057
#include "traceroute.h"


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: traceroute <ip_address>"); 
        return EXIT_FAILURE;
    }

    char* destination_ip = argv[1];

    const pid_t pid = getpid();

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) 
    {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}
    
    for (int ttl = 1; ttl <= TTL_MAX; ttl++)
    {
        if (send_packets(sockfd, destination_ip, ttl, pid) == EXIT_FAILURE)
            return EXIT_FAILURE;

        struct response responses[3];
        int num_of_responses = receive_packets(sockfd, pid, ttl, responses);
        if (num_of_responses < 0)
            return EXIT_FAILURE;

        if (num_of_responses >= 0)
            print_responses(responses, ttl, num_of_responses);
        
        if (check_final_ip(destination_ip, responses, num_of_responses))
            break;
    }

    return EXIT_SUCCESS;
}
