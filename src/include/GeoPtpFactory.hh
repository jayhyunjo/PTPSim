#ifndef __RAT_GeoPtpFactory__
#define __RAT_GeoPtpFactory__

#include <RAT/GeoSolidFactory.hh>

#include "G4OpticalSurface.hh"
#include "G4SurfaceProperty.hh"

namespace PTP {
class GeoPtpFactory : public RAT::GeoSolidFactory {
 public:
  G4OpticalSurfaceFinish GetOpticalSurfaceFinish(const std::string& finishStr);
  G4OpticalSurfaceModel GetOpticalSurfaceModel(const std::string& modelStr);
  G4SurfaceType GetOpticalSurfaceType(const std::string& typeStr);

  GeoPtpFactory() : GeoSolidFactory("ptp"){};
  virtual G4VSolid* ConstructSolid(RAT::DBLinkPtr table);
};

}  // namespace PTP

#endif
