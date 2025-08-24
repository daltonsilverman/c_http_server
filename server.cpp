#include <arpa/inet.h>
#include <cstddef>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  struct addrinfo hints, *res;
  int sockfd;

  // first, load up address structs with getaddrinfo();

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC; // use IPv4 or IPv6, whichever
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // fill in my IP for me

  getaddrinfo(NULL, "8080", &hints, &res);
  // TODO: Error Checking

  // make a socket

  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  // bind it to the port we passed in to getaddrinfo();

  bind(sockfd, res->ai_addr, res->ai_addrlen);
  // TODO: Error Checking

  // begin listening for requests
  listen(sockfd, 10);
  // TODO: Error Checking
}
