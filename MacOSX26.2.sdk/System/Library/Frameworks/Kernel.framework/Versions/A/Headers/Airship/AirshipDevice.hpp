//
//  AirshipDevice.hpp
//  Airship
//
//  Created by Jason McElrath on 2/3/23.
//

#ifndef airship__KernelFramework__AirshipDevice_hpp
#define airship__KernelFramework__AirshipDevice_hpp

#include <Airship/Airship.h>
#include <IOKit/IOLocks.h>
#include <IOKit/IOService.h>

class AirshipDriver;

enum AirshipDevicePowerState
{
    kAirshipDevicePowerStateOff = 0,
    kAirshipDevicePowerStateLpw = 1,
    kAirshipDevicePowerStateOn = 2,
    kAirshipDeviceNumPowerStates = 3,
};

struct AirshipDevice_IVars;
class AIRSHIP_EXPORT_CLASS AirshipDevice: public IOService
{
    OSDeclareAbstractStructors(AirshipDevice);

public:
    virtual bool init(OSDictionary *properties = nullptr) override;
    virtual void free() override;
    virtual bool start(IOService *provider) final;
    virtual void stop(IOService *provider) final;

    virtual bool matchPropertyTable(OSDictionary *table) final;
    bool matchesCriteria(const OSDictionary *criteria) const;

    virtual IOReturn setPowerState(unsigned long powerStateOrdinal, IOService *whatDevice) final;

    airship_device_transport_t getTransport() const;
    void addDriver(AirshipDriver *driver, bool acquirePowerAssertion);
    void removeDriver(const AirshipDriver *driver);
    void setPowerAssertion(const AirshipDriver *driver);
    void clearPowerAssertion(const AirshipDriver *driver);
    bool isPoweredOnWithAssertion(const AirshipDriver *driver) const;
    bool isPoweringOff() const;
    void bestEffortBlockAccessFromDevice();
    void appendDeviceStateDump(void *session_ptr) const;

protected:
    virtual bool matchesCriterion(const OSSymbol *key, const OSObject *value) const;
    IOLock *getLock() const;

private:
    virtual bool derivedStart(IOService *provider);
    virtual void derivedStop(IOService *provider);
    virtual void derivedSetPowerState(unsigned long powerStateOrdinal);
    virtual void derivedBestEffortBlockAccessFromDevice();

    virtual airship_device_transport_t derivedGetTransport() const = 0;
    virtual OSSharedPtr<const OSDictionary> derivedProbeDevice() = 0;

    void addPowerAssertion(const AirshipDriver *driver);
    void removePowerAssertion(const AirshipDriver *driver);
    void recomputePowerRequest();

private:
    static IOPMPowerState _powerStates[];
    AirshipDevice_IVars *ivars;
};

#endif /* airship__KernelFramework__AirshipDevice_hpp */
