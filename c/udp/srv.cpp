#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int port = 1234;

int main() {
	struct sockaddr_in srvAddr, clientAddr;
	char buf[1024];

	int s = socket(PF_INET, SOCK_DGRAM, 0);
	if(s < 0) {
		perror("socket");
		return 1;
	}


	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(port);
	srvAddr.sin_addr.s_addr = INADDR_ANY;

	if(bind(s, (struct sockaddr*) &srvAddr, sizeof(srvAddr)) != 0) {
		perror("bind");
		return 1;
	}

	printf("Listening on %d\n", port);

	socklen_t socketSize = sizeof(clientAddr);
	int len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*) &clientAddr, &socketSize);

	buf[len] = 0;
	printf("%s\n", buf);

	strcpy(buf, "nazdar");
	sendto(s, buf, strlen(buf), 0, (struct sockaddr*) &clientAddr, socketSize);

	close(s);

}
