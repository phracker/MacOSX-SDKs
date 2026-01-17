//
//  base.h
//  Airship
//
//  Created by Jason McElrath on 9/18/20.
//

#if !defined(airship_api_indirect) && !defined(__clang_tapi__)
#error Please #include <Airship/Airship.h> instead of this file directly.
#endif

#ifndef airship__core__api__base_h
#define airship__core__api__base_h

/**
 * @file base.h
 * @brief Public interface boilerplate and common types.
 * @namespace airship
 * @brief Public Airship interface.
 */

#include <AppleFeatures/AppleFeatures.h>
#include <TargetConditionals.h>
#include <os/availability.h>
#include <stdbool.h>
#include <stdint.h>
#include <uuid/uuid.h>

/**
 * @def AIRSHIP_EXPORT
 * @brief Internal macro to mark externally-visible symbols with C linkage.
 * @def AIRSHIP_EXPORT_CPP
 * @brief Internal macro to mark externally-visible symbols with C++ linkage.
 * @def AIRSHIP_EXPORT_CLASS
 * @brief Internal macro to mark externally-visible C++ structures.
 */

#ifdef __cplusplus
#define AIRSHIP_EXPORT extern "C" __attribute__((visibility("default")))
#define AIRSHIP_EXPORT_CPP extern "C++" __attribute__((visibility("default")))
#define AIRSHIP_EXPORT_CLASS __attribute__((visibility("default")))
#else
#define AIRSHIP_EXPORT extern __attribute__((visibility("default")))
#endif

/// Helper macros for concatenating macros with variables names.
#define COMBINE_INNER(X,Y) X##Y
#define COMBINE(X,Y) COMBINE_INNER(X,Y)

/// Internal macro to mark non-escaping parameters.
#define AIRSHIP_NOESCAPE __attribute__((noescape))

/// Internal macro to ensure symbols of unused types are retained in the DSYM.
#define AIRSHIP_RETAIN_TYPE_SYMBOLS(type) static type __attribute__((__used__)) COMBINE(__retain_var, __LINE__)

/**
 * @def AIRSHIP_ASSUME_NONNULL_BEGIN
 * @brief Internal macro to mark the beginning of a section where parameters are
 * non-null by default.
 * @def AIRSHIP_ASSUME_NONNULL_END
 * @brief Internal macro to mark the end of a section where parameters are
 * non-null by default.
 * @def AIRSHIP_NONNULL
 * @brief Internal macro to explicitly mark a parameter as non-null.
 * @def AIRSHIP_NULLABLE
 * @brief Internal macro to explicitly mark a parameter as nullable.
 */

#define AIRSHIP_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#define AIRSHIP_ASSUME_NONNULL_END _Pragma("clang assume_nonnull end")
#define AIRSHIP_NONNULL _Nonnull
#define AIRSHIP_NULLABLE _Nullable

/**
 * @typedef airship_string_t
 * @brief String type used by public Airship interfaces.
 * @typedef airship_array_t
 * @brief Array type used by public Airship interfaces.
 * @typedef airship_dictionary_t
 * @brief Dictionary type used by public Airship interfaces.
 */

#include <libkern/c++/OSContainers.h>
#include <libkern/c++/OSSharedPtr.h>
typedef const OSString *airship_string_t;
typedef const OSArray *airship_array_t;
typedef const OSDictionary *airship_dictionary_t;

/**
 * @def AIRSHIP_RETURNS_RETAINED
 * @brief Ownership annotation macro for Airship interface types.
 * @def AIRSHIP_RETURNS_NOT_RETAINED
 * @brief Ownership annotation macro for Airship interface types.
 */

#define AIRSHIP_RETURNS_RETAINED LIBKERN_RETURNS_RETAINED
#define AIRSHIP_RETURNS_NOT_RETAINED LIBKERN_RETURNS_NOT_RETAINED

#include <libkern/Block.h>


#include <IOKit/IOReturn.h>

