clc; clear;

if isunix
  
  include = ' -I/usr/local/include/opencv/ -I/usr/local/include/';
  libpath = '/usr/local/lib/';
  
  files = dir([libpath 'libopencv*.so']);
  lib = [];
  for( i = 1 : length(files) )
    lib = [lib ' ' libpath files(i).name];
  end
  
  objPath    = 'Objectness/Src/';
  linearPath = [objPath 'LibLinear/'];
  blasPath   = [linearPath 'blas/'];
  
  % Objectness 
  eval( ['mex -v CXXFLAGS="\$CXXFLAGS -std=c++0x" -O -c ' objPath 'DataSetVOC.cpp ' objPath 'CmFile.cpp ' ...
                      objPath 'CmShow.cpp ' objPath 'FilterTIG.cpp ' objPath 'Objectness.cpp '] );
                   
  % LibLinear
  eval( ['mex CXXFLAGS="\$CXXFLAGS -std=c++0x" -O -c ' linearPath 'linear.cpp ' linearPath 'tron.cpp'  ] )
  
  % BLAS
  eval( ['mex CXXFLAGS="\$CXXFLAGS -std=c++0x" -O -c ' blasPath 'daxpy.c ' blasPath 'ddot.c ' blasPath 'dnrm2.c ' blasPath 'dscal.c'])
  
  % MxArray
  mex -O -c MxArray.cpp;

  objectfiles = dir(['*.o']);
  objects = [];
  for( i = 1 : length(objectfiles) )
    objects = [ objects ' ' objectfiles(i).name ];
  end
  
  eval(['mex BINGSingle.cpp' include lib objects ' CFLAGS="\$CFLAGS -fopenmp" LDFLAGS="\$LDFLAGS -fopenmp" ']);
  eval(['mex trainBING.cpp' include lib objects ' CFLAGS="\$CFLAGS -fopenmp" LDFLAGS="\$LDFLAGS -fopenmp" ']);
  eval(['mex BINGMultiple.cpp' include lib objects ' CFLAGS="\$CFLAGS -fopenmp" LDFLAGS="\$LDFLAGS -fopenmp" ']);
  
  delete *.o
end