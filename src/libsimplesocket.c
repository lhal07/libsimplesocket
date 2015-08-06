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

int start_server()
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(11000);

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");

    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
        printf("Received: %s\n",client_message);
        //Send the message back to client
        write(client_sock , client_message , strlen(client_message));
    }

    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }

    return 0;
}
