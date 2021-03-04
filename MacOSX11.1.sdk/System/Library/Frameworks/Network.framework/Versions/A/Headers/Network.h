//
//  Network.h
//  Network
//
//  Copyright (c) 2014-2020 Apple Inc. All rights reserved.
//

#ifndef __NW_H__
#define __NW_H__

#ifndef __NW_INDIRECT__
#define __NW_INDIRECT__
#define __NW_SET_INDIRECT__
#endif // __NW_INDIRECT__

#include <Network/advertise_descriptor.h>
#include <Network/browser.h>
#include <Network/browse_result.h>
#include <Network/browse_descriptor.h>
#include <Network/connection.h>
#include <Network/connection_group.h>
#include <Network/connection_report.h>
#include <Network/content_context.h>
#include <Network/endpoint.h>
#include <Network/ethernet_channel.h>
#include <Network/framer_options.h>
#include <Network/group_descriptor.h>
#include <Network/interface.h>
#include <Network/ip_options.h>
#include <Network/listener.h>
#include <Network/error.h>
#include <Network/parameters.h>
#include <Network/path_monitor.h>
#include <Network/path.h>
#include <Network/privacy_context.h>
#include <Network/protocol_options.h>
#include <Network/resolver_config.h>
#include <Network/tcp_options.h>
#include <Network/tls_options.h>
#include <Network/txt_record.h>
#include <Network/udp_options.h>
#include <Network/ws_options.h>

#ifdef __NW_SET_INDIRECT__
#undef __NW_INDIRECT__
#endif // __NW_SET_INDIRECT__

#endif // __NW_H__
