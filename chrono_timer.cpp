#include <chrono>
#include <iostream>
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

class Secundometer {
    protected:
        chrono::system_clock::time_point Start_Time;
        chrono::system_clock::time_point Last_Time;
        double Elapsed_Seconds;
        bool Running;
    public:
        Secundometer() {
            //cout<<"\nSecundometer created:\n";
            Elapsed_Seconds = 0.0;
            Running = false;
            }
        bool Start() {
            if( Running ) return false;
            Start_Time = chrono::system_clock::now();
            Running = true;
            return true;
            }
        bool Stop() {
            if( !Running ) return false;
            Last_Time = chrono::system_clock::now();
            Running = false;
            Elapsed_Seconds += chrono::duration_cast<std::chrono::milliseconds>(Last_Time - Start_Time).count() / 1000.0;
            return true;
            }
        double GetElapsedSeconds() {
            if( !Running ) return Elapsed_Seconds;
            chrono::system_clock::time_point Current_Time = chrono::system_clock::now();
            double Add_Seconds = chrono::duration_cast<std::chrono::milliseconds>( Current_Time - Start_Time ).count() / 1000.0;
            return Elapsed_Seconds + Add_Seconds;
            }
    };

class Task : public Secundometer {
    protected:
        string Name;
    public:
        Task() {}
        Task(string name) {
            Name = name;
            }
        string ToStr() {
            return Name+" "+to_string(GetElapsedSeconds());
            }
    };

class TaskManager {
    protected:
        vector<Task> Tasks;
        int ActivePID = -1;
    public:
        int GetActivePID() { return ActivePID; }
        bool SetActivePID(int NewActivePID) {
            if(NewActivePID < 0 || NewActivePID > (Tasks.size() - 1)) return false;
            StopAll();
            Tasks[ NewActivePID ].Start();
            ActivePID = NewActivePID;
            return true;
            }
        TaskManager() {
            cout<<"\nRunning task manager...\n";
            Tasks.clear();
            }
        void TaskList() {
            cout<<"\nOur tasks:\n";
            for(int i = 0; i < Tasks.size(); i++)
                cout<<to_string(i)<<"\t"<<Tasks[i].ToStr()<<"\n";
            cout<<"Active: "<<ActivePID<<"\n";
            }
        void NewTask(string name) {
            Task newTask(name);
            newTask.Start();
            cout<<newTask.ToStr();
            //cout<<" Pushing";
            Tasks.push_back(newTask);
            //cout<<" Pushed";
            SetActivePID( Tasks.size() - 1 );
            }
        void StopAll() {
            for( int i = 0 ; i < Tasks.size() ; i++)
                Tasks[i].Stop();
            ActivePID = -1;
            }
        bool StopActive() {
            if( ActivePID < 0 ) return false;
            Tasks[ ActivePID ].Stop();
            ActivePID = -1;
            }
        bool Interpret(string Command) {
            //cout<<"\nGot Command: "<<Command;
            vector<string> Operands = Split(Command);
            //cout<<"\nCommand: "<<Operands[0]; //<<"_"<<Operands[1];
            
            string CommandList[5] = {"exit", "status", "end", "begin", "set"};
            int CommNum;
            for( CommNum = 0 ; CommNum < 5 ; CommNum++ ) if( CommandList[CommNum] == Operands[0] ) break;
            //cout<<"\nCommand Number: "<<CommNum;
            switch( CommNum ) {
                case 0:
                    return false;
                    break;
                case 1:
                    TaskList();
                    return true;
                    break;
                case 2:
                    StopAll();
                    return true;
                    break;
                case 3:
                    //cout<<"\nLet the task begins... "<<Operands[1];
                    NewTask( Operands[1] );
                    return true;
                    break;
                case 4:
                    SetActivePID( stoi(Operands[1]) );
                    return true;
                    break;
                } 
            return true;
        }
    };

int main() { // -Wno-psabi to suppress stupid warnings
    int k;
    TaskManager TM;
    string Input;
    do {
        cout<<"\nCommand: ";
        getline(std::cin, Input);
        //cin>>Input; // !!! NEVER FUCK DO THIS
        } while ( TM.Interpret(Input) ); 
   
/*
   TM.NewTask("Varit sup");
    cin>>k;
    //TM.StopAll();
    TM.NewTask("Jarit kartoshku");
    cin>>k;
    //TM.StopAll();
    TM.TaskList();
    TM.SetActivePID(0);
    cin>>k;
    TM.TaskList();
*/

    //vector<Secundometer> TTT;
    //Secundometer T;
    //TTT.push_back(T);
    return 0;
    }
