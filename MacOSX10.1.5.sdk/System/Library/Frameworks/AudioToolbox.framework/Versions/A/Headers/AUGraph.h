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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	AUGraph.h
//
//		subsystem  for maintaining arbitrary graphs of AudioUnits
//
//		The AUGraph APIs are responsible for representing the description of a
//		set of AudioUnit components, as well as the audio connections between
//		their inputs and outputs.  This representation may be saved/restored persistently
//		and "instantiated" (AUGraphOpen() ) by opening all of the AudioUnits, and making the physical
//		connections between them stored in the representation.  Thus the AUGraph is
//		a description of the various AudioUnits and their connections, but also may
//		manage the actual instantiated AudioUnits if AUGraphOpen() is actually called.
//		The AUGraph, in essence, is a complete description of an audio signal processing
//		network.
//
//		The AUGraph may be introspected, in order to get complete information about all
//		of the AudioUnits in the graph.  The various nodes (AUNode) in the AUGraph 
//		representing AudioUnits may be added or removed, and the connections between
//		them modified.
//
//		An AUNode representing an AudioUnit component is created by specifying a
//		ComponentDescription record (from the Component Manager), as well as
//		optional "class" data, which is passed to the AudioUnit when it is opened.
//		This "class" data is in an arbitrary format, and may differ depending on the
//		particular AudioUnit.  In general, the data will be used by the AudioUnit
//		to configure itself when it is opened (in object-oriented terms, it corresponds
//		to constructor arguments).  In addition, certain AudioUnits may provide their
//		own class data when they are closed, allowing their current state to be saved
//		for the next time they are instantiated.  This provides a general mechanism
//		for persistence.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#pragma once

#ifndef __AUGraph
#define __AUGraph

#include <CoreServices/CoreServices.h>
#include <AudioUnit/AudioOutputUnit.h>

#if defined(__cplusplus)
extern "C"
{
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// AUGraph and AUNode stuff
typedef long 	AUNode;
typedef	struct OpaqueAUGraph	*AUGraph;

enum {
	kAUGraphErr_NodeNotFound = -10860
};

// construction / destruction
extern OSStatus NewAUGraph(			AUGraph			*outGraph );
extern OSStatus DisposeAUGraph(		AUGraph			inGraph );

// if the node has no associated class data, pass in
// zero for inClassDataLength, and NULL for inClassData
extern OSStatus AUGraphNewNode(		AUGraph					inGraph,
								ComponentDescription	*inDescription,
								UInt32					inClassDataLength,
								const void				*inClassData,
								AUNode					*outNode	);



extern OSStatus AUGraphRemoveNode(		AUGraph			inGraph,
								AUNode			inNode	);

extern OSStatus AUGraphGetNodeCount(	AUGraph			inGraph,
								UInt32 			*outNumberOfNodes );

extern OSStatus AUGraphGetIndNode(		AUGraph			inGraph,
								UInt32 			inIndex,
								AUNode 			*outNode );

extern OSStatus AUGraphGetNodeInfo(	AUGraph					inGraph,
								AUNode					inNode,
								ComponentDescription	*outDescription,		// pass in NULL if not interested
								UInt32					*outClassDataLength,	// pass in NULL if not interested
								void					**outClassData,			// pass in NULL if not interested
								AudioUnit 				*outAudioUnit /* 0 if component not loaded (graph is not wired) */ );

// connect a node's output to a node's input
extern OSStatus AUGraphConnectNodeInput(	AUGraph			inGraph,
									AUNode			inSourceNode,
									UInt32			inSourceOutputNumber,
									AUNode			inDestNode,
									UInt32			inDestInputNumber	);

// disconnect a node's input
extern OSStatus AUGraphDisconnectNodeInput(	AUGraph			inGraph,
									AUNode			inDestNode,
									UInt32			inDestInputNumber	);

// start with a clean slate (all connections of all nodes)
extern OSStatus AUGraphClearConnections(	AUGraph			inGraph );


extern OSStatus AUGraphGetNumberOfConnections(	AUGraph		inGraph,
                                                UInt32		*outNumberOfConnections );

// it's OK to pass in NULL for any of the last four arguments                                                
extern OSStatus AUGraphGetConnectionInfo(	AUGraph		inGraph,
                                                UInt32		inConnectionIndex,
                                                AUNode		*outSourceNode,
                                                UInt32		*outSourceOutputNumber,
                                                AUNode		*outDestNode,
                                                UInt32		*outDestInputNumber );


// Call this after performing a series of "edits" on the AUGraph with calls such as AUGraphConnectNodeInput()
// to finalize.
// The call will be synchronous if outIsUpdated is NULL, meaning it will block until the changes are incorporated
// into the graph
// if outIsUpdated is non-NULL, then AUGraphUpdate() will return immediately and outIsUpdated will equal
// "true" if the changes were already made (no more changes to make) or "false" if the changes are still
// outstanding
extern OSStatus AUGraphUpdate(				AUGraph			inGraph,
									Boolean			*outIsUpdated );

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// The following calls must be made in this order:
//
//		AUGraphOpen()			AudioUnits are open but not initialized (no resource allocation occurs here)
//		AUGraphInitialize()			AudioUnitInitialize() is called on each open AudioUnit (get ready to render)
//		AUGraphStart()					...Start() is called on the "head" node(s) of the AUGraph	(now rendering starts)
//		AUGraphStop()					...Stop() is called on the "head" node(s) of the AUGraph	(rendering is stopped)
//		AUGraphUninitialize()		AudioUnitUninitialize() is called on each open AudioUnit
//		AUGraphClose()			all AudioUnits are closed



// instantiate the graph from the representation (opens all AudioUnits )
extern OSStatus AUGraphOpen(				AUGraph			inGraph );

// destroy the built graph (leaving only the representation -- closes all AudioUnits)
extern OSStatus AUGraphClose(				AUGraph			inGraph );

// fully initialize the AudioUnits (calls AudioUnitInitialize() on each) to prepare for audio processing
extern OSStatus AUGraphInitialize(			AUGraph			inGraph );

// uninitialize the AudioUnits (calls AudioUnitUninitialize() on each) without closing the components
extern OSStatus AUGraphUninitialize(		AUGraph			inGraph );

// instructs the graph to start rendering
extern OSStatus AUGraphStart(		AUGraph			inGraph );

// instructs the graph to stop rendering
extern OSStatus AUGraphStop(		AUGraph			inGraph );


// query APIs
extern OSStatus AUGraphIsOpen(			AUGraph			inGraph,
								Boolean			*outIsOpen );
							
extern OSStatus AUGraphIsInitialized(	AUGraph			inGraph,
								Boolean			*outIsInitialized );
							
extern OSStatus AUGraphIsRunning(		AUGraph			inGraph,
								Boolean			*outIsRunning );
							
extern OSStatus AUGraphSetRenderNotification(	AUGraph					inGraph,
												AudioUnitRenderCallback inCallback,
												void 					*inRefCon );



extern OSStatus AUGraphGetCPULoad(		AUGraph		inGraph,
                                                Float32		*outCPULoad );


                                                
                                            
							
#if defined(__cplusplus)
}
#endif


#endif // __AUGraph.h


