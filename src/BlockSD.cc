

#include "BlockSD.hh"
#include "BlockHit.hh"
#include "Constants.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//

BlockSD::BlockSD(G4String name)
: G4VSensitiveDetector(name),
  fHitsCollection(nullptr), fHCID(-1)
{
  collectionName.insert("EMcalorimeterColl");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BlockSD::~BlockSD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BlockSD::Initialize(G4HCofThisEvent* hce)
{
  fHitsCollection
    = new BlockHitsCollection(SensitiveDetectorName,collectionName[0]);
  if (fHCID<0) {
    fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
  }
  hce->AddHitsCollection(fHCID,fHitsCollection);

  // fill calorimeter hits with zero energy deposition
  for (auto i=0;i<kNoBlocks;i++) {
    fHitsCollection->insert(new BlockHit(i));
  }
}

//

G4bool BlockSD::ProcessHits(G4Step*step, G4TouchableHistory*)
{
  auto touchable = step->GetPreStepPoint()->GetTouchable();
  auto trackID = step->GetTrack()->GetTrackID();
  auto ringNo = touchable->GetCopyNumber(1);
  auto blockNo = touchable->GetCopyNumber(2);
  auto blockHitID = 10*ringNo+blockNo;
  auto hit = (*fHitsCollection)[blockHitID];
  auto edep = step->GetTotalEnergyDeposit();

  if (trackID == 2) {
      hit->AddEdep1(edep);
      if (hit->GetBlockID()<0) {
        hit->SetBlockID(blockHitID);
        hit->SetPos1(step->GetPreStepPoint()->GetPosition());
      }
  }

  if (trackID == 3) {
      hit->AddEdep2(edep);
      if (hit->GetBlockID()<0) {
        hit->SetBlockID(blockHitID);
        hit->SetPos2(step->GetPreStepPoint()->GetPosition());
      }
  }

  return true;
}

//
