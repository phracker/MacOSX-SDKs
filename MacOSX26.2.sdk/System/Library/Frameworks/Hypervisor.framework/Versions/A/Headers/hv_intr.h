//
//  hv_intr.h
//  Hypervisor
//
//  Copyright © 2021-2023 Apple Inc. All rights reserved.
//

#ifndef __HYPERVISOR_HV_INTR__
#define __HYPERVISOR_HV_INTR__

#include <Hypervisor/hv_base.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

enum hv_boot_state : uint32_t {
    HV_BS_INIT = 0,
    HV_BS_SIPI = 1,
    HV_BS_RUNNING = 2,
} __OS_ENUM_ATTR_CLOSED;

/* - local apic - */

struct hv_apic_state {
    uint64_t apic_gpa;
    uint64_t apic_controls;
    uint64_t tsc_deadline;
    uint32_t apic_id;
    uint32_t ver;
    uint32_t tpr;
    uint32_t apr;
    uint32_t ldr;
    uint32_t dfr;
    uint32_t svr;
    uint32_t isr[8];
    uint32_t tmr[8];
    uint32_t irr[8];
    uint32_t esr;
    uint32_t lvt[7];
    uint32_t icr[2];
    uint32_t icr_timer;
    uint32_t dcr_timer;
    uint32_t ccr_timer;
    uint32_t esr_pending;
    enum hv_boot_state boot_state;
    uint32_t aeoi[8];
};

#define HV_APIC_STATE_EXT_VER        (100)

typedef struct {
    uint32_t version;
    struct hv_apic_state state;
} hv_apic_state_ext_t;

/* - atpic - */

struct hv_atpic_state {
    bool    ready;
    uint8_t    icw_num;
    uint8_t    rd_cmd_reg;
    bool    aeoi;            /* auto-eoi */
    bool    poll;
    bool    rotate;            /* rotate on auto-eoi */
    bool    sfn;            /* special fully-nested mode */
    uint8_t    irq_base;
    uint8_t    request;        /* Interrupt Request Register (IRR) */
    uint8_t    service;        /* Interrupt Service (ISR) */
    uint8_t    mask;            /* Interrupt Mask Register (IMR) */
    bool    smm;            /* special mask mode */
    uint8_t last_request;    /* edge detect */
    uint8_t    lowprio;        /* lowest priority irq */
    bool    intr_raised;
    uint8_t elc;
};

#define HV_ATPIC_STATE_EXT_VER        (100)

typedef struct {
    uint32_t version;
    struct hv_atpic_state state;
} hv_atpic_state_ext_t;

/* - ioapic - */

struct hv_ioapic_state {
    uint64_t rtbl[32];
    uint32_t irr;
    uint32_t ioa_id;
    uint32_t ioregsel;
};

#define HV_IOAPIC_STATE_EXT_VER        (100)

typedef struct {
    uint32_t version;
    struct hv_ioapic_state state;
} hv_ioapic_state_ext_t;

__END_DECLS

OS_ASSUME_NONNULL_END

#endif /* __HYPERVISOR_HV_INTR__ */
