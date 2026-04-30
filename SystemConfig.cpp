#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// finalized
struct MAIN
{
    void title()
    {
        const char str[35] = "BANK CUSTOMERS QUEUING SYSTEM";
        int width = 40;
        cout << setw(40);
        cout << char(201); // upper left corner
        for (int i = 0; i < width; i++)
            cout << char(205);
        cout << char(187); // upper right corner
        cout << endl
             << setw(40) << char(186) << "      " << str << "      " << char(186) << endl;
        cout << setw(40);
        cout << char(200); // bottom left corner
        for (int i = 0; i < width; i++)
            cout << char(205);
        cout << char(188) << endl
             << endl
             << endl; // bottom right corner
    }

    void displayMainMenu()
    {
        cout << "=========================================\n";
        cout << "Welcome to the Bank Simulation System!" << endl;
        cout << "=========================================\n";
        cout << "Please select an option:" << endl;
        cout << "1. System Configuration" << endl;
        cout << "2. Run Simulation" << endl;
        cout << "3. View Reports" << endl;
        cout << "4. View Statistics" << endl;
        cout << "5. Exit" << endl;
        cout << "========================================" << endl;
    }

    void displaySystemConfigMenu()
    {
        cout << "========================================" << endl;
        cout << "System Configuration selected." << endl;
        cout << "========================================" << endl;
        cout << "1. Set Number of Tellers" << endl;
        cout << "2. Set Working Hours" << endl;
        cout << "3. Define Transaction Types" << endl;
        cout << "4. Set Yearly Customer Target" << endl;
        cout << "5. View Current Configuration" << endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "========================================" << endl;
    }
};

// finalized
struct NumberOfTellers
{
    // Function to validate the number of tellers
    bool isValidNumber(int num)
    {
        return num >= 1 && num <= 10;
    }

    // Code to set number of tellers and save this configuration
    void numberofTellers()
    {
        string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        int numTellers[7];

        for (int i = 0; i < 7; i++)
        {
            cout << "Enter the number of tellers on day " << days[i] << ": ";

            while (!(cin >> numTellers[i]) || !isValidNumber(numTellers[i]))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "ERROR\nPLEASE RE-ENTER A POSSIBLE NUMBER: ";
            }
        }

        // Code to save this configuration
        ofstream file("tellers.txt");
        int totalTellers = 0;
        file << "Day \t Number of Tellers\n";
        for (int i = 0; i < 7; i++)
        {
            file << days[i] << setw(15 - days[i].length()) << numTellers[i] << "\n";
            totalTellers += numTellers[i];
        }
        file << "-----------------------------------\n";
        file << "Total Tellers: " << totalTellers << endl;
        file.close();
    }

    // Function to display the number of tellers from the saved configuration
    void DisplayTellers()
    {
        cout << "=========================================\n";
        cout << "Current Number of Tellers Configuration:\n";
        cout << "=========================================\n";
        ifstream file("tellers.txt");
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
};

// finalized
struct WorkingHours
{
    int HourstoMinutes(string time)
    {
        return ((time[0] - '0') * 10 + (time[1] - '0')) * 60 + (time[3] - '0') * 10 + (time[4] - '0');
    }

    bool isValidTime(string time)
    {
        if (time.length() != 5 || time[2] != ':')
            return false;
        int hours = (time[0] - '0') * 10 + (time[1] - '0');
        int minutes = (time[3] - '0') * 10 + (time[4] - '0');
        return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60;
    }

    void setWorkingHours()
    {
        char opening[6], closing[6];
        do
        {
            cout << "ENTER OPENING TIME IN THIS FORMAT (HH:MM) 24_HR Format:\n";
            cin >> opening;

            while (!isValidTime(opening))
            {
                cout << "ERROR\n"
                     << "PLEASE RE-ENTER A VALID TIME\n";
                cin >> opening;
            }

            cout << "ENTER CLOSING TIME IN THIS FORMAT (HH:MM) 24_HR Format:\n";
            cin >> closing;

            while (!isValidTime(closing))
            {
                cout << "ERROR\n"
                     << "PLEASE RE-ENTER A VALID TIME\n";
                cin >> closing;
            }

            if (HourstoMinutes(closing) <= HourstoMinutes(opening))
                cout << "ERROR\nCLOSING TIME SHOULD BE AFTER OPENING TIME\nPLEASE RE-ENTER THEM\n";

            ofstream file("workinghours.txt");

            file << "Opening Time : " << opening << endl;
            file << "Closing Time : " << closing << endl;
            file << "Total Working Minutes : " << HourstoMinutes(closing) - HourstoMinutes(opening) << endl;
            file.close();

        } while (HourstoMinutes(closing) <= HourstoMinutes(opening));
    }

    void DisplayWorkingHours()
    {
        cout << "=========================================\n";
        cout << "Current Working Hours Configuration:\n";
        cout << "=========================================\n";

        ifstream file("workinghours.txt");

        string line;

        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
    }
};

// needs some work to solve the problem of adding transactions and a new line problem
struct Transactions
{

    // Utility to check if name is valid
    bool isValidName(const string &name)
    {
        return !name.empty() && name != "done";
    }

    // Utility to check if duration is valid
    bool isValidDuration(int duration)
    {
        return duration > 0;
    }

