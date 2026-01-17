/*
 * Copyright (c) 2025 Apple, Inc. All rights reserved.
 *
 */
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2004, 2011-2012 Intel Corporation.  All rights reserved.
 * Copyright (c) 2005, 2006, 2007 Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2005 PathScale, Inc.  All rights reserved.
 * Copyright (c) 2020 Intel Corporation.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef INFINIBAND_VERBS_H
#define INFINIBAND_VERBS_H

#include <stdint.h>
#include <pthread.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#ifdef __cplusplus
#include <limits>
#endif

#if __GNUC__ >= 3
#  define __attribute_const __attribute__((const))
#else
#  define __attribute_const
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IB_USER_IOCTL_VERBS_H
#define IB_UVERBS_ACCESS_OPTIONAL_FIRST (1 << 20)
#define IB_UVERBS_ACCESS_OPTIONAL_LAST (1 << 29)
#define	IB_UVERBS_ACCESS_OPTIONAL_RANGE (((IB_UVERBS_ACCESS_OPTIONAL_LAST << 1) - 1) & \
	    ~(IB_UVERBS_ACCESS_OPTIONAL_FIRST - 1))
enum ib_uverbs_advise_mr_advice {
	IB_UVERBS_ADVISE_MR_ADVICE_PREFETCH,
	IB_UVERBS_ADVISE_MR_ADVICE_PREFETCH_WRITE,
	IB_UVERBS_ADVISE_MR_ADVICE_PREFETCH_NO_FAULT,
};
#endif /* IB_USER_IOCTL_VERBS_H */

#define IBV_ACCESS_OPTIONAL_RANGE			IB_UVERBS_ACCESS_OPTIONAL_RANGE
#define IBV_ACCESS_OPTIONAL_FIRST			IB_UVERBS_ACCESS_OPTIONAL_FIRST
#define ibv_advise_mr_advice                            ib_uverbs_advise_mr_advice

union ibv_gid {
	uint8_t			raw[16];
	struct {
		uint64_t	subnet_prefix;
		uint64_t	interface_id;
	} global;
};

enum ibv_gid_type {
	IBV_GID_TYPE_IB,
	IBV_GID_TYPE_ROCE_V1,
	IBV_GID_TYPE_ROCE_V2,
};

struct ibv_gid_entry {
	union ibv_gid gid;
	uint32_t gid_index;
	uint32_t port_num;
	uint32_t gid_type; /* enum ibv_gid_type */
	uint32_t ndev_ifindex;
};

#ifdef __cplusplus
#define __VERBS_ABI_IS_EXTENDED ((void *)std::numeric_limits<uintptr_t>::max())
#else
#define __VERBS_ABI_IS_EXTENDED ((void *)UINTPTR_MAX)
#endif

enum ibv_node_type {
	IBV_NODE_UNKNOWN	= -1,
	IBV_NODE_CA 		= 1,
	IBV_NODE_SWITCH,
	IBV_NODE_ROUTER,
	IBV_NODE_RNIC,
	IBV_NODE_USNIC,
	IBV_NODE_USNIC_UDP,
	IBV_NODE_UNSPECIFIED,
	IBV_NODE_TBT = 100,
};

enum ibv_transport_type {
	IBV_TRANSPORT_UNKNOWN	= -1,
	IBV_TRANSPORT_IB	= 0,
	IBV_TRANSPORT_IWARP,
	IBV_TRANSPORT_USNIC,
	IBV_TRANSPORT_USNIC_UDP,
	IBV_TRANSPORT_UNSPECIFIED,
	IBV_TRANSPORT_TBT = 100,
};

enum ibv_device_cap_flags {
	IBV_DEVICE_RESIZE_MAX_WR	= 1,
	IBV_DEVICE_BAD_PKEY_CNTR	= 1 <<  1,
	IBV_DEVICE_BAD_QKEY_CNTR	= 1 <<  2,
	IBV_DEVICE_RAW_MULTI		= 1 <<  3,
	IBV_DEVICE_AUTO_PATH_MIG	= 1 <<  4,
	IBV_DEVICE_CHANGE_PHY_PORT	= 1 <<  5,
	IBV_DEVICE_UD_AV_PORT_ENFORCE	= 1 <<  6,
	IBV_DEVICE_CURR_QP_STATE_MOD	= 1 <<  7,
	IBV_DEVICE_SHUTDOWN_PORT	= 1 <<  8,
	IBV_DEVICE_INIT_TYPE		= 1 <<  9,
	IBV_DEVICE_PORT_ACTIVE_EVENT	= 1 << 10,
	IBV_DEVICE_SYS_IMAGE_GUID	= 1 << 11,
	IBV_DEVICE_RC_RNR_NAK_GEN	= 1 << 12,
	IBV_DEVICE_SRQ_RESIZE		= 1 << 13,
	IBV_DEVICE_N_NOTIFY_CQ		= 1 << 14,
	IBV_DEVICE_MEM_WINDOW           = 1 << 17,
	IBV_DEVICE_UD_IP_CSUM		= 1 << 18,
	IBV_DEVICE_XRC			= 1 << 20,
	IBV_DEVICE_MEM_MGT_EXTENSIONS	= 1 << 21,
	IBV_DEVICE_MEM_WINDOW_TYPE_2A	= 1 << 23,
	IBV_DEVICE_MEM_WINDOW_TYPE_2B	= 1 << 24,
	IBV_DEVICE_RC_IP_CSUM		= 1 << 25,
	IBV_DEVICE_RAW_IP_CSUM		= 1 << 26,
	IBV_DEVICE_MANAGED_FLOW_STEERING = 1 << 29
};


/*
 * Can't extended above ibv_device_cap_flags enum as in some systems/compilers
 * enum range is limited to 4 bytes.
 */
#define IBV_DEVICE_RAW_SCATTER_FCS (1ULL << 34)
#define IBV_DEVICE_PCI_WRITE_END_PADDING (1ULL << 36)

enum ibv_atomic_cap {
	IBV_ATOMIC_NONE,
	IBV_ATOMIC_HCA,
	IBV_ATOMIC_GLOB
};


struct ibv_device_attr {
	char			fw_ver[64];
	uint64_t		node_guid;
	uint64_t		sys_image_guid;
	uint64_t		max_mr_size;
	uint64_t		page_size_cap;
	uint32_t		vendor_id;
	uint32_t		vendor_part_id;
	uint32_t		hw_ver;
	int			max_qp;
	int			max_qp_wr;
	unsigned int		device_cap_flags;
	int			max_sge;
	int			max_sge_rd;
	int			max_cq;
	int			max_cqe;
	int			max_mr;
	int			max_pd;
	int			max_qp_rd_atom;
	int			max_ee_rd_atom;
	int			max_res_rd_atom;
	int			max_qp_init_rd_atom;
	int			max_ee_init_rd_atom;
	enum ibv_atomic_cap	atomic_cap;
	int			max_ee;
	int			max_rdd;
	int			max_mw;
	int			max_raw_ipv6_qp;
	int			max_raw_ethy_qp;
	int			max_mcast_grp;
	int			max_mcast_qp_attach;
	int			max_total_mcast_qp_attach;
	int			max_ah;
	int			max_fmr;
	int			max_map_per_fmr;
	int			max_srq;
	int			max_srq_wr;
	int			max_srq_sge;
	uint16_t		max_pkeys;
	uint8_t			local_ca_ack_delay;
	uint8_t			phys_port_cnt;
};

