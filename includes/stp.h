#ifndef STP_H_
#define STP_H_

#include <sys/types.h>

enum version_id {
  CONF_TCN_BPDU = 0x00,
  RST_BPDU = 0x02,
  MSTP_BPDU = 0x03,
  SPT_BPDU = 0x04
};

enum bpdu_type {
  CONFIG_BPDU_T = 0x00,
  TCN_BPDU_T = 0x80,
  RST_BPDU_T = 0x02
};

/*
 * destination MAC: 01:80:C2:00:00:00, or 01:00:0C:CC:CC:CD (VLAN)
 */

struct flags {
  u_char topology_name: 1;
  u_char proposal: 1;
  u_char port_role: 2;
  u_char learning: 1;
  u_char forwarding: 1;
  u_char agreement: 1;
  u_char tca: 1;
};

struct tag_bpdu_packet {
  u_char dmac[6];         /* dest. ether address */
  u_char smac[6];         /* src. ether address */
  u_char tpid[2];         /* tag proto id = 0x8100*/
  u_char pri_cfi_vlan[2]; /* frame priority 0 to 7, canonical format address
                             should be 0 for ethernet, vlan id from 0 to 4095 */
  u_char frame_type[2];   /* 0x00 0x26 */
  u_char llc_dsap;        /* 0x42 */
  u_char llc_ssap;        /* 0x42 */
  u_char command;         /* 03 why? I don`t know :( */
  u_char protoid[2];      /* Protocol Identifier */
  u_char protovid[1];     /* Protocol Version Identifier */
  u_char bpdu[1];         /* BPDU Type */
  struct flags flags;     /* Flags */
  u_char rootid[8];       /* Root Identifier */
  u_char rootpc[4];       /* Root Path Cost */
  u_char brid[8];         /* Bridge Identifier */
  u_char portid[2];       /* Port Identifier */
  u_char mage[2];         /* Message Age */
  u_char maxage[2];       /* Max Age */
  u_char hellotime[2];    /* Hello Time */
  u_char fdelay[2];       /* Forward Delay */
  u_char padding[4];      /* padding packet to 60 bytes */
};

struct bpdu_packet {
  u_char dmac[6];       /* dest. ether address */
  u_char smac[6];       /* src. ether address */
  u_char frame_type[2]; /* 0x00 0x26 */
  u_char llc_dsap;      /* 0x42 */
  u_char llc_ssap;      /* 0x42 */
  u_char command;       /* 03 command */
  u_char protoid[2];    /* Protocol Identifier */
  u_char protovid[1];   /* Protocol Version Identifier */
  u_char bpdu[1];       /* BPDU Type */
  u_char flags[1];      /* Flags */
  u_char rootid[8];     /* Root Identifier */
  u_char rootpc[4];     /* Root Path Cost */
  u_char brid[8];       /* Bridge Identifier */
  u_char portid[2];     /* Port Identifier */
  u_char mage[2];       /* Message Age */
  u_char maxage[2];     /* Max Age */
  u_char hellotime[2];  /* Hello Time */
  u_char fdelay[2];     /* Forward Delay */
  u_char padding[8];    /* padding packet to 60 bytes */
};

#endif // STP_H_
