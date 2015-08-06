#include "simplesocket.h"


//#define DEBUG
#define PORT 11000
#define SERVERIP "10.1.1.193"
#define DEBUG

int envia_log(char* param){

  int sock_descr;
  struct sockaddr_in server_addr;
  //struct hostent *he;
  struct in_addr ipv4addr;
  char *URL = "this is another test <EOF>";

  inet_pton(AF_INET, SERVERIP, &ipv4addr);
  //he = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET);

  //bcopy((char *)he->h_addr, (char *)&server_addr.sin_addr, he->h_length);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);

  if((sock_descr=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("ERROR: Could not open socket");
    exit(1);
  }

  if(connect(sock_descr, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    perror("ERROR: Could not connect to server");
    exit(1);
  }

  if(write(sock_descr, URL, strlen(URL)) != strlen(URL)){
    perror("ERROR: Could not send URL");
    exit(1);
  }

  printf("Sending: %s\n",URL);


  // Tell application that will not send anymore.
  // So it forces the data to be sent.
  shutdown(sock_descr, SHUT_WR);

#ifdef DEBUG
  char buffer[BUFSIZ+1];

  read(sock_descr, buffer, BUFSIZ);
  printf("%s\n", buffer);

#endif

  close(sock_descr);
  exit(0);
}
