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
#define IMAGE_IN      prhs[0]
#define VOC_IN        prhs[1]
#define MODELNAME_IN  prhs[2]

/** Output Arguments
 */
#define BB_OUT plhs[0]

/** Default Parameters
 */
#define NUM_PER_SZ 10

#define uint unsigned int

void mexFunction( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] )
{
  char*   voc       = NULL;
  char*   modelName = NULL;
  
  int     modelLoaded = 0;
  
  if( nrhs < 3 ) mexErrMsgTxt("... [ At least 3 inputs required ( image, ws1, ws2 )");
  
  voc       = mxArrayToString(VOC_IN);
  modelName = mxArrayToString(MODELNAME_IN);
  
  const string str(voc);
  DataSetVOC voc2007( str );
  voc2007.loadAnnotations();
  Objectness objectness( voc2007 );
  
  vector<Vec4i> boxes;
  cv::Mat image = MxArray(IMAGE_IN).toMat();
  objectness.getObjBndBoxesForTest( image, boxes, NUM_PER_SZ );
  
  /** Return value
   */
  int nBB = boxes.size();
  BB_OUT = mxCreateNumericMatrix( nBB, 4, mxUINT32_CLASS, mxREAL );
  uint* outptr = (uint*) mxGetData(BB_OUT);
  
  int ix, iy, idx;
  for( iy = 0; iy < nBB; iy++ )
  {
    Vec4i bb = boxes[iy];
    for( ix = 0; ix < 4; ix++ )
    {
      idx = iy + ix * nBB;
      outptr[idx] = bb[ix];
    }
  }
  
  /** Clean memory
   */
  mxFree( voc );
  mxFree( modelName );
  
}