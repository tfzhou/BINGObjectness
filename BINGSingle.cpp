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
#define BASE_IN       prhs[2]
#define W_IN          prhs[3]
#define NSS_IN        prhs[4]
#define NUM_PER_SZ_IN prhs[5]

/** Output Arguments
 */
#define BB_OUT plhs[0]

/** Default Parameters
 */
#define uint unsigned int

#define _BASE 2
#define _W    8
#define _NSS  2
#define _NUM_PER_SZ 130

void mexFunction( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] )
{
  char*   voc = NULL;
  double base = _BASE;
  int    W    = _W;
  int    NSS  = _NSS;
  int    numPerSz = _NUM_PER_SZ;
  
  if( nrhs < 2 ) mexErrMsgTxt("... [ At least 2 inputs required ( image, vocPath )");
  if( nrhs > 6 ) mexErrMsgTxt("--- [ No more than 6 inputs required ( image, voc2007, base, W, NSS, numPerSz )");
  
  voc = mxArrayToString(VOC_IN);
  if( nrhs >= 2 )
  {
    base      = (double) mxGetScalar( BASE_IN );
  }
  if( nrhs >= 3 )
  {
    W         = (int)    mxGetScalar( W_IN );
  }
  if( nrhs >= 4 )
  {
    NSS       = (int)    mxGetScalar( NSS_IN );
  }
  if( nrhs == 5 )
  {
    numPerSz  = (int)    mxGetScalar( NUM_PER_SZ_IN );
  }
  
  const string str(voc);
  DataSetVOC voc2007( str );
  voc2007.loadAnnotations();
  Objectness objectness( voc2007, base, W, NSS );
  
  vector<Vec4i> boxes;
  cv::Mat image = MxArray(IMAGE_IN).toMat();
  objectness.getObjBndBoxesForTest( image, boxes, numPerSz );
  
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
}