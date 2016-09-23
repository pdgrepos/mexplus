#include <mexplus.h>
#include "cGemPropertyList.hpp"

//#define VERBOSE true
#define VERBOSE false

using namespace mexplus;

// Initialise the session storage for PropertyList instances.
template class mexplus::Session<gem::PropertyList>;

namespace {

  // Destroy all PropertyList instances.
  MEX_DEFINE(clear) (
    int nlhs, mxArray* plhs[],
    int nrhs, const mxArray* prhs[]
  ) {
    InputArguments input(nrhs, prhs, 0);
    OutputArguments output(nlhs > 0 ? nlhs : 1, plhs, 1);

    Session<gem::PropertyList>::clear();

    output.set(0, true);  // return success

  }

  // Create a new instance of PropertyList and return its session id.
  MEX_DEFINE(new) (
    int nlhs, mxArray* plhs[],
    int nrhs, const mxArray* prhs[]
  ) {
    InputArguments input(nrhs, prhs, 0);
    OutputArguments output(nlhs, plhs, 1);
  
    intptr_t id = Session<gem::PropertyList>::create(new gem::PropertyList());

//** check if nlhs < 1 othewise object leaks
    output.set(0, id);

  }

  // Destroy a PropertyList instance.
  MEX_DEFINE(delete) (
    int nlhs, mxArray* plhs[],
    int nrhs, const mxArray* prhs[]
  ) {
    InputArguments input(nrhs, prhs, 1);
    OutputArguments output(nlhs, plhs, 0);

    Session<gem::PropertyList>::destroy(input.get(0));

//** ? return a bool:success ?

  }

  MEX_DEFINE(put) (
    int nlhs, mxArray* plhs[],
    int nrhs, const mxArray* prhs[]
  ) {
    InputArguments input(nrhs, prhs, 4);
    OutputArguments output(nlhs > 0 ? nlhs : 1, plhs, 1);

    std::string nodeType = input.get<std::string>(0);
    if(VERBOSE) mexPrintf("TYPE: %s\n", nodeType.c_str());

    gem::PropertyList* pl = Session<gem::PropertyList>::get(input.get(1));

    std::string key = input.get<std::string>(2);
    if(VERBOSE) mexPrintf("KEY: %s\n", key.c_str());

    if ("bool" == nodeType) {
      pl->put(key, input.get<bool>(3));
    } else if ("long" == nodeType) {
      pl->put(key, input.get<long>(3));
    } else if ("double" == nodeType) {
      pl->put(key, input.get<double>(3));
    } else if ("string" == nodeType) {
      pl->put(key, input.get<std::string>(3));
    } else if ("vbool" == nodeType) {
      pl->put(key, input.get<std::vector<bool> >(3));
    } else if ("vlong" == nodeType) {
      pl->put(key, input.get<std::vector<long>>(3));
    } else if ("vdouble" == nodeType) {
      pl->put(key, input.get<std::vector<double>>(3));
    } else if ("vstring" == nodeType) {
      pl->put(key, input.get<std::vector<std::string> >(3));
    } else {
      mexPrintf("PUT NOT IMPLEMENTED\n");
    }

    output.set(0, true);
  }

  MEX_DEFINE(get) (
    int nlhs, mxArray* plhs[],
    int nrhs, const mxArray* prhs[]
  ) {
    InputArguments input(nrhs, prhs, 2);
    OutputArguments output(nlhs > 0 ? nlhs : 1, plhs, 1);

    gem::PropertyList* pl = Session<gem::PropertyList>::get(input.get(0));

    std::string key = input.get<std::string>(1);
    if(VERBOSE) mexPrintf("KEY: %s\n", key.c_str());

    const std::type_info& nodeType = pl->type(key);
    if(VERBOSE) mexPrintf("TYPE: %s\n", nodeType.name());

    if (typeid(bool) == nodeType) {
      output.set(0, pl->get<bool>(key));
    } else if (typeid(long) == nodeType) {
      output.set(0, pl->get<long>(key));
    } else if (typeid(double) == nodeType) {
      output.set(0, pl->get<double>(key));
    } else if (typeid(std::string) == nodeType) {
      output.set(0, pl->get<std::string>(key));
    } else if (typeid(std::vector<bool>) == nodeType) {
      output.set(0, pl->get<std::vector<bool>>(key));
    } else if (typeid(std::vector<long>) == nodeType) {
      output.set(0, pl->get<std::vector<long>>(key));
    } else if (typeid(std::vector<double>) == nodeType) {
      output.set(0, pl->get<std::vector<double>>(key));
    } else if (typeid(std::vector<std::string>) == nodeType) {
      output.set(0, pl->get<std::vector<std::string>>(key));
    } else {
      mexPrintf("GET NOT IMPLEMENTED\n");
    }

  }









}

MEX_DISPATCH