/* An extensible input struct for possible future extensions of the
 * ibv_query_device_ex verb. */
struct ibv_query_device_ex_input {
	uint32_t		comp_mask;
};
struct ibv_odp_caps {
	uint64_t general_caps;
	struct {
		uint32_t rc_odp_caps;
		uint32_t uc_odp_caps;
		uint32_t ud_odp_caps;
	} per_transport_caps;
};

enum ibv_odp_general_caps {
	IBV_ODP_SUPPORT = 1 << 0,
	IBV_ODP_SUPPORT_IMPLICIT = 1 << 1,
};

struct ibv_tso_caps {
	uint32_t max_tso;
	uint32_t supported_qpts;
};

/* RX Hash function flags */
enum ibv_rx_hash_function_flags {
	IBV_RX_HASH_FUNC_TOEPLITZ	= 1 << 0,
};

/*
 * RX Hash fields enable to set which incoming packet's field should
 * participates in RX Hash. Each flag represent certain packet's field,
 * when the flag is set the field that is represented by the flag will
 * participate in RX Hash calculation.
 * Note: *IPV4 and *IPV6 flags can't be enabled together on the same QP
 * and *TCP and *UDP flags can't be enabled together on the same QP.
*/
enum ibv_rx_hash_fields {
	IBV_RX_HASH_SRC_IPV4	= 1 << 0,
	IBV_RX_HASH_DST_IPV4	= 1 << 1,
	IBV_RX_HASH_SRC_IPV6	= 1 << 2,
	IBV_RX_HASH_DST_IPV6	= 1 << 3,
	IBV_RX_HASH_SRC_PORT_TCP	= 1 << 4,
	IBV_RX_HASH_DST_PORT_TCP	= 1 << 5,
	IBV_RX_HASH_SRC_PORT_UDP	= 1 << 6,
	IBV_RX_HASH_DST_PORT_UDP	= 1 << 7,
	IBV_RX_HASH_IPSEC_SPI		= 1 << 8,
	IBV_RX_HASH_INNER		= (1UL << 31),
};

struct ibv_rss_caps {
	uint32_t supported_qpts;
	uint32_t max_rwq_indirection_tables;
	uint32_t max_rwq_indirection_table_size;
	uint64_t rx_hash_fields_mask; /* enum ibv_rx_hash_fields */
	uint8_t  rx_hash_function; /* enum ibv_rx_hash_function_flags */
};

struct ibv_packet_pacing_caps {
	uint32_t qp_rate_limit_min;
	uint32_t qp_rate_limit_max; /* In kbps */
	uint32_t supported_qpts;
};

enum ibv_raw_packet_caps {
	IBV_RAW_PACKET_CAP_CVLAN_STRIPPING	= 1 << 0,
	IBV_RAW_PACKET_CAP_SCATTER_FCS		= 1 << 1,
	IBV_RAW_PACKET_CAP_IP_CSUM		= 1 << 2,
	IBV_RAW_PACKET_CAP_DELAY_DROP		= 1 << 3,
};

enum ibv_tm_cap_flags {
	IBV_TM_CAP_RC		    = 1 << 0,
};

struct ibv_tm_caps {
	/* Max size of rendezvous request header */
	uint32_t max_rndv_hdr_size;
	/* Max number of tagged buffers in a TM-SRQ matching list */
	uint32_t max_num_tags;
	/* From enum ibv_tm_cap_flags */
	uint32_t flags;
	/* Max number of outstanding list operations */
	uint32_t max_ops;
	/* Max number of SGEs in a tagged buffer */
	uint32_t max_sge;
};

struct ibv_cq_moderation_caps {
	uint16_t max_cq_count;
	uint16_t max_cq_period; /* in micro seconds */
};

enum ibv_pci_atomic_op_size {
	IBV_PCI_ATOMIC_OPERATION_4_BYTE_SIZE_SUP = 1 << 0,
	IBV_PCI_ATOMIC_OPERATION_8_BYTE_SIZE_SUP = 1 << 1,
	IBV_PCI_ATOMIC_OPERATION_16_BYTE_SIZE_SUP = 1 << 2,
};

/*
 * Bitmask for supported operation sizes
 * Use enum ibv_pci_atomic_op_size
 */
struct ibv_pci_atomic_caps {
	uint16_t fetch_add;
	uint16_t swap;
	uint16_t compare_swap;
};

struct ibv_device_attr_ex {
	struct ibv_device_attr	orig_attr;
	uint32_t		comp_mask;
	struct ibv_odp_caps	odp_caps;
	uint64_t		completion_timestamp_mask;
	uint64_t		hca_core_clock;
	uint64_t		device_cap_flags_ex;
	struct ibv_tso_caps	tso_caps;
	struct ibv_rss_caps     rss_caps;
	uint32_t		max_wq_type_rq;
	struct ibv_packet_pacing_caps packet_pacing_caps;
	uint32_t		raw_packet_caps; /* Use ibv_raw_packet_caps */
	struct ibv_tm_caps	tm_caps;
	struct ibv_cq_moderation_caps  cq_mod_caps;
	uint64_t max_dm_size;
	struct ibv_pci_atomic_caps pci_atomic_caps;
	uint32_t xrc_odp_caps;
	uint32_t phys_port_cnt_ex;
};

enum ibv_mtu {
	IBV_MTU_256  = 1,
	IBV_MTU_512  = 2,
	IBV_MTU_1024 = 3,
	IBV_MTU_2048 = 4,
	IBV_MTU_4096 = 5
};

enum ibv_port_state {
	IBV_PORT_NOP		= 0,
	IBV_PORT_DOWN		= 1,
	IBV_PORT_INIT		= 2,
	IBV_PORT_ARMED		= 3,
	IBV_PORT_ACTIVE		= 4,
	IBV_PORT_ACTIVE_DEFER	= 5
};

enum {
	IBV_LINK_LAYER_UNSPECIFIED,
	IBV_LINK_LAYER_INFINIBAND,
	IBV_LINK_LAYER_ETHERNET,
	IBV_LINK_LAYER_THUNDERBOLT = 100,
};

enum ibv_port_cap_flags {
	IBV_PORT_SM				= 1 <<  1,
	IBV_PORT_NOTICE_SUP			= 1 <<  2,
	IBV_PORT_TRAP_SUP			= 1 <<  3,
	IBV_PORT_OPT_IPD_SUP			= 1 <<  4,
	IBV_PORT_AUTO_MIGR_SUP			= 1 <<  5,
	IBV_PORT_SL_MAP_SUP			= 1 <<  6,
	IBV_PORT_MKEY_NVRAM			= 1 <<  7,
	IBV_PORT_PKEY_NVRAM			= 1 <<  8,
	IBV_PORT_LED_INFO_SUP			= 1 <<  9,
	IBV_PORT_SYS_IMAGE_GUID_SUP		= 1 << 11,
	IBV_PORT_PKEY_SW_EXT_PORT_TRAP_SUP	= 1 << 12,
	IBV_PORT_EXTENDED_SPEEDS_SUP		= 1 << 14,
	IBV_PORT_CAP_MASK2_SUP			= 1 << 15,
	IBV_PORT_CM_SUP				= 1 << 16,
	IBV_PORT_SNMP_TUNNEL_SUP		= 1 << 17,
	IBV_PORT_REINIT_SUP			= 1 << 18,
	IBV_PORT_DEVICE_MGMT_SUP		= 1 << 19,
	IBV_PORT_VENDOR_CLASS_SUP		= 1 << 20,
	IBV_PORT_DR_NOTICE_SUP			= 1 << 21,
	IBV_PORT_CAP_MASK_NOTICE_SUP		= 1 << 22,
	IBV_PORT_BOOT_MGMT_SUP			= 1 << 23,
	IBV_PORT_LINK_LATENCY_SUP		= 1 << 24,
	IBV_PORT_CLIENT_REG_SUP			= 1 << 25,
	IBV_PORT_IP_BASED_GIDS			= 1 << 26
};

