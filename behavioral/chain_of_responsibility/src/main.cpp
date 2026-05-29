#include <iostream>

#include "Ticket.h"
#include "HelpDesk.h"
#include "TechnicalSupport.h"
#include "Developer.h"
#include "Manager.h"

int main() {
    using namespace std;
    HelpDesk *hpDesk = new HelpDesk();
    TechnicalSupport *thDesk = new TechnicalSupport();
    Developer *devDesk = new Developer();
    Manager *manDesk = new Manager();

    hpDesk->SetNext(thDesk)->SetNext(devDesk)->SetNext(manDesk);

    cout << hpDesk->Handle(Priority::LOW) << endl;          // Handle LOW priority by HelpDesk
    cout << hpDesk->Handle(Priority::MEDIUM) << endl;       // Handle Medium priority by TechnicalSupport
    cout << hpDesk->Handle(Priority::LOW) << endl;          // Handle LOW priority by HelpDesk
    cout << hpDesk->Handle(Priority::HIGH) << endl;         // Handle High priority by Developer
    cout << hpDesk->Handle(Priority::CRITICAL) << endl;     // Handle CRITICAL priority by Manager
    cout << hpDesk->Handle(Priority::NONE) << endl;         // NOT HANDLED

    delete hpDesk;
    delete thDesk;
    delete devDesk;
    delete manDesk;

    return 0;
}