    // Utility to check for duplicates
    bool alreadyExists(const vector<string> &names, const string &name)
    {
        return find(names.begin(), names.end(), name) != names.end();
    }

    // Modern approach: Using the loop condition to control flow
    string getValidTransactionName(const vector<string> &existingNames)
    {
        string input;

        while (true)
        {
            cout << "Enter transaction name (or 'done' to finish): ";
            // Use getline to allow names with spaces
            if (!getline(cin, input) || input == "done")
            {
                return "done";
            }

            if (input.empty())
            {
                cout << "ERROR: Name cannot be empty.\n";
                continue;
            }

            if (alreadyExists(existingNames, input))
            {
                cout << "ERROR: '" << input << "' already exists. Enter a unique name: \n";
                continue;
            }

            return input;
        }
    }

    int getValidTransactionDuration()
    {
        int duration;
        // Idiomatic: check the state of the stream inside the condition
        cout << "Enter average duration in minutes: ";
        while (!(cin >> duration) || !isValidDuration(duration))
        {
            cin.clear();                                         // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
            cout << "ERROR: Please enter a valid positive integer for duration: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clean buffer for next getline
        return duration;
    }

    void defineTransactionTypes()
    {
        vector<string> names;
        vector<int> durations;
        string name;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Using the "Best Practice" loop: The loop condition itself handles the 'done' logic
        while ((name = getValidTransactionName(names)) != "done")
        {
            int duration = getValidTransactionDuration();
            names.push_back(name);
            durations.push_back(duration);
        }

        saveToFile(names, durations);
        cout << "-------------------------------\n";
        cout << "Transactions Added successfully!" << endl;
    }

    // Helper to avoid code repetition in define and add
    void saveToFile(const vector<string> &names, const vector<int> &durations)
    {
        ofstream file("transactions.txt");
        if (!file)
            return;

        // We write a simple header
        file << "NAME_LIST_START" << endl;
        for (size_t i = 0; i < names.size(); ++i)
        {
            // We use a colon as a separator to handle names with spaces safely
            file << names[i] << ":" << durations[i] << endl;
        }
        file.close();
    }

    // Rest of your functions (addTransaction, etc.) would follow the same pattern...

    void addTransaction()
    {
        vector<string> names;
        vector<int> durations;

        // --- STEP 1: LOAD EXISTING DATA ---
        ifstream file("transactions.txt");
        string line;
        if (file.is_open())
        {
            getline(file, line); // Skip the header line "NAME_LIST_START"

            while (getline(file, line))
            {
                if (line.empty())
                    continue;

                size_t delimiterPos = line.find(':');
                if (delimiterPos != string::npos)
                {
                    string name = line.substr(0, delimiterPos);
                    int duration = stoi(line.substr(delimiterPos + 1));
                    names.push_back(name);
                }
            }
            file.close();
        }

        // --- STEP 2: CLEAR INPUT BUFFER ---
        // If you came from a menu, we must clear the '\n'
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // --- STEP 3: INPUT LOOP ---
        string newName;
        cout << "\n--- Adding Multiple Transactions (type 'done' to stop) ---\n";

        while (true)
        {
            newName = getValidTransactionName(names);
            if (newName == "done")
                break;

            int newDuration = getValidTransactionDuration();

            names.push_back(newName);
            durations.push_back(newDuration);

            cout << ">> '" << newName << "' added to queue.\n";
        }

        // --- STEP 4: SAVE ALL ---
        saveToFile(names, durations);
        cout << "Success: File updated with " << names.size() << " total transactions.\n";
    }

    void DisplayTransactions()
    {
        cout << "=========================================\n";
        cout << "Current Transactions Configuration:\n";
        cout << "=========================================\n";

        ifstream file("transactions.txt");
        string line;

        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
    }
};

// finalized
struct YearlyCustomerTarget
{
    void setYearlyCustomerTarget()
    {
        int target;
        while (true)
        {
            cout << "Enter target number of customers per year: ";
            if (!(cin >> target) || target < 30000)
            {
                cout << "Error: Value must be an integer greater than 30,000" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                int avgPerDay = target / 360;
                cout << "------------------------------------------------------------------------\n";
                cout << "Target set successfully! (Average ~" << avgPerDay << " customers/day)" << endl;
                break;
            }
        }

        ofstream file("yearlytarget.txt");
        file << "Yearly Customer Target: " << target << endl;
        file << "Average Customers per Day: " << target / 360 << endl;
        file.close();
    }

    void DisplayYearlyCustomerTarget()
    {
        cout << "=========================================\n";
        cout << "Current Yearly Customer Target Configuration:\n";
        cout << "=========================================\n";

        ifstream file("yearlytarget.txt");
        string line;

        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
    }
};

// integeration of all the above -- need to add some code to view current configuration in a nice format
void viewCurrentConfiguration()
{
    NumberOfTellers tellers;
    WorkingHours hours;
    Transactions transactions;
    YearlyCustomerTarget yearlyTarget;
    cout << "=========================================\n";
    cout << "Current System Configuration:\n";
    cout << "=========================================\n";
    // Code to read and display current configuration from saved files
    tellers.DisplayTellers();
    hours.DisplayWorkingHours();
    transactions.DisplayTransactions();
    yearlyTarget.DisplayYearlyCustomerTarget();
}