enum ibv_port_cap_flags2 {
	IBV_PORT_SET_NODE_DESC_SUP		= 1 << 0,
	IBV_PORT_INFO_EXT_SUP			= 1 << 1,
	IBV_PORT_VIRT_SUP			= 1 << 2,
	IBV_PORT_SWITCH_PORT_STATE_TABLE_SUP	= 1 << 3,
	IBV_PORT_LINK_WIDTH_2X_SUP		= 1 << 4,
	IBV_PORT_LINK_SPEED_HDR_SUP		= 1 << 5,
	IBV_PORT_LINK_SPEED_NDR_SUP		= 1 << 10,
};

struct ibv_port_attr {
	enum ibv_port_state	state;
	enum ibv_mtu		max_mtu;
	enum ibv_mtu		active_mtu;
	int			gid_tbl_len;
	uint32_t		port_cap_flags;
	uint32_t		max_msg_sz;
	uint32_t		bad_pkey_cntr;
	uint32_t		qkey_viol_cntr;
	uint16_t		pkey_tbl_len;
	uint16_t		lid;
	uint16_t		sm_lid;
	uint8_t			lmc;
	uint8_t			max_vl_num;
	uint8_t			sm_sl;
	uint8_t			subnet_timeout;
	uint8_t			init_type_reply;
	uint8_t			active_width;
	uint8_t			active_speed;
	uint8_t			phys_state;
	uint8_t			link_layer;
	uint8_t			flags;
	uint16_t		port_cap_flags2;
};

enum ibv_wc_status {
	IBV_WC_SUCCESS,
	IBV_WC_LOC_LEN_ERR,
	IBV_WC_LOC_QP_OP_ERR,
	IBV_WC_LOC_EEC_OP_ERR,
	IBV_WC_LOC_PROT_ERR,
	IBV_WC_WR_FLUSH_ERR,
	IBV_WC_MW_BIND_ERR,
	IBV_WC_BAD_RESP_ERR,
	IBV_WC_LOC_ACCESS_ERR,
	IBV_WC_REM_INV_REQ_ERR,
	IBV_WC_REM_ACCESS_ERR,
	IBV_WC_REM_OP_ERR,
	IBV_WC_RETRY_EXC_ERR,
	IBV_WC_RNR_RETRY_EXC_ERR,
	IBV_WC_LOC_RDD_VIOL_ERR,
	IBV_WC_REM_INV_RD_REQ_ERR,
	IBV_WC_REM_ABORT_ERR,
	IBV_WC_INV_EECN_ERR,
	IBV_WC_INV_EEC_STATE_ERR,
	IBV_WC_FATAL_ERR,
	IBV_WC_RESP_TIMEOUT_ERR,
	IBV_WC_GENERAL_ERR,
	IBV_WC_TM_ERR,
	IBV_WC_TM_RNDV_INCOMPLETE,
};
const char *ibv_wc_status_str(enum ibv_wc_status status);

enum ibv_wc_opcode {
	IBV_WC_SEND,
	IBV_WC_RDMA_WRITE,
	IBV_WC_RDMA_READ,
	IBV_WC_COMP_SWAP,
	IBV_WC_FETCH_ADD,
	IBV_WC_BIND_MW,
	IBV_WC_LOCAL_INV,
	IBV_WC_TSO,
	IBV_WC_FLUSH,
	IBV_WC_ATOMIC_WRITE = 9,
/*
 * Set value of IBV_WC_RECV so consumers can test if a completion is a
 * receive by testing (opcode & IBV_WC_RECV).
 */
	IBV_WC_RECV			= 1 << 7,
	IBV_WC_RECV_RDMA_WITH_IMM,

	IBV_WC_TM_ADD,
	IBV_WC_TM_DEL,
	IBV_WC_TM_SYNC,
	IBV_WC_TM_RECV,
	IBV_WC_TM_NO_TAG,
	IBV_WC_DRIVER1,
	IBV_WC_DRIVER2,
	IBV_WC_DRIVER3,
};

enum {
	IBV_WC_IP_CSUM_OK_SHIFT	= 2
};
enum ibv_wc_flags {
	IBV_WC_GRH		= 1 << 0,
	IBV_WC_WITH_IMM		= 1 << 1,
	IBV_WC_IP_CSUM_OK	= 1 << IBV_WC_IP_CSUM_OK_SHIFT,
	IBV_WC_WITH_INV		= 1 << 3,
	IBV_WC_TM_SYNC_REQ	= 1 << 4,
	IBV_WC_TM_MATCH		= 1 << 5,
	IBV_WC_TM_DATA_VALID	= 1 << 6,
};

struct ibv_wc {
	uint64_t		wr_id;
	enum ibv_wc_status	status;
	enum ibv_wc_opcode	opcode;
	uint32_t		vendor_err;
	uint32_t		byte_len;
	/* When (wc_flags & IBV_WC_WITH_IMM): Immediate data in network byte order.
	 * When (wc_flags & IBV_WC_WITH_INV): Stores the invalidated rkey.
	 */
	union {
		uint32_t	imm_data;
		uint32_t	invalidated_rkey;
	};
	uint32_t		qp_num;
	uint32_t		src_qp;
	unsigned int		wc_flags;
	uint16_t		pkey_index;
	uint16_t		slid;
	uint8_t			sl;
	uint8_t			dlid_path_bits;
};

enum ibv_access_flags {
	IBV_ACCESS_LOCAL_WRITE		= 1,
	IBV_ACCESS_REMOTE_WRITE		= (1<<1),
	IBV_ACCESS_REMOTE_READ		= (1<<2),
	IBV_ACCESS_REMOTE_ATOMIC	= (1<<3),
	IBV_ACCESS_MW_BIND		= (1<<4),
	IBV_ACCESS_ZERO_BASED		= (1<<5),
	IBV_ACCESS_ON_DEMAND		= (1<<6),
	IBV_ACCESS_HUGETLB		= (1<<7),
	IBV_ACCESS_FLUSH_GLOBAL		= (1 << 8),
	IBV_ACCESS_FLUSH_PERSISTENT	= (1 << 9),
	IBV_ACCESS_RELAXED_ORDERING	= IBV_ACCESS_OPTIONAL_FIRST,
};

struct ibv_mw_bind_info {
	struct ibv_mr	*mr;
	uint64_t	 addr;
	uint64_t	 length;
	unsigned int	 mw_access_flags; /* use ibv_access_flags */
};

