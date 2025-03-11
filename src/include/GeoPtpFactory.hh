#ifndef __RAT_GeoPtpFactory__
#define __RAT_GeoPtpFactory__

#include <RAT/GeoSolidFactory.hh>

#include "G4OpticalSurface.hh"

namespace PTP {
class GeoPtpFactory : public RAT::GeoSolidFactory {
 public:
  G4OpticalSurfaceFinish GetOpticalSurfaceFinish(const std::string& finishStr);
  G4OpticalSurfaceModel GetOpticalSurfaceModel(const std::string& modelStr);

  GeoPtpFactory() : GeoSolidFactory("ptp"){};
  virtual G4VSolid* ConstructSolid(RAT::DBLinkPtr table);
};

}  // namespace PTP

#endif
