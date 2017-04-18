#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "stp.h"

static void
process_packet(struct bpdu_packet *stp_listen_packet) {
  unsigned char k;
  char temp[2], rootid[17], brid[17], htime[5];

  if ((stp_listen_packet->llc_dsap == 0x42) &&
      (stp_listen_packet->llc_ssap == 0x42)) {

    printf("STP packet...\n");

    bzero(rootid, sizeof(rootid));
    bzero(brid, sizeof(brid));
    bzero(htime, sizeof(htime));
    for(k = 0; k < 8; k++) {
      sprintf(temp, "%x", stp_listen_packet->rootid[k]);
      if (strlen(temp) == 1) {
        strcat(rootid, "0");
      }
      strcat(rootid, temp);
    };
    sprintf(temp, "%x", stp_listen_packet->hellotime[0]);
    strcat(htime, "0");
    strcat(htime, temp);
    strcat(htime, "00");
  }
}

void
main_loop(int scap) {
  char buffer[65535];
  int loop = 1;

  while(loop) {
    size_t s = read(scap, buffer, sizeof(buffer));
    printf("dmac: %02x:%02x:%02x:%02x:%02x:%02x - %02x %02x\n",
      ((struct bpdu_packet *) buffer)->dmac[0],
      ((struct bpdu_packet *) buffer)->dmac[1],
      ((struct bpdu_packet *) buffer)->dmac[2],
      ((struct bpdu_packet *) buffer)->dmac[3],
      ((struct bpdu_packet *) buffer)->dmac[4],
      ((struct bpdu_packet *) buffer)->dmac[5],
      ((struct bpdu_packet *) buffer)->llc_dsap,
      ((struct bpdu_packet *) buffer)->llc_ssap
    );
    process_packet((struct bpdu_packet *) buffer);
  }
}
