# Puzzle-Solving-Framework-in-C-
Developed a framework for solving any kind of puzzle if rules of the puzzle are provided.

/*****
Author part 1,2 and 3 : Karan Bhagat & Vaibhav Page
Author part 4 : Vaibhav Page
Modified on : 11/07/2014
Revision : 4
*****/

Project Part 1,2,3 and 4 : Framework Design Document


__________________________________________________
''''''''''''''''''''''''''''''''''''''''''''''''''
1) Description of Classes and Methods of Framework
__________________________________________________
""""""""""""""""""""""""""""""""""""""""""""""""""
//This is an abstract class. This class provide
//the methods to define the current state and 
// to find the all next states which can be achieved from start 
// configuration.
// type C will actually define the type of configuration for each puzzle.

template <class C>
class Puzzle{
	private:
		
		C start;// start configuration of any puzzle

	public:
		/This method finds all the configuraion which can be achieved from given configuration
		// This returns a list of all configuration as an vector object.		
		virtual vector<C>& getAllNextConfigs(C) = 0;
		
		//This method displays the given configuration.
		virtual void display(C) = 0;
		
		//This method checks if given configuration is the Goal configuration.		
		virtual bool isGoal(C) = 0;

		//This method actually solve the puzzle by implement breadth first search using queue.
		vector< C >& solvePuzzle(){}

};


1.1 How SolvePuzzle works
""""""""""""""""""""""""""

Steps:
1. solvePuzzle() method of Puzzle class uses start config of type C of puzzle class and push it on queue.
2. Same start config is also pushed on map<C,C> so as to maintain list of unique configs.
3. Enters a while loop and runs untill the queue is empty.
4. In while loop.
5. Take out first configuration out of the queue and check if it is a goal config by calling Puzzle's isGoal(C) method.
   isGoal(C) method is actually a pure virtual method of puzzle and is defined by specific puzzles.
6. If it is goal then send vector of all configs through which goal is achieved (i.e. send all parents + this config to the invoking method ). This is done using map, as all configurations and their parents are being stored in the map.
7. If it is not a goal then find all next configurations by invoking Puzzles's getAllNextConfigs(C) method. This will return a vector of configurations.
8. Insert to queue and map all new configurations which are not already present.
9. If while loop hold then go to step 5 again.
10. return an empty vector<C> which will indicate that no solution exist.

following is code for above written algorithm.
		
		vector< C >& solvePuzzle(){
			
			C new_config;
			vector< C > child_configs;//to store child config of given config
			typedef map< C , C > MyMap;
			MyMap all_configs;// map< C,C > store all the unique configurations.
			vector< C > v_goal;//stores the goal path.
			queue< C > bfs;// queue to implement bfs
			C e; // an empty element of type C to push on map
			bfs.push(start);//add configuration to the queue and map
			
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

2) How the puzzles are being solved
___________________________________
"""""""""""""""""""""""""""""""""""
2.1 Clock Puzzle
""""""""""""""""
ClockPuzzle class inherits Puzzle< int > class to provide rule for the clock puzzle.
ClockPuzzle adds rules to the Puzzle framework and also declare type of configuration by giving a template parameter to the Puzzle class.

ClockPuzzle(int wrong_time,int correct_time,int modulo):Puzzle<int>(wrong_time){;}// This is constructor takes in wrong time,correct_time and modulo for the puzzle.

>>>All following methods are superclass methods<<<

vector< int > & getAllNextConfigs(int)  // This methods generate all the next achievable configurations.

void display(int)  // Display the current configuration

bool isGoal(int)//Check if given configuration is goal configuration. just check if wrongtime is equal to correct time.



Puzzle is being solved by a simple algorithm defined by ClockPuzzle class in  getAllNextConfigs() methods.

vector< Configuration* > & getAllNextConfigs(){
			int next_time;
			next_time = (w_time+1)%m == 0? m: w_time+1%m;  // w_time = wrong time , m = no. of hours on clock,
			v.push_back( new ClockPuzzle( next_time,this ));  // v = vector<configuratio*>, c_time = correct time.
			cout<< c_time <<" "<<next_time<<endl;
			next_time = (w_time-1)%m == 0? m: w_time-1%m;
			v.push_back( new ClockPuzzle( next_time,this ));
			cout<< c_time <<" "<<next_time<<endl;
			return v;
		}
This puzzle finds the time by taking next configurations by incrementing and decrementing current configuration by 1.
Let us say wrong time is 5 , correct time 9 and no. of hours on dial is 12. 
so all configurations would be like.

no. of hours say 12					
correct time   wrong time 
9		5
next two configuration generated from this configuration are
9 		6 ( adding one hour )
9		4 ( substracting one hour )

next two configuration generated from 9  6
9 		7 ( adding one hour )
9		5 ( substracting one hour ) this is repeated

