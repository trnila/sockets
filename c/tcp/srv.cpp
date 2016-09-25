#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

const int port = 1234;

int main() {
	struct sockaddr_in srvAddr, clientAddr;
	char buf[1024];
	int n;

	int s = socket(PF_INET, SOCK_STREAM, 0);
	if(s < 0) {
		perror("socket");
		return 1;
	}

	int reuse = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0) {
		perror("setsockopt failed");
	}


	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(port);
	srvAddr.sin_addr.s_addr = INADDR_ANY;

	if(bind(s, (struct sockaddr*) &srvAddr, sizeof(srvAddr)) != 0) {
		perror("bind");
		return 1;
	}

	listen(s, 10);

	printf("Listening on %d\n", port);

	socklen_t socketSize = sizeof(clientAddr);
	int client = accept(s, (struct sockaddr *) &clientAddr, &socketSize);
	n = read(client, buf, sizeof(buf));
	buf[n] = 0;

	printf("received: %s\n", buf);

	for(int i = 0; i < n; i++) {
		if(isupper(buf[i])) {
			buf[i] = tolower(buf[i]);
		} else if(islower(buf[i])) {
			buf[i] = toupper(buf[i]);
		}
	}

	write(client, buf, n);
	printf("sent: %s\n", buf);

}
