
#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"

// PGA
// based on Tangle2's back2back photons

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;

  // for a point source at the origin, uncomment this:
  G4double x0  = 0*cm, y0  = 0*cm, z0  = 0*cm;

  // find a random direction for the particle momentum
  G4ThreeVector random = G4RandomDirection();
  G4ThreeVector photondir = random.unit();

  // For single positrons, uncomment this:
  fParticleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e+"));
  fParticleGun->SetParticleEnergy(0*keV);
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
}

//

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    fParticleGun->GeneratePrimaryVertex(anEvent);
/*  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;

  // for a point source at the origin, uncomment this:
  G4double x0  = 0*cm, y0  = 0*cm, z0  = 0*cm;

  // for a uniform cylindrical patient source, uncomment this:
  /*
  G4double theta = G4UniformRand()*twopi;
  G4double z_coord = (G4UniformRand()*1.63) - 0.815;
  G4double x0 = 0.175*cos(theta)*m, y0 = 0.175*sin(theta)*m, z0 = z_coord*m;*/
  // note that this has the patient geometry hard coded
  // for a different patient:
  // z_coord = (G4UR*length) - halflength
  // x0 = rcos(theta), y0 = rsin(theta)

  // find a random direction for the particle momentum
/*  G4ThreeVector random = G4RandomDirection();
  G4ThreeVector photondir = random.unit();

  // For single positrons, uncomment this:
  fParticleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e+"));
  fParticleGun->SetParticleEnergy(0*keV);
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  fParticleGun->GeneratePrimaryVertex(anEvent);
*/
// For b2b photons, uncomment this:
/*
  fParticleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));

  // photon 1

  fParticleGun->SetParticleEnergy(511*keV);
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  fParticleGun->SetParticleMomentumDirection(photondir);
  fParticleGun->GeneratePrimaryVertex(anEvent);

  // photon 2

  fParticleGun->SetParticleEnergy(511*keV);
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  fParticleGun->SetParticleMomentumDirection(-photondir);
  fParticleGun->GeneratePrimaryVertex(anEvent);
*/
}
//