struct ibv_pd {
	struct ibv_context     *context;
	uint32_t		handle;
};

struct ibv_mr {
	struct ibv_context     *context;
	struct ibv_pd	       *pd;
	void		       *addr;
	size_t			length;
	uint32_t		handle;
	uint32_t		lkey;
	uint32_t		rkey;
};

enum ibv_mw_type {
	IBV_MW_TYPE_1			= 1,
	IBV_MW_TYPE_2			= 2
};

struct ibv_mw {
	struct ibv_context     *context;
	struct ibv_pd	       *pd;
	uint32_t		rkey;
	uint32_t		handle;
	enum ibv_mw_type	type;
};

struct ibv_global_route {
	union ibv_gid		dgid;
	uint32_t		flow_label;
	uint8_t			sgid_index;
	uint8_t			hop_limit;
	uint8_t			traffic_class;
};

struct ibv_grh {
	uint32_t		version_tclass_flow;
	uint16_t		paylen;
	uint8_t			next_hdr;
	uint8_t			hop_limit;
	union ibv_gid		sgid;
	union ibv_gid		dgid;
};

enum ibv_rate {
	IBV_RATE_MAX      = 0,
	IBV_RATE_2_5_GBPS = 2,
	IBV_RATE_5_GBPS   = 5,
	IBV_RATE_10_GBPS  = 3,
	IBV_RATE_20_GBPS  = 6,
	IBV_RATE_30_GBPS  = 4,
	IBV_RATE_40_GBPS  = 7,
	IBV_RATE_60_GBPS  = 8,
	IBV_RATE_80_GBPS  = 9,
	IBV_RATE_120_GBPS = 10,
	IBV_RATE_14_GBPS  = 11,
	IBV_RATE_56_GBPS  = 12,
	IBV_RATE_112_GBPS = 13,
	IBV_RATE_168_GBPS = 14,
	IBV_RATE_25_GBPS  = 15,
	IBV_RATE_100_GBPS = 16,
	IBV_RATE_200_GBPS = 17,
	IBV_RATE_300_GBPS = 18,
	IBV_RATE_28_GBPS  = 19,
	IBV_RATE_50_GBPS  = 20,
	IBV_RATE_400_GBPS = 21,
	IBV_RATE_600_GBPS = 22,
	IBV_RATE_800_GBPS = 23,
	IBV_RATE_1200_GBPS = 24,
};

/**
 * ibv_rate_to_mult - Convert the IB rate enum to a multiple of the
 * base rate of 2.5 Gbit/sec.  For example, IBV_RATE_5_GBPS will be
 * converted to 2, since 5 Gbit/sec is 2 * 2.5 Gbit/sec.
 * @rate: rate to convert.
 */
int  __attribute_const ibv_rate_to_mult(enum ibv_rate rate);

/**
 * mult_to_ibv_rate - Convert a multiple of 2.5 Gbit/sec to an IB rate enum.
 * @mult: multiple to convert.
 */
enum ibv_rate __attribute_const mult_to_ibv_rate(int mult);

/**
 * ibv_rate_to_mbps - Convert the IB rate enum to Mbit/sec.
 * For example, IBV_RATE_5_GBPS will return the value 5000.
 * @rate: rate to convert.
 */
int __attribute_const ibv_rate_to_mbps(enum ibv_rate rate);

/**
 * mbps_to_ibv_rate - Convert a Mbit/sec value to an IB rate enum.
 * @mbps: value to convert.
 */
enum ibv_rate __attribute_const mbps_to_ibv_rate(int mbps);

struct ibv_ah_attr {
	struct ibv_global_route	grh;
	uint16_t		dlid;
	uint8_t			sl;
	uint8_t			src_path_bits;
	uint8_t			static_rate;
	uint8_t			is_global;
	uint8_t			port_num;
};
enum ibv_qp_type {
	IBV_QPT_RC = 2,
	IBV_QPT_UC,
	IBV_QPT_UD,
	IBV_QPT_RAW_PACKET = 8,
	IBV_QPT_XRC_SEND = 9,
	IBV_QPT_XRC_RECV,
	IBV_QPT_DRIVER = 0xff,
};

struct ibv_qp_cap {
	uint32_t		max_send_wr;
	uint32_t		max_recv_wr;
	uint32_t		max_send_sge;
	uint32_t		max_recv_sge;
	uint32_t		max_inline_data;
};

struct ibv_qp_init_attr {
	void		       *qp_context;
	struct ibv_cq	       *send_cq;
	struct ibv_cq	       *recv_cq;
	struct ibv_srq	       *srq;
	struct ibv_qp_cap	cap;
	enum ibv_qp_type	qp_type;
	int			sq_sig_all;
};
enum ibv_qp_attr_mask {
	IBV_QP_STATE			= 1 << 	0,
	IBV_QP_CUR_STATE		= 1 << 	1,
	IBV_QP_EN_SQD_ASYNC_NOTIFY	= 1 << 	2,
	IBV_QP_ACCESS_FLAGS		= 1 << 	3,
	IBV_QP_PKEY_INDEX		= 1 << 	4,
	IBV_QP_PORT			= 1 << 	5,
	IBV_QP_QKEY			= 1 << 	6,
	IBV_QP_AV			= 1 << 	7,
	IBV_QP_PATH_MTU			= 1 << 	8,
	IBV_QP_TIMEOUT			= 1 << 	9,
	IBV_QP_RETRY_CNT		= 1 << 10,
	IBV_QP_RNR_RETRY		= 1 << 11,
	IBV_QP_RQ_PSN			= 1 << 12,
	IBV_QP_MAX_QP_RD_ATOMIC		= 1 << 13,
	IBV_QP_ALT_PATH			= 1 << 14,
	IBV_QP_MIN_RNR_TIMER		= 1 << 15,
	IBV_QP_SQ_PSN			= 1 << 16,
	IBV_QP_MAX_DEST_RD_ATOMIC	= 1 << 17,
	IBV_QP_PATH_MIG_STATE		= 1 << 18,
	IBV_QP_CAP			= 1 << 19,
	IBV_QP_DEST_QPN			= 1 << 20,
	/* These bits were supported on older kernels, but never exposed from
	   libibverbs:
	_IBV_QP_SMAC   			= 1 << 21,
	_IBV_QP_ALT_SMAC		= 1 << 22,
	_IBV_QP_VID    			= 1 << 23,
	_IBV_QP_ALT_VID 		= 1 << 24,
	*/
	IBV_QP_RATE_LIMIT		= 1 << 25,
};
enum ibv_qp_state {
	IBV_QPS_RESET,
	IBV_QPS_INIT,
	IBV_QPS_RTR,
	IBV_QPS_RTS,
	IBV_QPS_SQD,
	IBV_QPS_SQE,
	IBV_QPS_ERR,
	IBV_QPS_UNKNOWN
};

enum ibv_mig_state {
	IBV_MIG_MIGRATED,
	IBV_MIG_REARM,
	IBV_MIG_ARMED
};

