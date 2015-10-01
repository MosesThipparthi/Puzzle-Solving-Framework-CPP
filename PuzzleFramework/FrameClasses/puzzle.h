/*

puzzle.h
Modified on : 11/24/2014 
Modified By  : Karan Bhagat AND Vaibhav Page  
Version : 3.0
Revisions : 2
*/

#ifndef PUZZLE_FRAME
#define PUZZLE_FRAME


#include <queue>
#include <vector>
#include <map>
using namespace std;

//This is an abstract class declares solving machines of the puzzles
template <class C>// C stands for type of configuration
class Puzzle{
	private:
		C start;// start configuration of any puzzle
		
	public:

		//This method is solving machine for all puzzles
		//this implements breadth first search to get the 
		//puzzle solution.
		vector< C > solvePuzzle(){
			vector< C > child_configs;
			typedef map< C , C > MyMap;
			MyMap all_configs;// map< C,C > store all the unique configurations.
			queue< C > bfs;// queue to implement bfs
			vector< C > v_goal;//stores the goal path.

			C new_config;
			C e; // an empty element of type C to push on map
			bfs.push(start);//add configuration to the queue
			
			all_configs.insert(pair<C,C>(start, e));
			
			//loop till the queue got empty or till the goal is found
			while( !bfs.empty() ){
				new_config = bfs.front();
				bfs.pop();// take out the current config from the queue.
				
				if( isGoal( new_config ) ){
					//take goal path from the map and store it in the vector and return.
					typename MyMap::iterator it_map = all_configs.find(new_config);
					do{
						v_goal.push_back( it_map->first );
						it_map = all_configs.find( it_map->second );
					}while( it_map != all_configs.end() );
					return v_goal;
				}
				
				//get all new configurations from current configuration.
				child_configs = getAllNextConfigs( new_config );

				//store all new configuration to map and queue which are not already there.
				for( typename vector<C>::iterator it = child_configs.begin(); it != child_configs.end(); ++it){
					pair< typename MyMap::iterator,bool> ret;
					ret = all_configs.insert(pair<C,C>(*it, new_config ));
					if( ret.second ){
						bfs.push(*it);		
					}
				}

			}

			return v_goal;
		}

		//constructor for this framework 
		//taking start state as argument
		Puzzle(C s){
			start = s;
		}

		//virtual functions which will be implemented by
		//specific puzzles.
		virtual vector<C> getAllNextConfigs(C) = 0;
		virtual void display(C) = 0;
		virtual bool isGoal(C) = 0;

};

#endif
