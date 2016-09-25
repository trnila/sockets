#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int src_port = 1111;
const int dst_port = 1234;

int main() {
	struct sockaddr_in localAddr, remoteAddr;
	char buf[1024];

	int s = socket(PF_INET, SOCK_DGRAM, 0);
	if(s < 0) {
		perror("socket");
		return 1;
	}

	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(src_port);
	localAddr.sin_addr.s_addr = INADDR_ANY;
	
	if(bind(s, (struct sockaddr*) &localAddr, sizeof(localAddr)) != 0) {
		perror("bind");
		return 1;
	}

	remoteAddr.sin_family = AF_INET;
	remoteAddr.sin_port = htons(dst_port);
	remoteAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	strcpy(buf, "hello");
	socklen_t socketSize = sizeof(localAddr);
	sendto(s, buf, strlen(buf), 0, (struct sockaddr*) &remoteAddr, socketSize);

	int len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*) &localAddr, &socketSize);
	buf[len] = 0;
	printf("rcv: %s\n", buf);

}
