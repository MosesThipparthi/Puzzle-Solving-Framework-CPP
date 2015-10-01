/*

vclock.cpp
@author  : Vaibhav Page
@created on: 12/07/2014 
@Version : 1.0
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "puzzle.h"

using namespace std;

class VariantClock : public Puzzle<int>{
	private:
		int correctT;//correct time of the clock
		int totalT;// total number of hours on the clock
		vector<int> increments;//values to be incremented or decremented from currect wrong time

	public:
		VariantClock(vector<int> v, int w, int c, int t)
		:Puzzle<int>(w){//constructor of this class and sending wrong time to super class
			correctT = c;
			totalT = t;
			increments = v;
		}

		vector< int > getAllNextConfigs(int w){
			vector<int> new_configs;
			int newT;
			
			//finding next configs from current config
			vector<int>::iterator it;
			for( it = increments.begin(); it < increments.end(); it++ ){
				//checking if it is decrementing wrong time to negetive
				if( w + *it < 0){
					newT = totalT - ( abs(w + *it)%totalT );
					new_configs.push_back(newT);
				}
				else{
					newT = ( w + *it )%totalT;
					if( newT == 0){
						new_configs.push_back(totalT);
					}
					else{
						new_configs.push_back(newT);
					}
				}
			}

			return new_configs;
		}

		void display(int w){
			cout<<"Correct Time : "<<correctT<<"   Wrong Time : "<<w<<endl;
		}

		bool isGoal(int w){
			return w == correctT;
		}
};


int main( int argc, char *argv[] ){
	
	vector<int> increments;
	vector<int> goalpath;
	int totalT = atoi( argv[1] );
	int wrongT = atoi( argv[2] );
	int correctT = atoi( argv[3] );

	for( int i = 4; i < argc; i++){
		increments.push_back( atoi(argv[i]) );
	}
	
	VariantClock vc( increments, wrongT , correctT , totalT);
	
	goalpath = vc.solvePuzzle();

	if( !goalpath.empty() ){
		vector<int>::reverse_iterator it;
		for( it = goalpath.rbegin(); it != goalpath.rend(); it++){
			vc.display(*it);
		}
	}
	else{
		cout<<"No Solution"<<endl;
	}
}