next two configuration generated from 9  4
9 		5 ( adding one hour )	this is reapeated
9		3 ( substracting one hour ) 

next two configuration generated from 9  7
9 		8 ( adding one hour )
9		6 ( substracting one hour ) this is repeated

next two configuration generated from 9  3
9 		4 ( adding one hour )	this is reapeated
9		2 ( substracting one hour )

next two configuration generated from 9  8
9 		9 ( adding one hour )
9		7 ( substracting one hour ) this is repeated

(IN THIS CONFIGURATION SOLUTION IS ACHIEVED IN 4 STEPS OR AT THE DEPTH OF 4 IN THE TREE )

2.1.1 How clock puzzle is geting solved using framework
"""""""""""""""""""""""""""""""""""""""""""""""""""""""

An object of the ClockPuzzle class is being created in the main method.
Constructor of the ClockPuzzle class is intialized with wrongtime,correcttime,modulo.
Then solvePuzzle() of Puzzle class is being called through object of ClockPuzzle class
as Puzzle class is inherited by ClockPuzzle class.
solvePuzzle() method will return vector of all the configs through which solution is achieved.

	int modulo = atoi( argv[1] );
	int wrong_time = atoi( argv[2] );
	int correct_time = atoi( argv[3] );
	vector<int> goalpath;

	ClockPuzzle cp(wrong_time,correct_time,modulo);
	
	goalpath = cp.solvePuzzle();


2.2 Water Jug Puzzle
""""""""""""""""""""
Water Jug Puzzle's rules are being defined by class name JugPuzzle. This class also publicly inherits
Puzzle class with configuration type set as vector<int>. 

Methods defined in this class are following.

JugPuzzle(vector<int> start,vector<int> j, int n, int g):Puzzle< vector<int> >(start){;}  //Constructor takes start config, capacity of jugs, no. of jugs and goal config.


>>>All following methods are superclass methods

void display(C)  //display current configuration.

vector< vector<int> > & getAllNextConfigs(C)//return a vector of all new configurations which can achieved from this.

bool isGoal(C)  //Check if current configuration is a goal.


The main rules for finding next configuration lies in vector< vector<int> > & getAllNextConfigs(C) method.

In this method next configurations are being found using following steps.

1. For loop through all the jugs.
2. In For loop of jug i.
3. if current jug is empty, fill it fully and add this configuration to the vector<vector<int>> v_config.
4. if current jug is not empty. then
5. For loop through all the jugs except this jug.
6. In inner For loop of jugs j.
7. find the remaining capacity of jug j. "cap_left = (jugs_capacity[j]-v[j]);" 
	jugs_capacity contains the total capacity of all jugs
	v contains the amount of water in each jug.
