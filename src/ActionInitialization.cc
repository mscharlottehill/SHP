

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"

//

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}

//

ActionInitialization::~ActionInitialization()
{}

//

void ActionInitialization::BuildForMaster() const
{
  EventAction* eventAction = new EventAction;
  SetUserAction(new RunAction(eventAction));
}

//

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction);

  auto eventAction = new EventAction;
  SetUserAction(eventAction);

  SetUserAction(new RunAction(eventAction));
}

//
