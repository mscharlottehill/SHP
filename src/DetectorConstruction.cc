

#include "DetectorConstruction.hh"
#include "BlockSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"

#include "G4SDManager.hh"
#include "G4GenericMessenger.hh"
#include "G4RunManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//

//G4ThreadLocal

//

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true)
{
  DefineMaterials();
  Construct();
}

//

DetectorConstruction::~DetectorConstruction()
{
}

//

void DetectorConstruction::DefineMaterials()
{
  G4NistManager* man = G4NistManager::Instance();

  G4bool isotopes = false;

  G4Element*  O = man->FindOrBuildElement("O" , isotopes);
  G4Element* Si = man->FindOrBuildElement("Si", isotopes);
  G4Element* Lu = man->FindOrBuildElement("Lu", isotopes);

  G4Material* LSO = new G4Material("Lu2SiO5", 7.4*g/cm3, 3);
  LSO->AddElement(Lu, 2);
  LSO->AddElement(Si, 1);
  LSO->AddElement(O , 5);
}

//

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // change detector parameterisation HERE //
  //
  G4int blocks_per_ring = 10;
  G4int nb_rings = 8;
  G4double in_radius = 0.39*m;
  G4double rad_block_depth = 0.05*m;
  G4double det_length = 2.*m;

  // bookkeeping geometry parameters HERE //
  //
  G4double out_radius = in_radius+rad_block_depth;
  G4int nb_blocks = nb_rings*blocks_per_ring;
  G4double dPhi = twopi*rad;
  G4double dPhi_per_block = dPhi/blocks_per_ring;
  G4double ring_length = det_length/nb_rings;


  G4NistManager* nist = G4NistManager::Instance();
  G4Material* default_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* block_mat   = nist->FindOrBuildMaterial("Lu2SiO5");


  // Hello, World!
  // a simple cube full of air

  G4double world_half = 2.5*m;

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       world_half, world_half, world_half); //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        default_mat,         //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      fCheckOverlaps);       // checking overlaps


  // Tube Time!
  // a cylinder of LSO

  G4Tubs* solidTube =
    new G4Tubs("Tube", in_radius, out_radius, 0.5*det_length, 0., dPhi);

  G4LogicalVolume* logicTube =
    new G4LogicalVolume(solidTube,           //its solid
                        block_mat,         //its material
                        "Tube");             //its name

  G4VPhysicalVolume* physTube =
    new G4PVPlacement(0,                       //no rotation
                      G4ThreeVector(),         //at (0,0,0)
                      logicTube,           //its logical volume
                      "Tube",              //its name
                      logicWorld,              //its mother  volume
                      false,                   //no boolean operation
                      1,                       //copy number
                      fCheckOverlaps);         // checking overlaps


  // Put A Ring On It!
  // a ring of LSO

  G4Tubs* solidRing =
    new G4Tubs("Ring", in_radius, out_radius, 0.5*ring_length, 0., dPhi);

  G4LogicalVolume* logicRing =
    new G4LogicalVolume(solidRing,          //its solid
                        block_mat,           //its material
                        "Ring");        //its name

  G4double ringZpos = -0.5*(det_length+ring_length);

  for (G4int iring = 0; iring < nb_rings; iring++) {
    ringZpos += ring_length;
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,ringZpos), //position
                      logicRing,             //its logical volume
                      "physRing",                //its name
                      logicTube,         //its mother  volume
                      false,                 //no boolean operation
                      iring,                 //copy number
                      fCheckOverlaps);       // checking overlaps
    }

  // Let's Get Segmented!
  // define segments

  G4VSolid* DividedRing =
    new G4Tubs("DividedRing", in_radius, out_radius, 0.5*ring_length,
              -dPhi_per_block/2., dPhi_per_block);

  G4LogicalVolume* logicDividedRing =
    new G4LogicalVolume(DividedRing, block_mat, "logicDividedRing", 0, 0, 0);

  G4VPhysicalVolume* physDividedRing =
    new G4PVReplica("physDividedRing", logicDividedRing, logicRing, kPhi,
                    blocks_per_ring, dPhi_per_block);

  // Visualization attributes
  //
  logicRing->SetVisAttributes (G4VisAttributes::GetInvisible());


  //always return the physical World
  //
  return physWorld;
}

//

void DetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  auto blockSD
    = new BlockSD("blockSD");
  G4SDManager::GetSDMpointer()->AddNewDetector(blockSD);
  SetSensitiveDetector("logicDividedRing",blockSD);


}

//
