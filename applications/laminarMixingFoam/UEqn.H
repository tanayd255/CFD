//Defining momentum predictor equation
    fvVectorMatrix UEqn
    (
        fvm::ddt(rho, U)
      + fvm::div(rhoIntoPhi, U)
      - fvm::laplacian(muEff, U)
     );

if (finalIter)
    {
        UEqn.relax(1);
    }
else
    {
        UEqn.relax();
    }

//Per U iteration
        if (momentumPredictor)
	{
        solve (UEqn == -fvc::grad(p));
	}
