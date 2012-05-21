#ifndef ptdata_import_SportTracksImport_h
#define ptdata_import_SportTracksImport_h

#include <ptrackData/PTrackDataMacros.h>

#include <ptrackData/import/GenericImport.h>

#include <boost/filesystem/path.hpp>

namespace ptdata {
namespace import {

class PTDATA_API SportTracksImport : public GenericImport
{
public:
  SportTracksImport( boost::filesystem::path logbookPath );

  bool loadDataFromFile( boost::filesystem::path logbookPath );

private:
  boost::filesystem::path mLogbookPath;
};

} // namespace import
} // namespace ptdata

#endif
