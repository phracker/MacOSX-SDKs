//
//  AirshipPCIDevice.hpp
//  Airship
//
//  Created by Jason McElrath on 2/14/23.
//

#ifndef airship__KernelFramework__AirshipPCIDevice_hpp
#define airship__KernelFramework__AirshipPCIDevice_hpp

#include <Airship/Airship.h>
#include <Airship/AirshipDevice.hpp>
#include <IOKit/IOService.h>
#include <IOKit/pci/IOPCIDevice.h>

struct AirshipPCIDevice_IVars;
class AIRSHIP_EXPORT_CLASS AirshipPCIDevice: public AirshipDevice
{
    OSDeclareDefaultStructors(AirshipPCIDevice);

public:
    virtual bool init(OSDictionary *properties = nullptr) override;
    virtual void free() override;

private:
    virtual bool derivedStart(IOService *provider) override;
    virtual void derivedStop(IOService *provider) override;
    virtual void derivedBestEffortBlockAccessFromDevice() override;
    virtual airship_device_transport_t derivedGetTransport() const override;
    virtual OSSharedPtr<const OSDictionary> derivedProbeDevice() override;

    virtual bool matchesCriterion(const OSSymbol *key, const OSObject *value) const override;

private:
    AirshipPCIDevice_IVars *ivars;
};

#endif /* airship__KernelFramework__AirshipPCIDevice_hpp */
