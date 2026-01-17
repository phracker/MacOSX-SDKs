/*
     File:       AUGraph.h
 
     Contains:   AUGraph application interfaces
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X Public Beta
 
     Copyright:  (c) 2000 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AUGraph.h

	Subsystem for maintaining arbitrary graphs of AudioUnits.

	The AUGraph APIs are responsible for representing the description of a set
	of AudioUnit components, as well as the audio connections between their
	inputs and outputs.  This representation may be saved/restored persistently
	and "instantiated" (AUGraphOpen() ) by opening all of the AudioUnits, and
	making the physical connections between them stored in the representation. 
	Thus the AUGraph is a description of the various AudioUnits and their
	connections, but also may manage the actual instantiated AudioUnits if
	AUGraphOpen() is actually called. The AUGraph, in essence, is a complete
	description of an audio signal processing network.

	The AUGraph may be introspected, in order to get complete information about
	all of the AudioUnits in the graph.  The various nodes (AUNode) in the
	AUGraph representing AudioUnits may be added or removed, and the connections
	between them modified.

	An AUNode representing an AudioUnit component is created by specifying a
	ComponentDescription record (from the Component Manager), as well as
	optional "class" data, which is passed to the AudioUnit when it is opened.
	This "class" data is in an arbitrary format, and may differ depending on the
	particular AudioUnit.  In general, the data will be used by the AudioUnit to
	configure itself when it is opened (in object-oriented terms, it corresponds
	to constructor arguments).  In addition, certain AudioUnits may provide
	their own class data when they are closed, allowing their current state to
	be saved for the next time they are instantiated.  This provides a general
	mechanism for persistence.

	An AUGraph's state can be manipulated in both the rendering thread and in
	other threads. Consequently, any activities that effect the state of the
	graph are guarded with locks.

	To avoid spinning or waiting in the render thread (a bad idea!), many of the
	calls to AUGraph can return: kAUGraphErr_CannotDoInCurrentContext. This
	result is only generated when you call an AUGraph API from its render
	callback. It means that the lock that it required was held at that time, by
	another thread. If you see this result code, you can generally attempt the
	action again - typically the NEXT render cycle (so in the mean time the lock
	can be cleared), or you can delegate that call to another thread in your
	app. You should not spin or put-to-sleep the render thread as a general
	rule.

	The only exception to this is trying to remove an output node or a sub-graph
	FROM the render callback in a running graph (see below)

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __AUGraph
#define __AUGraph

#include <AvailabilityMacros.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreServices/CoreServices.h>
	#include <AudioUnit/AudioUnit.h>
		// AUNTComponent.h contains declarations for the V1 AU's which are deprecated
	#include <AudioUnit/AUNTComponent.h>
#else
	#include <CoreServices.h>
	#include <AudioUnit.h>
	#include <AUNTComponent.h>
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// AUGraph and AUNode stuff
typedef SInt32 	AUNode;
typedef	struct OpaqueAUGraph	*AUGraph;

struct AudioUnitNodeConnection
{
	AUNode		sourceNode;
	UInt32		sourceOutputNumber;
	AUNode		destNode;
	UInt32		destInputNumber;
};
typedef struct AudioUnitNodeConnection AudioUnitNodeConnection;

enum
{
	kAUGraphErr_NodeNotFound 				= -10860,
	kAUGraphErr_InvalidConnection 			= -10861,
	kAUGraphErr_OutputNodeErr				= -10862,
		//	AUGraphs can only contain one OutputUnit.
		//	this error is returned if trying to add a second output unit

	kAUGraphErr_CannotDoInCurrentContext	= -10863,
		// This result can be returned by a number of the API calls
		// (including AUGraphUpdate)
		// See the comments for AUGraphUpdate

	kAUGraphErr_InvalidAudioUnit			= -10864
		// You can only have audio units of either 'aunt' (V1) or the new types (V2)
		// in the same graph.
};

// construction / destruction
extern OSStatus
NewAUGraph(			AUGraph			*outGraph)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
DisposeAUGraph(		AUGraph			inGraph)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AUGraphNewNode

	This creates a node in the graph that is an AudioUnit, using the supplied
	ComponentDescription to find and open that unit.
	
	AudioUnits can also be reinstantiated from a saved state with serialized
	data - "class data" in the arguments below.
	
	Audio Units use a CFPropertyList (a constrained CFDictionary) to handle
	class data. In that case a size of zero should be passed in and the graph
	will take a retain on the CFPropertyList, which will be released when the
	node is removed from the graph.
	
	Because a CFPropertyList definition of the AU state contains the component
	description this call can be used with inDescription set to NULL and
	inClassDataSize to zero iff inClassData is one of these structures (which
	should be the normal case).

	(Passing a non-zero size was a previously drafted version of this API which
	is no longer supported as audio units now are expected to support the
	CFPropertyList version)... So, inClassDataSize should always be zero) - this
	parameter maybe re-tasked for some other usage later on.

	Of course, if you have no class data, set both size and ptr to 0.

	The call returns the new AUNode in outNode.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern OSStatus
AUGraphNewNode(	AUGraph						inGraph,
				const ComponentDescription	*inDescription,
				UInt32						inClassDataSize,// reserved: must be zero
				const void					*inClassData,
				AUNode						*outNode)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AUGraphNewNodeSubGraph
	
	This will create a node that represents a contained or member AUGraph.
	The AUGraph can be retrieved through the GetNodeInfoSubGraph call.
	The member AUGraph is owned by the parent graph and will be disposed when
	either:
	(1) The parent graph is disposed
	(2) The node is removed from the parent AUGraph
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern OSStatus
AUGraphNewNodeSubGraph( AUGraph				inGraph,
						AUNode				*outNode);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AUGraphRemoveNode

	Nodes can be removed from any thread context. However, the output node of
	the AUGraph, or a node that represents a sub-graph, cannot be removed from
	within the RenderCallback of the AUGraph (the graph would be running at that
	time and in the process of rendering). In that case an error
	(kAUGraphErr_CannotDoInCurrentContext) is returned. (The graph's output unit
	can be removed from any other thread of course).
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern OSStatus
AUGraphRemoveNode(  AUGraph			inGraph,
					AUNode			inNode)							AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
AUGraphGetNodeCount(AUGraph			inGraph,
					UInt32 			*outNumberOfNodes)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
AUGraphGetIndNode(  AUGraph			inGraph,
					UInt32 			inIndex,
					AUNode			*outNode)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AUGraphGetNodeInfo

	You can pass in NULL for any of the out parameters if you're not interested
	in that value.

	outClassDataSize should be set to zero - it is ignored

	outClassData should be passed a pointer to a CFPropertyListRef - this will
	handle then contain the current state of the audio unit, represented in this
	structure. If the application wants to use it, it should call CFRetain on
	the return value.

	See the comments on AUGraphNewNode for how the class data is handled
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

extern OSStatus
AUGraphGetNodeInfo(	AUGraph				inGraph,
					AUNode				inNode,
					ComponentDescription *outDescription,
					UInt32				*outClassDataSize,
					void				**outClassData,
					AudioUnit			*outAudioUnit)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
AUGraphGetNodeInfoSubGraph(	const AUGraph		inGraph,
							AUNode				inNode,
							AUGraph				*outSubGraph)		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
								
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AUGraphIsNodeSubGraph

	This returns true if the specified node is a subgraph
	it returns false if the specified node is not a subgraph
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern OSStatus
AUGraphIsNodeSubGraph(		const AUGraph		inGraph,
							AUNode				inNode,
							Boolean*			outFlag)			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
								
// connect a node's output to a node's input
extern OSStatus
AUGraphConnectNodeInput(	AUGraph			inGraph,
							AUNode			inSourceNode,
							UInt32			inSourceOutputNumber,
							AUNode			inDestNode,
							UInt32			inDestInputNumber)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// disconnect a node's input
extern OSStatus
AUGraphDisconnectNodeInput(	AUGraph			inGraph,
							AUNode			inDestNode,
							UInt32			inDestInputNumber)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

// start with a clean slate (all connections of all nodes)
extern OSStatus
AUGraphClearConnections(	AUGraph			inGraph)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


extern OSStatus
AUGraphGetNumberOfConnections(	AUGraph		inGraph,
								UInt32		*outNumConnections)		AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

// this returns the number of connections where the specified node is 
// either a source or a destination in the connection
extern OSStatus
AUGraphCountNodeConnections(	AUGraph 	inGraph,
								AUNode 		inNode,
								UInt32 		*outNumConnections)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Returns a list of connections where the specified node is either a source or
	destination. Pass in a number of connection structures that are used to
	receive the connection info. On input, ioNumConnections contains the number
	of connection structs that can be returned. On output, ioNumConnections
	contains the number of connections returned. The connections are returned in
	the order that they were made in the graph.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern OSStatus
AUGraphGetNodeConnections(		AUGraph						inGraph,
								AUNode						inNode,
								AudioUnitNodeConnection		*outConnections,
								UInt32						*ioNumConnections)	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

// it's OK to pass in NULL for any of the last four arguments
extern OSStatus
AUGraphGetConnectionInfo(	AUGraph		inGraph,
							UInt32		inConnectionIndex,
							AUNode		*outSourceNode,
							UInt32		*outSourceOutputNumber,
							AUNode		*outDestNode,
							UInt32		*outDestInputNumber)		AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AUGraphUpdate
	
	Call this after performing a series of "edits" on the AUGraph with calls 
	such as AUGraphConnectNodeInput() to finalize those edits.
	The call will be synchronous if outIsUpdated is NULL, 
	meaning it will block until the changes are incorporated
	into the graph OR an error is returned from the update process
	if outIsUpdated is non-NULL, then AUGraphUpdate() will return 
	immediately and outIsUpdated will equal "true" if the changes 
	were already made (no more changes to make) or "false" if changes are still
	outstanding.

	Calling from the AUGraphRenderNotification callback:
	Connection and Disconnection events can be completely processed
	in the render notification callback of the AUGraph
	Nodes can also be removed (except for the output node or a sub-graph of the AUGraph)
	as well. 

	Getting kAUGraphErr_CannotDoInCurrentContext as a result code:
	If AUGraphUpdate returns this result, then it means it was
	unable to process the update, due to an inability to safely
	alter the state of the graph (because another thread was accessing
	a call that relies on the graph's state having integrity).
	This result code is only a transitory state, which will pass as soon
	as your other thread's call to AUGraph (that has the lock) completes.

	If an error is encountered in the process of an update (say an invalid connection
	is attempted, a disconnection between nodes that are not connected, etc) on a running graph, 	then the call will return that error code. It only process events whilst it receives
	no error results. Thus, if an error is encountered, other events will not be
	processed until AUGraphUpdate is called again. This is done, in cases where
	the state of the graph could become inconsistent if further events were processed, so
	this decision is left up to you. The same applies to the "cant do" error - you have
	to explicitly call AUGraphUpdate again to have the processing of the events occur.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern OSStatus
AUGraphUpdate(		AUGraph			inGraph,
					Boolean			*outIsUpdated)					AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	The following calls must be made in this order:

	AUGraphOpen()			
			- AudioUnits are open but not initialized (no resource allocation occurs here)
	AUGraphInitialize()			
			- AudioUnitInitialize() is called on each opened node/AudioUnit
				(get ready to render) and SubGraph
	AUGraphStart()	
			- ...Start() is called on the "head" node(s) of the AUGraph	(now rendering starts)
	AUGraphStop()					
			- ...Stop() is called on the "head" node(s) of the AUGraph	(rendering is stopped)
	AUGraphUninitialize()		
			- AudioUnitUninitialize() is called on each open AudioUnit and SubGraph
	AUGraphClose()			
			- all AudioUnits are closed - leaving only its nodal representation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

extern OSStatus
AUGraphOpen(			AUGraph		inGraph)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
AUGraphClose(			AUGraph		inGraph)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
AUGraphInitialize(		AUGraph		inGraph)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
AUGraphUninitialize(	AUGraph		inGraph)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
AUGraphStart(			AUGraph		inGraph)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern OSStatus
AUGraphStop(			AUGraph		inGraph)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


extern OSStatus
AUGraphIsOpen(			AUGraph		inGraph,
						Boolean		*outIsOpen)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
							
extern OSStatus
AUGraphIsInitialized(	AUGraph		inGraph,
						Boolean		*outIsInitialized)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
							
extern OSStatus
AUGraphIsRunning(		AUGraph		inGraph,
						Boolean		*outIsRunning)					AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
						
extern OSStatus
AUGraphGetCPULoad(		AUGraph		inGraph,
						Float32		*outAverageCPULoad)				AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

extern OSStatus
AUGraphGetMaxCPULoad(	AUGraph		inGraph,
						Float32		*outMaxLoad)					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AUGraph Render Notifications
	
	In previous release this call would only allow one notification
	Now, multiple notifications can be registered, and are differentiated
	based on both the inCallback AND the inRefCon

	Passing in NULL as the inCallback will remove all render notifications
	To remove a specific render notification, you should use the 
	AUGraphRemoveRenderNotification passing in the inCallback and the inRefCon
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	These calls are used for an AUGraph that has AudioUnits of 'aunt' type
	see <AudioUnit/AUNTComponent.h> (V1)
	
	These API are deprecated (as is the V1 AU) and developers should only be using the V2
	based AU's (and their supporting API)...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern OSStatus
AUGraphSetRenderNotification(		AUGraph					inGraph,
									AudioUnitRenderCallback inCallback,
									void 					*inRefCon)	AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus
AUGraphRemoveRenderNotification(	AUGraph					inGraph,
									AudioUnitRenderCallback inCallback,
									void 					*inRefCon)	AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	These calls are used for an AUGraph that has AudioUnits of 'auxx' type
	where xx is a type that corresponds to one of the various types 
	of the AudioUnit v2 - see <AudioUnit/AUComponent.h>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern OSStatus
AUGraphAddRenderNotify(			AUGraph					inGraph,
								AURenderCallback 		inCallback,
								void 					*inRefCon)		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

extern OSStatus
AUGraphRemoveRenderNotify(		AUGraph					inGraph,
								AURenderCallback 		inCallback,
								void 					*inRefCon)		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#if defined(__cplusplus)
}
#endif


#endif // __AUGraph.h


