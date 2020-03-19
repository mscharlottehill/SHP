

#include "EventAction.hh"
#include "BlockHit.hh"
#include "Constants.hh"
#include "Analysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"


//

EventAction::EventAction()
: G4UserEventAction(),
  fBlockHCID  (-1)
{
  // set printing per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);
}

//

EventAction::~EventAction()
{}

BlockHitsCollection*
EventAction::GetHitsCollection(G4int hcID,
                                    const G4Event* event) const
{
  auto hitsCollection
    = static_cast<BlockHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

//

void EventAction::BeginOfEventAction(const G4Event*)
{
  // Find hit collections and histogram Ids by names (just once)
  // and save them in the data members of this class

  if (fBlockHCID == -1) {
      // hit collections IDs
      auto sdManager = G4SDManager::GetSDMpointer();
      fBlockHCID   = sdManager->GetCollectionID("blockColl");
    }
}

//

void EventAction::EndOfEventAction(const G4Event* event)
{
  //
  // Fill histograms & ntuple
  //
  auto hc = GetHitsCollection(fBlockHCID, event);
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Drift chambers hits
  auto hc = event->GetHCofThisEvent();
  if ( ! hc ) return;

  auto hit = static_cast<BlockHit*>(hc->GetHit());
  G4int blockid = hit->GetBlockID();
  G4double e1 = hit->GetEdep1();
  G4double e2 = hit->GetEdep2();
  G4ThreeVector pos1 = hit->GetPos1();
  G4ThreeVector pos2 = hit->GetPos2();

  analysisManager->FillNtupleIColumn(0, blockid);
  analysisManager->FillNtupleDColumn(1, e1);
  analysisManager->FillNtupleDColumn(2, e2);
  analysisManager->FillNtupleDColumn(3, pos1.getX());
  analysisManager->FillNtupleDColumn(4, pos2.getX());
  analysisManager->FillNtupleDColumn(5, pos1.getY());
  analysisManager->FillNtupleDColumn(6, pos2.getY());
  analysisManager->FillNtupleDColumn(7, pos1.getZ());
  analysisManager->FillNtupleDColumn(8, pos2.getZ());
  analysisManager->AddNtupleRow();

}

//
