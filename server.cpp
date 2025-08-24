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

#define MYPORT "8080" // the port users will be connecting to
#define BACKLOG 10    // how many pending connections queue holds

int main() {
  struct sockaddr_storage their_addr;
  socklen_t addr_size;
  struct addrinfo hints, *res;
  int sockfd, new_fd;

  // first, load up address structs with getaddrinfo();

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC; // use IPv4 or IPv6, whichever
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // fill in my IP for me

  getaddrinfo(NULL, MYPORT, &hints, &res);
  // TODO: Error Checking

  // make a socket

  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  // bind it to the port we passed in to getaddrinfo();

  bind(sockfd, res->ai_addr, res->ai_addrlen);
  // TODO: Error Checking

  // begin listening for requests
  listen(sockfd, BACKLOG);
  // TODO: Error Checking

  // accept an incoming connection:

  addr_size = sizeof their_addr;
  new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

  // ready to communicate on socket descriptor new_fd

  char *msg = "Server is working";
  int len, bytes_sent;
  len = strlen(msg);
  bytes_sent = send(sockfd, msg, len, 0);
  // TODO: Check that message was fully sent

  // close socket
  close(sockfd);
}
