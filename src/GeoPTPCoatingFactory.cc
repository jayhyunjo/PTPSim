#include <CLHEP/Units/SystemOfUnits.h>
#include <G4Colour.hh>
#include <G4LogicalSkinSurface.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4OpticalSurface.hh>
#include <G4PVPlacement.hh>
#include <G4Box.hh>
#include <G4ThreeVector.hh>
#include <G4UnitsTable.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VisAttributes.hh>
#include <RAT/DB.hh>
#include <GeoPTPCoatingFactory.hh>
#include <RAT/Log.hh>
#include <RAT/Materials.hh>
#include <string>
#include <vector>

namespace PTP {

G4VPhysicalVolume* GeoPTPCoatingFactory::Construct(RAT::DBLinkPtr table) {
	RAT::info << "Building PTP Coating" << newline;

  // Retrieve basic info from the table
  const std::string volumeName = table->GetIndex();
  const std::string motherName   = table->GetS("mother");

  // Dimensions for the coating box (full lengths)
  const double boxLength    = table->GetD("box_length");    // e.g., length along X
  const double boxWidth     = table->GetD("box_width");     // e.g., length along Y
  const double boxThickness = table->GetD("box_thickness"); // e.g., small thickness along Z

  // Read sigmaAlpha input for the optical surface
  const double sigmaAlpha = table->GetD("sigma_alpha");

  // Optionally, get a position offset
  const std::vector<double> posArray = table->GetDArray("position");
  G4ThreeVector offset(0,0,0);
  if (!posArray.empty() && posArray.size() >= 3) {
    offset = G4ThreeVector(posArray[0], posArray[1], posArray[2]);
  }

  // Get the material for the coating from the table ("coating_material")
  G4Material* coatingMaterial = G4Material::GetMaterial(table->GetS("coating_material"));
  if (!coatingMaterial) {
	  RAT::Log::Die("PTP Coating material not found: " + table->GetS("coating_material"));
  }

  // Create a box solid (G4Box takes half-dimensions)
  G4Box* coatingSolid = new G4Box("PTPCoating_Solid",
                                  boxLength,
                                  boxWidth,
                                  boxThickness);

  // Create the logical volume
  G4LogicalVolume* coatingLog = new G4LogicalVolume(coatingSolid, coatingMaterial, "PTPCoating_Logical");

  // Find the mother physical volume (provided by the base GeoFactory)
  G4VPhysicalVolume* motherPhys = FindPhysMother(motherName);
  if (!motherPhys) {
	  RAT::Log::Die("Mother volume not found: " + motherName);
  }

  // Determine placement: here we simply add the offset to the mother's translation
  G4RotationMatrix* rotation = motherPhys->GetObjectRotation();
  G4ThreeVector motherPos = motherPhys->GetObjectTranslation();
  G4ThreeVector position = motherPos + offset;

  // Place the coating volume inside the mother volume
  //new G4PVPlacement(rotation, position, coatingLog, "PTPCoating", motherPhys, false, 0);
  new G4PVPlacement(rotation, position, "PTPCoating", coatingLog, motherPhys, false, 0);

  // --- Define and attach an optical surface ---
  // Create an optical surface that will be applied as a skin surface to the coating
  G4OpticalSurface* ptpOpticalSurface = new G4OpticalSurface("PTPCoating_OpticalSurface");
  ptpOpticalSurface->SetType(dielectric_dielectric);
  ptpOpticalSurface->SetModel(unified);
  // Choose a finish (here we use 'ground'; adjust as needed)
  ptpOpticalSurface->SetFinish(polished);
  ptpOpticalSurface->SetSigmaAlpha(sigmaAlpha);

  // Attach the optical surface to the entire logical volume (skin surface)
  new G4LogicalSkinSurface("PTPCoating_SkinSurface", coatingLog, ptpOpticalSurface);

  // Set visualization attributes from table ("coating_color")
  SetVis(coatingLog, table->GetDArray("coating_color"));

  // (Return value is unused in many factories; here we return NULL.)
  return NULL;
}

void GeoPTPCoatingFactory::SetVis(G4LogicalVolume* volume, std::vector<double> color) {
  G4VisAttributes* att = GetColor(color);
  att->SetForceSolid(true);
  volume->SetVisAttributes(att);
}

G4VisAttributes* GeoPTPCoatingFactory::GetColor(std::vector<double> color) {
  if (color.size() == 4) {
    return new G4VisAttributes(G4Color(color[0], color[1], color[2], color[3]));
  } else if (color.size() == 3) {
    return new G4VisAttributes(G4Color(color[0], color[1], color[2]));
  } else {
    return new G4VisAttributes(G4Color());
  }
}

}  // namespace RAT

