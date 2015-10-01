/*

clock.cpp
Modified on : 11/24/2014 
Modified By  : Karan Bhagat AND Vaibhav Page  
Version : 3.0
Revisions : 2
*/
#include <iostream>
#include <cstdlib>
#include "puzzle.h"

class ClockPuzzle : public Puzzle<int>{
	private:
		int c_time; //correct time
		int m; // no. of hours
		

	public:
		//constructor for ClockPuzzle
		ClockPuzzle(int wrong_time,int correct_time,int modulo):Puzzle<int>(wrong_time){
			c_time = correct_time;
			m = modulo;
		}

		//generate new configurations by decreasing and increasing the one hour from current
		//wrong time.
		vector< int > getAllNextConfigs(int w_time){
			vector<int> v; // stores all next configurations from current config.
			int next_time;
			next_time = (w_time+1)%m == 0? m: w_time+1%m;
			v.push_back( next_time );
			next_time = (w_time-1)%m == 0? m: w_time-1%m;
			v.push_back( next_time );
			return v;
		}

		void display(int w_time){
			cout<<"Correct Time : "<<c_time<<"   Wrong Time : "<<w_time<<endl;
		}

		//check if this is goal config. by comparing wrong time and correct time.
		bool isGoal(int w_time){
			return w_time == c_time;
		}
};


int main( int argc, char *argv[] ){
	//take command line arguments
	int modulo = atoi( argv[1] );
	int wrong_time = atoi( argv[2] );
	int correct_time = atoi( argv[3] );
	vector<int> goalpath;

	//object of clock puzzle.
	ClockPuzzle cp(wrong_time,correct_time,modulo);
	
	goalpath = cp.solvePuzzle();

	//prints the goal path if exist
	if( !goalpath.empty() ){
		vector<int>::reverse_iterator it;
		for( it = goalpath.rbegin(); it != goalpath.rend(); it++){
			cp.display(*it);
		}
	}
	else{
		cout<<"No Solution"<<endl;
	}
}