#if 0
#elif defined __arm64e__
# include "rb_mjit_min_header-2.6.3-arm64e.h"
#elif defined __x86_64__
# include "rb_mjit_min_header-2.6.3-x86_64.h"
#else
# error unsupported platform
#endif
