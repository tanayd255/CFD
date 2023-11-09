//Defining reciprocal of coefficient matrix
    volScalarField rAU = 1.0/UEqn.A();
    U = rAU*UEqn.H();

//Defining old velocity field as flux phi
phi = (fvc::interpolate(U) & mesh.Sf()) + fvc::ddtPhiCorr(rAU,rho,U,phi);
adjustPhi(phi,U,p);

//Inside pressure loop
    for(int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
    {
	//Pressure equation as corrector
        fvScalarMatrix pEqn
        (
            fvm::laplacian(rAU, p) == fvc::div(phi)
        );

	//For every cell solve the pressure equation defined above
        pEqn.setReference(pRefCell,pRefValue);
	pEqn.solve();

	//Final pressure iteration
        if (nonOrth == nNonOrthCorr)
        {
            phi -= pEqn.flux();
        }
    }

#include "continuityErrs.H"

// Relaxing pressure equation except for last iteration
if (oCorr != nOuterCorr-1)
{
    p.relax();
}

//Momentum final steps
U -= rAU*fvc::grad(p);
U.correctBoundaryConditions();
