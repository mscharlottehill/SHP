

#ifndef BlockHit_h
#define BlockHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"


class BlockHit : public G4VHit
{
  public:
    BlockHit();
    BlockHit(G4int blockID);
    BlockHit(const BlockHit &right);
    virtual ~BlockHit();

    const BlockHit& operator=(const BlockHit &right);
    int operator==(const BlockHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    virtual void Print();

    void SetBlockID(G4int z) { fBlockID = z; }
    G4int GetBlockID() const { return fBlockID; }

    void SetEdep1(G4double de) { fEdep1 = de; }
    void AddEdep1(G4double de) { fEdep1 += de; }
    G4double GetEdep1() const { return fEdep1; }

    void SetEdep2(G4double de) { fEdep2 = de; }
    void AddEdep2(G4double de) { fEdep2 += de; }
    G4double GetEdep2() const { return fEdep2; }

    void SetPos1(G4ThreeVector xyz) { fPos1 = xyz; }
    G4ThreeVector GetPos1() const { return fPos1; }

    void SetPos2(G4ThreeVector xyz) { fPos2 = xyz; }
    G4ThreeVector GetPos2() const { return fPos2; }

  private:
    G4int fBlockID;
    G4double fEdep1;
    G4double fEdep2;
    G4ThreeVector fPos1;
    G4ThreeVector fPos2;
};

using BlockHitsCollection = G4THitsCollection<BlockHit>;

extern G4ThreadLocal G4Allocator<BlockHit>* BlockHitAllocator;

inline void* BlockHit::operator new(size_t)
{
  if (!BlockHitAllocator) {
       BlockHitAllocator = new G4Allocator<BlockHit>;
  }
  return (void*)BlockHitAllocator->MallocSingle();
}

inline void BlockHit::operator delete(void* aHit)
{
  BlockHitAllocator->FreeSingle((BlockHit*) aHit);
}

//

#endif
