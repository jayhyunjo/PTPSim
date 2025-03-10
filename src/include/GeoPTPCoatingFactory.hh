#ifndef __RAT_GeoPTPCoatingFactory__
#define __RAT_GeoPTPCoatingFactory__

#include <G4OpticalSurface.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VisAttributes.hh>
#include <RAT/GeoFactory.hh>
#include <vector>
#include <string>
#include "G4OpticalSurface.hh"

namespace PTP {

class GeoPTPCoatingFactory : public RAT::GeoFactory {
 public:
  GeoPTPCoatingFactory() : GeoFactory("PTPCoating") {};
  virtual G4VPhysicalVolume* Construct(RAT::DBLinkPtr table);

 protected:
  static G4VisAttributes* GetColor(std::vector<double> color);
  void SetVis(G4LogicalVolume* volume, std::vector<double> color);
};

}  // namespace RAT

#endif  // __RAT_GeoPTPCoatingFactory__

