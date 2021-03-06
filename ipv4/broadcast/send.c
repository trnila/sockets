#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 12345

int main() {
   int sock = socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) {
      perror("socket");
      exit(1);
   }

   // we dont bind to broadcast address - we are using sendto

   int enable = 1;
   if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &enable, sizeof(enable)) != 0) {
      perror("setsockopt");
      exit(1);
   }

   struct sockaddr_in addr;
   memset(&addr, 0, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = inet_addr("192.168.99.255");
   addr.sin_port = htons(PORT);
   socklen_t addrlen = sizeof(addr);

   int i = 0;
   for(;;) {
      char buf[1024];
      snprintf(buf, sizeof(buf), "Hello %d", i++);
      int r = sendto(sock, buf, 1024/4, 0, (struct sockaddr *) &addr, addrlen);
      if (r <= 0) {
	 perror("sendto");
	 exit(1);
      }
      usleep(2000/4);
   }

   return 0;
}

