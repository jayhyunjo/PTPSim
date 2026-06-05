# PTPSim — DUNE FD3 Light Trapper (X-Arapuca-like) Simulation

Geant4 / ratpac-two based optical simulation of a PTP-coated light trapper
(X-Arapuca-like) for the DUNE FD3 detector.

## Dependencies

External packages are **not** included in this repository. Install them
separately and make sure their environments are set up (so CMake can find
them) before building:

| Package    | Version this was developed against |
|------------|------------------------------------|
| ROOT       | 6.38.04                            |
| Geant4     | 11.2.1                             |
| [ratpac-two](https://github.com/rat-pac/ratpac-two) | 2.3.0 (commit `27966eb`) |

Other nearby versions will likely work, but the above combination is known
to build and run.

## Building

```bash
make
```

This configures CMake into `build/` and installs the `ptp` executable and
data into `install/`. Then set up the runtime environment:

```bash
source install/bin/ptp.sh   # sets PTPDATA, PATH, LD_LIBRARY_PATH
```

## Running

```bash
ptp run_ptp.mac        # batch mode
ptp --vis vis.mac      # interactive visualization
```

Geometry, materials, and optics live in `ratdb/` (project-specific tables
that extend/override the ratpac-two defaults).
