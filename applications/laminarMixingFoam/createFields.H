    Info<< "Reading transportProperties\n" << endl;

    IOdictionary transportProperties
    (
        IOobject
        (
            "transportProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );    

    Info<< "Reading field p\n" << endl;
    volScalarField p
    (
        IOobject
        (
            "p",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    Info<< "Reading field alpha1\n" << endl;
    volScalarField alpha1
    (
        IOobject
        (
            "alpha1",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    Info<< "Reading field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    #include "createPhi.H"

//Setting up the properties of two liquids for weighted averages
dimensionedScalar D
(
	transportProperties.lookup("D")
);

dimensionedScalar rho1
(
	transportProperties.lookup("rho1")
);

dimensionedScalar rho2
(
	transportProperties.lookup("rho2")
);

dimensionedScalar mu1
(
	transportProperties.lookup("mu1")
);

dimensionedScalar mu2
(
	transportProperties.lookup("mu2")
);


//Setting up how to count the mesh cells for pressure
    label pRefCell = 0;
    scalar pRefValue = 0.0;
    setRefCell
    (
        p,
        mesh.solutionDict().subDict("PIMPLE"),
        pRefCell,
        pRefValue
    );


volScalarField rho
    (
        IOobject
        (
            "rho",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        ),
        mesh
    );

surfaceScalarField rhoIntoPhi
    (
        IOobject
        (
            "rhoIntoPhi",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        ),
        mesh
    );

surfaceScalarField muEff
    (
        IOobject
        (
            "muEff",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        ),
        mesh
    );
