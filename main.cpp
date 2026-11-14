#include "Tema15_Telekom.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Tema15_Telekom.h"

using namespace std;

int main()
{
    try
    {
        vector<Subscription*> plans;

        plans.push_back(
            new PrepaidPlan(
                "0878655148",
                "Victoria",
                20,
                300,
                5000,
                50
            )
        );

        plans.push_back(
            new PostpaidPlan(
                "0899876543",
                "Aleksandar",
                30,
                500,
                10000,
                24
            )
        );

        plans[0]->Call(120);
        plans[0]->UseData(1500);

        plans[1]->Call(700);
        plans[1]->UseData(4000);

        Bundle extra(
            "Extra",
            200,
            3000,
            10
        );

        (*plans[0]) + extra;
        (*plans[1]) + extra;

        cout << "===== MONTHLY REPORT ====="
             << endl << endl;

        for (auto p : plans)
        {
            p->Print();

            cout << "Bill: "
                 << p->Bill()
                 << endl;

            cout << "------------------"
                 << endl;
        }

        Subscription::OperatorReport();

        for (auto p : plans)
        {
            delete p;
        }
    }
    catch (exception& e)
    {
        cout << "Error: "
             << e.what()
             << endl;
    }

    return 0;
}