#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4VUserDetectorConstruction.hh"
#include "construction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4AnalysisManager.hh"

SteppingAction::SteppingAction(EventAction* eventAction)
:G4UserSteppingAction(), fEventAction(eventAction)
{
  fEventAction = eventAction;
  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  analysisManager->CreateNtuple("Step", "Step");
  analysisManager->CreateNtupleIColumn("event");
  analysisManager->CreateNtupleSColumn("particlename");
  analysisManager->CreateNtupleIColumn("particlePDG");
  analysisManager->CreateNtupleDColumn("Energy");
  analysisManager->FinishNtuple(0);
}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{ 
  auto analysisManager = G4AnalysisManager::Instance();
  /*G4String fileName = "Step3.root";
  analysisManager->OpenFile(fileName);
  G4cout << "Using " << analysisManager->GetType() << G4endl;*/
  
  G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  const G4String particleName = step->GetTrack()->GetDefinition()->GetParticleName();
  
  const G4int particlePDG = step->GetTrack()->GetDefinition()->GetPDGEncoding();
  
  // get volume of the current step
  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  G4double KineticEnergy = step->GetTrack()->GetKineticEnergy();
  
  // energy deposit
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);
  
  analysisManager->FillNtupleIColumn(0, 0, evt);
  analysisManager->FillNtupleSColumn(0, 1, particleName);
  analysisManager->FillNtupleIColumn(0, 2, particlePDG);
  analysisManager->FillNtupleDColumn(0, 3, edepStep);
  analysisManager->AddNtupleRow(0);
  
  /*if (edepStep <= 0.)
      G4cout<<KineticEnergy<<G4endl;
      return;*/
  
  // step length
  G4double stepLength = 0.;
  if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    stepLength = step->GetStepLength();
  }
  /*analysisManager->Write();
  analysisManager->CloseFile();*/
}
