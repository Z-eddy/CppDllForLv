/* This header file contains the LV data structures and the list of functions 
   this dll exports.  A brief explanation of how each type of data is stored in
   LabVIEW memory is described.

*/
#include "extcode.h"

// Specific for CVI compilier to ensure data is packed by 1 byte.  
// For other compiliers there are settings to force 1-byte alignment.
// In MSVC++ 6.0 under Project>>Settings C/C++ Tab, in the category 
// for Code Generation, make sure the struct alignment is set to 1 
// byte to achive the same result.
#pragma pack(1)

// A 2-D array of 16 bit integers. The first parameters is an array of sizes.
// Since there are only 2 elements in the array, it's a 2-D array with each element
// in the array specifying how many numbers are in that dimension.  If the elements
// were 4 and 5, data would contain a 4x5 matrix.  Notice that even though this is a 2-D
// array, it is represented as a 1-D array of contiguous memory with 4X5 elements.  
// After the array of dimensions comes the matrix of data.
typedef struct {
  	int32 dimSizes[2];
  	int16 data[1];
} TD2;
// LabVIEW can pass handles to structures.  A handle is a pointer 
// to a pointer to the structure. 
typedef TD2 **TD2Hdl; //TD2Hdl is a handle 


// A 1-D array of doubles.  The first 32 bits are used to 
// store the size of the array.  Then the array of numbers follows 
// immediately afterwards
typedef struct {
	int32 dimSize;
	float64 arg1[1];
	} TD1;
typedef TD1 **TD1Hdl;

// A 1-D array of booleans
typedef struct {
	int32 dimSize;
	LVBoolean buf[1];
} LVBoolArray;
typedef LVBoolArray **LVBoolArrayHdl;

// A 1-D array of handles pointing to strings (ie an array of strings)
typedef struct {
	int32 dimSize;
	LStrHandle Strings[1];
} LVStringArray;
typedef LVStringArray **LVStrArrayHdl;

// A cluster with a double, string, double array, and a boolean in it
typedef struct {
  	float64 lvDouble;
  	LStrHandle lvString;
  	TD1Hdl lvDoubleArray;
  	LVBoolean lvBool;
} LVCluster;

// Tells CVI to align structures by 1 byte instead of default 8, corresponds 
// with above pragma command.
#pragma pack()


// The functions

// Modifies the contents of a 1-D array (NOTE it is passed as a double*) So LV 
// data types aren't required.  This method is convient, but crashing LV can 
// occur if you write past bounds of array.
_declspec(dllexport) int32 __cdecl Modify1DArray(double* in_array, int32 size);

// Does the same thing as above example, but uses LV data structure with size 
// of array built in.  This helps make it easier to keep track of size to 
// prevent writing past bounds.
_declspec(dllexport) int32 __cdecl ModifyLV1DArray(TD1Hdl in_array,double *arr,int size);

// Dynamically resizes a 1-D array to size and fills with data
_declspec(dllexport) int32 __cdecl Dynamic1DArrayResize(TD1Hdl in_array, int32 size);

// Modifies the contents of a 2-D array passed in from LabVIEW as a double*, so size
// information is required
_declspec(dllexport) int32 __cdecl Modify2DArray(double* in_array, int32 nrows, int32 ncols); 

// Modifies the contents of 2-D array passed as a handle to a LabVIEW structure, so 
// size information is in the structure.
_declspec(dllexport) int32 __cdecl Modify2DLVArray(TD2Hdl in_array);  

// Dynamically resizes a 2-D array and fills with new data
_declspec(dllexport) int32 __cdecl Dynamic2DArrayResize(TD2Hdl in_array, int32 nrows, int32 ncols);

// Modifies contents of string, can't change size of string though (NOTE it is a 
// char*, so size of the string passed in is not known.  Can use strlen to get 
// length.  (see C code)
_declspec(dllexport) int32 __cdecl ModifyString (char* in_string);  

// Modify a String (exactly same as above), but passes string as a LabVIEW string 
// instead of a C string
_declspec(dllexport) int32 __cdecl ModifyLVString(LStrHandle in_array);

// Dynamically changes size of string in LabVIEW
_declspec(dllexport) int32 __cdecl DynamicStringResize(LStrHandle in_string, int32 size);

// Dynamically creates an array of strings with different lengths for each string.  
// The array has size number of strings
_declspec(dllexport) int32 __cdecl DynamicStringArrayResize(LVStrArrayHdl in_array, int32 size);    

// Dynamically creates an array of booleans.
_declspec(dllexport) int32 __cdecl Dynamic1DBoolArrayResize(LVBoolArrayHdl in_array, int32 size);

// Modifies the contents of a cluster passed in from LabVIEW with an  
// array of numbers, a string, a boolean, and a number
_declspec(dllexport) int32 __cdecl ModifyCluster(LVCluster *in_cluster);    

// Note all LV passes handles to all these datatypes, except a cluster which is 
// passed as a pointer to the structure
