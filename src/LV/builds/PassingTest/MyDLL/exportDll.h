#include "extcode.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
	int32_t dimSize;
	double element[1];
} DoubleArrayBase;
typedef DoubleArrayBase **DoubleArray;

/*!
 * ExportLvDll
 */
void __cdecl ExportLvDll(int32_t count, DoubleArray *outArray);

MgErr __cdecl LVDLLStatus(char *errStr, int errStrLen, void *module);

/*
* Memory Allocation/Resize/Deallocation APIs for type 'DoubleArray'
*/
DoubleArray __cdecl AllocateDoubleArray (int32 elmtCount);
MgErr __cdecl ResizeDoubleArray (DoubleArray *hdlPtr, int32 elmtCount);
MgErr __cdecl DeAllocateDoubleArray (DoubleArray *hdlPtr);

void __cdecl SetExecuteVIsInPrivateExecutionSystem(Bool32 value);

#ifdef __cplusplus
} // extern "C"
#endif

