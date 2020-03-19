
#ifndef BlockSD_h
#define BlockSD_h 1

#include "G4VSensitiveDetector.hh"

#include "BlockHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

///

class BlockSD : public G4VSensitiveDetector
{
  public:
    BlockSD(G4String name);
    virtual ~BlockSD();

    virtual void Initialize(G4HCofThisEvent*HCE);
    virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);

  private:
    BlockHitsCollection* fHitsCollection;
    G4int fHCID;
};

//

#endif
