#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std;
using namespace std::chrono;

class ClockSleeper {
	protected:
		int WaitTime;
		string Message;	
	public:
		ClockSleeper(int waittime = 2000, string message = "Ding! Ding! ding!") {
			Message = message;
			if (waittime < 0) WaitTime = -waittime;
			else WaitTime = waittime;
			int ElapsedTime;
  			clock_t t1 = clock();
  			do{
  				clock_t t2 = clock();
				ElapsedTime = t2 - t1;
				cout << WaitTime - ElapsedTime << endl;
			} while(ElapsedTime < WaitTime);
  
		}
		~ClockSleeper() {
			cout << Message;
			std::cout << std::endl;
		}
};


class CountDownTimer {
	protected:
		double WaitTime;
		string Message;	
	public:
		CountDownTimer(double waittime = .1, string message = "Ding! Ding! ding!") {
			Message = message;
			if (waittime < 0) WaitTime = -waittime;
			else WaitTime = waittime;
			double ElapsedTime;
  			high_resolution_clock::time_point t1 = high_resolution_clock::now();
  			do{
  				high_resolution_clock::time_point t2 = high_resolution_clock::now();
  				duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
				ElapsedTime = time_span.count();
				cout << ElapsedTime << endl;
			} while(ElapsedTime < WaitTime);
  
		}
		~CountDownTimer() {
			cout << Message;
			std::cout << std::endl;
		}
		
};


int main () {
//	ClockSleeper CS;
//	cout << "clock per sec = " << CLOCKS_PER_SEC << endl;
	
	CountDownTimer CDT;
	CountDownTimer *CDTKUKU = new CountDownTimer(.003, "kuku");
	delete CDTKUKU;
  return 0;
}