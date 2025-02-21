{
name: "GEO",
index: "world",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "", // world volume has no mother
type: "box",
size: [400.0, 400.0, 400.0], // mm, half-length
material: "air",
invisible: 1,
}

{
name: "GEO",
index: "inner_surface",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "world",
type: "box",
size: [300,300,300],
position: [0.0, 0.0, 0.0],
material: "liquid_Ar",
color: [0.4, 0.4, 0.6, 0.3],
drawstyle: "solid"
}


// Daughter layer: PTP (6 mm thick → half-thickness = 3 mm)
// Positioned on the leftmost side of the layered structure.
// It extends from x = -12.5 to -6.5 mm (center at -9.5 mm).
{
  name: "GEO",
  index: "PTP",
  valid_begin: [0, 0],
  valid_end: [0, 0],
  mother: "inner_surface",
  type: "box",
  size: [3.0, 100.0, 100.0],
  position: [-9.5, 0.0, 0.0],
  material: "PTP",
  color: [1.0, 0.0, 0.0, 0.3],
  drawstyle: "solid"
}

// Daughter layer: WLS (6 mm thick → half-thickness = 3 mm)
// Positioned such that it does not touch the PTP layer, leaving a 6 mm gap.
// Here, WLS is centered at x = +2.5 mm, so it extends from -0.5 to +5.5 mm.
{
  name: "GEO",
  index: "WLS",
  valid_begin: [0, 0],
  valid_end: [0, 0],
  mother: "inner_surface",
  type: "box",
  size: [3.0, 100.0, 100.0],
  position: [2.5, 0.0, 0.0],
  material: "eljen_WLSP",
  color: [0.4, 0.4, 0.6, 0.3],
  drawstyle: "solid"
}

// Daughter layer: Reflector (1 mm thick → half-thickness = 0.5 mm)
// Positioned on the far right, leaving a 6 mm gap between WLS and Reflector.
// Its center is at x = +12.0 mm, so it extends from +11.5 to +12.5 mm.
{
  name: "GEO",
  index: "reflector",
  valid_begin: [0, 0],
  valid_end: [0, 0],
  mother: "inner_surface",
  type: "box",
  size: [0.5, 100.0, 100.0],
  position: [12.0, 0.0, 0.0],
  material: "Reflect",
  color: [1.0, 1.0, 1.0, 0.3],
  drawstyle: "solid"
}
{
  name: "GEO",
  index: "sipm_side",
  valid_begin: [0, 0],
  valid_end: [0, 0],
  mother: "inner_surface",
  type: "pmtarray",
  pmt_model: "lappd",
  pmt_detector_type: "idpmt",
  sensitive_detector: "/mydet/pmt/inner",
  efficiency_correction: 1.000,
  pos_table: "PMTINFO_sipm", //generated on the fly
  orientation: "manual",
}



