//
//  EXDisplayPipeTypes.h
//  EXDisplayPipeDriver
//
//  Created by Clement Moussu on 2/14/23.
//

#include <stdint.h>
#include <stdbool.h>

#pragma once

#define ENABLE_EXCLAVE_REG_INTERRUPTS 1
#define EXDISPLAY_PIPE_TIMER_PERIOD_MS 8

#define EXDISP_COMPANION_TELEMETRY_TIMER_PERIOD_MS (24 * 60 * 60 * 1000)

#define EXDISP_USE_COMPANION_KEXT_TIMER 0

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum {
    INDICATOR_CAM = 0,
    INDICATOR_MIC = 1,
    INDICATOR_MIC_ALT_ACCESSIBILITY = 2,
    INDICATOR_CAM_ALT_FACEID = 3,
    INDICATOR_CAM_ALT_FACEID_DELAYED = 4,
    INDICATOR_COUNT
} EXDisplayPipeIndicator;

#define EXDISP_SCL_REGION_COUNT 4

#define CANCELLED_QUEUE_MAX_LENGTH 10
#define DROPPED_QUEUE_MAX_LENGTH 10
#define SECURE_TE_INFO_MAX_LENGTH 10

typedef struct
{
    uint16_t x;
    uint16_t y;
    float alpha;
} EXDisplayPipeIndicatorParams;

typedef struct
{
    uint64_t timestamp;
    bool health;
} EXDisplayPipeHealthRecord;

typedef struct
{
    EXDisplayPipeHealthRecord sca_driver_health;
    EXDisplayPipeHealthRecord sca_algorithm_health;
    EXDisplayPipeHealthRecord scl_health;
    EXDisplayPipeHealthRecord pipe_health;
    EXDisplayPipeHealthRecord link_health;
    bool health;
} EXDisplayPipeHealthReport;

typedef struct
{
    uint64_t displayedSwapID;
    bool validDisplayedID;
    bool poweredOn;
    struct
    {
        EXDisplayPipeIndicator indicator;
        uint16_t x;
        uint16_t y;
        uint16_t w;
        uint16_t h;
        float alpha;
        bool enabled;
        bool populated;
    } indicators[EXDISP_SCL_REGION_COUNT];
    EXDisplayPipeHealthReport health_report;
    uint64_t cancelledQueue[CANCELLED_QUEUE_MAX_LENGTH];
    uint64_t droppedQueue[DROPPED_QUEUE_MAX_LENGTH];
    uint8_t cancelledCount;
    uint8_t droppedCount;
} EXDisplayPipeStatus;

typedef struct
{
    EXDisplayPipeHealthRecord healthRecord;
    uint64_t errorCount;
    uint64_t lastErrorTimestamp;
    uint64_t maxConsecutiveErrors;
    uint64_t lastErrorVal;
    bool enabled;
    struct {
        uint64_t prevTimebase;
        uint64_t prevTimestamp;
        uint64_t currTimebase;
        uint64_t currTimestamp;
        uint64_t timeDiff;
        uint64_t timebaseDiff;
    } errorInfo[SECURE_TE_INFO_MAX_LENGTH];
    int errorInfoCount;
} EXDisplayPipeSecureTEStatus;

typedef struct
{
    uint64_t globalhealth;
    uint64_t scldriver;
    uint64_t scadriver;
    uint64_t scaalgorithm;
    uint64_t pipe;
    uint64_t link;
    uint64_t brightness;
    uint64_t tconcrc;
    uint64_t tconhealth;
    uint64_t tconhpd;
    uint64_t dcptransporthealth;
    uint64_t silhealth;
    uint64_t periodicHealthCheck;
    uint64_t hwlinkfailures;
    uint64_t nonauthenticpanel;
    // new stats information
    uint64_t sclDriverFailureTime;
    uint64_t scaDriverFailureTime;
    uint64_t scaAlgorithmFailureTime;
    uint64_t pipeFailureTime;
    uint64_t linkFailureTime;
    uint64_t globalHealthFailureTime;
    uint64_t hwlinkfailuresFailureTime;
    uint64_t silHealthFailureTime;
    uint64_t brightnessFailureTime;
    uint64_t tconCrcFailureTime;
    uint64_t tconHealthFailureTime;
    uint64_t tconHpdFailureTime;
    uint64_t dcpTransportHealthFailureTime;
    uint64_t nonauthenticpanelFailureTime;

    uint64_t scaFailuresBeyondThresh;
    uint64_t crcFailuresBeyondThresh;

    // Chillpill (cp) counters
    uint64_t globalHealthCp;
    uint64_t sclDriverCp;
    uint64_t scaDriverCp;
    uint64_t scaAlgorithmCp;
    uint64_t pipeCp;
    uint64_t linkCp;
    uint64_t brightnessCp;
    uint64_t tconCrcCp;
    uint64_t tconHealthCp;
    uint64_t tconHpdCp;
    uint64_t dcpTransportHealthCp;
    uint64_t silHealthCp;
    uint64_t hwlinkfailuresCp;
    uint64_t nonauthenticpanelCp;

    // Average variance counters
    uint64_t averageSCAVariance;
    uint64_t averageCRCVariance;
} EXDisplayPipeHealthStats;

// kEXBrightMessageFunction API
// callPlatformFunction( kEXBrightMessageFunction, false,
//                       param1 = msgSize (size_t *),
//                       param2 = msg (EXBrightMessage *),
//                       nullptr, nullptr )
#define kEXBrightMessageFunction "EXBrightMessageFunction"

typedef enum
{
    kLoadALSSCalibration = 0
} EXBrightMessageType;


typedef struct
{
    EXBrightMessageType type;
    uint32_t arg0;
    uint32_t arg1;
} EXBrightMessage;

#ifdef __cplusplus
}
#endif
