/*
 * Copyright (c) 2020 Apple, Inc. All rights reserved.
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

#ifndef _IOUSERNETWORKETHERNETNICPROXY_H
#define _IOUSERNETWORKETHERNETNICPROXY_H

#include <netinet/in.h>
#include <net/ethernet.h>
#pragma pack(1)

//
// IP V4 TCP Keepalive structure.
//
typedef struct offload_v4_keep_alive_s {
    uint32_t timeout;
    in_port_t local_port;
    in_port_t remote_port;
    ether_addr_t remote_mac_addr;
    uint16_t win_size;
    uint32_t seq_num;
    uint32_t ack_num;
    in_addr_t local_ip;
    in_addr_t remote_ip;
} offload_v4_keep_alive_t;

//
// IP V6 TCP Keepalive structure.
//
typedef struct offload_v6_keep_alive_s {
    uint32_t timeout;
    in_port_t local_port;
    in_port_t remote_port;
    ether_addr_t remote_mac_addr;
    uint16_t win_size;
    uint32_t seq_num;
    uint32_t ack_num;
    in6_addr_t local_ip;
    in6_addr_t remote_ip;
} offload_v6_keep_alive_t;

typedef struct offload_inet_info_s {
    uint8_t v4LocalAddrCount;
    uint8_t v4AddrCount;
    uint8_t v6LocalAddrCount;
    uint8_t v6AddrCount;
    // FW will add the base to the following offset members and will treat them as pointers.
    // The offsets are relative to the start of this struct so that the struct is pretty much self-contained
    // in_addr_t *
    uint32_t v4AddrOfft;
    // uint8_t *
    uint32_t v4PrefixOfft;
    // in6_addr *
    uint32_t v6AddrOfft;
    // uint8_t *
    uint32_t v6PrefixOfft;
} offload_inet_info_t;

typedef struct offload_port_info_s {
    uint16_t UDPPortCount;
    uint16_t TCPPortCount;
    // in_port_t *
    uint32_t UDPPortOfft;       // See the comment in the offload_inet_info struct
    // in_port_t *
    uint32_t TCPPortOfft;
} offload_port_info_t;

typedef struct offload_keep_alive_info_s {
    uint16_t v4KACount;
    uint16_t v6KACount;
    uint32_t retryCount;
    uint32_t retryInterval;
    // offload_v4_keep_alive_t *
    uint32_t v4KAOfft;          // See the comment in the offload_inet_info struct
    // offload_v6_keep_alive_t *
    uint32_t v6KAOfft;
} offload_keep_alive_info_t;

typedef struct offload_rr_info_s {
    uint32_t RRCount;
    uint32_t RRBufLen;
    // Offset to RR index table relative to the start of offloadRRInfo struct. The indices
    // themselves are relative to the start of RR buffer. FW can add the buffer address
    // and treat them as pointers.
    // uint8_t **
    uint32_t RRIdxOfft;
    // Offset to the RR buffer relative to the start of offloadRRInfo struct.
    // uint8_t *
    uint32_t RRBufOfft;
} offload_rr_info_t;

#define NIC_PROXY_FLAGS_WONLINK     (1 << 7);
#define NIC_PROXY_FLAGS_WOMP        (1 << 6);

typedef struct offload_info_s {
    uint32_t len;                   // The whole structure length including the variable-size buf
    ether_addr_t mac_addr;
    uint8_t flags;
    uint8_t reserved;
    offload_inet_info_t ips;
    offload_port_info_t ports;
    offload_keep_alive_info_t kas;
    offload_rr_info_t rrs;
    uint8_t buf[0];
} offload_info_t;

//
// Resource Record definitions.
//
typedef union rr_record_s {
    struct {
        uint8_t len;
        union {
            uint8_t name[];
            uint8_t record[];
        };
    } label;
    struct {
        uint8_t hb;
        uint8_t lb;
        uint8_t record[];
    } ptr;
    struct {
        uint16_t type;
        uint16_t rr_class;
        uint32_t ttl;
        uint16_t len;
    } rr;
} rr_record_t;

typedef struct rr_sub_type_s {
    uint16_t sub_typ_cnt;
    uint8_t sub_typ_name[];
} rr_sub_type_t;

typedef struct rr_srv_record_s {
    rr_record_t rr_record;
    struct {
        uint16_t priority;
        uint16_t weight;
        uint16_t port;
        uint8_t target[];
    };
    rr_sub_type_t sub_type;
} rr_srv_record_t;

typedef struct rr_txt_record_s {
    rr_record_t rr_record;
    uint8_t txt[];
} rr_txt_record_t;

typedef struct rr_ptr_record_s {
    rr_record_t rr_record;
    uint8_t name[];
} rr_ptr_record_t;

typedef struct rr_null_record_s {
    rr_record_t rr_record;
    uint8_t data[];
} rr_null_record_t;

#pragma pack()

#endif
