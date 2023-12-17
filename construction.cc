#include "construction.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  G4bool checkOverlaps = true;
  
  G4double innerRadius = 0. * cm;
  G4double outerRadius = 21.5 * cm;
  G4double hz = 43.0 * cm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;
  
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* world_log = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* inner_log = nist->FindOrBuildMaterial("G4_lAr");
  
  G4Tubs* TubeWorld = new G4Tubs("World",
                                 1.2 * innerRadius,
                                 1.2 * outerRadius,
                                 1.2 * hz,
                                 startAngle,
                                 spanningAngle);     

  G4LogicalVolume *logicWorld = new G4LogicalVolume(TubeWorld,  
                                                    world_mat,                                       
                                                    "World");                                       

  G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr,
                                                   G4ThreeVector(),                           
                                                   logicWorld,                                
                                                   "World",                                   
                                                   nullptr,                                  
                                                   false,                                     
                                                   0,                                         
                                                   checkOverlaps);

  G4Tubs* trackerTube = new G4Tubs("Tracker",
                                   1.00001 * innerRadius,
                                   1.00001 * outerRadius,
                                   hz,
                                   startAngle,
                                   spanningAngle);
                                    
  G4LogicalVolume* trackerLog = new G4LogicalVolume(trackerTube, 
                                                    world_log, 
                                                    "Tracker");

  G4VPhysicalVolume* trackerPhys = new G4PVPlacement(nullptr,                            // no rotation
                                                     G4ThreeVector(0., 0., 0.),          // translation position
                                                     trackerLog,                         // its logical volume
                                                     "Tracker",                          // its name
                                                     logicWorld,                         // its mother (logical) volume
                                                     false,                              // no boolean operations
                                                     0,                                  // its copy number 
                                                     checkOverlaps);

  G4Tubs* InnerTube = new G4Tubs("InnerTube",
                                 innerRadius,
                                 outerRadius,
                                 hz,
                                 startAngle,
                                 spanningAngle);     

  G4LogicalVolume *innerlog = new G4LogicalVolume(InnerTube,  
                                                  inner_log,                                       
                                                  "InnerTube");                                       

  G4VPhysicalVolume* physinner = new G4PVPlacement(nullptr,
                                                   G4ThreeVector(),                           
                                                   innerlog,                                
                                                   "InnerTube",                                   
                                                   trackerLog,                                  
                                                   false,                                     
                                                   0,                                         
                                                   checkOverlaps);
                                                
  G4VisAttributes* red = new G4VisAttributes(G4Colour::Red());
  red->SetVisibility(true);
  red->SetForceWireframe(true);
  innerlog->SetVisAttributes(red);

 
  G4VisAttributes* blue = new G4VisAttributes(G4Colour::Blue());
  blue->SetVisibility(true);
  blue->SetForceWireframe(true);
  trackerLog->SetVisAttributes(blue);

  G4VisAttributes* green = new G4VisAttributes(G4Colour::Green());
  green->SetVisibility(true);
  green->SetForceWireframe(true);
  logicWorld->SetVisAttributes(green);

  return physWorld; 
}
