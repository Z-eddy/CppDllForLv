#include "CtoLV.h"

// Changes the contents of a 1-D array NOTE LV passes the data as a double*, so no size information is available
// and the additional paramter size tells us how many elements were in the LV array.
int32 Modify1DArray(double* in_array, int32 size)
{
  //If you don't modify the size of the array passed in by labview, you can use double*
  //instead of LabVIEW datatypes like TD1Hdl.
  int32 i;
  
  for (i=0; i < size; i++)
    in_array[i]= (float64)(i+.5);
  return 0;
}

// Modifies contents of LV array.  Since the LV array structure is passed, the size information 
// is in this structre.
int32 ModifyLV1DArray(TD1Hdl in_array)
{
  //if you use LV data types, the size information is inside the structure.
  
  int32 i;
  
  for (i=0; i < (*in_array)->dimSize; i++)
    (*in_array)[1].arg1[i-1] = (float64)(i+0.5);
  return 0;
}

// Dynamically resizes a 1-D array to size and fills with data
int32 Dynamic1DArrayResize(TD1Hdl in_array, int32 size) 
{
  MgErr error;
  int32 i;     
	
  // The first 32 bits are used for size information, and then the array comes after the size
  error = DSSetHandleSize(in_array, sizeof(int32) + size*sizeof(float64) );
  if (error != mFullErr && error != mZoneErr)
  {
    (*in_array)->dimSize = size;
    
    for (i=0;i < size;i++)
    {
      (*in_array)[1].arg1[i-1]=(float64)(i +.5);
	}
    return 0;
  }
  else return -1;
}
    
// Changes the values in a 2-D array passed from LV.  Note it's passed as a double* since LV stores it as a 1-D
// array.  No size information is in the double*, so these values must be passed with the matrix.
int32 Modify2DArray(double* in_array, int32 nrows, int32 ncols)
{
  int32 i,j;

  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
      in_array[i*ncols+j] = i*ncols+j;
  return 0;
}

// Dynamically creates and fills 2-D array with it's index.  A 2-D array in LV is 
// actually represented as a 1-D array with MxN elements where M is the number 
// of columns and N is the number of rows.
int32 Dynamic2DArrayResize(TD2Hdl in_array, int32 nrows, int32 ncols)
{
	MgErr error;
	int32 i, j;     /* use LV datatypes for portability */
	
	// note that the data is in 1-D format with size=rows*cols.  All of row 0 is first, then
	// row 1, etc.  This is how they are stored in LV's memory.  The first two 32 bits number 
	// tells labview how many rows and columns are in the array.
    error = DSSetHandleSize(in_array, sizeof(int32)*2 + nrows*ncols*sizeof(int16) );
	if (error != mFullErr && error != mZoneErr)  
	{
	  // Sets number of rows and columns.  These numbers are part of the structure LV uses for 2-D arrays
	  (*in_array)->dimSizes[0] = nrows;
	  (*in_array)->dimSizes[1] = ncols;
	  
	  // Fill 2-D array with their index, so it's in column-major order.
	  for (i=0; i<nrows; i++)
	    for (j=0; j<ncols; j++)
	      (*in_array)->data[i*ncols+j] = i*ncols+j;
	  return 0;
	 }
	 else return -1;  //return -1 if error allocating space
}

//The function modifies a 2-D array passed as a handle to a LabVIEW structure.
// Size information is already in structure.
int32 Modify2DLVArray(TD2Hdl in_array)
{
  int32 i,j, ncols, nrows;
  
  ncols = (*in_array)->dimSizes[0];
  nrows = (*in_array)->dimSizes[1];
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
      (*in_array)->data[i*ncols+j]=i*ncols+j;
  return 0;
}

// Changes the contents of a string.  NOTE it passes a char*
int32 ModifyString (char* in_string)
{
  // If you don't change size of string, you can pass char*
  // No size information in char*, so use strlen to get length of string
  
  int32 i;
  
  for (i=0; i<strlen(in_string); i++)
    in_string[i] = in_string[0]+i;	  //shift all letters up one starting with first letter
  return 0;							  // so "hello" becomes "hijkl"
}

