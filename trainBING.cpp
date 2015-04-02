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
#define NSS_IN        prhs[3]
#define NUM_PER_SZ_IN prhs[4]

/** Output Arguments
 */
// #define BB_OUT prhs[0] 

/** Default Parameters
 */
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
  
  if( nrhs < 1 ) mexErrMsgTxt("... [ At least 1 inputs required ( voc2007 )");
  if( nrhs > 5 ) mexErrMsgTxt("--- [ No more than 5 inputs required ( voc2007, base, W, NSS, numPerSz )");
  
  voc = mxArrayToString( VOC_IN );
  
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
  
  const string str( voc );
  DataSetVOC voc2007( str );
  voc2007.loadAnnotations();
  
  Objectness objectness( voc2007, base, W, NSS );
  objectness.trainObjectness( numPerSz );
    
  /** Clean memory
   */
  mxFree( voc );
}