struct ibv_qp_attr {
	enum ibv_qp_state	qp_state;
	enum ibv_qp_state	cur_qp_state;
	enum ibv_mtu		path_mtu;
	enum ibv_mig_state	path_mig_state;
	uint32_t		qkey;
	uint32_t		rq_psn;
	uint32_t		sq_psn;
	uint32_t		dest_qp_num;
	unsigned int		qp_access_flags;
	struct ibv_qp_cap	cap;
	struct ibv_ah_attr	ah_attr;
	struct ibv_ah_attr	alt_ah_attr;
	uint16_t		pkey_index;
	uint16_t		alt_pkey_index;
	uint8_t			en_sqd_async_notify;
	uint8_t			sq_draining;
	uint8_t			max_rd_atomic;
	uint8_t			max_dest_rd_atomic;
	uint8_t			min_rnr_timer;
	uint8_t			port_num;
	uint8_t			timeout;
	uint8_t			retry_cnt;
	uint8_t			rnr_retry;
	uint8_t			alt_port_num;
	uint8_t			alt_timeout;
	uint32_t		rate_limit;
};
enum ibv_wr_opcode {
	IBV_WR_RDMA_WRITE,
	IBV_WR_RDMA_WRITE_WITH_IMM,
	IBV_WR_SEND,
	IBV_WR_SEND_WITH_IMM,
	IBV_WR_RDMA_READ,
	IBV_WR_ATOMIC_CMP_AND_SWP,
	IBV_WR_ATOMIC_FETCH_AND_ADD,
	IBV_WR_LOCAL_INV,
	IBV_WR_BIND_MW,
	IBV_WR_SEND_WITH_INV,
	IBV_WR_TSO,
	IBV_WR_DRIVER1,
	IBV_WR_FLUSH = 14,
	IBV_WR_ATOMIC_WRITE = 15,
};

enum ibv_send_flags {
	IBV_SEND_FENCE		= 1 << 0,
	IBV_SEND_SIGNALED	= 1 << 1,
	IBV_SEND_SOLICITED	= 1 << 2,
	IBV_SEND_INLINE		= 1 << 3,
	IBV_SEND_IP_CSUM	= 1 << 4
};
struct ibv_sge {
	uint64_t		addr;
	uint32_t		length;
	uint32_t		lkey;
};

struct ibv_send_wr {
	uint64_t		wr_id;
	struct ibv_send_wr     *next;
	struct ibv_sge	       *sg_list;
	int			num_sge;
	enum ibv_wr_opcode	opcode;
	unsigned int		send_flags;
	/* When opcode is *_WITH_IMM: Immediate data in network byte order.
	 * When opcode is *_INV: Stores the rkey to invalidate
	 */
	union {
		uint32_t		imm_data;
		uint32_t		invalidate_rkey;
	};
	union {
		struct {
			uint64_t	remote_addr;
			uint32_t	rkey;
		} rdma;
		struct {
			uint64_t	remote_addr;
			uint64_t	compare_add;
			uint64_t	swap;
			uint32_t	rkey;
		} atomic;
		struct {
			struct ibv_ah  *ah;
			uint32_t	remote_qpn;
			uint32_t	remote_qkey;
		} ud;
	} wr;
	union {
		struct {
			uint32_t    remote_srqn;
		} xrc;
	} qp_type;
	union {
		struct {
			struct ibv_mw	*mw;
			uint32_t		rkey;
			struct ibv_mw_bind_info	bind_info;
		} bind_mw;
		struct {
			void		       *hdr;
			uint16_t		hdr_sz;
			uint16_t		mss;
		} tso;
	};
};

struct ibv_recv_wr {
	uint64_t		wr_id;
	struct ibv_recv_wr     *next;
	struct ibv_sge	       *sg_list;
	int			num_sge;
};

enum ibv_ops_wr_opcode {
	IBV_WR_TAG_ADD,
	IBV_WR_TAG_DEL,
	IBV_WR_TAG_SYNC,
};

enum ibv_ops_flags {
	IBV_OPS_SIGNALED = 1 << 0,
	IBV_OPS_TM_SYNC  = 1 << 1,
};

struct ibv_ops_wr {
	uint64_t				wr_id;
	struct ibv_ops_wr		       *next;
	enum ibv_ops_wr_opcode			opcode;
	int					flags;
	struct {
		uint32_t			unexpected_cnt;
		uint32_t			handle;
		struct {
			uint64_t		recv_wr_id;
			struct ibv_sge	       *sg_list;
			int			num_sge;
			uint64_t		tag;
			uint64_t		mask;
		} add;
	} tm;
};
struct ibv_qp {
	struct ibv_context     *context;
	void		       *qp_context;
	struct ibv_pd	       *pd;
	struct ibv_cq	       *send_cq;
	struct ibv_cq	       *recv_cq;
	struct ibv_srq	       *srq;
	uint32_t		handle;
	uint32_t		qp_num;
	enum ibv_qp_state       state;
	enum ibv_qp_type	qp_type;

	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
	uint32_t		events_completed;
};
struct ibv_comp_channel {
	struct ibv_context     *context;
	int			fd;
	int			refcnt;
};

struct ibv_cq {
	struct ibv_context     *context;
	struct ibv_comp_channel *channel;
	void		       *cq_context;
	uint32_t		handle;
	int			cqe;

	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
	uint32_t		comp_events_completed;
	uint32_t		async_events_completed;
};
struct ibv_device;
struct ibv_context;

/* Obsolete, never used, do not touch */
struct _ibv_device_ops {
	struct ibv_context *	(*_dummy1)(struct ibv_device *device, int cmd_fd);
	void			(*_dummy2)(struct ibv_context *context);
};

enum {
	IBV_SYSFS_NAME_MAX	= 64,
	IBV_SYSFS_PATH_MAX	= 256
};

struct ibv_device {
	struct _ibv_device_ops	_ops;
	enum ibv_node_type	node_type;
	enum ibv_transport_type	transport_type;
	/* Name of underlying kernel IB device, eg "mthca0" */
	char			name[IBV_SYSFS_NAME_MAX];
	/* Name of uverbs device, eg "uverbs0" */
	char			dev_name[IBV_SYSFS_NAME_MAX];
	/* Path to infiniband_verbs class device in sysfs */
	char			dev_path[IBV_SYSFS_PATH_MAX];
	/* Path to infiniband class device in sysfs */
	char			ibdev_path[IBV_SYSFS_PATH_MAX];
};

struct _compat_ibv_port_attr;
struct ibv_context_ops {
	int (*_compat_query_device)(struct ibv_context *context,
				    struct ibv_device_attr *device_attr);
	int (*_compat_query_port)(struct ibv_context *context,
				  uint8_t port_num,
				  struct _compat_ibv_port_attr *port_attr);
	void *(*_compat_alloc_pd)(void);
	void *(*_compat_dealloc_pd)(void);
	void *(*_compat_reg_mr)(void);
	void *(*_compat_rereg_mr)(void);
	void *(*_compat_dereg_mr)(void);
	struct ibv_mw *		(*alloc_mw)(struct ibv_pd *pd, enum ibv_mw_type type);
	int			(*bind_mw)(struct ibv_qp *qp, struct ibv_mw *mw,
					   struct ibv_mw_bind *mw_bind);
	int			(*dealloc_mw)(struct ibv_mw *mw);
	void *(*_compat_create_cq)(void);
	int			(*poll_cq)(struct ibv_cq *cq, int num_entries, struct ibv_wc *wc);
	int			(*req_notify_cq)(struct ibv_cq *cq, int solicited_only);
	void *(*_compat_cq_event)(void);
	void *(*_compat_resize_cq)(void);
	void *(*_compat_destroy_cq)(void);
	void *(*_compat_create_srq)(void);
	void *(*_compat_modify_srq)(void);
	void *(*_compat_query_srq)(void);
	void *(*_compat_destroy_srq)(void);
	int			(*post_srq_recv)(struct ibv_srq *srq,
						 struct ibv_recv_wr *recv_wr,
						 struct ibv_recv_wr **bad_recv_wr);
	void *(*_compat_create_qp)(void);
	void *(*_compat_query_qp)(void);
	void *(*_compat_modify_qp)(void);
	void *(*_compat_destroy_qp)(void);
	int			(*post_send)(struct ibv_qp *qp, struct ibv_send_wr *wr,
					     struct ibv_send_wr **bad_wr);
	int			(*post_recv)(struct ibv_qp *qp, struct ibv_recv_wr *wr,
					     struct ibv_recv_wr **bad_wr);
	void *(*_compat_create_ah)(void);
	void *(*_compat_destroy_ah)(void);
	void *(*_compat_attach_mcast)(void);
	void *(*_compat_detach_mcast)(void);
	void *(*_compat_async_event)(void);
};