//Changes the contents of a string.  Passes string as a LV structure, with size information
// inside the structure
int32 ModifyLVString(LStrHandle in_array)
{
  int32 i;
  
  for (i=0; i<(*in_array)->cnt; i++)
    (*in_array)->str[i] = (*in_array)->str[0]+i;
  return 0;
}
      
// Changes the size of a string
int32 DynamicStringResize(LStrHandle in_string, int32 size)
{
  MgErr error; 
  int32 i;
  
  // Strings have the first 32 bits determine how many characters are in the string
  error = DSSetHandleSize(in_string, sizeof(int32) + size*sizeof(uChar) ); 
  if (error != mFullErr && error != mZoneErr)  
  {
    (*in_string)->cnt=size;
    for (i=0; i<size; i++)
      (*in_string)->str[i]=(uChar)(65+i);  //65 is decimal for character 'A'
	return 0;
  }
  else return -1;
}

// Dynamically creates an array of strings with size elements.  The size of each string is randomly long.
int32 DynamicStringArrayResize(LVStrArrayHdl in_array, int32 size)
{
  MgErr error; 
  int32 i, j;
  float64 LVRand;
  int32 StringLen, Current=65;
  
  // An array of strings actually consists of the first 32 bits tell how many strings there are and then 
  // there is an array of handles to strings
  error = DSSetHandleSize(in_array, sizeof(int32) + size*sizeof(LStrHandle) );
  if (error != mFullErr && error != mZoneErr)  
  {
    (*in_array)->dimSize = size;
    for (i=0; i<size; i++)
    {
      RandomGen(&LVRand);	 			// Make each string a random length 
      StringLen = (int32)(LVRand*5+2);  // from 2 to 7 characters
      // Each handle to a string must be allocated
      (*in_array)->Strings[i] = (LStrHandle)(DSNewHandle(sizeof(int32) + StringLen*sizeof(uChar)));
        
      (*(*in_array)->Strings[i])->cnt=StringLen;
      for (j=0; j<StringLen; j++)
        (*(*in_array)->Strings[i])->str[j]=Current++;  //Starts with the letter 'A'
    }
    return 0;
  }
  else return -1;
}      

// Dynamically creates a 1-D boolean array of size.
int32 Dynamic1DBoolArrayResize(LVBoolArrayHdl in_array, int32 size)
{
  MgErr error; 
  int32 i;
  
  // first 32 bits tell size of array
  error = DSSetHandleSize(in_array, sizeof(int32) + size*sizeof(LVBoolean) );
  if (error != mFullErr && error != mZoneErr)  
  {
    (*in_array)->dimSize = size;
    for (i=0; i<size; i++)
	  (*in_array)->buf[i]=i%2; // Alternating True False
	return 0;
  }
  return -1;
}


// Modifies contents of cluster.  Cluster had a double, string, array of doubles, and boolean
// See header file to view cluster prototype.  Note in_cluster is a pointer, not a handle.  
// All other datatypes in this code uses handles, clusters are passed differently from LV though.  
int32 ModifyCluster(LVCluster* in_cluster)
{
	MgErr error;
	int32 i;
	
	// Assign value to double in cluster
	in_cluster->lvDouble = 1.23;
	
	// Allocate space for LabVIEW string with 5 characters
	DSSetHandleSize(in_cluster->lvString, sizeof(int32) + 5*sizeof(uChar) );
	// Set the size paramater of the LV string structure
	(*(in_cluster->lvString))->cnt=5;
	// Fill the LV string with the string we want in the cluster
    strcpy ( (*(in_cluster->lvString))->str, "hello" );
    
    // Allocate space for array of doubles (float64)
    DSSetHandleSize(in_cluster->lvDoubleArray, sizeof(int32) + 5*sizeof(float64) );
    // Set size paramater of the LV array structure
    (*(in_cluster->lvDoubleArray))->dimSize=5;
    // Fill array with numbers we want in the cluster
    for (i=0; i<5; i++)
      (*(in_cluster->lvDoubleArray))->arg1[i]=(float64)i/5;
      
    // Assign true to LV boolean
	in_cluster->lvBool=LVTRUE;
	return 0;
}
  
