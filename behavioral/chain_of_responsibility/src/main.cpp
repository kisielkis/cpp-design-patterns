#include <iostream>

#include "Ticket.h"
#include "HelpDesk.h"
#include "TechnicalSupport.h"
#include "Developer.h"
#include "Manager.h"

int main() {
    using namespace std;
    auto hpDesk = std::make_shared<HelpDesk>();
    auto thDesk = std::make_shared<TechnicalSupport>();
    auto devDesk = std::make_shared<Developer>();
    auto manDesk = std::make_shared<Manager>();

    hpDesk->SetNext(thDesk)->SetNext(devDesk)->SetNext(manDesk);
    cout << "START:" << endl;
    cout << hpDesk->Handle(Priority::LOW) << endl;          // Handle LOW priority by HelpDesk
    cout << hpDesk->Handle(Priority::MEDIUM) << endl;       // Handle Medium priority by TechnicalSupport
    cout << hpDesk->Handle(Priority::LOW) << endl;          // Handle LOW priority by HelpDesk
    cout << hpDesk->Handle(Priority::HIGH) << endl;         // Handle High priority by Developer
    cout << hpDesk->Handle(Priority::CRITICAL) << endl;     // Handle CRITICAL priority by Manager
    cout << hpDesk->Handle(Priority::NONE) << endl;         // NOT HANDLED
    cout << "END" << endl;
    
    return 0;
}