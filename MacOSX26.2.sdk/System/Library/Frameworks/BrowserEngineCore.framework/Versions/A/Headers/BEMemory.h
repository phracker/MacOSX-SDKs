//
//  BEMemory.h
//

#ifndef BEMemory_h
#define BEMemory_h

#include <Availability.h>
#include <BrowserEngineCore/BEMacros.h>
#include <TargetConditionals.h>
#include <os/base.h>

#if TARGET_OS_OSX || TARGET_OS_IOS
#if TARGET_CPU_ARM64

/*
    We export this symbol, but this function should never be called directly.
    Call be_memory_inline_jit_restrict_rwx_to_rw_with_witness directly.
*/
__SWIFT_UNAVAILABLE
__API_AVAILABLE(macos(14.3), ios(17.4))
__API_UNAVAILABLE(tvos, watchos, driverkit, macCatalyst)
__attribute__((preserve_all))
__attribute__((optnone))
__attribute__((noinline))
__attribute__((direct_call_only))
BROWSERENGINE_EXPORT void be_memory_inline_jit_restrict_rwx_to_rw_with_witness_impl(void);

/*
    We export this symbol, but this function should never be called directly.
    Call be_memory_inline_jit_restrict_rwx_to_rx_with_witness directly.
*/
__SWIFT_UNAVAILABLE
__API_AVAILABLE(macos(14.3), ios(17.4))
__API_UNAVAILABLE(tvos, watchos, driverkit, macCatalyst)
__attribute__((preserve_all))
__attribute__((optnone))
__attribute__((noinline))
__attribute__((direct_call_only))
BROWSERENGINE_EXPORT void be_memory_inline_jit_restrict_rwx_to_rx_with_witness_impl(void);

/*
    Returns true iff the inlinable version of the jit_write_protect API
    is available.
*/
__SWIFT_UNAVAILABLE
__API_AVAILABLE(macos(14.3), ios(17.4))
__API_UNAVAILABLE(tvos, watchos, driverkit, macCatalyst)
__attribute__((noinline))
BROWSERENGINE_EXPORT int be_memory_inline_jit_restrict_with_witness_supported(void);

/*
   This is the globally unique diversifier used in the implementation
   of be_memory_inline_jit_restrict_rwx_to_rw_with_witness_impl
   Ensure that your implementation does not use this diversifier for anything else.
*/
#define BE_JIT_WRITE_PROTECT_TAG 0x4a4954l

#define _BE_STRINGIZE(exp) #exp
#define _BE_STRINGIZE_VALUE_OF(exp) _BE_STRINGIZE(exp)
#define _BE_SYMBOL_STRING(name) "_" #name

#define _BE_INST_PACIBZ ".int 0xd503235f"
#define _BE_INST_PACIB_X0_X1 ".int 0xdac10420"

/*
    These functions that can toggle JIT R^X permissions, while enforcing
    control flow integrity using PAC. This function is intended to be used
    only in performance-critical sections of code. Please consult the documentation
    extensively before relying on this API.

    This function should always be inlined. It will sign the return lr pointer
    as a witness using PAC, and then call into the implementation.

    This implementation is not permitted to be inlined into app binaries
    because the instruction sequence required may change in the future.

    Instead, we use a custom calling convention. This serves two purposes:
    1) Performance. The effects of this call can be precisely modeled, so
        the performance is as close as possible to the case where we can
        inline this body directly.
    2) Security. This calling convention greatly reduces the chances of spilling
        an important value to the stack. See below.

    In support of this function's security goals, users of this function must
        confirm the following:

    1) You must not emit general PAC signing gadgets.
    2) The critical section defined by calls to these two functions must not
        loop on any induction variable that is spilled to the stack, or otherwise
        spill any important values there. An attacker can control these values.
        If any values must be spilled or loaded from the heap or stack, they should be signed
        outside the critical section, and authenticated inside.
    3) Do not create a gadget that is overly general. For example, wrapping this
        function inside a body like this is very bad:

        NEVER_INLINE void myFunction() {
        if (variableFromStackOrHeap)
            be_memory_inline_jit_restrict_rwx_to_rx_with_witness();
        else
            be_memory_inline_jit_restrict_rwx_to_rw_with_witness();
        }

        Each use of this function should be maximally inlined to reduce the power
        that attackers gain by manipulating calls to it.

    There is an additional clang attribute that can help you detect these spills. Please
    look at the WebKit source code for an example.
*/
__SWIFT_UNAVAILABLE
__API_AVAILABLE(macos(14.3), ios(17.4))
__API_UNAVAILABLE(tvos, watchos, driverkit, macCatalyst)
__attribute__((preserve_all))
__attribute__((always_inline))
__attribute__((visibility("hidden")))
__attribute__((direct_call_only))
inline
void be_memory_inline_jit_restrict_rwx_to_rw_with_witness(void)
{
    __asm__ volatile (
#ifdef __arm64e__
    ".arch_extension pauth" "\n"
#endif
    "adr x0, %=2f" "\n"

    "movz x1, #" _BE_STRINGIZE_VALUE_OF(((BE_JIT_WRITE_PROTECT_TAG >>  0) & 0xFFFF)) ", lsl #0 \n"
    "movk x1, #" _BE_STRINGIZE_VALUE_OF(((BE_JIT_WRITE_PROTECT_TAG >> 16) & 0xFFFF)) ", lsl #16\n"

#ifdef __arm64e__
    "pacib x0, x1" "\n"
#else
    "mov x30, x1" "\n"
    _BE_INST_PACIBZ "\n"
    "cmp x30, x1" "\n"
    "beq %=1f" "\n"
    _BE_INST_PACIB_X0_X1 "\n"
    "%=1:" "\n"
#endif // !__arm64e__

    "bl " _BE_SYMBOL_STRING(be_memory_inline_jit_restrict_rwx_to_rw_with_witness_impl) "\n"
    "%=2:" "\n"
    "nop" "\n"
    : /* no output */
    : /* no input */
    : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r16", "r17", "lr", "memory", "cc"
    );
}

/*
 See @be_memory_inline_jit_restrict_rwx_to_rw_with_witness
 */
 __SWIFT_UNAVAILABLE
__API_AVAILABLE(macos(14.3), ios(17.4))
__API_UNAVAILABLE(tvos, watchos, driverkit, macCatalyst)
__attribute__((preserve_all))
__attribute__((always_inline))
__attribute__((visibility("hidden")))
__attribute__((direct_call_only))
inline
void be_memory_inline_jit_restrict_rwx_to_rx_with_witness(void)
{
    __asm__ volatile (
    "bl " _BE_SYMBOL_STRING(be_memory_inline_jit_restrict_rwx_to_rx_with_witness_impl) "\n"
    "%=:" "\n"
    "nop" "\n"
    : /* no output */
    : /* no input */
    : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r16", "r17", "lr", "memory", "cc"
    );
}

#undef _BE_INST_PACIBZ
#undef _BE_INST_PACIB_X0_X1

#undef _BE_STRINGIZE
#undef _BE_STRINGIZE_VALUE_OF
#undef _BE_SYMBOL_STRING

#endif // TARGET_CPU_ARM64
#endif // TARGET_OS_OSX || TARGET_OS_IOS


#endif /* BEMemory_h */
