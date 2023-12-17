#ifndef SteppingAction_HH
#define SteppingAction_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "globals.hh"
#include "EventAction.hh"
#include "construction.hh"

//class G4LogicalVolume;

/// Stepping action class
///

//class construction;

class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(EventAction* eventAction);
  ~SteppingAction();

    // method from the base class
  void UserSteppingAction(const G4Step* step) /*override*/;

private:
  EventAction* fEventAction;
};

#endif
