#include <iostream>
#include <time.h>
#include <iomanip>
#include <vector>
using namespace std;

vector<string> Split(string Data, string Delimiter=" ") {
    //cout<<"\nSplitting string: >"<<Data<<"< by delimiter >"<<Delimiter<<"<\n";
    vector<string> result;
    string CurrSubs;
    auto start = 0U;
    auto end = Data.find(Delimiter);
    while (end != string::npos) {
        CurrSubs = Data.substr(start, end - start);
        //cout<<CurrSubs<<endl;
        result.push_back(CurrSubs);
        start = end + Delimiter.length();
        end = Data.find(Delimiter, start);
        }
    CurrSubs = Data.substr(start, end - start);
    //cout<<CurrSubs<<endl;
    //cout << Data.substr(start, end);
    result.push_back(CurrSubs);
    return result;
    }


class Date {
    protected:
        time_t TData;
        tm Local;
        //tm *pLocal;
    public:
        time_t GetTimeT() { return TData; }
        tm GetTM() { return Local; }
        Date() {
            //cout<<endl<<"Default Date C-tor"<<endl;
            TData = time(nullptr);
            Local = *localtime( &TData );
            }
        Date( tm *pNewTM ) {
            //cout<<endl<<"Constructing Date from *tm... "<<pNewTM->tm_year<<endl;
            TData = mktime( pNewTM );
            Local = *localtime( &TData );
            }
        Date( tm NewTM ) {
            //cout<<endl<<"Constructing Date from tm... "<<NewTM.tm_mday<<NewTM.tm_mon<<NewTM.tm_year<<endl;
            tm temp_tm = { 0 };
            temp_tm.tm_mday = NewTM.tm_mday;
            temp_tm.tm_mon = NewTM.tm_mon;
            temp_tm.tm_year = NewTM.tm_year;
            TData = 0;
            TData = mktime( &temp_tm ); //cout<<" TData: "<<TData;
            Local = { 0 };
            Local = *localtime( &TData );
            //pLocal = localtime ( &TData );
            }
            
        string ToString() {
            string result;
            stringstream textStream;
            textStream<<put_time(&Local, "%Y/%m/%d %H/%M/%S");
            result = textStream.str();
            return result;
            }
        /*    
        string ToStringp() {
            string result;
            stringstream textStream;
            textStream<<put_time(pLocal, "%Y/%m/%d %H/%M/%S");
            result = textStream.str();
            return result;
            }*/
        void FromString( string StrDate ) {
            istringstream ss(StrDate);
            ss >> get_time( &Local, "%Y/%m/%d");
            TData = mktime( &Local );
            }
        int CompareDays(Date OtherDate) {
            double difference = difftime(GetTimeT(), OtherDate.GetTimeT()) / (60. * 60. * 24.);
            return (int)difference;
            }

    };


class Person {
    protected:
        string Name;
        Date Birthday;
    public:
        Person(string name, string birthday) {
            Name = name;
            Birthday.FromString(birthday);
            }
        string ToString() {
            string result = Name + " born: ";
            return result + Split(Birthday.ToString())[0];
            }
        int CompareBirthday( Date CmpDate ) {
            //cout<<" CmpDate: "<<CmpDate.ToString()<<" Birthday: "<<Birthday.ToString()<<" ";
            tm D1 = { 0 }; D1 = Birthday.GetTM(); //proceed 29 feb here !!!
            D1.tm_year = CmpDate.GetTM().tm_year;//122;
            //if(D1.tm_mday == 29 && D1.tm_mon == 1) { D1.tm_mday = 1 ; D1.tm_mon = 2 ; }
            Date Dat1(D1);
            //cout<<" Dat1: "<<Dat1.ToString()<<" "<<" CmpDate: "<<CmpDate.ToString()<<" ";
            if ( Dat1.CompareDays( CmpDate ) >= 0 ) 
                return  Dat1.CompareDays( CmpDate );
            else {
                D1.tm_year++;
                Date Dat2(D1);
                return  Dat2.CompareDays( CmpDate );
                }
            }

    };
    

class People {
    protected:
        vector<Person> Persons;
    public:
        Person operator[](int i) { return Persons[i]; }
        People() { Persons.clear(); }
        void AddPerson(string name, string birthday) {
            Person NewP(name, birthday);
            Persons.push_back( NewP );
            }
        void AddPerson(Person NewP) { Persons.push_back( NewP ); }
        void Print() {
            cout<<endl<<"Our persons:"<<endl;
            Date D;
            for(int i = 0 ; i < Persons.size() ; i++) {
                cout<< Persons[i].ToString()<<" days left: "<< Persons[i].CompareBirthday( D ) << endl;
            }
            for(int i = 0 ; i < Persons.size() ; i++) {
                if( Persons[i].CompareBirthday( D ) == 0 ) cout << "Hurray!! " + Persons[i].ToString() << endl;
            }
        }
    };

int main() {
    People OurPeople;
    OurPeople.AddPerson("Kirill", "1981/04/12");
    OurPeople.AddPerson("Irina", "1979/04/12");
    OurPeople.AddPerson("Alexey", "1951/04/12");
    OurPeople.AddPerson("Lydmila", "1928/04/12");
    OurPeople.AddPerson("Katya", "1986/04/28");
    OurPeople.AddPerson("John", "2022/12/13");
    OurPeople.AddPerson("Pasha", "1983/05/11");
    OurPeople.AddPerson("Anton", "1983/05/11");
    OurPeople.AddPerson("Elena", "2020/02/29");
    OurPeople.AddPerson("Elei", "2022/12/13");
    
    OurPeople.Print();
    
    cout<<endl; 
    return 0;	
}