struct ibv_context {
	struct ibv_device      *device;
	struct ibv_context_ops	ops;
	int			cmd_fd;
	int			async_fd;
	int			num_comp_vectors;
	pthread_mutex_t		mutex;
	void		       *abi_compat;
};
struct verbs_context {
	/*  "grows up" - new fields go here */
	int (*query_port)(struct ibv_context *context, uint8_t port_num,
			  struct ibv_port_attr *port_attr,
			  size_t port_attr_len);
	int (*advise_mr)(struct ibv_pd *pd,
			 enum ibv_advise_mr_advice advice,
			 uint32_t flags,
			 struct ibv_sge *sg_list,
			 uint32_t num_sges);
	struct ibv_mr *(*alloc_null_mr)(struct ibv_pd *pd);
	int (*read_counters)(struct ibv_counters *counters,
			     uint64_t *counters_value,
			     uint32_t ncounters,
			     uint32_t flags);
	int (*attach_counters_point_flow)(struct ibv_counters *counters,
					  struct ibv_counter_attach_attr *attr,
					  struct ibv_flow *flow);
	struct ibv_counters *(*create_counters)(struct ibv_context *context,
						struct ibv_counters_init_attr *init_attr);
	int (*destroy_counters)(struct ibv_counters *counters);
	struct ibv_mr *(*reg_dm_mr)(struct ibv_pd *pd, struct ibv_dm *dm,
				    uint64_t dm_offset, size_t length,
				    unsigned int access);
	struct ibv_dm *(*alloc_dm)(struct ibv_context *context,
				   struct ibv_alloc_dm_attr *attr);
	int (*free_dm)(struct ibv_dm *dm);
	int (*modify_flow_action_esp)(struct ibv_flow_action *action,
				      struct ibv_flow_action_esp_attr *attr);
	int (*destroy_flow_action)(struct ibv_flow_action *action);
	struct ibv_flow_action *(*create_flow_action_esp)(struct ibv_context *context,
							  struct ibv_flow_action_esp_attr *attr);
	int (*modify_qp_rate_limit)(struct ibv_qp *qp,
				    struct ibv_qp_rate_limit_attr *attr);
	struct ibv_pd *(*alloc_parent_domain)(struct ibv_context *context,
					      struct ibv_parent_domain_init_attr *attr);
	int (*dealloc_td)(struct ibv_td *td);
	struct ibv_td *(*alloc_td)(struct ibv_context *context, struct ibv_td_init_attr *init_attr);
	int (*modify_cq)(struct ibv_cq *cq, struct ibv_modify_cq_attr *attr);
	int (*post_srq_ops)(struct ibv_srq *srq,
			    struct ibv_ops_wr *op,
			    struct ibv_ops_wr **bad_op);
	int (*destroy_rwq_ind_table)(struct ibv_rwq_ind_table *rwq_ind_table);
	struct ibv_rwq_ind_table *(*create_rwq_ind_table)(struct ibv_context *context,
							  struct ibv_rwq_ind_table_init_attr *init_attr);
	int (*destroy_wq)(struct ibv_wq *wq);
	int (*modify_wq)(struct ibv_wq *wq, struct ibv_wq_attr *wq_attr);
	struct ibv_wq * (*create_wq)(struct ibv_context *context,
				     struct ibv_wq_init_attr *wq_init_attr);
	int (*query_rt_values)(struct ibv_context *context,
			       struct ibv_values_ex *values);
	struct ibv_cq_ex *(*create_cq_ex)(struct ibv_context *context,
					  struct ibv_cq_init_attr_ex *init_attr);
	struct verbs_ex_private *priv;
	int (*query_device_ex)(struct ibv_context *context,
			       const struct ibv_query_device_ex_input *input,
			       struct ibv_device_attr_ex *attr,
			       size_t attr_size);
	int (*ibv_destroy_flow) (struct ibv_flow *flow);
	void (*ABI_placeholder2) (void); /* DO NOT COPY THIS GARBAGE */
	struct ibv_flow * (*ibv_create_flow) (struct ibv_qp *qp,
					      struct ibv_flow_attr *flow_attr);
	void (*ABI_placeholder1) (void); /* DO NOT COPY THIS GARBAGE */
	struct ibv_qp *(*open_qp)(struct ibv_context *context,
			struct ibv_qp_open_attr *attr);
	struct ibv_qp *(*create_qp_ex)(struct ibv_context *context,
			struct ibv_qp_init_attr_ex *qp_init_attr_ex);
	int (*get_srq_num)(struct ibv_srq *srq, uint32_t *srq_num);
	struct ibv_srq *	(*create_srq_ex)(struct ibv_context *context,
						 struct ibv_srq_init_attr_ex *srq_init_attr_ex);
	struct ibv_xrcd *	(*open_xrcd)(struct ibv_context *context,
					     struct ibv_xrcd_init_attr *xrcd_init_attr);
	int			(*close_xrcd)(struct ibv_xrcd *xrcd);
	uint64_t _ABI_placeholder3;
	size_t   sz;			/* Must be immediately before struct ibv_context */
	struct ibv_context context;	/* Must be last field in the struct */
};

static inline struct verbs_context *verbs_get_ctx(struct ibv_context *ctx)
{
	if (ctx->abi_compat != __VERBS_ABI_IS_EXTENDED)
		return NULL;

	/* open code container_of to not pollute the global namespace */
	return (struct verbs_context *)(((uint8_t *)ctx) -
					offsetof(struct verbs_context,
						 context));
}

#define verbs_get_ctx_op(ctx, op) ({ \
	struct verbs_context *__vctx = verbs_get_ctx(ctx); \
	(!__vctx || (__vctx->sz < sizeof(*__vctx) - offsetof(struct verbs_context, op)) || \
	 !__vctx->op) ? NULL : __vctx; })

/**
 * ibv_get_device_list - Get list of IB devices currently available
 * @num_devices: optional.  if non-NULL, set to the number of devices
 * returned in the array.
 *
 * Return a NULL-terminated array of IB devices.  The array can be
 * released with ibv_free_device_list().
 */
