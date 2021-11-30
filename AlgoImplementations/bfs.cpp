#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define ROW 6
#define COLUMN 8
#define CONST 121

using namespace std;

class SearchAlgo{
    int xStart, yStart;
    int xEnd, yEnd;
    int obstacles, choice;
    int board[ROW][COLUMN];
    int check[ROW][COLUMN];

    public:
        SearchAlgo(int choice, int obstacles, pair<int, int> startPos, pair<int, int> endPos){
            this->choice = choice;
            this->obstacles = obstacles;
            this->xStart = startPos.first;
            this->yStart = startPos.second;
            this->xEnd = endPos.first;
            this->yEnd = endPos.second;
            memset(board, 0, sizeof(board));
            memset(check, 0, sizeof(check));
        }

        void get_manhantan(){
            for (int i = 0; i < ROW; i++){
                for (int j = 0; j < COLUMN; j++){
                    if (board[i][j] != -1){
                        if (choice == 1)
                            board[i][j] = abs(i - xEnd) + abs(j - yEnd);
                        else
                            board[i][j] = abs(i - xEnd) + abs(j - yEnd) + (i - xStart) + (j - yStart);
                    }
                        
                }
            }
        }

        void printBoard(int board[ROW][COLUMN]){
            for (int i = 0; i < ROW; i++){
                for (int j = 0; j < COLUMN; j++){
                    if (board[i][j] == -11)
                        cout << " - ";
                    else if(board[i][j] == -1)
                        cout << " X ";
                    else
                        cout << " " << board[i][j] << " ";
                }
                cout << endl;
            }   
            cout << endl << endl;       
        }

        void printPath(vector<pair<int, int>> path){
            int temp[ROW][COLUMN];
            for (int i = 0; i < path.size(); i++){
                board[path[i].first][path[i].second] = -11;
            }

            printBoard(board);
            cout << endl;
        }

        bool isValid(int i, int j, int x, int y){
            if ((check[i][j] != -1) && (board[i][j] != -1))
                return (i >= 0) && (i < ROW) && (j >= 0) && (j < COLUMN);
            
            return false;
        }

        bool search(){
            int cords = CONST * xStart + yStart;
            priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
            pq.push(make_pair(board[xStart][yStart], cords));
            check[xStart][yStart] = -1;

            vector<pair<int, int>> path;
            while(!pq.empty()){
                int x, y;

                int distance = pq.top().first;
                int cords = pq.top().second;
                x = cords / CONST, y = cords % CONST;
                pq.pop();

                check[x][y] = -1;
                path.push_back(make_pair(x, y));

                cout << x << " " << y << endl;
                if (x == xEnd && y == yEnd){
                    cout << "Path is as follows: " << endl;
                    printPath(path);
                    return true;
                }

                vector<pair<int, int>> valid = {{x-1, y}, {x, y-1}, {x+1, y}, {x, y+1}};
                for (int i = 0; i < valid.size(); i++){
                    int m = valid[i].first, n = valid[i].second;
                    if (isValid(m, n, x, y)){
                        pq.push(make_pair(board[m][n], (CONST * m + n)));
                    }
                }

            }
            
            return false;
        }

        void get_input(){
            int m, n;

            cout << "Enter Positions of Obstacles: " << endl;
            for (int i = 0; i < obstacles; i++){
                cin >> m >> n;
                board[m][n] = -1;
            }

            printBoard(board);
        }

        void get_output(){
            get_manhantan();
            cout << endl << "Manhantan Distance of each co-ord: " << endl;
            printBoard(board);

            bool path = search();
            if (!path)
                cout << "No Path Found!" << endl;
        }

};

int main(){
    int choice, obstacles;

    pair<int, int> startPos;
    pair<int, int> endPos;

    cout << "Enter Starting Position(RxC): ";
    cin >> startPos.first >> startPos.second;
    cout << endl;

    cout << "Enter Target Position(RxC): ";
    cin >> endPos.first >> endPos.second;
    cout << endl;

    cout << "Enter Number of obstacles: ";
    cin >> obstacles;
    cout << endl;

    cout << "Choose the algorithm to Implement:\n1.BFS\n2.A*" << endl<< endl;
    cout << "Choice(1/2): ";
    cin >> choice;
    cout << endl;

    if (choice != 1 && choice != 2){
        cout << "Invalid choice." << endl;
    }
    else{
        SearchAlgo search(choice, obstacles, startPos, endPos);
        search.get_input();
        search.get_output();
    }
    
    return 0;
}

//   0 1 2 3 4 5 6 7
// 0 _ X _ _ _ _ _ _
// 1 _ _ S _ X _ X _
// 2 _ X X _ _ _ _ _
// 3 _ X X X _ _ _ _
// 4 _ X E _ _ X _ _
// 5 _ _ _ _ X _ _ _ 
