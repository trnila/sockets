#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GROUP "239.0.0.1"
#define PORT 12345

int main() {
   int sock = socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) {
      perror("socket");
      exit(1);
   }

   struct sockaddr_in addr;
   memset(&addr, 0, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = inet_addr(GROUP);
   addr.sin_port = htons(PORT);
   socklen_t addrlen = sizeof(addr);

   int i = 0;
   for(;;) {
      char buf[32];
      snprintf(buf, sizeof(buf), "Hello %d", i++);
      int r = sendto(sock, buf, strlen(buf), 0, (struct sockaddr *) &addr, addrlen);
      if (r <= 0) {
	 perror("sendto");
	 exit(1);
      }
      sleep(1);
   }

   return 0;
}

