#ifndef ptdata_import_GenericImport_h
#define ptdata_import_GenericImport_h

#include <ptrackData/PTrackDataMacros.h>

#include <string>

namespace ptdata {
namespace import {

class PTDATA_API GenericImport
{
public:
  virtual std::string data();
};

} // namespace import
} // namespace ptdata

#endif
