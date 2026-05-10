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