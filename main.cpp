#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "filehandler.h"
#include "CargoList.h"
#include "FreightList.h"
#include "ScheduleList.h"

using namespace std;

void displayCargos(const CargoList& clist) {
    cout << "\n=== Cargo List ===\n";
    for (const Cargo& c : clist.getCargoList()) {
        cout << c;
    }
}

void displayFreights(const FreightList& flist) {
    cout << "\n=== Freight List ===\n";
    for (const Freight& f : flist.getFreightList()) {
        cout << f;
    }
}

void displayUnmatched(const CargoList& clist, const FreightList& flist) {
    cout << "\n=== Unmatched Cargos ===\n";
    if (clist.getUnmatchedCargo().empty())
        cout << "None\n";
    else {
        for (const Cargo& c : clist.getUnmatchedCargo()) {
            cout << c;
        }
    }
    cout << "\n=== Unmatched Freights ===\n";
    if (flist.getUnmatchedFreight().empty())
        cout << "None\n";
    else {
        for (const Freight& f : flist.getUnmatchedFreight()) {
            cout << f;
        }
    }
}

void displaySchedules(const ScheduleList& slist) {
    cout << "\n=== Schedule List ===\n";
    for (const Schedule& s : slist.getSchedule()) {
        cout << s;
    }
}

int main() {
    filehandler fh;
    FreightList freightList;
    CargoList cargoList;
    ScheduleList scheduleList;

    string cargofile, freightfile, schedulefile;

    cout << "=== Transport Management System ===\n\n";

    cout << "Location of cargo file: ";
    getline(cin, cargofile);

    cout << "Location of freight file: ";
    getline(cin, freightfile);

    cout << "Location of schedule file: ";
    getline(cin, schedulefile);

    vector<string> cargoLines;
    if (fh.readLines(cargofile, cargoLines)) {
        for (const auto& line : cargoLines) {
            try {
                Cargo c = Cargo::fromString(line);
                cargoList.addcargo(c);
            }
            catch (...) {}
        }
    }

    vector<string> freightLines;
    if (fh.readLines(freightfile, freightLines)) {
        for (const auto& line : freightLines) {
            try {
                Freight f = Freight::fromString(line);
                freightList.addfreight(f);
            }
            catch (...) {}
        }
    }

    scheduleList.updateScheduleandUnmatched(cargoList, freightList);

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    // Initial display
    displayCargos(cargoList);
    displayFreights(freightList);
    displaySchedules(scheduleList);
    displayUnmatched(cargoList, freightList);

    while (true) {
        cout << "\nSelect action:\n1. Cargo\n2. Freight\n3. Exit\n> ";
        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 3) break;

        if (choice == 1) { // Cargo menu
            cout << "\nCargo actions:\n1. Add\n2. Edit\n3. Remove\n4. Back\n> ";
            int sub;
            if (!(cin >> sub) || sub < 1 || sub > 4) {
                cout << "Invalid input.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (sub == 1) { // Add cargo
                // --- Input and validation INLINE here ---
                int id, h, m ,cargosz;
                string dest, ampm;

                cout << "Enter Cargo ID: ";
                while (!(cin >> id)) {
                    cout << "Invalid input, enter number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter destination: ";
                getline(cin, dest);

                cout << "Enter time (hour minute): ";
                while (!(cin >> h >> m) || !cargoList.isValidTime(h, m)) {
                    cout << "Invalid time, enter again: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                // ---------------------------------------

                Cargo c(id, dest, h, m);
                cargoList.addcargo(c);
                cout << "Cargo added.\n";

                scheduleList.updateScheduleandUnmatched(cargoList, freightList);
            }
            else if (sub == 2) { // Edit cargo
                int id;
                cout << "Enter Cargo ID to edit: ";
                while (!(cin >> id)) {
                    cout << "Invalid input, enter number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                Cargo* existing = cargoList.searchcargo(id);
                if (!existing) {
                    cout << "Cargo not found.\n";
                    continue;
                }

                // --- All prompt/input for new data inline ---
                int newId = existing->getidnum();
                string newDest = existing->getdest();
                int newH = existing->gettimeh();
                int newM = existing->gettimem();
                string input;

                cout << "Enter new ID (or Enter to keep " << newId << "): ";
                getline(cin, input);
                if (!input.empty()) newId = stoi(input);

                cout << "Enter new destination (or Enter to keep " << newDest << "): ";
                getline(cin, input);
                if (!input.empty()) newDest = input;

                cout << "Enter new hour (0-23) (or Enter to keep " << newH << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    newH = stoi(input);
                    if (newH < 0 || newH > 23) {
                        cout << "Invalid hour.\n";
                        continue;
                    }
                }

                cout << "Enter new minute (0-59) (or Enter to keep " << newM << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    newM = stoi(input);
                    if (newM < 0 || newM > 59) {
                        cout << "Invalid minute.\n";
                        continue;
                    }
                }
                // ----------------------------------------

                Cargo newCargo(newId, newDest, newH, newM);
                if (cargoList.editCargo(id, newCargo))
                    cout << "Cargo updated.\n";
                else
                    cout << "Failed to update cargo.\n";

                scheduleList.updateScheduleandUnmatched(cargoList, freightList);
            }
            else if (sub == 3) { // Remove cargo
                int id;
                cout << "Enter Cargo ID to remove: ";
                while (!(cin >> id)) {
                    cout << "Invalid input, enter number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (cargoList.removeCargo(id))
                    cout << "Cargo removed.\n";
                else
                    cout << "Cargo not found.\n";

                scheduleList.updateScheduleandUnmatched(cargoList, freightList);
            }
        }
        else if (choice == 2) { // Freight menu
            cout << "\nFreight actions:\n1. Add\n2. Edit\n3. Remove\n4. Back\n> ";
            int sub;
            if (!(cin >> sub) || sub < 1 || sub > 4) {
                cout << "Invalid input.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (sub == 1) { // Add freight
                int id, h, m;
                string dest;

                cout << "Enter Freight ID: ";
                while (!(cin >> id)) {
                    cout << "Invalid input, enter number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter destination: ";
                getline(cin, dest);

                cout << "Enter time (hour minute): ";
                while (!(cin >> h >> m) || !freightList.isValidTime(h, m)) {
                    cout << "Invalid time, enter again: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                Freight f(id, dest, h, m);
                freightList.addfreight(f);
                cout << "Freight added.\n";

                scheduleList.updateScheduleandUnmatched(cargoList, freightList);
            }
            else if (sub == 2) { // Edit freight
                int id;
                cout << "Enter Freight ID to edit: ";
                while (!(cin >> id)) {
                    cout << "Invalid input, enter number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                Freight* existing = freightList.searchFreight(id);
                if (!existing) {
                    cout << "Freight not found.\n";
                    continue;
                }

                int newId = existing->getidnum();
                string newDest = existing->getdest();
                int newH = existing->gettimeh();
                int newM = existing->gettimem();
                string input;

                cout << "Enter new ID (or Enter to keep " << newId << "): ";
                getline(cin, input);
                if (!input.empty()) newId = stoi(input);

                cout << "Enter new destination (or Enter to keep " << newDest << "): ";
                getline(cin, input);
                if (!input.empty()) newDest = input;

                cout << "Enter new hour (0-23) (or Enter to keep " << newH << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    newH = stoi(input);
                    if (newH < 0 || newH > 23) {
                        cout << "Invalid hour.\n";
                        continue;
                    }
                }

                cout << "Enter new minute (0-59) (or Enter to keep " << newM << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    newM = stoi(input);
                    if (newM < 0 || newM > 59) {
                        cout << "Invalid minute.\n";
                        continue;
                    }
                }

                Freight newF(newId, newDest, newH, newM);
                if (freightList.editFreight(id, newF))
                    cout << "Freight updated.\n";
                else
                    cout << "Failed to update freight.\n";

                scheduleList.updateScheduleandUnmatched(cargoList, freightList);
            }
            else if (sub == 3) { // Remove freight
                int id;
                cout << "Enter Freight ID to remove: ";
                while (!(cin >> id)) {
                    cout << "Invalid input, enter number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (freightList.removeFreight(id))
                    cout << "Freight removed.\n";
                else
                    cout << "Freight not found.\n";

                scheduleList.updateScheduleandUnmatched(cargoList, freightList);
            }
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

        // Clear screen & redisplay all data after each operation (preserved your original display calls)
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        displayFreights(freightList);
        displayCargos(cargoList);
        displaySchedules(scheduleList);
        displayUnmatched(cargoList, freightList);
    }

    // Write all data back to files before GUI exits
    vector<string> cargoOutLines, freightOutLines, scheduleOutLines;
    for (const auto& c : cargoList.getCargoList()) {
        cargoOutLines.push_back(Cargo::toString(c));
    }
    for (const auto& f : freightList.getFreightList()) {
        freightOutLines.push_back(Freight::toString(f));
    }
    for (const auto& s : scheduleList.getSchedule()) {
        scheduleOutLines.push_back(Schedule::toString(s));
    }

    fh.writeLines(cargofile, cargoOutLines);
    fh.writeLines(freightfile, freightOutLines);
    fh.writeLines(schedulefile, scheduleOutLines);

    cout << "\nAll data saved. Goodbye!\n";
    return 0;
}
