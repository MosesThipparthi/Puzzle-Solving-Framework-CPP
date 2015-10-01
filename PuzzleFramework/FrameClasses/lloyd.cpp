/*

lloyd.cpp
Modified on : 11/24/2014 
Modified By  : Karan Bhagat AND Vaibhav Page  
Version : 1.0
Revisions : 0
*/
#include <iostream>
#include <cstdlib>
#include <fstream>//for file input/output
#include <string.h>
#include "puzzle.h"

using namespace std;

class LloydPuzzle : public Puzzle< vector<char> >{
	private:
		int width; //width of the block puzzle
		int height;//height of the block puzzle
		vector<char> goal;// goal state
		
	
	public:
		//constructor to the LloydPuzzle
		LloydPuzzle( vector<char> s, vector<char> g, int w, int h ):Puzzle< vector<char> >(s){
			goal = g;
			width = w;
			height = h;
		}
		

		vector< vector<char> > getAllNextConfigs( vector<char> v){
			vector< vector<char> > v_config;
			vector<char> tmp_v;
			for( int i = 0; i < width*height; i++ ){
				if( v[i] == '.'){
					
					//case 1 checking left
						if( i%width != 0){
							tmp_v = v;
							tmp_v[i] = tmp_v[i-1];
							tmp_v[i-1] = '.';
							v_config.push_back(tmp_v);
							
						}

					//case 2 checking above
						if( i >= width){
							tmp_v = v;
							tmp_v[i] = tmp_v[i-width];
							tmp_v[i-width] = '.';
							v_config.push_back(tmp_v);
							
						}
					//case 3 checking right
						if( i%width != width-1 ){
							tmp_v = v;
							tmp_v[i] = tmp_v[i+1];
							tmp_v[i+1] = '.';
							v_config.push_back(tmp_v);
							
						}
					//case 4 checking down
						if( i < width*(height-1)){
							tmp_v = v;
							tmp_v[i] = tmp_v[i+width];
							tmp_v[i+width] = '.';
							v_config.push_back(tmp_v);
							
						}
						

				}
			}

			return v_config;
		}

		void display(vector<char> c){
			for(int i = 0; i < height*width; i++){
				cout<<c[i]<<" ";
				if( i%width == width-1){
					cout<<endl;
				}
			}
			cout<<endl;			
		}

		void writeFile(vector<char> c, ofstream &of){
			for(int i = 0; i < height*width; i++){
				of<<c[i]<<" ";
				if( i%width == width-1){
					of<<"\n";
				}
			}
			of<<"\n";
		}

		bool isGoal(vector<char> c){
			for( int i = 0; i < width*height; i++){
				if( c[i] != goal[i] ){
					return false;
				}
			}
			return true;
		}
};


int main( int argc, char *argv[] ){
	
	vector<char> start;
	vector<char> goal;
	vector< vector<char> > goalpath;
	int width;
	int height;
	int in_cnt = 0; //for checking irregularities in input

	if( strcmp(argv[1],"-") == 0 ){
		///take input from Std IO
			cin>>width>>height;
			start.resize( width*height,48);
			goal.resize( width*height,48);
    		for( int i = 0; i < height*width; i++){
    				cin>>start[i];
    				in_cnt++;
    		}

    		for( int i = 0; i < height*width; i++){
    				cin>>goal[i];
    				in_cnt++;
    		}

    		if( in_cnt != 2*width*height){
    			cerr<<"Invalid Input";
    			return EXIT_FAILURE;
    		}
	}
	else{
		//take input from file
		 ifstream infile (argv[1]);
		 if(infile.is_open()){

		 	infile>>width>>height;
		 	start.resize( width*height,48);
			goal.resize( width*height,48);
    		for( int i = 0; i < height*width; i++){
    				infile>>start[i];
    				in_cnt++;
    		}

    		for( int i = 0; i < height*width; i++){
    				infile>>goal[i];
    				in_cnt++;
    		}

    		if( in_cnt != 2*width*height){
    			cerr<<"Invalid Input";
    			return EXIT_FAILURE;
    		}

		 	infile.close();
		 }
		 else{
		 	cerr << "File failed to open";
    		return EXIT_FAILURE;
		 }
	}

	LloydPuzzle lloyd(start,goal,width,height);
	goalpath = lloyd.solvePuzzle();

	if( strcmp(argv[2],"-") == 0 ){
		//output to std IO
		
		if( !goalpath.empty() ){
			vector< vector<char> >::reverse_iterator it;
			for( it = goalpath.rbegin(); it != goalpath.rend(); it++){
				lloyd.display(*it);
			}
		
		}
		else{
			cout<<"No Solution"<<endl;
		}
	
	}
	else{
		//output to file
		ofstream outfile (argv[2]);
		if(outfile.is_open()){
		 	if( !goalpath.empty() ){
				vector< vector<char> >::reverse_iterator it;
				for( it = goalpath.rbegin(); it != goalpath.rend(); it++){
					lloyd.writeFile(*it,outfile);
				}
			}
			else{
				outfile<<"No Solution"<<"\n";
			}
		 	outfile.close();
		}
		else{
			cerr << "File failed to open";
    		return EXIT_FAILURE;
		}
	}
}