struct ibv_device **ibv_get_device_list(int *num_devices);
/**
 * ibv_free_device_list - Free list from ibv_get_device_list()
 *
 * Free an array of devices returned from ibv_get_device_list().  Once
 * the array is freed, pointers to devices that were not opened with
 * ibv_open_device() are no longer valid.  Client code must open all
 * devices it intends to use before calling ibv_free_device_list().
 */
void ibv_free_device_list(struct ibv_device **list);

/**
 * ibv_get_device_name - Return kernel device name
 */
const char *ibv_get_device_name(struct ibv_device *device);

/**
 * ibv_get_device_index - Return kernel device index
 *
 * Available for the kernel with support of IB device query
 * over netlink interface. For the unsupported kernels, the
 * relevant -1 will be returned.
 */
int ibv_get_device_index(struct ibv_device *device);

/**
 * ibv_get_device_guid - Return device's node GUID
 */
uint64_t ibv_get_device_guid(struct ibv_device *device);

/**
 * ibv_open_device - Initialize device for use
 */
struct ibv_context *ibv_open_device(struct ibv_device *device);

/**
 * ibv_close_device - Release device
 */
int ibv_close_device(struct ibv_context *context);

/**
 * ibv_query_device - Get device properties
 */
int ibv_query_device(struct ibv_context *context,
		     struct ibv_device_attr *device_attr);

/**
 * ibv_query_port - Get port properties
 */
int ibv_query_port(struct ibv_context *context, uint8_t port_num,
		   struct _compat_ibv_port_attr *port_attr);

static inline int ___ibv_query_port(struct ibv_context *context,
				    uint8_t port_num,
				    struct ibv_port_attr *port_attr)
{
	struct verbs_context *vctx = verbs_get_ctx_op(context, query_port);

	if (!vctx) {
		int rc;

		memset(port_attr, 0, sizeof(*port_attr));

		rc = ibv_query_port(context, port_num,
				    (struct _compat_ibv_port_attr *)port_attr);
		return rc;
	}

	return vctx->query_port(context, port_num, port_attr,
				sizeof(*port_attr));
}

#define ibv_query_port(context, port_num, port_attr) \
	___ibv_query_port(context, port_num, port_attr)

/**
 * ibv_query_gid - Get a GID table entry
 */
int ibv_query_gid(struct ibv_context *context, uint8_t port_num,
		  int index, union ibv_gid *gid);

int _ibv_query_gid_ex(struct ibv_context *context, uint32_t port_num,
		     uint32_t gid_index, struct ibv_gid_entry *entry,
		     uint32_t flags, size_t entry_size);

/**
 * ibv_query_gid_ex - Read a GID table entry
 */
static inline int ibv_query_gid_ex(struct ibv_context *context,
				   uint32_t port_num, uint32_t gid_index,
				   struct ibv_gid_entry *entry, uint32_t flags)
{
	return _ibv_query_gid_ex(context, port_num, gid_index, entry, flags,
				 sizeof(*entry));
}

ssize_t _ibv_query_gid_table(struct ibv_context *context,
			     struct ibv_gid_entry *entries, size_t max_entries,
			     uint32_t flags, size_t entry_size);

/*
 * ibv_query_gid_table - Get all valid GID table entries
 */
static inline ssize_t ibv_query_gid_table(struct ibv_context *context,
					  struct ibv_gid_entry *entries,
					  size_t max_entries, uint32_t flags)
{
	return _ibv_query_gid_table(context, entries, max_entries, flags,
				    sizeof(*entries));
}

/**
 * ibv_query_pkey - Get a P_Key table entry
 */
int ibv_query_pkey(struct ibv_context *context, uint8_t port_num,
		   int index, uint16_t *pkey);

/**
 * ibv_get_pkey_index - Translate a P_Key into a P_Key index
 */
int ibv_get_pkey_index(struct ibv_context *context, uint8_t port_num,
		       uint16_t pkey);

/**
 * ibv_alloc_pd - Allocate a protection domain
 */
struct ibv_pd *ibv_alloc_pd(struct ibv_context *context);

/**
 * ibv_dealloc_pd - Free a protection domain
 */
int ibv_dealloc_pd(struct ibv_pd *pd);
/**
 * ibv_reg_mr_iova2 - Register memory region with a virtual offset address
 *
 * This version will be called if ibv_reg_mr or ibv_reg_mr_iova were called
 * with at least one potential access flag from the IBV_OPTIONAL_ACCESS_RANGE
 * flags range The optional access flags will be masked if running over kernel
 * that does not support passing them.
 */
struct ibv_mr *ibv_reg_mr_iova2(struct ibv_pd *pd, void *addr, size_t length,
				uint64_t iova, unsigned int access);
/**
 * ibv_reg_mr - Register a memory region
 */
struct ibv_mr *ibv_reg_mr(struct ibv_pd *pd, void *addr, size_t length,
			  int access);
/* use new ibv_reg_mr version only if access flags that require it are used */
__attribute__((__always_inline__)) static inline struct ibv_mr *
__ibv_reg_mr(struct ibv_pd *pd, void *addr, size_t length, unsigned int access,
	     int is_access_const)
{
	if (is_access_const && (access & IBV_ACCESS_OPTIONAL_RANGE) == 0)
		return ibv_reg_mr(pd, addr, length, (int)access);
	else
		return ibv_reg_mr_iova2(pd, addr, length, (uintptr_t)addr,
					access);
}

#define ibv_reg_mr(pd, addr, length, access)                                   \
	__ibv_reg_mr(pd, addr, length, access,                                 \
		     __builtin_constant_p(				       \
			     ((int)(access) & IBV_ACCESS_OPTIONAL_RANGE) == 0))
/**
 * ibv_dereg_mr - Deregister a memory region
 */
int ibv_dereg_mr(struct ibv_mr *mr);
/**
 * ibv_create_comp_channel - Create a completion event channel
 */
struct ibv_comp_channel *ibv_create_comp_channel(struct ibv_context *context);

/**
 * ibv_destroy_comp_channel - Destroy a completion event channel
 */
int ibv_destroy_comp_channel(struct ibv_comp_channel *channel);


/**
 * ibv_create_cq - Create a completion queue
 * @context - Context CQ will be attached to
 * @cqe - Minimum number of entries required for CQ
 * @cq_context - Consumer-supplied context returned for completion events
 * @channel - Completion channel where completion events will be queued.
 *     May be NULL if completion events will not be used.
 * @comp_vector - Completion vector used to signal completion events.
 *     Must be >= 0 and < context->num_comp_vectors.
 */
struct ibv_cq *ibv_create_cq(struct ibv_context *context, int cqe,
			     void *cq_context,
			     struct ibv_comp_channel *channel,
			     int comp_vector);
/**
 * ibv_resize_cq - Modifies the capacity of the CQ.
 * @cq: The CQ to resize.
 * @cqe: The minimum size of the CQ.
 *
 * Users can examine the cq structure to determine the actual CQ size.
 */
int ibv_resize_cq(struct ibv_cq *cq, int cqe);

/**
 * ibv_destroy_cq - Destroy a completion queue
 */
int ibv_destroy_cq(struct ibv_cq *cq);

/**
 * ibv_get_cq_event - Read next CQ event
 * @channel: Channel to get next event from.
 * @cq: Used to return pointer to CQ.
 * @cq_context: Used to return consumer-supplied CQ context.
 *
 * All completion events returned by ibv_get_cq_event() must
 * eventually be acknowledged with ibv_ack_cq_events().
 */
