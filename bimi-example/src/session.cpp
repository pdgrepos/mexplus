#include <../containers/include/matrix.h>
#include <mexplus.h>
#include <string>
#include <map>

class SimpleObject {

  typedef std::map<std::string,double> container;

  public:
    std::string Name;
    std::matrix<double> dMTX;
    std::matrix<std::string> sMTX;

    SimpleObject(const std::string& name) {
      Name = name;
    }

    virtual ~SimpleObject() {}

    bool add(const std::string& key, double value) {
      std::pair<container::iterator,bool> ans = records_.insert(
        container::value_type(key, value)
      );
      return ans.second;
    }

    double query(const std::string& key) const {
      container::const_iterator record  = records_.find(key);
      return (record != records_.end()) ? record->second : std::numeric_limits<double>::quiet_NaN();
    }

  private:
    container records_;

};

void debugprint(std::string message) {
#ifndef NDEBUG
  mexPrintf("%s\n", message.c_str());
#endif
}

/* ===================================================== */
/* ==========   std::matrix<T> overloadings   ========== */
/* ===================================================== */
namespace mexplus {

  /* ========================= */
  /* =====  MxArray::to  ===== */
  /* ========================= */
  template <typename T>
  void stdmatrix_to(const mxArray* array, std::matrix<T>* mtx) {
    MxArray mxa(array);
    mtx->clear();
    for (mwSize i = 0; i < mxa.rows() ; ++i) {
      for (mwSize j = 0; j < mxa.cols() ; ++j) {
        mtx->push_back(mxa.at<T>(i,j));
      }
    }
    mtx->reshape(mxa.rows(),mxa.cols());
  }

  template <>
  void MxArray::to(const mxArray* array, std::matrix<double>* mtx) {
    stdmatrix_to(array, mtx);
  }

  template <>
  void MxArray::to(const mxArray* array, std::matrix<std::string>* mtx) {
    stdmatrix_to(array, mtx);
  }

  /* =========================== */
  /* =====  MxArray::from  ===== */
  /* =========================== */
  template <typename T>
  mxArray* CreateMxArray(int rows = 1, int columns = 1) {
    return MxArray::Numeric<T>(rows, columns);
  }

  template <>
  mxArray* CreateMxArray<std::string>(int rows, int columns) {
    return MxArray::Cell(rows, columns);
  }

  template <typename T>
  mxArray* stdmatrix_from(const std::matrix<T>& mtx) {
    int r = mtx.rows();
    int c = mtx.cols();

    MxArray mxa(CreateMxArray<T>(r, c));

    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        mxa.set(i,j,mtx[i][j]);
      }
    }

    return mxa.release();
  }

  template <>
  mxArray* MxArray::from(const std::matrix<double>& mtx) {
    return stdmatrix_from(mtx);
  }

  template <>
  mxArray* MxArray::from(const std::matrix<std::string>& mtx) {
    return stdmatrix_from(mtx);
  }

} // namespace mexplus

using namespace mexplus;

// Instance manager for SimpleObjects.
template class Session<SimpleObject>;
typedef Session<SimpleObject> ObjManager;

// Delete all SimpleObject instances.
MEX_DEFINE(clear_all) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {

  InputArguments input(nrhs, prhs, 0);
  OutputArguments output(nlhs, plhs, 1);

  ObjManager::clear();

  output.set(0,true);

}

// Create a new SimpleObject instance and returns its id.
MEX_DEFINE(new) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {

  InputArguments input(nrhs, prhs, 1);
  OutputArguments output(nlhs, plhs, 1);

  output.set(
    0,
    ObjManager::create(
      new SimpleObject(
        input.get<std::string>(0)
      )
    )
  );

  debugprint("Object created.");

}

// SimpleObject destructor. Called when the matlab object is clear'ed.
MEX_DEFINE(delete) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {

  InputArguments input(nrhs, prhs, 1);
  OutputArguments output(nlhs, plhs, 1);

  ObjManager::destroy(
    input.get(0)
  );

  debugprint("Object destroyed.");

  output.set(0,true);

}

