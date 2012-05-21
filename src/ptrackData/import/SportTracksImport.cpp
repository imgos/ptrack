#include <ptrackData/import/SportTracksImport.h>

#include <boost/filesystem.hpp>

namespace ptdata {
namespace import {

/*
 * SportTracksImport
 */
SportTracksImport::SportTracksImport( boost::filesystem::path logbookPath )
 : mLogbookPath( logbookPath )
{
  loadDataFromFile( logbookPath );
}

/*
 * loadDataFromFile
 */
bool SportTracksImport::loadDataFromFile( boost::filesystem::path logbookPath )
{
  if( !boost::filesystem::exists( logbookPath ) ) {
    return false;
  }

  if( !boost::filesystem::is_regular_file( logbookPath ) ) {
    return false;
  }

}

} // namespace import
} // namespace ptdata
