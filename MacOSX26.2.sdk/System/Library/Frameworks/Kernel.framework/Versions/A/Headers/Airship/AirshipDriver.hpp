//
//  AirshipDriver.hpp
//  Airship
//
//  Created by Jason McElrath on 2/3/23.
//

#ifndef airship__KernelFramework__AirshipDriver_hpp
#define airship__KernelFramework__AirshipDriver_hpp

#include <Airship/Airship.h>
#include <IOKit/IOInterruptEventSource.h>
#include <IOKit/IOLocks.h>
#include <IOKit/IOService.h>
#include <IOKit/IOTimerEventSource.h>

class AirshipDriver;
class AirshipDevice;

enum AirshipDriverPowerState
{
    kAirshipDriverPowerStateOff = 0,
    kAirshipDriverPowerStateLpw = 1,
    kAirshipDriverPowerStateOn = 2,
    kAirshipDriverNumPowerStates = 3,
};

using AirshipDriverErrorHandler = void (^)(AirshipDriver *driver, uint32_t driverErrors, uint32_t errorDetail);
using AirshipDriverErrorHandlerV2 = void (^)(AirshipDriver *driver, const OSString *errorDesc, uint32_t arg0, uint32_t arg1);
using AirshipDriverFatalErrorHandler = void (^)(AirshipDriver *driver, const OSString *fatalErrorDesc);
using AirshipDriverExecStageChangeHandler = void (^)(AirshipDriver *driver, uint32_t execStage);

struct AirshipDriver_IVars;
class AIRSHIP_EXPORT_CLASS AirshipDriver: public IOService
{
    OSDeclareDefaultStructors(AirshipDriver);

public:
    virtual bool init(OSDictionary *properties = nullptr) override;
    virtual void free() override;
    virtual bool start(IOService *provider) override;
    virtual void stop(IOService *provider) override;
    virtual IOReturn setPowerState(unsigned long powerStateOrdinal, IOService *whatDevice) override;
    virtual IOReturn newUserClient(task_t owningTask, void *securityID, UInt32 type, OSDictionary *properties, IOUserClient **handler) override;

    void devicePowerStateChanged(AirshipDevice *device);

    void enterReset();
    void exitReset();

    void setErrorHandler(AirshipDriverErrorHandler handler);
    void setErrorHandler(AirshipDriverErrorHandlerV2 handler);
    void setFatalErrorHandler(AirshipDriverFatalErrorHandler handler);
    OSSharedPtr<const OSString> getErrorState(uint32_t *outArg0, uint32_t *outArg1) const;

    void setExecStageChangeHandler(AirshipDriverExecStageChangeHandler handler);
    uint32_t getExecStage() const;

    airship_driver_t getDriver() const;
    OSSharedPtr<IOWorkLoop> getQueue(const char *name) const;

    uint32_t getDriverNominalStateDumpSize() const;
    uint32_t retrieveDriverStateDumpInfo(uint8_t *buffer, uint32_t max_length) const;
    void appendDriverStateDump(void *session_ptr) const;

    void dumpDriverDebugLogs(bool device_access);

private:
    void finishExitResetIfNeeded();

    bool deviceMatched(void *refCon, IOService *newService, IONotifier *notifier);
    void attachToPendingDeviceIfNeeded();
    void detachFromDevice();
    void requestDevicePower(bool request);
    void handlePendingDevicePowerOffIfNeeded();

    void setPowerVote(uint32_t vote);
    void clearPowerVote(uint32_t vote);
    void setPowerClamp(uint32_t clamp);
    void clearPowerClamp(uint32_t clamp);
    void recomputePowerRequest();

    void setTransportBlocker(uint32_t blockers);
    void clearTransportBlocker(uint32_t blockers);

    bool isDevicePowerStateValidForDriverPowerState(unsigned long powerStateOrdinal) const;
    bool isIpcPowerStateValidForDriverPowerState(unsigned long powerStateOrdinal) const;

    void ipcCalloutOccurred();
    void setIpcPowerStateCalloutEnabled(bool enable);

    void updateTimerSchedule();
    void timerExpired();
    void startTimer(uint64_t *field, uint32_t intervalMs);
    void cancelTimer(uint64_t *field);

    void errorOccurred(airship_driver_error_t error);
    void fatalErrorOccurred(OSString *fatalError);
    OSSharedPtr<const OSString> getErrorDescription(uint32_t driverError, uint32_t ipcError) const;

    static OSSharedPtr<const OSString> swizzleConfigName(const OSString *configName);
    void saveConfigDetails(const OSString *configName, const OSString *ipcProtocol);
    void initDriverIOServiceParams(const OSDictionary *ipcConfig);

    static OSSharedPtr<IOWorkLoop> getGlobalWorkloop(const OSSymbol *name);

private:
    static IOPMPowerState _powerStates[];
    AirshipDriver_IVars *ivars;
};

#endif /* airship__KernelFramework__AirshipDriver_hpp */
