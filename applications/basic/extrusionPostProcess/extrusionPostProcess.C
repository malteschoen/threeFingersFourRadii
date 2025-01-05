/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  |
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

Application
    extrusionPostProcess

Description
    Converts the rho-normalized pressure p to a regular Pressure in bars.
    Calculates shear rates.
    Converts kinematic viscosity into dynamic viscosity.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "fvOptions.H"
#include "simpleControl.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"

    simpleControl simple(mesh);

    #include "createFields.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

p_bar = p*(1e-5)*rho;
p_bar.write();
    Info<< "\nCalculated p_bar" << endl;

strainRate = scalar(1.41421)*mag(symm(fvc::grad(U)));
strainRate.write();
    Info<< "\nCalculated shearRate" << endl;

outputGradU = fvc::grad(U);
outputGradU.write();
    Info<< "\nCalculated gradU" << endl;

forAll (elongRates, cellI)
{
elongRates[cellI] = vector(outputGradU[cellI].component(tensor::XX),outputGradU[cellI].component(tensor::YY),outputGradU[cellI].component(tensor::ZZ));
}
elongRates.write();
    Info<< "\nCalculated elongational rates" << endl;

dimensionedScalar avgVolume = gSum(mesh.V())/mesh.nCells();
avgVolume.dimensions().reset(dimensionSet(0,0,0,0,0,0,0));
Info<< "\naverage cell volume = "<< avgVolume.value() << endl;

dimensionedScalar avgLength = pow(avgVolume, 0.333333);
avgLength.dimensions().reset(dimensionSet(0,1,0,0,0,0,0));
Info<< "\naverage cell side length = "<< avgLength.value() << endl;

volTensorField tau = nu * (outputGradU + outputGradU.T()); 
tauFixed = fvc::div(tau)*rho*scalar(-1.0)*avgLength;
tauFixed.write();
    Info<< "\nCalculated tauFixed" << endl;

eta = nu*rho;
eta.write();	
    Info<< "\nCalculated dynamic viscosities eta" << endl;			

Info<< "Postprocessing complete\n" << endl;

    return 0;
}


// ************************************************************************* //