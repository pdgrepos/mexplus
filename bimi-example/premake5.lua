workspace "MexPlus"
  configurations { "Debug" }
  location "build"

project "mexlib"
  location "build"
  kind "SharedLib"
  includedirs {
    "../include",
    "../_matlab_/R2014b/include",
    "../../../HEAD/pdglib/libs/pdgbase/include"
  }

  files {
    "src/*.cpp",
    "../include/mexplus/arguments.h",
    "../include/mexplus/dispatch.h",
    "../include/mexplus/mxarray.h",
    "../../../HEAD/pdglib/libs/pdgbase/containers/include/matrix.h",
    }
