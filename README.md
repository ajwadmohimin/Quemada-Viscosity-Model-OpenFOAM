# Quemada-Viscosity-Model-OpenFOAM
The incompressible Quemada quasi-mechanistic non-Newtonian viscosity model is implemented in OpenFOAM

## Installation / Compiling
* Find your OpenFOAM installation directory.
* Backup and open `<OF_INSTALLATION_DIR>/src/transportModels/incompressible/Make/files`
* Add the following line at the end of the first paragraph (with all other viscosity model)
  ```
  viscosityModels/Quemada/Quemada.C
  ```
* Clone the repo and extract, and put the `Quemada` folder in `<OF_INSTALLATION_DIR>/src/transportModels/incompressible/viscosityModels`
* Change your working directory to `<OF_INSTALLATION_DIR>/src/transportModels/incompressible` and run `wmake`
* Quemada viscosity model is now compiled.
