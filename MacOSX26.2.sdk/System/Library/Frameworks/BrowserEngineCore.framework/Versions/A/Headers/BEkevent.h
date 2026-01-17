//
//  BEkevent.h
//

#ifndef BEkevent_h
#define BEkevent_h

#include <Availability.h>
#include <BrowserEngineCore/BEMacros.h>
#include <TargetConditionals.h>
#include <sys/event.h>

#if TARGET_OS_IOS && !TARGET_OS_VISION

#define BE_KEVENT_NO_FLAGS 0x0
#define BE_KEVENT_RETURN_IMMEDIATELY 0x1

__API_AVAILABLE(ios(18.4))
__API_UNAVAILABLE(macos, tvos, watchos, visionos, driverkit, macCatalyst)
BROWSERENGINE_EXPORT int be_kevent(int kq, const struct kevent* changelist, int nchanges, struct kevent* eventlist, int nevents, unsigned int be_flags);

__API_AVAILABLE(ios(18.4))
__API_UNAVAILABLE(macos, tvos, watchos, visionos, driverkit, macCatalyst)
BROWSERENGINE_EXPORT int be_kevent64(int kq, const struct kevent64_s* changelist, int nchanges, struct kevent64_s* eventlist, int nevents, unsigned int flags);

#endif

#endif /* BEkevent_h */
