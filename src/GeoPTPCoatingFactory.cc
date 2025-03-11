#include <CLHEP/Units/SystemOfUnits.h>

#include <G4Box.hh>
#include <G4Colour.hh>
#include <G4LogicalSkinSurface.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4OpticalSurface.hh>
#include <G4PVPlacement.hh>
#include <G4ThreeVector.hh>
#include <G4UnitsTable.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VisAttributes.hh>
#include <GeoPTPCoatingFactory.hh>
#include <RAT/DB.hh>
#include <RAT/Log.hh>
#include <RAT/Materials.hh>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace PTP {

G4OpticalSurfaceFinish GetOpticalSurfaceFinish(const std::string& finishStr) {
  static const std::map<std::string, G4OpticalSurfaceFinish> finishMap = {
      {"polished", polished},
      {"polishedfrontpainted", polishedfrontpainted},
      {"polishedbackpainted", polishedbackpainted},
      {"ground", ground},
      {"groundfrontpainted", groundfrontpainted},
      {"groundbackpainted", groundbackpainted},
      {"polishedlumirrorair", polishedlumirrorair},
      {"polishedlumirrorglue", polishedlumirrorglue},
      {"polishedair", polishedair},
      {"polishedteflonair", polishedteflonair},
      {"polishedtioair", polishedtioair},
      {"polishedtyvekair", polishedtyvekair},
      {"polishedvm2000air", polishedvm2000air},
      {"polishedvm2000glue", polishedvm2000glue},
      {"etchedlumirrorair", etchedlumirrorair},
      {"etchedlumirrorglue", etchedlumirrorglue},
      {"etchedair", etchedair},
      {"etchedteflonair", etchedteflonair},
      {"etchedtioair", etchedtioair},
      {"etchedtyvekair", etchedtyvekair},
      {"etchedvm2000air", etchedvm2000air},
      {"etchedvm2000glue", etchedvm2000glue},
      {"groundlumirrorair", groundlumirrorair},
      {"groundlumirrorglue", groundlumirrorglue},
      {"groundair", groundair},
      {"groundteflonair", groundteflonair},
      {"groundtioair", groundtioair},
      {"groundtyvekair", groundtyvekair},
      {"groundvm2000air", groundvm2000air},
      {"groundvm2000glue", groundvm2000glue}};

  auto it = finishMap.find(finishStr);
  if (it != finishMap.end()) {
    return it->second;
  } else {
    throw std::runtime_error("Invalid G4OpticalSurfaceFinish string: " + finishStr);
  }
}

G4OpticalSurfaceModel GetOpticalSurfaceModel(const std::string& modelStr) {
  static const std::map<std::string, G4OpticalSurfaceModel> modelMap = {
      {"glisur", glisur}, {"unified", unified}, {"LUT", LUT}, {"dichroic", dichroic}};

  auto it = modelMap.find(modelStr);
  if (it != modelMap.end()) {
    return it->second;
  } else {
    throw std::runtime_error("Invalid G4OpticalSurfaceModel string: " + modelStr);
  }
}

G4SurfaceType GetSurfaceType(const std::string& typeStr) {
    static const std::map<std::string, G4SurfaceType> typeMap = {
        {"dielectric_metal", dielectric_metal},
        {"dielectric_dielectric", dielectric_dielectric},
        {"firsov", firsov},
        {"x_ray", x_ray}
    };

    auto it = typeMap.find(typeStr);
    if (it != typeMap.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Invalid G4SurfaceType string: " + typeStr);
    }
}

G4VPhysicalVolume* GeoPTPCoatingFactory::Construct(RAT::DBLinkPtr table) {
  RAT::info << "Building PTP Coating" << newline;

  // Retrieve basic info from the table
  const std::string volumeName = table->GetIndex();
  const std::string motherName = table->GetS("mother");

  // Dimensions for the coating box (full lengths)
  const double boxLength = table->GetD("box_length");        // e.g., length along X
  const double boxWidth = table->GetD("box_width");          // e.g., length along Y
  const double boxThickness = table->GetD("box_thickness");  // e.g., small thickness along Z

  // Read sigmaAlpha input for the optical surface
  const double sigmaAlpha = table->GetD("sigma_alpha");

  // Optionally, get a position offset
  const std::vector<double> posArray = table->GetDArray("position");
  G4ThreeVector offset(0, 0, 0);
  if (!posArray.empty() && posArray.size() >= 3) {
    offset = G4ThreeVector(posArray[0], posArray[1], posArray[2]);
  }

  // Get the material for the coating from the table ("coating_material")
  G4Material* coatingMaterial = G4Material::GetMaterial(table->GetS("coating_material"));
  if (!coatingMaterial) {
    RAT::Log::Die("PTP Coating material not found: " + table->GetS("coating_material"));
  }

  // Create a box solid (G4Box takes half-dimensions)
  G4Box* coatingSolid = new G4Box("PTPCoating_Solid", boxLength, boxWidth, boxThickness);

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
  // G4ThreeVector position = motherPos + offset;
  G4ThreeVector position = offset;

  // Place the coating volume inside the mother volume
  // new G4PVPlacement(rotation, position, coatingLog, "PTPCoating", motherPhys, false, 0);
  new G4PVPlacement(rotation, position, "PTPCoating", coatingLog, motherPhys, false, 0);

  const std::string ifinish = table->GetS("finish");
  const std::string imodel = table->GetS("model");
  const double ipolish = table->GetD("polish");
  const std::string itype = table->GetS("surfaceType");

  // --- Define and attach an optical surface ---
  // Create an optical surface that will be applied as a skin surface to the coating
  G4OpticalSurface* ptpOpticalSurface = new G4OpticalSurface("PTPCoating_OpticalSurface");
  ptpOpticalSurface->SetType(GetSurfaceType(itype));
  ptpOpticalSurface->SetModel(GetOpticalSurfaceModel(imodel));
  ptpOpticalSurface->SetFinish(GetOpticalSurfaceFinish(ifinish));
  ptpOpticalSurface->SetSigmaAlpha(sigmaAlpha);
  ptpOpticalSurface->SetPolish(ipolish);

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

}  // namespace PTP
