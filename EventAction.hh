#ifndef EventAction_HH
#define EventAction_HH

#include "G4UserEventAction.hh"
#include "globals.hh"

class EventAction : public G4UserEventAction
{
  public:
    EventAction() /*= default*/;
    ~EventAction() /*override = default*/;

    void  BeginOfEventAction(const G4Event* event) /*override*/;
    void    EndOfEventAction(const G4Event* event) /*override*/;

    void AddAbs(G4double de, G4double dl);
    void AddGap(G4double de, G4double dl);
    void AddEdep(G4double Edep);

  private:
    G4double fEnergyAbs;
    G4double fEnergyGap;
    G4double fTrackLAbs;
    G4double fTrackLGap;
    G4double fTotalEnergyDeposit;
    

    /*G4double  fEnergyAbs = 0.;
    G4double  fEnergyGap = 0.;
    G4double  fTrackLAbs = 0.;
    G4double  fTrackLGap = 0.;*/
};

inline void EventAction::AddAbs(G4double de, G4double dl) {
  fEnergyAbs += de;
  fTrackLAbs += dl;
}

inline void EventAction::AddGap(G4double de, G4double dl) {
  fEnergyGap += de;
  fTrackLGap += dl;
}

/*inline void EventAction::AddEdep(G4double Edep) {
  fTotalEnergyDeposit+= Edep;
}*/
#endif





