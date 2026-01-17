/*
 * Copyright (c) 2000-2023 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1982, 1986, 1989, 1993
 *    The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the University of
 *    California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *    From: @(#)if.h    8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/net/if_var.h,v 1.18.2.7 2001/07/24 19:10:18 brooks Exp $
 */

#ifndef _NET_IF_VAR_PRIVATE_H_
#define _NET_IF_VAR_PRIVATE_H_

#ifndef DRIVERKIT_PRIVATE
#include <net/if_var_status.h>
#endif
#include <net/route.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/ioccom.h>

struct if_traffic_class {
	u_int64_t               ifi_ibepackets;/* TC_BE packets received on interface */
	u_int64_t               ifi_ibebytes;/* TC_BE bytes received on interface */
	u_int64_t               ifi_obepackets;/* TC_BE packet sent on interface */
	u_int64_t               ifi_obebytes;/* TC_BE bytes sent on interface */
	u_int64_t               ifi_ibkpackets;/* TC_BK packets received on interface */
	u_int64_t               ifi_ibkbytes;/* TC_BK bytes received on interface */
	u_int64_t               ifi_obkpackets;/* TC_BK packet sent on interface */
	u_int64_t               ifi_obkbytes;/* TC_BK bytes sent on interface */
	u_int64_t               ifi_ivipackets;/* TC_VI packets received on interface */
	u_int64_t               ifi_ivibytes;/* TC_VI bytes received on interface */
	u_int64_t               ifi_ovipackets;/* TC_VI packets sent on interface */
	u_int64_t               ifi_ovibytes;/* TC_VI bytes sent on interface */
	u_int64_t               ifi_ivopackets;/* TC_VO packets received on interface */
	u_int64_t               ifi_ivobytes;/* TC_VO bytes received on interface */
	u_int64_t               ifi_ovopackets;/* TC_VO packets sent on interface */
	u_int64_t               ifi_ovobytes;/* TC_VO bytes sent on interface */
	u_int64_t               ifi_ipvpackets;/* TC priv packets received on interface */
	u_int64_t               ifi_ipvbytes;/* TC priv bytes received on interface */
	u_int64_t               ifi_opvpackets;/* TC priv packets sent on interface */
	u_int64_t               ifi_opvbytes;/* TC priv bytes sent on interface */
};

struct if_data_extended {
	u_int64_t       ifi_alignerrs;/* unaligned (32-bit) input pkts */
	u_int64_t       ifi_dt_bytes;/* Data threshold counter */
	u_int64_t       ifi_fpackets;/* forwarded packets on interface */
	u_int64_t       ifi_fbytes; /* forwarded bytes on interface */
	u_int64_t       reserved[12];/* for future */
};

struct if_packet_stats {
	/* TCP */
	u_int64_t               ifi_tcp_badformat;
	u_int64_t               ifi_tcp_unspecv6;
	u_int64_t               ifi_tcp_synfin;
	u_int64_t               ifi_tcp_badformatipsec;
	u_int64_t               ifi_tcp_noconnnolist;
	u_int64_t               ifi_tcp_noconnlist;
	u_int64_t               ifi_tcp_listbadsyn;
	u_int64_t               ifi_tcp_icmp6unreach;
	u_int64_t               ifi_tcp_deprecate6;
	u_int64_t               ifi_tcp_rstinsynrcv;
	u_int64_t               ifi_tcp_ooopacket;
	u_int64_t               ifi_tcp_dospacket;
	u_int64_t               ifi_tcp_cleanup;
	u_int64_t               ifi_tcp_synwindow;
	u_int64_t               reserved[6];
	/* UDP */
	u_int64_t               ifi_udp_port_unreach;
	u_int64_t               ifi_udp_faithprefix;
	u_int64_t               ifi_udp_port0;
	u_int64_t               ifi_udp_badlength;
	u_int64_t               ifi_udp_badchksum;
	u_int64_t               ifi_udp_badmcast;
	u_int64_t               ifi_udp_cleanup;
	u_int64_t               ifi_udp_badipsec;
	u_int64_t               _reserved[4];
};

/*
 * Structure to report link heuristics
 */
#define HAS_IF_LINK_HEURISTICS_STATS 1
struct if_linkheuristics {
	u_int64_t       iflh_link_heuristics_cnt;  /* Count of congested link indications */
	u_int64_t       iflh_link_heuristics_time; /* Duration of congested link indications (msec) */

