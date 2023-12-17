#include <iostream>
#include <fstream>
#include <cstdlib>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "construction.hh"
#include "G4VisAttributes.hh"

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "physics.hh"

#include "G4VUserActionInitialization.hh"
#include "ActionInitialization.hh"
#include "G4UserEventAction.hh"
#include "RunAction.hh"
#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4UIterminal.hh"
#include "EventAction.hh"
#include "G4Event.hh"

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "G4Step.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"

using namespace std;

int main(int argc, char** argv)
{ 
  G4UIExecutive* ui = nullptr;
  if ( argc == 1 ) { ui = new G4UIExecutive(argc, argv); }
  G4RunManager *runManager= new G4RunManager();
    
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization());
  runManager->SetUserAction(new PrimaryGeneratorAction());
  runManager->Initialize();
    
  // Initialize visualization
  G4VisManager *VisManager = new G4VisExecutive();
  VisManager->Initialize();
  
  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  //UImanager->ApplyCommand("/control/execute gps.mac");
  //UImanager->ApplyCommand("/control/execute run2.mac");
  //UImanager->ApplyCommand("/control/execute run1.mac");
    // Process macro or start UI session
  //
  if ( ! ui ) {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  
  ui->SessionStart();
  
  return 0;

}
