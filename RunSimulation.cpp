#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include<vector>
using namespace std;
struct submenu
{
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
};




int mincustomersperday (int averagecustomersperday)
{

    return ( averagecustomersperday+rand()%20);
}
int CustomerTarget()
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
int numberofcustomers;
numberofcustomers=mincustomersperday(avgperday);
return numberofcustomers;
}



struct customerdata //needs Service Start/End Time, Served Status (Yes/No) - most probably after doing simulation
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
    string opening,closing,arriving,leaving;
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
  int arrivalhour= HourstoMinutes(opening)+rand()%total;
  string time ;
  int hours= arrivalhour/60;
  int minutes=arrivalhour%60;
time+=char(hours/10+48);
time+=char(hours%10+48);
time+=":";
time+=char(minutes/10+48);
time+=char(minutes%10+48);
  return time;
  }

struct transaction
{
    int duration;
    string Transaction;
};
vector<transaction>alltransactions;
transaction customertransaction()
{  
    ifstream file ("transactions.txt");
    string header;
    getline(file,header);
    transaction t;
    while (file>>t.Transaction>>t.duration)
    {
        alltransactions.push_back(t);
    }
  
    int index= rand()%alltransactions.size();
    transaction customertrans= alltransactions[index];
    return customertrans;
}
int id;
string arrive;
transaction transtype;

};


void generatingcustomers()
{
  customerdata customer;
  vector<customerdata>c;
  int x= CustomerTarget();
  cout<<x;
  for (int i=0;i<x;i++)
  {
   customer.id= customer.customerid();
   customer.arrive=customer.arrivaltime();
   customer.transtype=customer.customertransaction();
   c.push_back(customer);
  }
   ofstream file ("customer.txt", ios::trunc);
   file<< " ID "<<setw(24)<< "arrival time "<<setw (48) << "Transaction time "<<setw(60)<< "Transactionduration"<<endl;
  for (int  i=0;i<x;i++)
  {
 
  file<<c[i].id<< setw(24)<< c[i].arrive << setw(48) << c[i].transtype.Transaction<< setw(60)<<c[i].transtype.duration<<endl;
 
  }
  file<< "customer generated = "<<x<<endl;
   file.close();
  
}


 int readingnumberoftellers ()
{
   int i;
  string useless;
    ifstream file ("tellers.txt");
    getline (file,useless);
    struct days
    {
    int numtellers;
    string day;
    };
    vector<days>tellperday;
    days teller;
    for( i=0;i<7;i++)
    {
        file>> teller.day>>teller.numtellers;
        tellperday.push_back(teller);
    }
    file.close();
    cout<< "choose day number to simulate\n";
    cout<<"1.Sunday\t2.Monday\t3.Tuesday\t4.Wednesday\t5.Thursday\t6.Friday\t7.Saturday\n";
    cin>>i;
    while (i<1||i>7)
    {
        cout<<"out of range please re enter your choice\n";
    cin>>i;
    }
    return tellperday[i-1].numtellers;
}

struct tellersdata //needs Status (Available/Busy/On Break) 
{
 string tellerID()
 { 
string T_id="T";
int temp=rand()%readingnumberoftellers ()+1;
if (temp<10)
{T_id+="0";}
T_id+=char(temp);
return T_id;
 }


struct alltrans
    {
        int duration;
        string transactions;
    };

 alltrans tellertransaction()
 { string transaction;
    
    string header;
    alltrans T;
    vector<alltrans>transactions;
    ifstream file("transactions.txt");
    getline(file,header);
    while(file>>T.transactions>>T.duration)
    {
        transactions.push_back(T);
    }
int index=rand()%transactions.size();
return  transactions[index];
 }
 string Tellerid;
 string transactionassigned;
};


void generatingtellers()
{ tellersdata teller_;
    int x=readingnumberoftellers ();
    ofstream file("tellersdata.txt", ios::trunc);
    for (int j=0;j<x;j++)
    {
   teller_.Tellerid=teller_.tellerID();
   teller_.transactionassigned=teller_.tellertransaction().transactions;
   file<<teller_.Tellerid<< setw(20)<< teller_.transactionassigned<<endl;
    }
    file.close();
}


