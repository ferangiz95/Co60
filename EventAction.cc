#include "EventAction.hh"
#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

EventAction::EventAction()
:G4UserEventAction(), fTotalEnergyDeposit(0.)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
  // initialisation per event
  fEnergyAbs = 0.;
  fEnergyGap = 0.;
  fTrackLAbs = 0.;
  fTrackLGap = 0.;
  fTotalEnergyDeposit = 0.;
}

void EventAction::AddEdep(G4double Edep)
{

  fTotalEnergyDeposit += Edep;
}

void EventAction::EndOfEventAction(const G4Event* event)
{
  // Accumulate statistics

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  analysisManager->FillH1(0, fEnergyAbs);
  analysisManager->FillH1(1, fEnergyGap);
  analysisManager->FillH1(2, fTrackLAbs);
  analysisManager->FillH1(3, fTrackLGap);
  analysisManager->FillH1(4, fTotalEnergyDeposit);

  // fill ntuple
  /*analysisManager->FillNtupleDColumn(0, fEnergyAbs);
  analysisManager->FillNtupleDColumn(1, fEnergyGap);
  analysisManager->FillNtupleDColumn(2, fTrackLAbs);
  analysisManager->FillNtupleDColumn(3, fTrackLGap);
  analysisManager->FillNtupleDColumn(4, fTotalEnergyDeposit);
  analysisManager->AddNtupleRow();*/
   
  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;

    G4cout
       << "   Absorber: total energy: " << std::setw(0)
                                        << G4BestUnit(fEnergyAbs,"Energy")
       << "       total track length: " << std::setw(1)
                                        << G4BestUnit(fTrackLAbs,"Length")
       << G4endl
       << "        Gap: total energy: " << std::setw(2)
                                        << G4BestUnit(fEnergyGap,"Energy")
       << "       total track length: " << std::setw(3)
                                        << G4BestUnit(fTrackLGap,"Length")
       << "       total track Edep: "   << std::setw(4)
                                        << G4BestUnit(fTotalEnergyDeposit,"Energy")
       << G4endl;
  }
  
}
