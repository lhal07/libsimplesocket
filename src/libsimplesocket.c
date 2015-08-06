#include "simplesocket.h"


#define DEBUG

int send_message(char* server_ip, int port, char* message)
{

  int sock_descr;
  struct sockaddr_in server_addr;
  //struct hostent *he;
  struct in_addr ipv4addr;

  inet_pton(AF_INET, server_ip, &ipv4addr);
  //he = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET);

  //bcopy((char *)he->h_addr, (char *)&server_addr.sin_addr, he->h_length);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);

  if((sock_descr=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("ERROR: Could not open socket");
    return(1);
  }

  if(connect(sock_descr, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    perror("ERROR: Could not connect to server");
    return(1);
  }

  if(write(sock_descr, message, strlen(message)) != strlen(message)){
    perror("ERROR: Could not send message");
    return(1);
  }

  printf("Sending: %s\n",message);


  // Tell application that will not send anymore.
  // So it forces the data to be sent.
  shutdown(sock_descr, SHUT_WR);

#ifdef DEBUG
  char buffer[BUFSIZ+1];

  read(sock_descr, buffer, BUFSIZ);
  printf("Received: %s\n", buffer);

#endif

  close(sock_descr);
  return(0);
}
