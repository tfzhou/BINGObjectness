#include "mex.h"

/** Objectness headers
 */
#include "Objectness/Src/kyheader.h"
#include "Objectness/Src/Objectness.h"
#include "Objectness/Src/CmShow.h"
#include "Objectness/Src/DataSetVOC.h"
#include "Objectness/Src/ValStructVec.h"

/** C++
 */
#include <iostream>
using namespace std;

/** From mexOpencv
 */
#include "MxArray.hpp"

/** Input Arguments
 */
#define VOC_IN        prhs[0]
#define BASE_IN       prhs[1]
#define W_IN          prhs[2]
#define NUM_PER_SZ_IN prhs[3]

/** Output Arguments
 */
#define BB_OUT plhs[0]

/** Default Parameters
 */
#define NUM_PER_SZ 130

extern "C" mxArray* mxCreateReference(mxArray*);

void mexFunction( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] )
{
  char*   voc       = NULL;
  char*   modelName = NULL;
  
  int     modelLoaded = 0;
  
  if( nrhs < 1 ) mexErrMsgTxt("... [ At least 3 inputs required ( voc2007 )");
  
  voc = mxArrayToString(VOC_IN);
  
  const string str(voc);
  DataSetVOC voc2007( str );
  voc2007.loadAnnotations();
  
  Objectness objectness( voc2007 );
  
  vector<vector<Vec4i>> _boxesTests;
  objectness.getObjBndBoxesForTestsFast( _boxesTests, NUM_PER_SZ );
  
  int nTest = _boxesTests.size();
  BB_OUT = mxCreateCellMatrix(nTest, 1);
  
  int k, ix, iy, idx;
  for(k = 0; k < nTest; k++)
  {
    vector<Vec4i> bbs = _boxesTests[k];
    int nBB = bbs.size();
    mxArray* boxes = mxCreateNumericMatrix( nBB, 4, mxUINT32_CLASS, mxREAL );
    uint* outptr = (uint*) mxGetData(boxes);
    
    for(int iy = 0; iy < nBB; iy++ )
    {
      Vec4i bb = bbs[iy];
      for( ix = 0; ix < 4; ix++ )
      {
        idx = iy + ix * nBB;
        outptr[idx] = bb[ix];
      }
    }
    
    mxSetCell(BB_OUT, k, mxCreateReference(boxes));
    mxDestroyArray(boxes);
  }
  
  /** Clean memory
   */
  mxFree( voc );
  mxFree( modelName );
  
}