	u_int64_t       iflh_congested_link_cnt;  /* Count of congested link indications */
	u_int64_t       iflh_congested_link_time; /* Duration of congested link indications (msec) */

	u_int64_t       iflh_lqm_good_cnt;       /* Count of LQM good */
	u_int64_t       iflh_lqm_good_time;      /* Duration of LQM good (msec) */

	u_int64_t       iflh_lqm_poor_cnt;       /* Count of LQM poor */
	u_int64_t       iflh_lqm_poor_time;      /* Duration of LQM poor (msec) */

	u_int64_t       iflh_lqm_min_viable_cnt;  /* Count of LQM minimally viable */
	u_int64_t       iflh_lqm_min_viable_time; /* Duration of LQM minimally viable (msec) */

	u_int64_t       iflh_lqm_bad_cnt;         /* Count of LQM bad */
	u_int64_t       iflh_lqm_bad_time;        /* Duration of LQM bad (msec) */

	u_int64_t       iflh_tcp_linkheur_stealthdrop;
	u_int64_t       iflh_tcp_linkheur_noackpri;
	u_int64_t       iflh_tcp_linkheur_comprxmt;
	u_int64_t       iflh_tcp_linkheur_synrxmt;
	u_int64_t       iflh_tcp_linkheur_rxmtfloor;

	u_int64_t       iflh_udp_linkheur_stealthdrop;
};

struct if_description {
	u_int32_t       ifd_maxlen; /* must be IF_DESCSIZE */
	u_int32_t       ifd_len;    /* actual ifd_desc length */
	u_int8_t        *__sized_by(ifd_maxlen) ifd_desc;  /* ptr to desc buffer */
};

struct if_bandwidths {
	uint64_t       eff_bw;     /* effective bandwidth */
	uint64_t       max_bw;     /* maximum theoretical bandwidth */
};

struct if_latencies {
	u_int64_t       eff_lt;     /* effective latency */
	u_int64_t       max_lt;     /* maximum theoretical latency */
};

typedef enum {
	IF_NETEM_MODEL_NULL = 0,
	IF_NETEM_MODEL_NLC = 1,
} if_netem_model_t;

#define IF_NETEM_PARAMS_PSCALE  100000
struct if_netem_params {
	/* packet scheduler model */
	if_netem_model_t        ifnetem_model;

	/* bandwidth limit */
	uint64_t        ifnetem_bandwidth_bps;

	/* latency (normal distribution with jitter as stdev) */
	uint32_t        ifnetem_latency_ms;
	uint32_t        ifnetem_jitter_ms;

	/*
	 * NetEm probabilistic model parameters has a scaling factor of 100,000
	 * for 5 digits precision. For instance, probability 12.345% is
	 * expressed as uint32_t fixed point 12345 in ifnet_*_p variable below.
	 */
	/* random packet corruption */
	uint32_t        ifnetem_corruption_p;

	/* random packet duplication */
	uint32_t        ifnetem_duplication_p;

	/* 4 state Markov loss model */
	uint32_t        ifnetem_loss_p_gr_gl;/* P( gap_loss   | gap_rx     ) */
	uint32_t        ifnetem_loss_p_gr_bl;/* P( burst_loss | gap_rx     ) */
	uint32_t        ifnetem_loss_p_bl_br;/* P( burst_rx   | burst_loss ) */
	uint32_t        ifnetem_loss_p_bl_gr;/* P( gap_rx     | burst_loss ) */
	uint32_t        ifnetem_loss_p_br_bl;/* P( burst_loss | burst_rx   ) */

	uint32_t        ifnetem_loss_recovery_ms;/* time to recovery loss */

	/* random packet reordering */
	uint32_t        ifnetem_reordering_p;/* reorder probability */

	/*
	 * NetEm output scheduler by default is waken up upon input event as
	 * well as timer interval to avoid excessive delay. If
	 * ifnetem_output_ival is set to non-zero value, it overrides the
	 * default output interval as well as disables output scheduler wakeup
	 * upon input events.
	 */
	uint32_t        ifnetem_output_ival_ms;/* output interval */
};

struct if_rxpoll_stats {
	u_int32_t       ifi_poll_off_req;   /* total # of POLL_OFF reqs */
	u_int32_t       ifi_poll_off_err;   /* total # of POLL_OFF errors */
	u_int32_t       ifi_poll_on_req;    /* total # of POLL_ON reqs */
	u_int32_t       ifi_poll_on_err;    /* total # of POLL_ON errors */

