#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define NO_SYS                  1
#define LWIP_SOCKET             0
#define LWIP_NETCONN            0

#define LWIP_NETIF_STATUS_CALLBACK  0
#define LWIP_NETIF_LINK_CALLBACK    1

#define ETH_PAD_SIZE            2

#define MEM_ALIGNMENT           4

#define MEM_SIZE                12 * 1024

#define PBUF_POOL_SIZE          16
#define PBUF_POOL_BUFSIZE       1536
#define MEMP_NUM_PBUF           16
#define MEMP_NUM_TCP_SEG        16

#define LWIP_UDP                1
#define LWIP_TCP                1
#define TCP_MSS                 1460
#define TCP_WND                 (8 * TCP_MSS)
#define TCP_SND_BUF             (8 * TCP_MSS)
#define TCP_SND_QUEUELEN        16

#define LWIP_STATS 0

#define CHECKSUM_GEN_IP         0
#define CHECKSUM_GEN_UDP        0
#define CHECKSUM_GEN_TCP        0
#define CHECKSUM_GEN_ICMP       0
#define CHECKSUM_CHECK_IP       0
#define CHECKSUM_CHECK_UDP      0
#define CHECKSUM_CHECK_TCP      0

#define MEMP_NUM_SYS_TIMEOUT    (LWIP_TCP + IP_REASSEMBLY + LWIP_ARP + (2*LWIP_DHCP) + LWIP_AUTOIP + LWIP_IGMP + LWIP_DNS + PPP_SUPPORT + 5)

#if defined(__GNUC__)
#define MEMCPY(dst,src,len)     thumb2_memcpy(dst,src,len)
#define SMEMCPY(dst,src,len)    thumb2_memcpy(dst,src,len)
#else
#define MEMCPY(dst,src,len)     memcpy(dst,src,len)
#define SMEMCPY(dst,src,len)    memcpy(dst,src,len)
#endif

#ifdef __cplusplus
}
#endif
#endif /* __LWIPOPTS_H__ */

