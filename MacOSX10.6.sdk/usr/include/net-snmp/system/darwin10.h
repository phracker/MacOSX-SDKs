/* This is a place for the changes needed to get net_snmp runnning on darwin10 including 
   support for GCC 4.2
   Currently this just enatils including darwin9.h
*/

#include "darwin9.h"

#ifndef darwin10
#   define darwin10 darwin
#endif