	u_int32_t       ifi_poll_wakeups_avg;/* avg # of wakeup reqs */
	u_int32_t       ifi_poll_wakeups_lowat;/* wakeups low watermark */
	u_int32_t       ifi_poll_wakeups_hiwat;/* wakeups high watermark */

	u_int64_t       ifi_poll_packets;   /* total # of polled packets */
	u_int32_t       ifi_poll_packets_avg;/* average polled packets */
	u_int32_t       ifi_poll_packets_min;/* smallest polled packets */
	u_int32_t       ifi_poll_packets_max;/* largest polled packets */
	u_int32_t       ifi_poll_packets_lowat;/* packets low watermark */
	u_int32_t       ifi_poll_packets_hiwat;/* packets high watermark */

	u_int64_t       ifi_poll_bytes;     /* total # of polled bytes */
	u_int32_t       ifi_poll_bytes_avg; /* average polled bytes */
	u_int32_t       ifi_poll_bytes_min; /* smallest polled bytes */
	u_int32_t       ifi_poll_bytes_max; /* largest polled bytes */
	u_int32_t       ifi_poll_bytes_lowat;/* bytes low watermark */
	u_int32_t       ifi_poll_bytes_hiwat;/* bytes high watermark */

	u_int32_t       ifi_poll_packets_limit;/* max packets per poll call */
	u_int64_t       ifi_poll_interval_time;/* poll interval (nsec) */
};

struct if_netif_stats {
	u_int64_t       ifn_rx_mit_interval;/* rx mitigation ival (nsec) */
	u_int32_t       ifn_rx_mit_mode;    /* 0: static, 1: dynamic */
	u_int32_t       ifn_rx_mit_packets_avg;/* average # of packets */
	u_int32_t       ifn_rx_mit_packets_min;/* smallest # of packets */
	u_int32_t       ifn_rx_mit_packets_max;/* largest # of packets */
	u_int32_t       ifn_rx_mit_bytes_avg;/* average # of bytes */
	u_int32_t       ifn_rx_mit_bytes_min;/* smallest # of bytes */
	u_int32_t       ifn_rx_mit_bytes_max;/* largest # of bytes */
	u_int32_t       ifn_rx_mit_cfg_idx; /* current config selector */
	u_int32_t       ifn_rx_mit_cfg_packets_lowat;/* pkts low watermark */
	u_int32_t       ifn_rx_mit_cfg_packets_hiwat;/* pkts high watermark */
	u_int32_t       ifn_rx_mit_cfg_bytes_lowat;/* bytes low watermark */
	u_int32_t       ifn_rx_mit_cfg_bytes_hiwat;/* bytes high watermark */
	u_int32_t       ifn_rx_mit_cfg_interval;/* delay interval (nsec) */
};

struct if_tcp_ecn_perf_stat {
	u_int64_t total_txpkts;
	u_int64_t total_rxmitpkts;
	u_int64_t total_rxpkts;
	u_int64_t total_oopkts;
	u_int64_t total_reorderpkts;
	u_int64_t rtt_avg;
	u_int64_t rtt_var;
	u_int64_t sack_episodes;
	u_int64_t rxmit_drop;
	u_int64_t rst_drop;
	u_int64_t oo_percent;
	u_int64_t reorder_percent;
	u_int64_t rxmit_percent;
};

struct if_tcp_ecn_stat {
	u_int64_t timestamp;
	u_int64_t ecn_client_setup;
	u_int64_t ecn_server_setup;
	u_int64_t ecn_client_success;
	u_int64_t ecn_server_success;
	u_int64_t ecn_peer_nosupport;
	u_int64_t ecn_syn_lost;
	u_int64_t ecn_synack_lost;
	u_int64_t ecn_recv_ce;
	u_int64_t ecn_recv_ece;
	u_int64_t ecn_conn_recv_ce;
	u_int64_t ecn_conn_recv_ece;
	u_int64_t ecn_conn_plnoce;
	u_int64_t ecn_conn_plce;
	u_int64_t ecn_conn_noplce;
	u_int64_t ecn_fallback_synloss;
	u_int64_t ecn_fallback_reorder;
	u_int64_t ecn_fallback_ce;
	u_int64_t ecn_off_conn;
	u_int64_t ecn_total_conn;
	u_int64_t ecn_fallback_droprst;
	u_int64_t ecn_fallback_droprxmt;
	u_int64_t ecn_fallback_synrst;
	struct if_tcp_ecn_perf_stat ecn_on;
	struct if_tcp_ecn_perf_stat ecn_off;
};

