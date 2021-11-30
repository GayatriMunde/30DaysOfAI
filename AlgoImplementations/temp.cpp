#include <cstdlib>
#include <iostream>
#include <math.h>
#include <deque>
#include <string>
#include <fstream>

using namespace std;

static const int BOARDSIZE = 7; 

static const int FREE 		= 1; 	
static const int START 		= 4;	
static const int BLOCK 		= 5;	
static const int OPEN 		= 6;	
static const int CLOSED 	= 7;	
static const int E 		    = 8;	

class Coord
{
	private:
            int row, col;               	
			int depth;						
			int functionF;					
			Coord * parent;					
			
	public:
			Coord( int row, int col, int depth, int functionF, Coord * parent ) {	
				this->row = row;
				this->col = col;
				this->depth = depth;
				this->functionF = functionF;
				this->parent = parent;
			}
			
			~Coord() { delete parent; }
			
			int getRow() { return row; };
			int getCol() { return col; };
			int getDepth() { return depth; };
			int getFunctionF() { return functionF; };
			Coord * getParent() { return parent; };
};

class Search 
{
	private:			
			int mazeMap [BOARDSIZE][BOARDSIZE];					
			int mazeRoute [BOARDSIZE][BOARDSIZE]; 				
            int startRow, startCol;	
			int exitRow, exitCol;					
			int cost;						
			int maxOpenQSize; 				
			deque<Coord *> openDeque;
			deque<Coord *> closedDeque;	
			
	public:
            Search();
			void SearchTemplate();
			void SearchImplementation( int, int );
			void AStarSort( int, int, int, Coord * );
			void Print();
			void CleanUp();
};

Search::Search():cost( 0 ), maxOpenQSize( 0 ) {
    ifstream mapFile;
    mapFile.open( "map.txt", ios::in );
    if ( mapFile.is_open() )
    {
		for ( int i = 0; i < BOARDSIZE; i++ ) {
			for ( int j = 0; j < BOARDSIZE; j++ ) {
				mapFile >> mazeMap [i][j];
				mazeRoute [i][j] = mazeMap [i][j];

				if ( mazeMap[i][j] == START ) {
					startRow = i;
					startCol = j;
				} else if ( mazeMap[i][j] == E ) {
					exitRow = i;
					exitCol = j;
				}
			}
		} 
		mapFile.close();
    } else {
        cout << "Unable to open file";
    }        
}

void Search::SearchTemplate( ) {
    int functionF = abs( startRow - exitRow ) + abs( startCol - exitCol ); 
    openDeque.push_back( new Coord( startRow, startCol, 0, functionF, 0 ) );
	maxOpenQSize = 1;
	
	mazeRoute[startRow][startCol] = OPEN;
	
	int row = 0;
	int col = 0;
	bool win = false;

	while( openDeque.size() != 0 ) {

		row = openDeque.front() -> getRow();
		col = openDeque.front() -> getCol();
		
		mazeRoute[row][col] = CLOSED; 								
		cost++; 													
		if( mazeMap[row][col] == E ) { 							
			
			closedDeque.push_back( openDeque.front() );
			openDeque.pop_front();
			win = true;
			break; 													

		} else { 													
			
			closedDeque.push_back( openDeque.front() );
			openDeque.pop_front(); 									
			
			SearchImplementation( row, col );
		}
	}
	
	if ( !win ) { cout << "This maze has no solution!" << endl; }
	
	Print();
}

