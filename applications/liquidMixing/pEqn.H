    volScalarField rAU = 1.0/UEqn.A();
    surfaceScalarField rAUf = fvc::interpolate(rAU);

    U = rAU*UEqn.H();

    adjustPhi(phi, U, p);

    for(int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
    {
        fvScalarMatrix pEqn
        (
            fvm::laplacian(rAUf, p) == fvc::div(phi)
        );

        pEqn.setReference(pRefCell, getRefCellValue(p, pRefCell));

        pEqn.solve();

        if (nonOrth == nNonOrthCorr)
        {
            phi -= pEqn.flux();
        }
    }

    U -= rAU*fvc::grad(p);
    U.correctBoundaryConditions();

    #include "continuityErrs.H"
