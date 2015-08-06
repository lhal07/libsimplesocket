#include "simplesocket.h"

#define PORT 11000
#define SERVERIP "10.1.1.193"

int main(){

  return(send_message(SERVERIP,PORT,"teste <EOF>"));

}