MEX_DEFINE(set_name) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {

  InputArguments input(nrhs, prhs, 2);
  OutputArguments output(nlhs, plhs, 0);

  SimpleObject* obj = ObjManager::get(
    input.get(0)
  );

  obj->Name = input.get<std::string>(1);

}

MEX_DEFINE(get_name) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {

  InputArguments input(nrhs, prhs, 1);
  OutputArguments output(nlhs, plhs, 1);

  const SimpleObject& obj = ObjManager::getConst(input.get(0));

  //SimpleObject* obj = ObjManager::get(
  //  input.get(0)
  //);

  output.set(0, obj.Name);

}

MEX_DEFINE(add) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {

  InputArguments input(nrhs, prhs, 3);
  OutputArguments output(nlhs, plhs, 1);

  SimpleObject* obj = ObjManager::get(
    input.get(0)
  );

  bool ans = obj->add(
    input.get<std::string>(1),
    input.get<double>(2)
  );

  output.set(0,ans);

}

MEX_DEFINE(query) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {

  InputArguments input(nrhs, prhs, 2);
  OutputArguments output(nlhs, plhs, 1);

  const SimpleObject& obj = ObjManager::getConst(
    input.get(0)
  );

  output.set(
    0,
    obj.query(
      input.get<std::string>(1)
    )
  );

}

MEX_DEFINE(set_mtx) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {

  InputArguments input(nrhs, prhs, 3);
  OutputArguments output(nlhs, plhs, 1);

  SimpleObject* obj = ObjManager::get(
    input.get(0)
  );

  char c = input.get<char>(1);

  bool coerced = false;
  if ('d' == c) {
    obj->dMTX = input.get<std::matrix<double>>(2);
    coerced = true;
  }
  else if ('s' == c) {
    obj->sMTX = input.get<std::matrix<std::string>>(2);
    coerced = true;
  }
  else {
    debugprint("Invalid std::matrix type.");
  }

  output.set(0,coerced);

}

MEX_DEFINE(get_mtx) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {

  InputArguments input(nrhs, prhs, 2);
  OutputArguments output(nlhs, plhs, 1);

  const SimpleObject& obj = ObjManager::getConst(
    input.get(0)
  );

  char c = input.get<char>(1);

  if ('d' == c) {
    output.set(0,obj.dMTX);
  }
  else if ('s' == c) {
    output.set(0,obj.sMTX);
  }
  else {
    debugprint("Invalid std::matrix type.");
  }

}

#if 0
MEX_DEFINE(butta) (
  int nlhs, mxArray* plhs[],
  int nrhs, const mxArray* prhs[]
) {
  InputArguments input(nrhs, prhs, 0);
  OutputArguments output(nlhs > 0 ? nlhs : 1, plhs, 4);

  std::vector<double> x;
  x += 1,2,3,4,5,6,7,8,9,10,11,12;

  output.set(0, x);

  mxArray* tmp = output[0];
  mwSize dimensionSize = mxGetNumberOfDimensions(tmp);
  const mwSize* dimensions = mxGetDimensions(tmp);
  std::vector<mwSize> vdims(dimensions, dimensions + dimensionSize);

  vdims[0] = 3;
  vdims[1] = 2;
  vdims.push_back(2);

  int ans = mxSetDimensions(tmp, &vdims[0], 3);

  mexPrintf("Reshape retcode: %i\n", ans);

  std::matrix<double> y;
  y += 1,2,3,4,5,6,7,8,9,10,11,12;
  y.reshape(4,3);

  output.set(1, y);

  std::matrix<std::string> z;
  z += "a","bb","ccc","dddd";
  z.reshape(2,2);

//  output.set(2, z);

  std::matrix<bool> b;
  b += true,true,false,false,true,true;
  b.reshape(3,2);

  //output.set(3, FromStdMatrix(b));

}
#endif

//navigazione struct