struct if_lim_perf_stat {
	u_int64_t lim_dl_max_bandwidth; /* bits per second */
	u_int64_t lim_ul_max_bandwidth; /* bits per second */
	u_int64_t lim_total_txpkts; /* Total transmit packets, count */
	u_int64_t lim_total_rxpkts; /* Total receive packets, count */
	u_int64_t lim_total_retxpkts; /* Total retransmit packets */
	u_int64_t lim_packet_loss_percent; /* Packet loss rate */
	u_int64_t lim_total_oopkts; /* Total out-of-order packets */
	u_int64_t lim_packet_ooo_percent; /* Out-of-order packet rate */
	u_int64_t lim_rtt_variance; /* RTT variance, milliseconds */
	u_int64_t lim_rtt_average;  /* RTT average, milliseconds */
	u_int64_t lim_rtt_min;      /* RTT minimum, milliseconds */
	u_int64_t lim_conn_timeouts; /* connection timeouts */
	u_int64_t lim_conn_attempts; /* connection attempts */
	u_int64_t lim_conn_timeout_percent; /* Rate of connection timeouts */
	u_int64_t lim_bk_txpkts;    /* Transmit packets with BK service class, that use delay based algorithms */
	u_int64_t lim_dl_detected:1, /* Low internet */
	    lim_ul_detected:1;
};

#define IF_VAR_H_HAS_IFNET_STATS_PER_FLOW 1
#define IF_VAR_H_HAS_IFNET_STATS_PER_FLOW_LINKHEUR 1
struct ifnet_stats_per_flow {
	u_int64_t bk_txpackets;
	u_int64_t txpackets;
	u_int64_t rxpackets;
	u_int32_t txretransmitbytes;
	u_int32_t rxoutoforderbytes;
	u_int32_t rxmitpkts;
	u_int32_t rcvoopack;
	u_int32_t pawsdrop;
	u_int32_t sack_recovery_episodes;
	u_int32_t reordered_pkts;
	u_int32_t dsack_sent;
	u_int32_t dsack_recvd;
	u_int32_t srtt;
	u_int32_t rttupdated;
	u_int32_t rttvar;
	u_int32_t rttmin;
	u_int32_t bw_sndbw_max;
	u_int32_t bw_rcvbw_max;
	u_int32_t ecn_recv_ece;
	u_int32_t ecn_recv_ce;
	u_int32_t ecn_flags;
	u_int16_t ipv4:1,
	    local:1,
	    connreset:1,
	    conntimeout:1,
	    rxmit_drop:1,
	    ecn_fallback_synloss:1,
	    ecn_fallback_droprst:1,
	    ecn_fallback_droprxmt:1,
	    ecn_fallback_ce:1,
	    ecn_fallback_reorder:1,
	    _reserved_6:6;
	u_int16_t _reserved_16;
	u_int32_t _reserved_32;
	u_int64_t linkheur_noackpri;
	u_int64_t linkheur_comprxmt;
	u_int64_t linkheur_synrxmt;
	u_int64_t linkheur_rxmtfloor;
};

struct if_interface_state {
	/*
	 * The bitmask tells which of the fields
	 * to consider:
	 * - When setting, to control which fields
	 *   are being modified;
	 * - When getting, it tells which fields are set.
	 */
	u_int8_t valid_bitmask;
#define IF_INTERFACE_STATE_RRC_STATE_VALID              0x1
#define IF_INTERFACE_STATE_LQM_STATE_VALID              0x2
#define IF_INTERFACE_STATE_INTERFACE_AVAILABILITY_VALID 0x4

	/*
	 * Valid only for cellular interface
	 */
	u_int8_t rrc_state;
#define IF_INTERFACE_STATE_RRC_STATE_IDLE       0x0
#define IF_INTERFACE_STATE_RRC_STATE_CONNECTED  0x1

	/*
	 * Values normalized to the edge of the following values
	 * that are defined on <net/if.h>:
	 *  IFNET_LQM_THRESH_BAD
	 *  IFNET_LQM_THRESH_POOR
	 *  IFNET_LQM_THRESH_GOOD
	 */
	int8_t lqm_state;

	/*
	 * Indicate if the underlying link is currently
	 * available
	 */
	u_int8_t interface_availability;
#define IF_INTERFACE_STATE_INTERFACE_AVAILABLE          0x0
#define IF_INTERFACE_STATE_INTERFACE_UNAVAILABLE        0x1
};

