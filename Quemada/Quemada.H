/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2017-2019 OpenCFD Ltd.
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

Class
    Foam::viscosityModels::Quemada

Description
    An incompressible Quemada quasi-mechanistic non-Newtonian viscosity model.

    It takes the hematocrit level into account. In this code, parameters are
    defined as follow:

    nuPlasma- plasma visocity
    Hct- Hematocrit level
    k0- model coefficient
    kinf- model coefficient
    gammaDot- Critical shear rate

SourceFiles
    Quemada.C

\*---------------------------------------------------------------------------*/

#ifndef Quemada_H
#define Quemada_H

#include "viscosityModel.H"
#include "dimensionedScalar.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{

/*---------------------------------------------------------------------------*\
                           Class Quemada Declaration
\*---------------------------------------------------------------------------*/

class Quemada
:
    public viscosityModel
{
    // Private data

        dictionary QuemadaCoeffs_;

        dimensionedScalar nuPlasma_;
        dimensionedScalar Hct_;
        dimensionedScalar k0_;
        dimensionedScalar kInf_;
        dimensionedScalar gammaDot_;


protected:

    // Protected Data

        volScalarField nu_;

    // Protected Member Functions

        //- Calculate and return the laminar viscosity
        tmp<volScalarField> calcNu() const;
        


public:

    //- Runtime type information
    TypeName("Quemada");


    // Constructors

        //- Construct from components
        Quemada
        (
            const word& name,
            const dictionary& viscosityProperties,
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    //- Destructor
    virtual ~Quemada() = default;


    // Member Functions

        //- Return the laminar viscosity
        virtual tmp<volScalarField> nu() const
        {
            return nu_;
        }

        //- Return the laminar viscosity for patch
        virtual tmp<scalarField> nu(const label patchi) const
        {
            return nu_.boundaryField()[patchi];
        }

        //- Correct the laminar viscosity
        virtual void correct()
        {
            nu_ = calcNu();
        }

        //- Read transportProperties dictionary
        virtual bool read(const dictionary& viscosityProperties);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace viscosityModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
