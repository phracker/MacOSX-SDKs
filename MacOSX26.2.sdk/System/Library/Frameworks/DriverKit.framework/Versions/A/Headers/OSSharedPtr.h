/*
 * Copyright (c) 2020-2020 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef DRIVERKIT_OSSHAREDPTR_H
#define DRIVERKIT_OSSHAREDPTR_H

#include <type_traits>
#include <cstddef>

#if !__IIG
#include <DriverKit/OSMetaClass.h>
#endif

struct OS_no_retain_t {
	explicit constexpr OS_no_retain_t() {}
};

struct OS_retain_t {
	explicit constexpr OS_retain_t() {}
};

static inline constexpr auto OSNoRetain = OS_no_retain_t{};
static inline constexpr auto OSRetain = OS_retain_t{};

template <typename T>
struct OSSharedPtr {
	using pointer = T *;
	using element_type = T;
    using retain_t = OS_retain_t;
    using no_retain_t = OS_no_retain_t;

	// Constructs a null shared pointer.
	//
	// A null shared pointer can't be dereferenced, but it can be checked
	// for nullness, assigned to, reset, etc.
	constexpr OSSharedPtr() noexcept : ptr_(nullptr) {
	}
	constexpr OSSharedPtr(std::nullptr_t) noexcept : ptr_(nullptr) {
	}

	// Constructs a shared pointer to the given object, incrementing the
	// refcount for that object.
	//
	// This constructor is adequate when transforming a raw pointer with
	// shared ownership into a shared pointer, when the raw pointer is at
	// +1. This can be done by replacing the raw pointer and the manual call
	// to `retain()` by a shared pointer constructed with this constructor,
	// which will retain the pointed-to object.
	//
	// If the original code did not contain a manual retain and you use this
	// constructor, you will create a leak.
	explicit
	OSSharedPtr(pointer p, retain_t) noexcept : ptr_(p) {
		if (ptr_ != nullptr) {
            ptr_->retain();
		}
	}

	// Constructs a shared pointer to the given object, without incrementing
	// the refcount for that object.
	//
	// This constructor is adequate when transforming a raw pointer with
	// shared ownership into a shared pointer, when the raw pointer is at
	// +0. This can be done by replacing the raw pointer by a shared
	// pointer constructed with this constructor, which does not retain
	// the pointed-to object.
	//
	// If the original code contained a manual retain that you removed and
	// you use this constructor, you will cause a use-after-free bug.
	explicit constexpr
	OSSharedPtr(pointer p, no_retain_t) noexcept : ptr_(p) {
	}


	// Makes a copy of a shared pointer, incrementing the refcount.
	//
	// Since this creates a new reference to the pointed-to object, the
	// refcount is increased. Unlike for move operations, the source
	// pointer is left untouched.
	OSSharedPtr(OSSharedPtr const & other) : ptr_(other.ptr_) {
		if (ptr_ != nullptr) {
            ptr_->retain();
		}
	}

	// Makes a copy of a shared pointer from another compatible shared pointer,
	// increasing the refcount.
	//
	// This converting constructor is enabled whenever `U*` is implicitly
	// convertible to `T*`. This allows the usual implicit conversions
	// between base-and-derived types.
	//
	// Since this creates a new reference to the pointed-to object, the
	// refcount is increased. Unlike for move operations, the source
	// pointer is left untouched.
	template <typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*> > >
	OSSharedPtr(OSSharedPtr<U> const & other) : ptr_(other.ptr_) {
		if (ptr_ != nullptr) {
            ptr_->retain();
		}
	}

	// Moves a shared pointer into another one, nulling the source.
	//
	// Since this moves the ownership from one pointer to another, no
	// refcount increment or decrement is required. The moved-from pointer
	// becomes a null pointer, as if it had been default-constructed.
	constexpr OSSharedPtr(OSSharedPtr && other) noexcept : ptr_(other.ptr_) {
		other.ptr_ = nullptr;
	}

	// This is here to allow OSSharedPointer(Foo::withBar(bar), OSNoRetain) to remain 
	// legal as Foo::withBar() is converted from returning Foo* to OSPtr<Foo>
	constexpr
	OSSharedPtr(OSSharedPtr &&other, no_retain_t) noexcept : ptr_(other.ptr_) { 
		other.ptr_ = nullptr;
	}

	// Moves a shared pointer to a type `U` into a shared pointer
	// to a type `T`.
	//
	// This converting constructor is enabled whenever `U*` is implicitly
	// convertible to `T*`. This allows the usual implicit conversions
	// between base-and-derived types.
	//
	// Since this moves the ownership from one pointer to another, no
	// refcount increment or decrement is required. The moved-from pointer
	// becomes a null pointer, as if it had been default-constructed.
	template <typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*> > >
	constexpr OSSharedPtr(OSSharedPtr<U>&& other) noexcept : ptr_(other.ptr_) {
		other.ptr_ = nullptr;
	}

	// Destroys a shared pointer.
	//
	// The destruction of the shared pointer implies that one fewer reference
	// to the pointed-to object exist, which means that the refcount of the
	// pointed-to object is decremented.
	//
	// If that decrement causes the refcount to reach 0, the refcounting
	// policy must destroy the pointed-to object and perform any cleanup
	// associated to it (such as freeing the allocated memory).
	~OSSharedPtr() {
		reset();
	}

	// Copy-assigns a shared pointer.
	//
	// Since this creates a new reference to the pointed-to object, the
	// refcount is increased. Unlike for move operations, the source
	// pointer is left untouched.
	//
	// If the destination shared pointer is pointing to an object before
	// the assignment, the refcount is decremented on that object after
	// the assignment is performed.
	OSSharedPtr&
	operator=(OSSharedPtr const& other)
	{
		reset(other.get(), OSRetain);
		return *this;
	}

	// Copy-assigns a shared pointer, enabling implicit conversions.
	//
	// This converting copy-assignment is enabled whenever `U*` is implicitly
	// convertible to `T*`. This allows the usual implicit conversions
	// between base-and-derived types.
	//
	// Since this creates a new reference to the pointed-to object, the
	// refcount is increased. Unlike for move operations, the source
	// pointer is left untouched.
	//
	// If the destination shared pointer is pointing to an object before
	// the assignment, the refcount is decremented on that object after
	// the assignment is performed.
	template <typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*> > >
	OSSharedPtr&
	operator=(OSSharedPtr<U> const& other)
	{
		reset(other.get(), OSRetain);
		return *this;
	}

	// Move-assigns a shared pointer.
	//
	// Since this moves the ownership from one pointer to another, no
	// refcount increment or decrement is required. The moved-from pointer
	// becomes a null pointer, as if it had been default-constructed.
	//
	// If the destination shared pointer is pointing to an object before
	// the assignment, the refcount is decremented on that object after
	// the assignment is performed.
	OSSharedPtr&
	operator=(OSSharedPtr&& other)
	{
		reset(other.get(), OSNoRetain);
		other.ptr_ = nullptr;
		return *this;
	}

	// Move-assigns a shared pointer, enabling implicit conversions.
	//
	// This converting move-assignment is enabled whenever `U*` is implicitly
	// convertible to `T*`. This allows the usual implicit conversions
	// between base-and-derived types.
	//
	// Since this moves the ownership from one pointer to another, no
	// refcount increment or decrement is required. The moved-from pointer
	// becomes a null pointer, as if it had been default-constructed.
	//
	// If the destination shared pointer is pointing to an object before
	// the assignment, the refcount is decremented on that object after
	// the assignment is performed.
	template <typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*> > >
	OSSharedPtr&
	operator=(OSSharedPtr<U>&& other)
	{
		reset(other.get(), OSNoRetain);
		other.ptr_ = nullptr;
		return *this;
	}

	// Resets a shared pointer to a null pointer, as if calling `reset()`.
	//
	// If the destination shared pointer is pointing to an object before
	// the assignment, the refcount is decremented on that object after
	// the assignment is performed.
	OSSharedPtr&
	operator=(std::nullptr_t) noexcept
	{
		reset();
		return *this;
	}

	// Returns a reference to the object pointed-to by the shared pointer.
	constexpr T&
	operator*() const noexcept
	{
		return *ptr_;
	}
	constexpr pointer
	operator->() const noexcept
	{
		return ptr_;
	}

	// Implicit conversion to bool, returning whether the shared pointer is null.
	explicit constexpr
	operator bool() const noexcept
	{
		return ptr_ != nullptr;
	}

	// Sets a shared pointer to null.
	//
	// If the shared pointer is pointing to an object, the refcount is
	// decremented on that object.
	OSSharedPtr&
	reset() noexcept
	{
		if (ptr_ != nullptr) {
            ptr_->release();
		}
		ptr_ = nullptr;
		return *this;
	}

	// Sets the object pointed-to by the shared pointer to the given object.
	//
	// This variant of `reset()` does not increment the refcount on the object
	// assigned to the shared pointer.
	//
	// If the shared pointer is pointing to an object before calling `reset`,
	// the refcount is decremented on that object.
	OSSharedPtr&
	reset(pointer p, no_retain_t) noexcept
	{
		if (ptr_ != nullptr) {
            ptr_->release();
		}
		ptr_ = p;
		return *this;
	}

	// Sets the object pointed-to by the shared pointer to the given object.
	//
	// This variant of `reset()` increments the refcount on the object
	// assigned to the shared pointer.
	//
	// If the shared pointer is pointing to an object before calling `reset`,
	// the refcount is decremented on that object.
	OSSharedPtr&
	reset(pointer p, retain_t) noexcept
	{
		// Make sure we don't release-before-we-retain in case of self-reset
		pointer old = ptr_;
		ptr_ = p;
		if (ptr_ != nullptr) {
            ptr_->retain();
		}
		if (old != nullptr) {
            old->release();
		}
		return *this;
	}

	// Retrieves the raw pointer held by a shared pointer.
	//
	// The primary intended usage of this function is to aid bridging between
	// code that uses shared pointers and code that does not, or simply to
	// obtain a non-owning reference to the object managed by the shared pointer.
	//
	// After this operation, the shared pointer still manages the object it
	// points to (unlike for `detach()`).
	//
	// One must not hold on to the pointer returned by `.get()` after the
	// last shared pointer pointing to that object goes out of scope, since
	// it will then be a dangling pointer. To try and catch frequent cases of
	// misuse, calling `.get()` on a temporary shared pointer is not allowed.
	constexpr pointer
	get() const & noexcept
	{
		return ptr_;
	}

	constexpr pointer
	    get() const&& noexcept = delete;

	// Returns the raw pointer contained in a shared pointer, detaching
	// ownership management from the shared pointer.
	//
	// This operation returns a pointer to the object pointed-to by the
	// shared pointer, and severs the link between the shared pointer and
	// that object. After this operation, the shared pointer is no longer
	// responsible for managing the object, and instead whoever called
	// `detach()` has that responsibility.
	//
	// `detach()` does _not_ decrement the refcount of the pointee, since
	// the caller of `detach()` is responsible for managing the lifetime of
	// that object.
	//
	// After a call to `detach()`, the shared pointer is null since it has
	// no more object to manage.
	constexpr pointer
	detach() noexcept
	{
		pointer tmp = ptr_;
		ptr_ = nullptr;
		return tmp;
	}

	// Converts an OSSharedPtr to an OSPtr.
#if DRIVERKIT_ENABLE_SHARED_PTR
	OSSharedPtr &detachAsOSPtr() noexcept
	{
		return *this
	}
#else 
	pointer detachAsOSPtr() noexcept
	{
		return detach();
	}
#endif

	struct attacher {
		OSSharedPtr &sp;
		attacher(OSSharedPtr &sp) noexcept : sp(sp) {};
		operator pointer*() const noexcept {
			return &sp.ptr_;
		}
		operator OSSharedPtr*() const noexcept {
			return &sp;
		}
	};

	// Return something that can be passed to an output parameter of
	// type T** or OSSharedPtr<T> *
	//
	// For example if you have a function: IOReturn getFoo(Foo **foop)
	// which places a +1 retained Foo* (or NULL) into *foop,
	//
	// then you may call it as:
	//
	// OSSharedPtr<Foo> foo;
	// getFoo(foo.attach())
	//
	// This will also work for: IOReturn getFoo(OSSharedPtr<Foo> *foop)
	attacher attach() noexcept {
		reset();
		return attacher(*this);
	}

private:
	friend constexpr void
	swap(OSSharedPtr& a, OSSharedPtr& b) noexcept
	{
		pointer tmp = a.ptr_;
		a.ptr_ = b.ptr_;
		b.ptr_ = tmp;
	}

	template <typename U>
	friend struct OSSharedPtr;

    pointer ptr_;
};

#if DRIVERKIT_FIX_OSTYPEID

template <typename T>
OSSharedPtr<T>
OSMakeShared()
{
	T* memory = OSTypeAlloc(T);
	// OSTypeAlloc returns an object with a refcount of 1, so we must not
	// retain when constructing the shared pointer.
	return OSSharedPtr<T>(memory, OSNoRetain);
}

template <typename Destination, typename Source>
OSSharedPtr<Destination>
OSDynamicPtrCast(OSSharedPtr<Source> const& source)
{
	Destination* raw = OSDynamicCast(Destination, source.get());
	if (raw == nullptr) {
		return nullptr;
	} else {
		OSSharedPtr<Destination> dest(raw, OSRetain);
		return dest;
	}
}

template <typename Destination, typename Source>
OSSharedPtr<Destination>
OSDynamicPtrCast(OSSharedPtr<Source> && source)
{
	Destination* raw = OSDynamicCast(Destination, source.get());
	if (raw == nullptr) {
		return nullptr;
	} else {
		OSSharedPtr<Destination> dest(raw, OSNoRetain);
		source.detach(); // we stole the retain!
		return dest;
	}
}

#endif //DRIVERKIT_FIX_OSTYPEID

#if !__IIG

template <typename To, typename From>
OSSharedPtr<To>
OSStaticPtrCast(OSSharedPtr<From> const& ptr) noexcept
{
	return OSSharedPtr<To>(static_cast<To*>(ptr.get()), OSRetain);
}

template <typename To, typename From>
OSSharedPtr<To>
OSStaticPtrCast(OSSharedPtr<From>&& ptr) noexcept
{
	return OSSharedPtr<To>(static_cast<To*>(ptr.detach()), OSNoRetain);
}

template <typename To, typename From>
OSSharedPtr<To>
OSConstPtrCast(OSSharedPtr<From> const& ptr) noexcept
{
	return OSSharedPtr<To>(const_cast<To*>(ptr.get()), OSRetain);
}

template <typename To, typename From>
OSSharedPtr<To>
OSConstPtrCast(OSSharedPtr<From>&& ptr) noexcept
{
	return OSSharedPtr<To>(const_cast<To*>(ptr.detach()), OSNoRetain);
}

#endif


#endif