struct chain_len_stats {
	uint64_t        cls_one;
	uint64_t        cls_two;
	uint64_t        cls_three;
	uint64_t        cls_four;
	uint64_t        cls_five_or_more;
} __attribute__((__aligned__(sizeof(uint64_t))));


#define if_mtu          if_data.ifi_mtu
#define if_type         if_data.ifi_type
#define if_typelen      if_data.ifi_typelen
#define if_physical     if_data.ifi_physical
#define if_addrlen      if_data.ifi_addrlen
#define if_hdrlen       if_data.ifi_hdrlen
#define if_metric       if_data.ifi_metric
#define if_baudrate     if_data.ifi_baudrate
#define if_hwassist     if_data.ifi_hwassist
#define if_ipackets     if_data.ifi_ipackets
#define if_ierrors      if_data.ifi_ierrors
#define if_opackets     if_data.ifi_opackets
#define if_oerrors      if_data.ifi_oerrors
#define if_collisions   if_data.ifi_collisions
#define if_ibytes       if_data.ifi_ibytes
#define if_obytes       if_data.ifi_obytes
#define if_imcasts      if_data.ifi_imcasts
#define if_omcasts      if_data.ifi_omcasts
#define if_iqdrops      if_data.ifi_iqdrops
#define if_noproto      if_data.ifi_noproto
#define if_lastchange   if_data.ifi_lastchange
#define if_recvquota    if_data.ifi_recvquota
#define if_xmitquota    if_data.ifi_xmitquota

/*
 * All of the following IF_HWASSIST_* flags are defined in kpi_interface.h as
 * IFNET_* flags. These are redefined here as constants to avoid failures to
 * build user level programs that can not include kpi_interface.h. It is
 * important to keep this in sync with the definitions in kpi_interface.h.
 * The corresponding constant for each definition is mentioned in the comment.
 *
 * Bottom 16 bits reserved for hardware checksum
 */
#define IF_HWASSIST_CSUM_IP             0x0001  /* will csum IP, IFNET_CSUM_IP */
#define IF_HWASSIST_CSUM_TCP            0x0002  /* will csum TCP, IFNET_CSUM_TCP */
#define IF_HWASSIST_CSUM_UDP            0x0004  /* will csum UDP, IFNET_CSUM_UDP */
#define IF_HWASSIST_CSUM_IP_FRAGS       0x0008  /* will csum IP fragments, IFNET_CSUM_FRAGMENT */
#define IF_HWASSIST_CSUM_FRAGMENT       0x0010  /* will do IP fragmentation, IFNET_IP_FRAGMENT */
#define IF_HWASSIST_CSUM_TCPIPV6        0x0020  /* will csum TCPv6, IFNET_CSUM_TCPIPV6 */
#define IF_HWASSIST_CSUM_UDPIPV6        0x0040  /* will csum UDPv6, IFNET_CSUM_UDP */
#define IF_HWASSIST_CSUM_FRAGMENT_IPV6  0x0080  /* will do IPv6 fragmentation, IFNET_IPV6_FRAGMENT */
#define IF_HWASSIST_CSUM_PARTIAL        0x1000  /* simple Sum16 computation, IFNET_CSUM_PARTIAL */
#define IF_HWASSIST_CSUM_ZERO_INVERT    0x2000  /* capable of inverting csum of 0 to -0 (0xffff) */
#define IF_HWASSIST_CSUM_MASK           0xffff
#define IF_HWASSIST_CSUM_FLAGS(hwassist)        ((hwassist) & IF_HWASSIST_CSUM_MASK)

/* VLAN support */
#define IF_HWASSIST_VLAN_TAGGING        0x00010000      /* supports VLAN tagging, IFNET_VLAN_TAGGING */
#define IF_HWASSIST_VLAN_MTU            0x00020000      /* supports VLAN MTU-sized packet (for software VLAN), IFNET_VLAN_MTU */

/* TCP Segment Offloading support */

#define IF_HWASSIST_TSO_V4              0x00200000      /* will do TCP Segment offload for IPv4, IFNET_TSO_IPV4 */
#define IF_HWASSIST_TSO_V6              0x00400000      /* will do TCP Segment offload for IPv6, IFNET_TSO_IPV6 */

#define IFXNAMSIZ       (IFNAMSIZ + 8)  /* external name (name + unit) */
#define IFNET_NETWORK_ID_LEN 32


#endif /* !_NET_IF_VAR_PRIVATE_H_ */
