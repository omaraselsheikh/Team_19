#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <vector>

using namespace std;

struct WorkingHours1
{
    string opening;
    string closing;
    int totalMinutes;
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

    WorkingHours1 readWorkingHours()
    {
        WorkingHours1 wh;
        ifstream file("workinghours.txt");
        if (file.is_open())
        {
            string skip;
            getline(file, skip); // skip header
            getline(file, wh.opening);
            getline(file, skip); // skip
            getline(file, wh.closing);
            getline(file, skip); // skip
            file >> wh.totalMinutes;
            file.close();
        }
        return wh;
    }

    vector<string> readtransactionnames()
    {
        vector<string> names;

        ifstream file("transactions.txt");
        string header, tempName;
        int tempDuration;

        file >> header;

        while (file >> tempName >> header)
        {
            names.push_back(tempName);
        }
        return names;
    }

    vector<int> readtransactiondurations()
    {
        vector<int> durations;

        ifstream file("transactions.txt");
        string header, tempName;
        int tempDuration;

        file >> header;

        while (file >> header >> tempDuration)
        {
            durations.push_back(tempDuration);
        }
        return durations;
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

struct customerdata // needs Service Start/End Time, Served Status (Yes/No) - most probably after doing simulation
{
    int customerid()
    {

        return (rand() % 1000 + 1);
    }
    int HourstoMinutes(string time)
    {
        return ((time[0] - '0') * 10 + (time[1] - '0')) * 60 + (time[3] - '0') * 10 + (time[4] - '0');
    }
    string arrivaltime()
    {
        string opening, closing, arriving, leaving;
        int total;
        ifstream file("workinghours.txt");
        if (file.is_open())
        {
            string skip;

            getline(file, skip);
            getline(file, opening);

            getline(file, skip);
            getline(file, closing);

            getline(file, skip);
            file >> total;
            file.close();
        }
        int arrivalhour = HourstoMinutes(opening) + rand() % total;
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

    struct transaction
    {
        int duration;
        string Transaction;
    };
    vector<transaction> alltransactions;
    transaction customertransaction()
    {
        ifstream file("transactions.txt");
        string header;
        getline(file, header);
        transaction t;
        while (file >> t.Transaction >> t.duration)
        {
            alltransactions.push_back(t);
        }

        int index = rand() % alltransactions.size();
        transaction customertrans = alltransactions[index];
        return customertrans;
    }
    int id;
    string arrive;
    transaction transtype;
};

void generatingcustomers()
{
    readData avgcustomers;
    customerdata customer;
    vector<customerdata> c;
    int x = avgcustomers.read_avg_customers();
    cout << x;
    for (int i = 0; i < x; i++)
    {
        customer.id = customer.customerid();
        customer.arrive = customer.arrivaltime();
        customer.transtype = customer.customertransaction();
        c.push_back(customer);
    }
    ofstream file("customer.txt", ios::trunc);
    file << " ID " << setw(24) << "arrival time " << setw(48) << "Transaction time " << setw(60) << "Transactionduration" << endl;
    for (int i = 0; i < x; i++)
    {

        file << c[i].id << setw(24) << c[i].arrive << setw(48) << c[i].transtype.Transaction << setw(60) << c[i].transtype.duration << endl;
    }
    file << "customer generated = " << x << endl;
    file.close();
}

int readingnumberoftellers()
{
    int i;
    string useless;
    ifstream file("tellers.txt");
    getline(file, useless);
    struct days
    {
        int numtellers;
        string day;
    };
    vector<days> tellperday;
    days teller;
    for (i = 0; i < 7; i++)
    {
        file >> teller.day >> teller.numtellers;
        tellperday.push_back(teller);
    }
    file.close();
    cout << "choose day number to simulate\n";
    cout << "1.Sunday\t2.Monday\t3.Tuesday\t4.Wednesday\t5.Thursday\t6.Friday\t7.Saturday\n";
    cin >> i;
    while (i < 1 || i > 7)
    {
        cout << "out of range please re enter your choice\n";
        cin >> i;
    }
    return tellperday[i - 1].numtellers;
}

struct tellersdata // needs Status (Available/Busy/On Break)
{
    string tellerID()
    {
        string T_id = "T";
        int temp = rand() % readingnumberoftellers() + 1;
        if (temp < 10)
        {
            T_id += "0";
        }
        T_id += char(temp);
        return T_id;
    }

    struct alltrans
    {
        int duration;
        string transactions;
    };

    alltrans tellertransaction()
    {
        string transaction;

        string header;
        alltrans T;
        vector<alltrans> transactions;
        ifstream file("transactions.txt");
        getline(file, header);
        while (file >> T.transactions >> T.duration)
        {
            transactions.push_back(T);
        }
        int index = rand() % transactions.size();
        return transactions[index];
    }
    string Tellerid;
    string transactionassigned;
};

void generatingtellers()
{
    tellersdata teller_;
    int x = readingnumberoftellers();
    ofstream file("tellersdata.txt", ios::trunc);
    for (int j = 0; j < x; j++)
    {
        teller_.Tellerid = teller_.tellerID();
        teller_.transactionassigned = teller_.tellertransaction().transactions;
        file << teller_.Tellerid << setw(20) << teller_.transactionassigned << endl;
    }
    file.close();
}