void Search::SearchImplementation( int row, int col ) {
	int depth = ( closedDeque.back() -> getDepth() ) + 1; 
	Coord * parent = closedDeque.back();

	if ( ( col - 1 > -1 ) && mazeRoute[row][col - 1] != BLOCK && mazeRoute[row][col - 1] != CLOSED && mazeRoute[row][col - 1] != OPEN ) {
		mazeRoute[row][col - 1] = OPEN;
        AStarSort( row, col - 1, depth, parent );
	}
	if ( ( row - 1 > -1 ) && mazeRoute[row - 1][col] != BLOCK && mazeRoute[row - 1][col] != CLOSED && mazeRoute[row - 1][col] != OPEN ) {
		mazeRoute[row - 1][col] = OPEN;
        AStarSort( row - 1, col, depth, parent );
	}
	if ( ( col + 1 < BOARDSIZE ) && mazeRoute[row][col + 1] != BLOCK && mazeRoute[row][col + 1] != CLOSED && mazeRoute[row][col + 1] != OPEN ) {
		mazeRoute[row][col + 1] = OPEN;
		AStarSort( row, col + 1, depth, parent );
	}
	if ( ( row + 1 < BOARDSIZE ) && mazeRoute[row + 1][col] != BLOCK && mazeRoute[row + 1][col] != CLOSED && mazeRoute[row + 1][col] != OPEN ) {
		mazeRoute[row + 1][col] = OPEN;
		AStarSort( row + 1, col, depth, parent );
	}
	maxOpenQSize = ( openDeque.size() > maxOpenQSize ) ? openDeque.size() : maxOpenQSize;
}

void Search::AStarSort( int row, int col, int depth, Coord * parent ) {
	int gN = depth;
	int hN = abs( exitRow - row ) + abs( exitCol - col );
	int functionF = gN + hN;
	
	bool insertSuccess = false;

	if ( openDeque.size() == 0 ) {
		openDeque.push_back( new Coord( row, col, depth, functionF, parent ) );
	} else {
		deque<Coord *>::iterator it;
		int i = 0;
		for ( it = openDeque.begin(); it != openDeque.end(); it++ ) {
			if ( functionF < openDeque[i] -> getFunctionF() ) {
				openDeque.insert( it, new Coord( row, col, depth, functionF, parent ) );
				insertSuccess = true;
				break;
			}
			i++;
		}
		if ( !insertSuccess ) {
			openDeque.push_back	( new Coord( row, col, depth, functionF, parent ) );
		}	
	}
}

void Search::Print() {
	Coord * Iterator;
	deque<Coord *> path;
	for ( Iterator = closedDeque.back(); Iterator -> getParent() != 0; Iterator = Iterator -> getParent() ) {
		path.push_front( Iterator );
	}
	
	path.push_front( Iterator );
    
    cout << "\nPath Taken" << endl;
	for ( int i = 0; i < BOARDSIZE; i++ ) {
        for ( int j = 0; j < BOARDSIZE; j++ ) {
			if( mazeMap [i][j] == BLOCK ) cout << "B";
            else if(mazeMap [i][j] == START) cout << "S";
            else if( mazeMap [i][j] == E ) cout << "E";
            else {
                 bool on_the_path = false;
                 for( int k = 0; k < path.size(); k++ ) {
                      if( path[k] -> getRow() == i && path[k] -> getCol() == j ) on_the_path = true;
                 }
                 if( on_the_path ) cout << "*";
                 else cout << " ";
            }
        }
        cout << "\n";
    }

	// cout << "\nComplete path: " << endl;
	// for ( int k = 0; k < path.size(); k++ ){
    //      cout << "(" << ( path[k] -> getCol() ) << "," <<  BOARDSIZE - ( path[k] -> getRow() ) - 1 << ")";
    //      if( k < path.size() - 1 ) cout << " -> ";
    // }
    // cout << endl << endl;
}

void Search::CleanUp() {
	for ( int i = 0; i < BOARDSIZE; i++ ) {
        for ( int j = 0; j < BOARDSIZE; j++ ) {
            mazeRoute [i][j] = mazeMap[i][j];
        }
    }
	openDeque.clear();
	closedDeque.clear();
	cost = 0;
	maxOpenQSize = 0;
}

int main() {	
	Search * s = new Search();	
	cout << "Search for Exit" << endl;
	s -> SearchTemplate();
	s -> CleanUp();
	delete s;
    return 0;
}

