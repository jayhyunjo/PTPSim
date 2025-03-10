#ifndef __RAT_GeoPtpFactory__
#define __RAT_GeoPtpFactory__

#include <RAT/GeoSolidFactory.hh>
#include "G4OpticalSurface.hh"

namespace PTP {
class GeoPtpFactory : public RAT::GeoSolidFactory {
 public:

  GeoPtpFactory() : GeoSolidFactory("ptp"){};
  virtual G4VSolid *ConstructSolid(RAT::DBLinkPtr table);
  G4OpticalSurfaceFinish GetOpticalSurfaceFinish(const std::string& finishStr);
};

}  // namespace PTP

#endif
