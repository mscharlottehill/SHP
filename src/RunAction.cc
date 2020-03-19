

#include "RunAction.hh"
#include "EventAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//

RunAction::RunAction(EventAction* eventAction)
 : G4UserRunAction(),
   fEventAction(eventAction)
{
  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in Analysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Default settings
  analysisManager->SetNtupleMerging(true);
     // Note: merging ntuples is available only with Root output
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("");

  // Creating ntuple
  //
  if ( fEventAction ) {
    analysisManager->CreateNtuple("", "Hits");
/*    analysisManager->CreateNtupleIColumn("RingID");  // column Id = 0
    analysisManager->CreateNtupleIColumn("BlockID");  // column Id = 1*/
    analysisManager->CreateNtupleIColumn("UniqueBlockID") // column Id = 0
    analysisManager->CreateNtupleDColumn("Energy1"); // column Id = 1
    analysisManager->CreateNtupleDColumn("Energy2"); // column Id = 2
    analysisManager->CreateNtupleDColumn("X1");    // column Id = 3
    analysisManager->CreateNtupleDColumn("X2");    // column Id = 4
    analysisManager->CreateNtupleDColumn("Y1");    // column Id = 5
    analysisManager->CreateNtupleDColumn("Y2");    // column Id = 6
    analysisManager->CreateNtupleDColumn("Z1");    // column Id = 7
    analysisManager->CreateNtupleDColumn("Z2");    // column Id = 8
  }
}

//

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();
}

//

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  // The default file name is set in RunAction::RunAction(),
  // it can be overwritten in a macro
  analysisManager->OpenFile();
}

//

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // save histograms & ntuple
  //
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

}

//
