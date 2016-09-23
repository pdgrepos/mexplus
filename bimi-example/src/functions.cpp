#include <mexplus.h>

using namespace mexplus;

MEX_DEFINE(spit_mtx) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {
  InputArguments input(nrhs, prhs, 0);
  // min(nargout) = 1 to have 'ans' populated
  OutputArguments output(nlhs > 0 ? nlhs : 1, plhs, 1);

  int r = 5, c =2;
  MxArray mxa(MxArray::Numeric<double>(r, c));

  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      mxa.set(i, j, i*c + j + 1);
    }
  }

  plhs[0] = mxa.release();

}

MEX_DEFINE(reshape) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {
  InputArguments input(nrhs, prhs, 0);
  OutputArguments output(nlhs > 0 ? nlhs : 1, plhs, 1);

  std::vector<double> v;
  for (int i = 0; i < 16; ++i) v.push_back(i+1);

  output.set(0, v);

  mxArray* tmp = plhs[0];
  mwSize dimensionSize = mxGetNumberOfDimensions(tmp);
  const mwSize* dimensions = mxGetDimensions(tmp);
  std::vector<mwSize> vdims(dimensions, dimensions + dimensionSize);

  vdims[0] = 4;
  vdims[1] = 2;
  vdims.push_back(2);

  int ans = mxSetDimensions(tmp, &vdims[0], 3);
  mexPrintf("Reshape:\n  retcode := %i\n  result  := %s\n", ans, ans == 0 ? "OK" : "KO" );

}

void printFields(const MxArray& mxa , int level) {

  std::vector<std::string> fields = mxa.fieldNames();

  for (std::vector<std::string>::const_iterator i = fields.begin(); i != fields.end(); ++i) {
    std::string spc(2 + 2*level,' ');    
    mexPrintf("%s%s\n", spc.c_str(),i->c_str());
    
    MxArray m(mxa.at(*i));
    if (m.isStruct()) {
      printFields(m,++level);
    }
  }

}

MEX_DEFINE(describe) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {
  InputArguments input(nrhs, prhs, 1);
  OutputArguments output(nlhs > 0 ? nlhs : 1, plhs, 1);

  MxArray my(prhs[0]);

  if (my.isStruct()) {
    mexPrintf("=== BEGIN ===\n");
    printFields(my,0);
    mexPrintf("=== END ===\n");
  }

  output.set(0, true);

}


/* ==========   UTILITIES   ========== */
template<class T>
std::string xtos(const T& x) {
  std::ostringstream s;
  s << x;
  return s.str();
}

template<class T>
T stox(const std::string & s) {
  std::istringstream stream(s);
  T x;
  stream >> x;
  return x;
}
