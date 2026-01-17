/*
 *  AddressBook.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 *
 *  !!!! DEPRECATED !!!!
 *
 *  AddressBook framework is deprecated as of iOS 9.0
 *  Please use Contacts framework instead.
 *
 *  !!!! DEPRECATED !!!!
 *
 *
 *  This library is not threadsafe. Recommended practice is to use
 *  a separate ABAddressBook instance on each thread in your
 *  application. You can register a callback on each instance
 *  that will be invoked when another instance in another thread
 *  or process makes changes to the shared AddressBook database.
 *  
 *  Alternately if needed, multiple threads could use a shared 
 *  ABAddressBook instance by serializing all AddressBook API usage 
 *  with the same dispatch queue. It is important to follow these 
 *  rules when doing this:
 *  1) Threads can only use value types from the block's
 *     ABRecordRef and ABMultiValueRef objects.
 *  2) Threads can reference these objects by their ABRecordID
 *     and ABMultiValueIdentifier.
 *  3) The AddressBook change callback must also be serialized
 *     with the same dispatch queue. For example, to revert
 *     the ABAddressBook instance.
 *
 *  Changes to records have no external effect until the ABAddressBook
 *  is saved. It is possible for other ABAddressBook instances to make
 *  conflicting changes during that time. To reduce the likelihood
 *  of that event, save the ABAddressBook as soon as possible after
 *  each set of related changes.
 *
 */

#ifndef __AddressBook__
#define __AddressBook__

#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABPerson.h>
#include <AddressBook/ABGroup.h>
#include <AddressBook/ABMultiValue.h>

#endif