int ibv_get_cq_event(struct ibv_comp_channel *channel,
		     struct ibv_cq **cq, void **cq_context);

/**
 * ibv_ack_cq_events - Acknowledge CQ completion events
 * @cq: CQ to acknowledge events for
 * @nevents: Number of events to acknowledge.
 *
 * All completion events which are returned by ibv_get_cq_event() must
 * be acknowledged.  To avoid races, ibv_destroy_cq() will wait for
 * all completion events to be acknowledged, so there should be a
 * one-to-one correspondence between acks and successful gets.  An
 * application may accumulate multiple completion events and
 * acknowledge them in a single call to ibv_ack_cq_events() by passing
 * the number of events to ack in @nevents.
 */
void ibv_ack_cq_events(struct ibv_cq *cq, unsigned int nevents);

/**
 * ibv_poll_cq - Poll a CQ for work completions
 * @cq:the CQ being polled
 * @num_entries:maximum number of completions to return
 * @wc:array of at least @num_entries of &struct ibv_wc where completions
 *   will be returned
 *
 * Poll a CQ for (possibly multiple) completions.  If the return value
 * is < 0, an error occurred.  If the return value is >= 0, it is the
 * number of completions returned.  If the return value is
 * non-negative and strictly less than num_entries, then the CQ was
 * emptied.
 */
static inline int ibv_poll_cq(struct ibv_cq *cq, int num_entries, struct ibv_wc *wc)
{
	return cq->context->ops.poll_cq(cq, num_entries, wc);
}

/**
 * ibv_req_notify_cq - Request completion notification on a CQ.  An
 *   event will be added to the completion channel associated with the
 *   CQ when an entry is added to the CQ.
 * @cq: The completion queue to request notification for.
 * @solicited_only: If non-zero, an event will be generated only for
 *   the next solicited CQ entry.  If zero, any CQ entry, solicited or
 *   not, will generate an event.
 */
static inline int ibv_req_notify_cq(struct ibv_cq *cq, int solicited_only)
{
	return cq->context->ops.req_notify_cq(cq, solicited_only);
}

static inline int ibv_modify_cq(struct ibv_cq *cq, struct ibv_modify_cq_attr *attr)
{
	struct verbs_context *vctx = verbs_get_ctx_op(cq->context, modify_cq);

	if (!vctx)
		return EOPNOTSUPP;

	return vctx->modify_cq(cq, attr);
}
/**
 * ibv_create_qp - Create a queue pair.
 */
struct ibv_qp *ibv_create_qp(struct ibv_pd *pd,
			     struct ibv_qp_init_attr *qp_init_attr);
/**
 * ibv_query_device_ex - Get extended device properties
 */
static inline int
ibv_query_device_ex(struct ibv_context *context,
		    const struct ibv_query_device_ex_input *input,
		    struct ibv_device_attr_ex *attr)
{
	struct verbs_context *vctx;
	int ret;

	if (input && input->comp_mask)
		return EINVAL;

	vctx = verbs_get_ctx_op(context, query_device_ex);
	if (!vctx)
		goto legacy;

	ret = vctx->query_device_ex(context, input, attr, sizeof(*attr));
	if (ret == EOPNOTSUPP || ret == ENOSYS)
		goto legacy;

	return ret;

legacy:
	memset(attr, 0, sizeof(*attr));
	ret = ibv_query_device(context, &attr->orig_attr);

	return ret;
}
/**
 * ibv_modify_qp - Modify a queue pair.
 */
int ibv_modify_qp(struct ibv_qp *qp, struct ibv_qp_attr *attr,
		  int attr_mask);
/**
 * ibv_query_qp - Returns the attribute list and current values for the
 *   specified QP.
 * @qp: The QP to query.
 * @attr: The attributes of the specified QP.
 * @attr_mask: A bit-mask used to select specific attributes to query.
 * @init_attr: Additional attributes of the selected QP.
 *
 * The qp_attr_mask may be used to limit the query to gathering only the
 * selected attributes.
 */
int ibv_query_qp(struct ibv_qp *qp, struct ibv_qp_attr *attr,
		 int attr_mask,
		 struct ibv_qp_init_attr *init_attr);

/**
 * ibv_destroy_qp - Destroy a queue pair.
 */
int ibv_destroy_qp(struct ibv_qp *qp);
/**
 * ibv_post_send - Post a list of work requests to a send queue.
 *
 * If IBV_SEND_INLINE flag is set, the data buffers can be reused
 * immediately after the call returns.
 */
static inline int ibv_post_send(struct ibv_qp *qp, struct ibv_send_wr *wr,
				struct ibv_send_wr **bad_wr)
{
	return qp->context->ops.post_send(qp, wr, bad_wr);
}

/**
 * ibv_post_recv - Post a list of work requests to a receive queue.
 */
static inline int ibv_post_recv(struct ibv_qp *qp, struct ibv_recv_wr *wr,
				struct ibv_recv_wr **bad_wr)
{
	return qp->context->ops.post_recv(qp, wr, bad_wr);
}

/**
 * ibv_create_ah - Create an address handle.
 */
struct ibv_ah *ibv_create_ah(struct ibv_pd *pd, struct ibv_ah_attr *attr);

/**
 * ibv_init_ah_from_wc - Initializes address handle attributes from a
 *   work completion.
 * @context: Device context on which the received message arrived.
 * @port_num: Port on which the received message arrived.
 * @wc: Work completion associated with the received message.
 * @grh: References the received global route header.  This parameter is
 *   ignored unless the work completion indicates that the GRH is valid.
 * @ah_attr: Returned attributes that can be used when creating an address
 *   handle for replying to the message.
 */
int ibv_init_ah_from_wc(struct ibv_context *context, uint8_t port_num,
			struct ibv_wc *wc, struct ibv_grh *grh,
			struct ibv_ah_attr *ah_attr);

/**
 * ibv_create_ah_from_wc - Creates an address handle associated with the
 *   sender of the specified work completion.
 * @pd: The protection domain associated with the address handle.
 * @wc: Work completion information associated with a received message.
 * @grh: References the received global route header.  This parameter is
 *   ignored unless the work completion indicates that the GRH is valid.
 * @port_num: The outbound port number to associate with the address.
 *
 * The address handle is used to reference a local or global destination
 * in all UD QP post sends.
 */
struct ibv_ah *ibv_create_ah_from_wc(struct ibv_pd *pd, struct ibv_wc *wc,
				     struct ibv_grh *grh, uint8_t port_num);

/**
 * ibv_destroy_ah - Destroy an address handle.
 */
int ibv_destroy_ah(struct ibv_ah *ah);


/**
 * ibv_node_type_str - Return string describing node_type enum value
 */
const char *ibv_node_type_str(enum ibv_node_type node_type);

/**
 * ibv_port_state_str - Return string describing port_state enum value
 */
const char *ibv_port_state_str(enum ibv_port_state port_state);

static inline int ibv_is_qpt_supported(uint32_t caps, enum ibv_qp_type qpt)
{
	return !!(caps & (1 << qpt));
}


#ifdef __cplusplus
}
#endif

#  undef __attribute_const


#endif /* INFINIBAND_VERBS_H */
