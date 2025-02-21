// World volume: defined as in the BNL30TSim convention.
{
  name: "GEO",
  index: "world",
  valid_begin: [0, 0],
  valid_end: [0, 0],
  mother: "",
  type: "box",
  size: [30000.0, 40000.0, 30000.0],  // mm, half-lengths
  material: "air",
  invisible: 1
}

// Overall LAr container that spans the full layered region.
// Here, the x half-length is 12.5 mm (total thickness = 25 mm),
// while y and z half-lengths are set to 500 mm.
{
  name: "GEO",
  index: "LAr_main",
  valid_begin: [0, 0],
  valid_end: [0, 0],
  mother: "world",
  type: "box",
  size: [20, 600.0, 600.0],
  position: [0.0, 0.0, 0.0],
  material: "LAr",
  color: [0.0, 0.0, 1.0, 0.1],
  drawstyle: "solid"
}

// Daughter layer: PTP (6 mm thick → half-thickness = 3 mm)
// Positioned on the leftmost side of the layered structure.
// It extends from x = -12.5 to -6.5 mm (center at -9.5 mm).
//{
//  name: "GEO",
//  index: "PTP",
//  valid_begin: [0, 0],
//  valid_end: [0, 0],
//  mother: "LAr_main",
//  type: "box",
//  size: [3.0, 500.0, 500.0],
//  position: [-9.5, 0.0, 0.0],
//  material: "PTP",
//  color: [1.0, 0.0, 0.0, 0.3],
//  drawstyle: "solid"
//}

// Daughter layer: WLS (6 mm thick → half-thickness = 3 mm)
// Positioned such that it does not touch the PTP layer, leaving a 6 mm gap.
// Here, WLS is centered at x = +2.5 mm, so it extends from -0.5 to +5.5 mm.
//{
//  name: "GEO",
//  index: "WLS",
//  valid_begin: [0, 0],
//  valid_end: [0, 0],
//  mother: "LAr_main",
//  type: "box",
//  size: [3.0, 500.0, 500.0],
//  position: [2.5, 0.0, 0.0],
//  material: "eljen_WLSP",
//  color: [0.4, 0.4, 0.6, 0.3],
//  drawstyle: "solid"
//}

// Daughter layer: Reflector (1 mm thick → half-thickness = 0.5 mm)
// Positioned on the far right, leaving a 6 mm gap between WLS and Reflector.
// Its center is at x = +12.0 mm, so it extends from +11.5 to +12.5 mm.
//{
//  name: "GEO",
//  index: "reflector",
//  valid_begin: [0, 0],
//  valid_end: [0, 0],
//  mother: "LAr_main",
//  type: "box",
//  size: [0.5, 500.0, 500.0],
//  position: [12.0, 0.0, 0.0],
//  material: "Reflect",
//  color: [1.0, 1.0, 1.0, 0.3],
//  drawstyle: "solid"
//}

//{
//name:"GEO",
//index:"side_sipm",
//valid_begin:[0.0,0.0],
//valid_end:[0.0,0.0],
//mother:"LAr_main",
//type:"pmtarray",
//pmt_model:"sipm",
//pmt_detector_type:"idpmt",
//sensitive_detector:"/mydet/pmt/inner",
//pos_table:"PMTINFO_bottom",
//orientation:"manual",
//}