8. if remaining capacity is not 0. Then 
9. 	if remaining capacity of jug j is more than or equal to water in jug i. Then
10.  	make jug i = 0 and add water amount in jug i to jug j. Push this configuration on v_config.
11.     else remaining capacity of jug j is less than jug i. Then
12.     Add required amount of water in jug j and leave rest of the water in jug i. Push this configuratioin on v_config.
13. now make the current jug i empty and push this configuration on v_config.
14. now make the current jug i full and push this configuration on v_config.
15. return v_config.	


		vector< vector<int> >& getAllNextConfigs( vector<int> v){
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

How configurations are generated in WaterJug Puzzle.

let the input in 4 2 6
the start configuration is 0,0 for 2 jugs capacity 2 and 6. 
{0,0} : {2,0},{0,6}
{2,0} : {0,2},{0,0},{2,0},{2,6}
{0,6} : {2,6},{2,4},{0,0},{0,6}
{0,2} : {2,2},{2,0},{0,0},{0,6}
{2,6} : {0,6},{2,0}
{2,4} : Goal state

returned path
{0,0}
{0,6}
{2,4}

2.2.1 How water jug puzzle is geting solved using framework
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

An object of the  class JugPuzzle is being created in the main method.
Constructor of the JugPuzzle class is intialized with start amount,total capacity,no. of the jugs and
goal amount.
Then solvePuzzle() of Puzzle class is being called through object of JugPuzzle class
as Puzzle class is inherited by JugPuzzle class.
solvePuzzle() method will return vector of all the configs through which solution is achieved.

	JugPuzzle jug(jugs_start,jugs_capacity, argc-2, atoi(argv[1]));

	goalpath = jug.solvePuzzle();


2.3 Lloyd Sliding Block Puzzle
""""""""""""""""""""""""""""""
Sliding Block Puzzle's rules are being defined by class name LloydPuzzle. This class also publicly inherits
Puzzle class with configuration type set as vector<char>. 

Methods defined in this class are following.

LloydPuzzle( vector<char> s, vector<char> g, int w, int h ):Puzzle< vector<char> >(s){;}//Constructor of LloydPuzzle takes
start config, goal config, width of the puzzle and height of the puzzle.

void writeFile(vector<char> c, ofstream &of){} //This method write each config to output file.

>>>All following methods are superclass methods

void display(C)  //display current configuration.

vector< vector<char> > & getAllNextConfigs(C)//return a vector of all new configurations which can achieved from this.

bool isGoal(C)  //Check if current configuration is a goal.



The main rules for finding next configuration lies in vector< vector<char> > & getAllNextConfigs(C) method.

In this method next configurations are being found using following steps.

1.For loop through all the elements of vector<char>
2.If character is "." then
3. //generating one config for each of the following steps.
   it can be moved to left
   it can be moved to right
   it can be moved to down
   it can be moved to up
4.go back to 1 until loop condition holds

		vector< vector<char> >& getAllNextConfigs( vector<char> v){
			vector<char> tmp_v;
			char tmp_c;
			for( int i = 0; i < width*height; i++ ){
				if( v[i] == '.'){
					
					//case 1 checking left
						if( i%width != 0){
							tmp_v = v;
							tmp_c = tmp_v[i-1];
							tmp_v[i-1] = tmp_v[i];
							tmp_v[i] = tmp_c;
							v_config.push_back(tmp_v);
							
						}

					//case 2 checking above
						if( i >= width){
							tmp_v = v;
							tmp_c = tmp_v[i-width];
							tmp_v[i-width] = tmp_v[i];
							tmp_v[i] = tmp_c;
							v_config.push_back(tmp_v);
							
						}
					//case 3 checking right
						if( i%width != width-1 ){
							tmp_v = v;
							tmp_c = tmp_v[i+1];
							tmp_v[i+1] = tmp_v[i];
							tmp_v[i] = tmp_c;
							v_config.push_back(tmp_v);
							
						}
					//case 4 checking down
						if( i < width*(height-1)){
							tmp_v = v;
							tmp_c = tmp_v[i+width];
							tmp_v[i+width] = tmp_v[i];
							tmp_v[i] = tmp_c;
							v_config.push_back(tmp_v);
							
						}
						

				}
			}

			return v_config;
		}

How configurations are generated in LloydPuzzle.
Let take input as:
width = 2
height = 1

start config
. a b

goal config
a b .

>>next config : "." can move RIGHT
a . b

current config 
a . b

>>next config : "." can move LEFT and RIGHT
. a b

a b .

current config
a b .

which is the goal configuration.

2.2.1 How sliding block puzzle is geting solved using framework
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Input of this puzzle can be taken by command line or by file input and also output can be given by command line 
or file output.
LloydPuzzle inherit the solvePuzzle method from the Puzzle Framework. So it can call it directly to solve the puzzle.
solvePuzzle gives the solution in the form of vector of all the configuration through which goal state is achieved.

LloydPuzzle lloyd(start,goal,width,height);
	goalpath = lloyd.solvePuzzle();


2.4 Variant Clock Puzzle
""""""""""""""""
VClockPuzzle class inherits Puzzle< int > class to provide rule for the clock puzzle.
VClockPuzzle adds rules to the Puzzle framework and also declare type of configuration by giving a template parameter to the Puzzle class.

ClockPuzzle(int wrong_time,int correct_time,int modulo,vector<int> v):Puzzle<int>(wrong_time){;}// This is constructor takes in wrong time,correct_time and modulo for the puzzle.

>>>All following methods are superclass methods<<<

vector< int > & getAllNextConfigs(int)  // This methods generate all the next achievable configurations.

void display(int)  // Display the current configuration

bool isGoal(int)//Check if given configuration is goal configuration. just check if wrongtime is equal to correct time.



Puzzle is being solved by a simple algorithm defined by ClockPuzzle class in  getAllNextConfigs() methods.

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
This puzzle finds the time by taking next configurations by incrementing and decrementing current configuration by set of given increment or decrement values
Let us say wrong time is 5 , correct time 9 and no. of hours on dial is 12 and we have three values 2 , 3 and -5 for incrementing and decrementing.
so all configurations would be like.

no. of hours say 12					
correct time   wrong time 
9		5
next configuration generated from this configuration are
9 		7( add 2 )
9		8( add 3 )
9		12( subtract -5 )

next two configuration generated from 9  7
9 		9 ( add 2 )
9		10 ( add 3 )
9               2 ( subtract -5 )

next two configuration generated from 9  8
9 		10 ( add 2 )
9		11 ( add 3 )
9 		3 ( subtract -5 ) 

next two configuration generated from 9  1
9 		2 ( add 2 )
9		3 ( add 3 )
9		7 ( subtract -5 )

next configuration in the queue is 9 9 which is the goal configuration.

-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-

