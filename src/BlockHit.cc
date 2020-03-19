

#include "BlockHit.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//

G4ThreadLocal G4Allocator<BlockHit>* BlockHitAllocator;

//

BlockHit::BlockHit()
: G4VHit(),
  fBlockID(-1), fEdep1(0.), fEdep2(0.), fPos1(0.), fPos2(0.)
{}

//

BlockHit::BlockHit(G4int blockID)
: G4VHit(),
  fBlockID(blockID), fEdep1(0.), fEdep2(0.), fPos1(0.), fPos2(0.)
{}

//

BlockHit::~BlockHit()
{}

//

BlockHit::BlockHit(const BlockHit &right)
: G4VHit(),
  fBlockID(right.fBlockID),
  fEdep1(right.fEdep1),
  fEdep2(right.fEdep2),
  fPos1(right.fPos1),
  fPos2(right.fPos2)
{}

//

const BlockHit& BlockHit::operator=(const BlockHit
                                                          &right)
{
  fBlockID = right.fBlockID;
  fEdep1 = right.fEdep1;
  fEdep2 = right.fEdep2;
  fPos1 = right.fPos1;
  fPos2 = right.fPos2;
  return *this;
}

//

int BlockHit::operator==(const BlockHit &right) const
{
  return (fBlockID==right.fBlockID);
}


//


void BlockHit::Print()
{
  G4cout << "  Cell[" << fBlockID << "] " << fEdep1/MeV << " (MeV)" << G4endl;
}

//
