/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2017-2020 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "Quemada.H"
#include "addToRunTimeSelectionTable.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{
    defineTypeNameAndDebug(Quemada, 0);
    addToRunTimeSelectionTable
    (
        viscosityModel,
        Quemada,
        dictionary
    );
}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField>
Foam::viscosityModels::Quemada::calcNu() const
{   
    return
        nuPlasma_
        * Foam::pow((1.0 - 0.5*((k0_ + kInf_ * Foam::sqrt(strainRate()/gammaDot_))
                    / (scalar(1.0) + Foam::sqrt(strainRate()/gammaDot_))) * Hct_),-2);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::viscosityModels::Quemada::Quemada
(
    const word& name,
    const dictionary& viscosityProperties,
    const volVectorField& U,
    const surfaceScalarField& phi
)
:
    viscosityModel(name, viscosityProperties, U, phi),
    QuemadaCoeffs_
    (
        viscosityProperties.optionalSubDict(typeName + "Coeffs")
    ),

    nuPlasma_("nuPlasma", dimViscosity, QuemadaCoeffs_),
    Hct_("Hct", dimless, QuemadaCoeffs_),
    k0_("k0", dimless, QuemadaCoeffs_),
    kInf_("kInf", dimless, QuemadaCoeffs_),
    gammaDot_("gammaDot", dimensionSet(0 ,0 , -1, 0, 0, 0, 0), QuemadaCoeffs_),

    nu_
    (
        IOobject
        (
            name,
            U_.time().timeName(),
            U_.db(),
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        calcNu()
    )
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::viscosityModels::Quemada::read
(
    const dictionary& viscosityProperties
)
{
    viscosityModel::read(viscosityProperties);

    QuemadaCoeffs_ =
        viscosityProperties.optionalSubDict(typeName + "Coeffs");

    QuemadaCoeffs_.readEntry("nuPlasma", nuPlasma_);
    QuemadaCoeffs_.readEntry("Hct", Hct_);
    QuemadaCoeffs_.readEntry("k0", k0_);
    QuemadaCoeffs_.readEntry("kInf", kInf_);
    QuemadaCoeffs_.readEntry("gammaDot", gammaDot_);

    return true;
}


// ************************************************************************* //
