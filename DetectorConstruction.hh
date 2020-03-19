

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include "G4FieldManager.hh"

#include <vector>

class MagneticField;

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4GenericMessenger;

/// Detector construction

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void ConstructMaterials();

  private:

    G4GenericMessenger* fMessenger;

    static G4ThreadLocal MagneticField* fMagneticField;
    static G4ThreadLocal G4FieldManager* fFieldMgr;

    G4LogicalVolume* fHodoscope1Logical;
    G4LogicalVolume* fHodoscope2Logical;
    G4LogicalVolume* fWirePlane1Logical;
    G4LogicalVolume* fWirePlane2Logical;
    G4LogicalVolume* fCellLogical;
    G4LogicalVolume* fHadCalScintiLogical;
    G4LogicalVolume* fMagneticLogical;

    std::vector<G4VisAttributes*> fVisAttributes;

    G4double fArmAngle;
    G4RotationMatrix* fArmRotation;
    G4VPhysicalVolume* fSecondArmPhys;
};

//

#endif
