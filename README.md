# PTPSim — DUNE FD3 Light Trapper (X-Arapuca-like) Simulation

A Geant4 / [ratpac-two](https://github.com/rat-pac/ratpac-two) optical
simulation of a PTP-coated light trapper (X-Arapuca-like) for the DUNE FD3
detector.

---

## For new students: read this first

This project is **small** — it is just the `ptp` executable plus geometry and
material files. All of the heavy physics machinery lives in three external
packages that you must install *before* you can build PTPSim:

```
        ROOT  ─┐
               ├─►  ratpac-two  ─►  PTPSim  (this repo)
     Geant4  ─┘
```

- **ROOT** — CERN data-analysis framework (histograms, the `.root` files).
- **Geant4** — the particle/optical-photon transport engine.
- **ratpac-two** — a simulation framework built on top of ROOT + Geant4.
  PTPSim is an "experiment" that plugs into it.

None of these are stored in this git repository, and you should **never**
commit them here — they are hundreds of MB to GB in size and are installed
separately on each machine. This repo only contains *our* code and geometry;
CMake finds ROOT/Geant4/ratpac on your system at build time.

So the work is done in two stages:

1. **Install the dependencies** (ROOT + Geant4 + ratpac-two). This is the
   slow, one-time part — budget **1–3 hours** of mostly-unattended compiling.
2. **Build PTPSim** (this repo). This takes **under a minute**.

> **Shortcut for the impatient:** ratpac-two publishes a ready-made container
> image with every dependency already built. If you have Docker or
> Apptainer/Singularity, see [Option B](#option-b-container-fastest-no-compiling)
> — you skip stage 1 entirely.

---

## Prerequisites (system packages)

Tested on **Debian 12 / Ubuntu 22.04+**. You need a C++17 compiler, CMake
≥ 3.22, git, and Python 3, plus the libraries ROOT and Geant4 expect. On
Debian/Ubuntu:

```bash
sudo apt update
sudo apt install -y \
    build-essential cmake git python3 python3-pip \
    libx11-dev libxpm-dev libxft-dev libxext-dev \
    libssl-dev libgl1-mesa-dev libglu1-mesa-dev \
    qtbase5-dev libqt5opengl5-dev \
    libexpat1-dev libxerces-c-dev
```

(`qtbase5-dev` matters: PTPSim's CMake asks Geant4 for its **Qt** component so
the visualizer works. If you build Geant4 yourself, enable Qt support.)

On macOS use Homebrew (`brew install cmake qt xerces-c`) and Xcode command-line
tools; the rest of the flow is the same.

---

## Stage 1 — Install the dependencies

### Option A — `ratpac-setup` (recommended)

The ratpac-two team maintains a single script,
[**ratpac-setup**](https://github.com/rat-pac/ratpac-setup), that downloads and
compiles **cmake, ROOT, Geant4, and ratpac-two** into one self-contained
directory. This is the most reliable way to get a matching set of versions and
is what you should use unless you have a reason not to.

```bash
# Pick a location with a few GB free, e.g. your home directory
cd ~
git clone https://github.com/rat-pac/ratpac-setup.git
cd ratpac-setup

# Follow the instructions in that repo's README to run the build.
# It will compile ROOT and Geant4 from source — expect 1–3 hours.
```

> ⚠️ **Follow ratpac-setup's own README for the exact build command and
> flags** — they change over time, and that repo is the authoritative source.
> Do not copy a command from here and assume it is current.

When it finishes it produces an environment script (an `env.sh` /
`ratpac.sh`-style file). **Every time you open a new terminal** to work on the
simulation, you must `source` it so that `root-config`, `geant4-config`, and
ratpac are on your `PATH`:

```bash
source ~/ratpac-setup/env.sh      # exact name/path is printed at the end of the build
```

Verify the dependencies are visible before moving on:

```bash
root-config --version       # expect 6.2x or newer
geant4-config --version     # expect 11.0 or newer
echo "$RATROOT"             # should point at your ratpac-two install
```

### Option B — Container (fastest, no compiling)

If you have Docker or Apptainer/Singularity, pull the prebuilt image — ROOT,
Geant4, and ratpac-two are already inside:

```bash
# Apptainer / Singularity (common on HPC clusters)
apptainer pull ratpac2.sif docker://ratpac/ratpac-two:main
apptainer run ratpac2.sif        # drops you into a shell with everything set up
```

Then clone PTPSim inside the container and jump to [Stage 2](#stage-2--build-ptpsim).

### Option C — Manual install

Only if you know what you're doing: install ROOT, Geant4 (with Qt), and cmake
yourself, build ratpac-two per its
[README](https://github.com/rat-pac/ratpac-two#installation), and `source` its
`ratpac.sh`. The version combination known to work with this code is in the
[Versions](#versions) table below.

---

## Stage 2 — Build PTPSim

Once the dependencies are installed **and their environment is sourced in your
current terminal**, building this repo is one command:

```bash
git clone https://github.com/jayhyunjo/PTPSim.git
cd PTPSim
make
```

`make` runs CMake to configure the project, compiles it into `build/`, and
installs the `ptp` executable and data files into `install/`. Both `build/` and
`install/` are git-ignored — they are yours to delete and rebuild anytime.

If it fails, the first thing to check is that the dependency environment is
sourced (`echo $RATROOT` should be non-empty). See
[Troubleshooting](#troubleshooting).

To rebuild after editing the code, just run `make` again. To start completely
clean:

```bash
make clean && make
```

---

## Stage 3 — Set up the runtime environment and run

`make` generates `install/bin/ptp.sh`, which points the simulation at this
repo's data (geometry, materials) and adds the `ptp` executable to your
`PATH`. Source it (in addition to the ratpac environment from Stage 1):

```bash
source install/bin/ptp.sh
```

Now run the simulation. The `ptp` executable takes a macro file:

```bash
ptp ptp.mac                 # run the simulation in batch mode
ptp --vis vis.mac           # open the interactive 3-D visualizer (polished geometry)
ptp --vis vis_ground.mac    # same, for the ground-finish geometry
```

Output is written to a `.root` file (see the `/rat/procset` lines inside the
`.mac` files for the exact name). These `.root` outputs are git-ignored and
should not be committed.

> **Tip:** put both `source` lines in a shell function or alias so you don't
> retype them, e.g. in your `~/.bashrc`:
> ```bash
> alias ptpsim='source ~/ratpac-setup/env.sh && source ~/PTPSim/install/bin/ptp.sh'
> ```
> (adjust the two paths to match where you installed things).

---

## What's in this repo

| Path            | What it is                                                        |
|-----------------|-------------------------------------------------------------------|
| `src/`          | C++ source — the `ptp` executable and the `PTP` library           |
| `ratdb/`        | ratpac database files: geometry (`ratdb/Ptp/*.geo`), materials, optics. **This is where the detector is defined.** |
| `*.mac`         | Geant4/rat macro files that drive a run (`ptp.mac`, `vis*.mac`)    |
| `examples/`     | Small C++/Python examples for reading the output `.root` files    |
| `plotter/`      | ROOT/Python scripts for making plots from the output              |
| `config/`       | Templates CMake fills in (`ptp.sh`, `Config.hh`)                   |
| `CMakeLists.txt`, `Makefile` | Build configuration                                  |
| `build/`, `install/` | Generated by `make` — **git-ignored**, safe to delete       |

To change the detector geometry or materials, edit the files under `ratdb/` and
re-run — no recompile of C++ needed for geometry/material changes.

---

## Versions

External packages are **not** included in this repository. The combination
this code was developed and tested against:

| Package                                              | Version                     |
|------------------------------------------------------|-----------------------------|
| ROOT                                                 | 6.38.04                     |
| Geant4                                               | 11.2.1 (built with Qt)      |
| [ratpac-two](https://github.com/rat-pac/ratpac-two)  | 2.3.0 (commit `27966eb`)    |
| CMake                                                | ≥ 3.22                      |

Nearby versions generally work (ratpac-two needs ROOT ≥ 6.25, Geant4 ≥ 11.0),
but the above set is known-good.

---

## Troubleshooting

| Symptom | Likely cause / fix |
|---------|--------------------|
| `Could NOT find ROOT` / `Geant4` / `Ratpac` during `make` | The dependency environment isn't sourced in this terminal. `source` your ratpac-setup env script (Stage 1), confirm with `echo $RATROOT`, then `make` again. |
| `Could not find a package configuration file provided by "Geant4" ... COMPONENTS qt` | Your Geant4 was built without Qt. Rebuild Geant4/ratpac-setup with Qt enabled, and install `qtbase5-dev` (Stage 0). |
| `ptp: command not found` | You didn't `source install/bin/ptp.sh` (Stage 3), or `make` didn't finish. |
| Visualizer window doesn't open / OpenGL errors over SSH | You need X-forwarding (`ssh -X`) or a local display; the Qt/OpenGL visualizer needs a graphical session. Batch runs (`ptp ptp.mac`) don't. |
| `error while loading shared libraries: libRAT...` | The ratpac environment isn't sourced, or `LD_LIBRARY_PATH` was reset. Re-source Stage 1 + Stage 3. |
| Build succeeds but you edited `ratdb/*.geo` and see no change | Geometry is read at run time from this repo's `ratdb/`. Make sure `install/bin/ptp.sh` is sourced so `PTPDATA` points here; you do **not** need to rebuild for `ratdb` edits. |

If you're stuck, the ratpac-two [docs](https://ratpac.readthedocs.io) and its
[README](https://github.com/rat-pac/ratpac-two) cover the dependency side; open
an issue on this repo for PTPSim-specific problems.
