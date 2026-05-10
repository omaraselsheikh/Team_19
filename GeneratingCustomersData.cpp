#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <vector>
#include <cstdlib>

using namespace std;

int HourstoMinutes(string time)
{
    return ((time[0] - '0') * 10 + (time[1] - '0')) * 60 + (time[3] - '0') * 10 + (time[4] - '0');
}
struct workingHours
{
    string opening;
    string closing;
    int totalMinutes = HourstoMinutes(closing) - HourstoMinutes(opening);
};

struct transactions
{
    string name;
    int duration;
};

bool isValidDayName(string day)
{
    if (day == "Sunday" || day == "Monday" || day == "Tuesday" ||
        day == "Wednesday" || day == "Thursday" || day == "Friday" ||
        day == "Saturday")

        return true;
    else
        return false;
}

void displayRunSimulationMenu()
{
    cout << "========================================" << endl;
    cout << "Run Simulation selected." << endl;
    cout << "========================================" << endl;
    cout << "1. Run daily simulation" << endl;
    cout << "2. Run weekly simulation" << endl;
    cout << "3. Run full year simulation" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "========================================" << endl;
}

struct readData
{

    int read_avg_customers()
    {
        int avgperday;
        string word;
        ifstream file("yearlytarget.txt");
        if (file.is_open())
        {
            file >> word >> word >> word >> avgperday;
            file >> word >> word >> word >> word >> avgperday;
            file.close();
        }
        return avgperday;
    }

    workingHours readWorkingHours()
    {
        workingHours wh;
        ifstream file("workinghours.txt");
        if (file.is_open())
        {
            string header;
            getline(file, header); // skip header
            getline(file, wh.opening);
            getline(file, wh.closing);
            file.close();
        }
        return wh;
    }

    vector<transactions> alltransactions;
    transactions readtransaction()
    {
        transactions t;

        ifstream file("transactions.txt");
        string header;
        getline(file, header);
        while (getline(file, t.name))
        {
            file >> t.duration;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            alltransactions.push_back(t);
        }

        int index = rand() % alltransactions.size();
        transactions customertrans = alltransactions[index];
        return customertrans;
    }

    int readTellersNumber()
    {
        string day;
        int numTellers = 0;

        string chosenDay;
        cout << "Enter the day of the week (e.g., Sunday, Monday, etc.): ";
        cin >> chosenDay;

        if (isValidDayName(chosenDay))
        {

            ifstream file("tellers.txt");

            string header;
            getline(file, header); // skip header

            while (file >> day >> numTellers)
            {
                if (day == chosenDay)
                {
                    break;
                }
            }

            file.close();
        }

        else
        {
            cout << "Invalid Day Name, Try again" << endl;
            readTellersNumber();
        }

        return numTellers;
    }
};

// adds a number between (1-20) to avg customers per day it need to subtract too

int customersperday()
{
    readData avgcustomer;
    int avgperday = avgcustomer.read_avg_customers();
    return (avgperday + rand() % 20);
}

struct customerdata : public readData // needs Service Start/End Time, Served Status (Yes/No) - most probably after doing simulation
{
    int customerid()
    {
        return (1000 + rand() % 1000);
    }

    string arrivaltime()
    {
        string opening, closing;
        int workingmin;

        workingHours wh = readWorkingHours();

        opening = wh.opening;
        closing = wh.closing;
        workingmin = wh.totalMinutes;

        int arrivalhour = HourstoMinutes(opening) + rand() % workingmin;

        string time;
        int hours = arrivalhour / 60;
        int minutes = arrivalhour % 60;
        time += char(hours / 10 + 48);
        time += char(hours % 10 + 48);
        time += ":";
        time += char(minutes / 10 + 48);
        time += char(minutes % 10 + 48);
        return time;
    }

    int id;
    string arrive;
    transactions transtype;
};

void generatingcustomers()
{
    readData data;
    customerdata customer;
    vector<customerdata> c;
    int x = data.read_avg_customers();
    cout << x;
    for (int i = 0; i < x; i++)
    {
        customer.id = customer.customerid();
        customer.arrive = customer.arrivaltime();
        customer.transtype = customer.readtransaction();
        c.push_back(customer);
    }
    ofstream file("customer.txt", ios::trunc);
    file << " ID " << setw(24) << "arrival time " << setw(48) << "Transaction time " << setw(60) << "Transactionduration" << endl;
    for (int i = 0; i < x; i++)
    {

        file << c[i].id << setw(24) << c[i].arrive << setw(48) << c[i].transtype.name << setw(60) << c[i].transtype.duration << endl;
    }
    file << "customer generated = " << x << endl;
    file.close();
}
