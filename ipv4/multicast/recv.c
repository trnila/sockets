#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

   if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {        
      perror("bind");
      exit(1);
   }    

   struct ip_mreq mreq;
   mreq.imr_multiaddr.s_addr = inet_addr(GROUP);
   //mreq.imr_interface.s_addr = inet_addr("172.20.6.40");
   mreq.imr_interface.s_addr = INADDR_ANY;
   if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
      perror("setsockopt mreq");
      exit(1);
   }         

   for(;;) {
      char buf[1024];
      int r = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *) &addr, &addrlen);
      if (r <= 0) {
	 perror("recvfrom");
	 exit(1);
      }

      buf[r] = 0;
      printf("%s: '%s'\n", inet_ntoa(addr.sin_addr), buf);
   }

   return 0;
}

