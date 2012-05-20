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
};

} // namespace import
} // namespace ptdata

#endif
