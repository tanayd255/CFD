    surfaceScalarField muEff
    (
        "muEff",
        twoPhaseProperties.muf()
      + fvc::interpolate(rho*turbulence->nut())
    );

    fvVectorMatrix UEqn
    (
        fvm::ddt(rho, U)
      + fvm::div(rhoPhi, U)
      - fvm::laplacian(muEff, U)
      - (fvc::grad(U) & fvc::grad(muEff))
    //- fvc::div(muEff*(fvc::interpolate(dev(fvc::grad(U))) & mesh.Sf()))
    );
    volScalarField rAU = 1.0/UEqn.A();

    if (finalIter)
    {
        UEqn.relax(1);;

    }
    else
    {
        UEqn.relax();
    }

    if (momentumPredictor)
    {
        solve
        (
            UEqn == -fvc::grad(p)
	);
    }
    else
    {
	U = rAU*(UEqn.H() - fvc::grad(p));
	U.correctBoundaryConditions();
    }
