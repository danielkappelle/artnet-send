#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <stdint.h> 

// Driver code 
int send_udp_packet(char* buf, unsigned int size, char* addr, uint16_t port) { 
	int sockfd; 
	struct sockaddr_in address; 

  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = inet_addr(addr);

	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	}

  printf("size: %d", sizeof(buf));

  if (sendto(sockfd, buf,
    size, 0,
    (struct sockaddr *) &address, sizeof(address)) < 0) {
      perror("sendto()");
    }
	
  close(sockfd);
	
	return 0; 
} 
