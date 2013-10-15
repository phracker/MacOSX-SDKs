/*	Copyright: 	© Copyright (c) 2006-2007 Apple Inc. All rights reserved.

	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Inc.
			("Apple") in consideration of your agreement to the following terms, and your
			use, installation, modification or redistribution of this Apple software
			constitutes acceptance of these terms.  If you do not agree with these terms,
			please do not use, install, modify or redistribute this Apple software.

			In consideration of your agreement to abide by the following terms, and subject
			to these terms, Apple grants you a personal, non-exclusive license, under Apple's
			copyrights in this original Apple software (the "Apple Software"), to use,
			reproduce, modify and redistribute the Apple Software, with or without
			modifications, in source and/or binary forms; provided that if you redistribute
			the Apple Software in its entirety and without modifications, you must retain
			this notice and the following text and disclaimers in all such redistributions of
			the Apple Software.  Neither the name, trademarks, service marks or logos of
			Apple Inc. may be used to endorse or promote products derived from the
			Apple Software without specific prior written permission from Apple.  Except as
			expressly stated in this notice, no other rights or licenses, express or implied,
			are granted by Apple herein, including but not limited to any patent rights that
			may be infringed by your derivative works or by other works in which the Apple
			Software may be incorporated.

			The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
			WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
			WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
			PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
			COMBINATION WITH YOUR PRODUCTS.

			IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
			CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
			GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
			ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION
			OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT
			(INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN
			ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// -----------------------------------------------------------------------------
// LogicAUProperties.h
// -----------------------------------------------------------------------------

#ifndef __LogicAUProperties_h__
#define __LogicAUProperties_h__

// -----------------------------------------------------------------------------
// NOTE: At the end of this file you will find detailed information on
// Logic Node mechanisms and operation.
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// The following properties describe the Logic Node capabilities and the
// mode of operation of Audio Units that may run in a Logic Node environment.

enum
{
  // kLogicAUProperty_NodeOperationMode (UInt32)
  // On read: The Audio Unit can describe what mode of operation it supports
  // when running in a Logic Node system. On write: The host sets the
  // current operation mode. For details on the operation mode see the
  // operation mode flags and the Logic Node documentation at the end of
  // this file.
  //
  // If the property is not supported, the Audio Unit will run in default
  // mode, which is UI return mode.
  kLogicAUProperty_NodeOperationMode        = 9000,

  // kLogicAUProperty_NodePropertyDescriptions
  // Read only: The Audio Unit returns an array of LogicAUNodePropertyDescription
  // data structures containing a description of all properties (public
  // and private) that are used in the UI <-> Audio Unit communication.
  // This property needs only be supported if the Audio Unit can run
  // in remote UI mode. Public properties need only to be included in
  // the list, if they are used by the UI.
  kLogicAUProperty_NodePropertyDescriptions = 9001
};

// -----------------------------------------------------------------------------
// Operation mode flags
// Used by the kLogicAUProperty_NodeOperationMode property. On read: Describe 
// in what operation modes a Logic Node system can run the Audio Unit. On
// write: Describe the operation modes the Audio Unit is currently run in.

enum
{
  // On read this flag indicates that the Audio Unit can run on a Logic Node. More 
  // specific it may be used to actively prohibit Logic Node operation of the 
  // Audio Unit by supporting the kLogicAUProperty_NodeOperationMode property 
  // and _not_ setting this flag.
  // On write: The host sets this flag if the Audio Unit currently runs on an Node; may
  // be used to run alternative copy protection code.
  kLogicAUNodeOperationMode_NodeEnabled           = (1<<0),

  // On read: With this flag the Audio Unit may indicate that it can run in remote UI mode.
  // The Audio Unit uses only properties or parameters to communicate with the UI 
  // and supports the kLogicAUProperty_NodePropertyDescriptions property.
  // On write: The host sets this flag if the UI is open on the master while the Audio
  // Unit runs on a Node.
  kLogicAUNodeOperationMode_RemoteUI              = (1<<1),

  // Onw read this flag indicates that the Audio Unit can run in Node systems with different 
  // endians.It is only evaluated, if kLogicAUNodeOperationMode_RemoteUI flag 
  // is set.
  // On write the host sets this flag if the Node has a different endian than the master.
  // The Audio Unit on the Node is responsible for swapping both incoming and
  // outgoing property data. It may use the endian conversion services provided
  // by the Logic Node system to handle this.
  kLogicAUNodeOperationMode_EndianSwap            = (1<<2),

  // On read a shortcut for 'Audio Unit can run in full compatible mode'.
  kLogicAUNodeOperationMode_FullSupport           = (kLogicAUNodeOperationMode_NodeEnabled | kLogicAUNodeOperationMode_RemoteUI | kLogicAUNodeOperationMode_EndianSwap)
};

// -----------------------------------------------------------------------------
// Property description
// Describes a property that is used for communication of UI and core.

typedef struct
{
  // the ID of the property
  AudioUnitPropertyID mPropertyID;

  // This describes how data should be treated in mixed endian Node systems.
  // See the Node documentation below for details.
  UInt32 mEndianMode;

  // see flags below
  UInt32 mFlags;
} LogicAUNodePropertyDescription;

// -----------------------------------------------------------------------------
// Property description flags
// Signal special requirements for the property exchange across process or
// machine boundaries.

enum
{
  // This flag indicates that the data exchange has to be synchronous for the 
  // property. Please use this wisely. See the Node documentation below for details.
  kLogicAUNodePropertyFlag_Synchronous          = (1<<0),

  // With this flag the Audio Unit indicates that the data cache for this property 
  // has to be initialized before the first  access. See the Node documentation 
  // below for details.
  kLogicAUNodePropertyFlag_NeedsInitialization  = (1<<1),

  // This flag indicates that the data has to be send/received in a full roundtrip.
  // See the Node documentation below for details.
  kLogicAUNodePropertyFlag_FullRoundTrip        = (1<<2)
};

// -----------------------------------------------------------------------------
// Property description endian modes
// Describe how the host application should treat the property data in Nodes
// systems with mixed endianess.

enum
{
  // The data is not touched by the host. The Audio Unit must evaluate the
  // kLogicAUNodeOperationMode_EndianSwap flag and handle endianess
  // cnversions as needed.
  kLogicAUNodePropertyEndianMode_DontTouch          = 0,

  // The data is an array of 32 bit values and is endian converted 
  // automatically by the host.
  kLogicAUNodePropertyEndianMode_All32Bits          = 1,

  // The data is an array of 64 bit values and is endian converted 
  // automatically by the host.
  kLogicAUNodePropertyEndianMode_All64Bits          = 2,

  // The data is a reference to a serializable Core Foundation type; for network
  // transfers the data is serialized, sent and deserialized. This takes
  // care of the endianess.
  kLogicAUNodePropertyEndianMode_SerializableCFType = 3
};

#endif // __LogicAUProperties_h__

// -----------------------------------------------------------------------------
// Logic Nodes how-to
// -----------------------------------------------------------------------------

/*

Abstract

Logic Nodes is a feature of Logic that allows distributed processing of 
plug-ins on several computers that are connected via Ethernet. Logic users can 
scale the CPU power of their audio platform simply by connecting more node 
computers to the network. Currently nodes can only process Logic's built in 
plug-ins. In order to enable Audio Units to work with Logic Nodes, the Audio 
Units have to match some requirements outlined in this document.

How it works

This section explains the basic mechanisms of a Logic Node environment and 
defines some terms that will be used throughout this document.
A Logic Node is a computer that runs the Logic Node application, which is a 
stripped down version of Logic's plug-in host. Logic can connect to any number 
of nodes if these are connected by Ethernet to the computer Logic runs on. 
This computer is called the master.

Audio processing

Every time a plug-in is instantiated on the master, an instance is also created 
on every connected node. The instance on the master is referred to as the master 
plug-in, the instances running on nodes are called node plug-ins. In addition an 
instance of the plug-in proxy is created, that handles communication between 
Logic's audio engine, master plug-in and the node plug-ins. 

When Logic's audio engine starts streaming audio, the node scheduler decides for 
every master plug-in wether it will be processed on the master or on one of the 
nodes. The result of this process is called the schedule for the plug-in and the 
corresponding instance is called the active instance. This is not changed during 
playback, only when the engine is stopped.

Pictures 1 and 2 illustrate the data flow between audio engine, plug-in proxy 
and master and node instances. First one should note that there are two different 
kinds of data the plug-in proxy has to handle. The first kind is control data that 
is always broadcasted to the master plug-in and all node plug-ins, so the control 
state of the plug-in instances is consistent. Thus control data queries can always 
be read from the master plug-in. The second kind of data is audio data. This data 
class contains the audio data for processing and synchronization data. All other 
data is considered control data, for example MIDI events, parameter changes, 
Audio Unit properties (including ClassInfo) and actions like Initialize() or 
Reset(). 

Audio data is always sent to the active plug-in only. So the audio state of master 
and node instances is not consistent. But as the schedule for a plug-in is not 
changed during playback and all instances are reset after stop, this is not a 
problem for most plug-ins. Some plug-ins may be affected however, if they compute 
long term statistics of the audio data for example. Then changing the schedule of 
the plug-in results in different statistical data for master and node instances.



         Master                                 | Node         |
                                                |              +---  Control Data     
         +-----------------------------+        |
         |     Logic Audio Engine      |        |              :
         +-----------------------------+        |              ....  Audio Data
                             |      A           |
                             |      :           |
                             |      :           |
                             |      :           |
                             V      V           |
                          +------------+        |
                          | Core Proxy |        |
                          +------------+        |
                             |      A           |
                             |      :           |
                             |      :           |
                             +------:------------------+       
                             |      :           |      |       
                             V      V           |      V       
                          +------------+        |    +-----------+
                          | Master AU  |        |    |  Node AU  |
                          +------------+        |    +-----------+
                                                |
        Picture 1 - Node system with audio processing on the master



         Master                                 | Node         |
                                                |              +---  Control Data     
         +-----------------------------+        |
         |     Logic Audio Engine      |        |              :
         +-----------------------------+        |              ....  Audio Data
                             |      A           |
                             |      :           |
                             |      :           |
                             |      :           |
                             V      V           |
                          +------------+        |
                          | Core Proxy |        |
                          +------------+        |
                             |      A           |
                             |      :           |
                             |      ............................
                             +-------------------------+       :
                             |                  |      |       :
                             V                  |      V       V
                          +------------+        |    +-----------+
                          | Master AU  |        |    |  Node AU  |
                          +------------+        |    +-----------+
                                                |
          Picture 2 - Node system with audio processing on the Node



         Master                                 | Node         |
                                                |              +---  Control Data     
         +-----------------------------+        |
         |     Logic Audio Engine      |        |              :
         +-----------------------------+        |              ....  Audio Data
                             |      A           |
         +-----------+       |      :           |
         |  AU GUI   |       |      :           |
         +-----------+       |      :           |
               A             V      V           |
               |          +------------+        |
               |          | Core Proxy |        |
               |          +------------+        |
               V             |      A           |
         +-----------+       |      :           |
         | GUI Proxy |       |      ............................
         +-----------+       +-------------------------+       :
               A             |                  |      |       :
               |             V                  |      V       V
               |          +------------+        |    +-----------+
               |          | Master AU  |        |    |  Node AU  |
               |          +------------+        |    +-----------+
               |             A                  |      A
               |             |                  |      |
               +-------------+-------------------------+
                                                |
                Picture 3 - Node system with remote GUI

                                        
UI interaction

While audio processing on Logic Nodes is rather simple to support, things become 
more complicated when dealing with custom UI view components. Picture 3 gives an 
overview. It shows that the plug-in GUI does not communicate with the master 
plug-in directly but with a new entity called GUI proxy. For Audio Units this 
proxy is just another component that is inserted between the Audio Unit and its 
UI component. On creation of the UI component it is not connected to the Audio 
Unit but to the GUI proxy instead. Likewise the GUI proxy acts as the UI 
component for the Audio Unit. All data exchanged between UI component and GUI 
proxy - namely parameter and property values - is handled like control data with 
one exception: It is read on request from the active instead of the master 
instance, because it most likely is display data computed from the audio material 
and the audio status is not consistent between instances. Table 1 summarizes the 
data flow in a Logic Node environment.

Table 1 - Summary of data flow in Logic Node environments

Direction of Data Flow      Control Data          Audio Data
----------------------------------------------------------------------------
plug-in proxy to plug-in    broadcasted           to active plug-in
plug-in to plug-in proxy    from master plug-in   from active plug-in
GUI proxy to plug-in        broadcasted           n/a
plug-in to GUI proxy        from active plug-in    n/a

Essentials

This section is about what developers should keep in mind when planning support 
for Logic Node processing in an Audio Units. If it follows the Audio Unit 
specifications closely - that fortunately already provide everything needed for 
node processing - only a few small details may have to be altered to make it Logic 
Node compatible.

There are several levels of compatibility an Audio Unit can have with the Logic 
Node environment. The basic level is incompatible which is pretty self-explanatory. 
The next compatibility level is GUI return. In this mode the Audio Unit can be 
processed on a node while its custom UI component is closed. When the GUI is 
opened, the master plug-in becomes the active instance and the GUI proxy data is 
not broadcasted to the nodes. Instead the control state is synchronized as soon as 
the GUI is closed.

Please note that in a clean Audio Unit implementation the Audio Unit itself has 
absolutely no UI interaction. This becomes even more important for Logic Node 
systems because a node may not be connected to a display. Thus an alert box may 
remain unnoticed and block audio processing on the node.
The GUI return mode has some drawbacks. For example it may lead to inconsistent 
audio states that require a playback stop/restart. So we don't encourage the use of 
it. Nevertheless it might be a good solution for existing plug-ins that cannot 
operate in the full compatibility mode for some reason.

The optimal mode for node environments is full compatibility mode. This enables Audio 
Units to be processed on a node even when the custom UI component is open. Obviously 
the restrictions for GUI return mode are still valid but there are some additional 
conditions. Most important: UI component and Audio Unit component must not share 
pointers. While shared memory is common practice in other plug-in architectures, 
Audio Units provide a much better way of communication using message-based data 
exchange. Developers may use one of the following mechanisms to send data from UI to 
plug-in:

make parameter changes calling AUParameterSet()
call standard Audio Unit functions like AudioUnitReset()
set standard or custom properties

For architectural reasons, a plug-in running in a Logic Node environment can not 
send data to the UI component. Instead the UI component has to query data from the 
plug-in by using one of the following methods:

use a hidden read-only parameter
call GetProperty() for a custom property

Regardless of the compatibility level an Audio Unit may or may not support mixed 
endian systems, thus enabling setups with different endian processors in one node 
network. While the node environment takes care of parameter values and all standard 
properties and guaranties that the data is delivered to the Audio Unit with the 
appropriate data endianess, the Audio Unit must handle endianess of custom properties 
itself.

Property data exchange details

When exchanging data between UI and Audio Unit over machine boundaries some problems
may occur that are usually not present in single address space environments. The most
prominent among them are latency and bandwidth. To minimize effects of latency, data
transfers across machine boundaries are usually asynchronous:

1. the UI calls GetProperty
2. the node proxy reads the property data from a cache present in the master
3. it asynchronously sends a GetProperty request to the active node
4. when the data returns from the node, it is stored in the property data cache
   for future GetProperty calls
   
This leads to two effects. First the data for GetProperty might be considerably old.
And second the first GetProperty call will deliver a buffer all filled with zeroes. 
This should be ok for most properties, but if it is not, you can use the
kLogicAUNodePropertyFlag_Synchronous and kLogicAUNodePropertyFlag_NeedsInitialization 
flags for that property. The former flag forces GetProperty and SetProperty to be
synchronous, thus waiting with program execution until the data returns from the node.
Be aware that this may take several milliseconds during which the main thread of the
UI is blocked. The latter flag forces the node system to prefill the property data 
cache synchronously once on Audio Unit instantiation.

To utilize bandwidth efficiently, property data transfer usually is one way, that is,
GetProperty sends the property ID and the data buffer travels from node to master 
only. SetProperty sends the data from master to node and not back. You may override
this behaviour by setting the kLogicAUNodePropertyFlag_FullRoundTrip flag for a
property. Then the data contained in the buffer provided to the GetProperty() call
will be first sent to the node and back to the master for both GetProperty and 
SetProperty.

Installation and content

In order to run in an Logic Node environment, an Audio Unit must be installed on every 
node in the system. In addition everything that is loaded directly by the Audio Unit 
needs to be installed on the nodes. Typically such data is not directly accessible by 
the user and stored either within the component bundle or in the system Application
Support folder.

Standard Audio Unit presets may be installed on the master machine only. They are 
broadcasted to the nodes by the plug-in proxy. In case the preset contains file 
references, we suggest to follow the guidelines described AUPresetsAndFileReferences.rtf 
in the Core Audio documentation of the Developer SDK. 

Problems may occur with content that is stored in arbitrary locations and can be modified 
by the user, samples for example. In this case we recommend to place the loading code 
entirely into the UI component and use a custom property to send the data to the Audio Unit, 
thus enabling the GUI proxy to broadcast the data automatically.

*/