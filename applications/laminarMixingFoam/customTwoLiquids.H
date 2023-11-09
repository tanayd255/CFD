surfaceScalarField muEff ("muEff", (alpha1*mu1 + (scalar(1)-alpha1)*mu2));
volScalarField rho ("rho", (alpha1*rho1 + (scalar(1)-alpha1)*rho2));
surfaceScalarField rhof = fvc::interpolate(rho);
surfaceScalarField rhoIntoPhi ("rhoIntoPhi", rhof*phi);
