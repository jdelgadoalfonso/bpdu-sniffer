#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <string.h>

static int
create_socket(char *dev, struct ifreq *ifr) {
  int sock = socket(AF_INET, SOCK_PACKET, htons(ETH_P_ALL));

  // Open raw socket
  if (sock >= 0) {
    strcpy(ifr->ifr_name, dev);
  }

  return sock;
}

int
raw_socket(char *dev) {
  struct ifreq ifr;
  int sock = create_socket(dev, &ifr);

  // Open raw socket
  if (sock >= 0) {
    if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
      close(sock);
      sock = -1;
    }
  }

  return sock;
}

int
promisc_mode(char *dev)
{
  struct ifreq ifr_listen;
  int ok = 0;
  int listen = create_socket(dev, &ifr_listen);

  if (listen >= 0) {
    if (ioctl(listen, SIOCGIFFLAGS, &ifr_listen) >= 0) {
      ifr_listen.ifr_flags |= IFF_PROMISC;
      if (ioctl(listen, SIOCSIFFLAGS, &ifr_listen) >= 0) {
        ok++;
      }
    }
  }

  if (!ok) {
    close(listen);
    listen = -1;
  }

  return listen;
}