/// Status codes returned by public Airship interfaces.
typedef enum airship_result
{
    AIRSHIP_OK = 0,                 ///< Success.
    AIRSHIP_ERROR = kIOReturnError, ///< General error.

    AIRSHIP_EBADARGUMENT = kIOReturnBadArgument,         ///< Invalid argument.
    AIRSHIP_ECANCELED = kIOReturnAborted,                ///< Operation canceled.
    AIRSHIP_ECANTMAP = kIOReturnCannotWire,              ///< Unable to map memory.
    AIRSHIP_EDISCONNECTED = kIOReturnNoDevice,           ///< Disconnected.
    AIRSHIP_EEXCLUSIVEACCESS = kIOReturnExclusiveAccess, ///< Exclusive access and already in use.
    AIRSHIP_EIO = kIOReturnIOError,                      ///< I/O error.
    AIRSHIP_ENOTOPEN = kIOReturnNotOpen,                 ///< Not open.
    AIRSHIP_ENOSPACE = kIOReturnNoSpace,                 ///< No space for data.
    AIRSHIP_ENOTPRIVILEGED = kIOReturnNotPrivileged,     ///< Not privileged.
    AIRSHIP_ENOTREADY = kIOReturnNotReady,               ///< Not ready.
    AIRSHIP_ETIMEOUT = kIOReturnTimeout,                 ///< Timeout occurred.
    AIRSHIP_EDEVICE = kIOReturnDeviceError,              ///< Device error.
} airship_result_t;

/**
 * @brief Returns a C string representation of an Airship status code.
 *
 * The contents of the strings returned by this function are subject to change
 * without notice.
 *
 * @param code The status code.
 * @returns A C string representation of the status code.
 */
AIRSHIP_EXPORT
const char *AIRSHIP_NONNULL airship_strerror(airship_result_t code);

/**
 * @brief Retrieve a textual description for an IPC error code.
 *
 * The contents of the strings returned by this function are subject to change
 * without notice.
 *
 * @param protocol The name of an Airship IPC protocol.
 * @param error An IPC error code.
 * @returns A string representing the error.
 */
AIRSHIP_EXPORT
const char *AIRSHIP_NONNULL airship_get_ipc_error_description(airship_string_t AIRSHIP_NONNULL protocol, uint32_t error);

/**
 * @typedef airship_execution_queue_t
 * @brief Execution context type used by public Airship interfaces.
 */

#include <IOKit/IOWorkLoop.h>
typedef IOWorkLoop *airship_execution_queue_t;

/// Basic callback type used by public Airship interfaces.
typedef void (^airship_block_t)(void);
/// Basic callback type used by public Airship interfaces.
typedef void (*airship_function_t)(void *AIRSHIP_NULLABLE);

#ifdef __cplusplus
namespace airship {
/**
 * @brief C++ wrapper for automatic lifecycle management of public API objects.
 * @tparam T Type of the managed object.
 * @tparam Deleter Function used to destroy the managed object.
 */
template <typename T, void Deleter(T *AIRSHIP_NONNULL)>
struct wrapper
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"
    IOOverrideTypedOperators(wrapper);
#pragma clang diagnostic pop

public:
    /// Takes ownership of an object.
    static wrapper created(T *AIRSHIP_NULLABLE obj) { return wrapper(obj); }

    /// Constructs an empty wrapper.
    wrapper() = default;
    /// Destroys the managed object.
    ~wrapper() { reset(); }

    wrapper(const wrapper &) = delete;
    wrapper &operator=(const wrapper &) = delete;
    /// Move constructor. Transfers ownership of the managed object.
    wrapper(wrapper &&other): _obj(other.detach()) {}
    /// Move assignment operator. Transfers ownership of the managed object.
    wrapper &operator=(wrapper &&other)
    {
        wrapper tmp(static_cast<wrapper &&>(other));
        swap(*this, tmp);
        return *this;
    }
    /// `%swap()` overload. Swaps managed objects and their ownership.
    friend void swap(wrapper &a, wrapper &b)
    {
        T *tmp = a._obj;
        a._obj = b._obj;
        b._obj = tmp;
    }

    /// Returns a pointer to the managed object, if any.
    T *AIRSHIP_NULLABLE get() const { return _obj; }
    /// Checks if there is a managed object.
    explicit operator bool() const { return _obj; }

    /// Transfers ownership of the managed object to the caller.
    T *AIRSHIP_NULLABLE detach()
    {
        T *ret = _obj;
        _obj = nullptr;
        return ret;
    }

    /// Destroys the managed object.
    void reset()
    {
        if (_obj)
        {
            Deleter(_obj);
        }
        _obj = nullptr;
    }

private:
    /// Constructor for use by `wrapper::created`.
    wrapper(T *AIRSHIP_NULLABLE obj): _obj(obj) {}

private:
    /// Pointer to the managed object, if any.
    T *AIRSHIP_NULLABLE _obj = nullptr;
};
} // namespace airship
#endif

#endif /* airship__core__api__base_h */
