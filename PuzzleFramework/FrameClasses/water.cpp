/*

water.cpp
Modified on : 11/24/2014 
Modified By  : Karan Bhagat AND Vaibhav Page  
Version : 2.0
Revisions : 1
*/

#include <iostream>
#include <cstdlib>
#include "puzzle.h"

using namespace std;

class JugPuzzle : public Puzzle< vector<int> >{
	private:
		vector<int> jugs_capacity;//water capacity that jugs can hold
		int no_of_jugs;//total no. of jugs available
		int goal_qty;// quantity of water needed
		
	
	public:
		//constructor of JugState
		JugPuzzle(vector<int> start,vector<int> j, int n, int g):Puzzle< vector<int> >(start){
			no_of_jugs = n;
			goal_qty = g;
			jugs_capacity = j;

		}

		//Generating all next configs from current configs
		vector< vector<int> > getAllNextConfigs( vector<int> v){
			vector< vector<int> > v_config;//vector to return next configs generated from current config
			int temp_vi;//temporary variable to hold the jug water.
			int temp_vj;
			int cap_left;// capacity left in the jug


			//this loop go through all the jugs one by one	
			for(int i = 0; i < no_of_jugs; i++ ){
				//if current jug is empty, then fill it.
				if(v[i] == 0){
					v[i] = jugs_capacity[i];
					v_config.push_back( v );
					v[i] = 0;
				}
				//if its not empty,then find
				//amount of water in other jugs
				// and pour water in those jugs from
				//current jugs
				else{
					//if( v[i] == jugs_capacity[i] )
					for(int j = 0; j < no_of_jugs; j++){
						if( j != i){
							temp_vi = v[i];
							cap_left = (jugs_capacity[j]-v[j]);
							if( cap_left != 0){
								if( cap_left >= v[i] ){
									temp_vj = v[j];
									v[j] = v[j] + v[i];
									v[i] = 0;
									v_config.push_back( v );
									v[i] = temp_vi;
									v[j] = temp_vj;
								}
								else{
									temp_vj = v[j];
									v[i] = v[i] - cap_left;
									v[j] = v[j] + cap_left;
									
									v_config.push_back( v );
									v[i] = temp_vi;
									v[j] = temp_vj;
								}
							}
						}
					}

					temp_vi = v[i];
					v[i] = 0;
					v_config.push_back( v );
					
					v[i] = temp_vi;

					if( v[i] < jugs_capacity[i] ){
						temp_vi = v[i];
						v[i] = jugs_capacity[i];
						v_config.push_back( v );
						v[i] = temp_vi;
					}
				}
			}
			return v_config;
		}

		void display(vector<int> c){
			for(int i = 0; i < no_of_jugs; i++){
				cout<<c[i]<<" ";
			}
			cout<<endl;			
		}

		bool isGoal(vector<int> c){
			for( int i = 0; i < no_of_jugs; i++){
				if( c[i] == goal_qty ){
					return true;
				}
			}
			return false;
		}
};


int main( int argc, char *argv[] ){
	vector<int> jugs_capacity;
	vector<int> jugs_start;
	vector< vector<int> > goalpath;
	//intializing variable from commandline args.
	for( int i = 2 ; i < argc; i++ ){
		jugs_capacity.push_back( atoi(argv[i]) );
		jugs_start.push_back(0);
	}
	//creating object of JugState.
	JugPuzzle jug(jugs_start,jugs_capacity, argc-2, atoi(argv[1]));

	goalpath = jug.solvePuzzle();

	//printing all the state from start to goal
	if( !goalpath.empty() ){
		vector< vector<int> >::reverse_iterator it;
		for( it = goalpath.rbegin(); it != goalpath.rend(); it++){
			jug.display(*it);
		}
		
	}
	else{
		cout<<"No Solution"<<endl;
	}
}
