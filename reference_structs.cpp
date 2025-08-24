#include <cmath>
#include <cstddef>
#include <cstdio>
#include <sys/_types/_u_int16_t.h>
#include <sys/_types/_u_int32_t.h>
struct addrinfo {
  int ai_flags;             // AI_PASSIVE, AI_CANONNAME, etc.
  int ai_family;            // AF_INET, AF_INET6, AF_UNSPEC
  int ai_socktype;          // SOCK_STREAM, SOCK_DGRAM
  int ai_protocol;          // use 0 for "any"
  std::size_t ai_addrlen;   // size of ai_addr in bytes
  struct sockaddr *ai_addr; // struct sockaddr_in or _in6
  char *ai_canonname;       // full canonical hostname
  struct addrinfo *ai_next; // linked list, next node
};

struct sockaddr {
  unsigned short sa_family; // address family, AF_xxx
  char sa_data[14];         // 14 bytes of protocol address
};

// sa_family is AF_INET or AF_INET6. sa_data contains
// a destination address and port number for the socket
//
// sockaddr_in can be cast to a pointer to a struct sockaddr
// and vice versa

struct sockaddr_in {
  short int sin_family;        // Address family, AF_INET
  unsigned short int sin_port; // Port number
  struct in_addr sin_addr;     // internet address
  unsigned char sin_zero[8];   // Same size as struct sockaddr
};

// (IPv4 only -- see struct in6_addr for IPv6)

// Internet address (a struct for historical reasons)
struct in_addr {
  uint32_t s_addr; // 32-bit int or 4 bytes
};

struct sockaddr_in6 {
  u_int16_t sin6_family;     // address family, AF_INET6
  u_int16_t sin6_port;       // port, NBO
  u_int32_t sin6_flowinfo;   // Ipv6 flow info
  struct in6_addr sin6_addr; // IPv6 address
  u_int32_t sin6_scope_id;   // Scope ID
};

struct in6_addr {
  unsigned char s6_addr[16];
};

// inet_pton() converts IP in numbers/dots to in_addr(6)

struct sockaddr_in sa;
struct sockaddr_in6 sa6;

inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr));
inet_pton(AF_INET6, "2001:db8: 63b3:1::3490", &(sa6.sin6_addr));

// inet_ntop() goes from struct to hex/dots notation

// IPv4:

char ip4[INET_ADDRSTRLEN]; // space to hold the IPv4 string
struct sockaddr_in sa;     // pretend this contains something

inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);

printf("The address is: %s\n", ip4);

// IPv6:

char ip6[INET6_ADDRSTRLEN]; // space to hold the IPv6 string
struct sockaddr_in6 sa6;    // pretend this is loaded
