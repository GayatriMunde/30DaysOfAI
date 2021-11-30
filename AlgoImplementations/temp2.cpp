#include<bits/stdc++.h>

using namespace std;

class lab3
{
private:
    int board[100][100];
    bool visited[100][100];
    int n,m,obstacles;
    int x1,y1,x2,y2;
    bool isBFS;
public:

    lab3(bool ip)
    {
        memset(board,0,sizeof(board));
        memset(visited,false,sizeof(visited));
        isBFS = ip;
    }
   
    void manhattan()
    {
        int i,j;
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
            {
                if(board[i][j]!=-1)
                if(isBFS)
                    board[i][j]=abs(i-x2)+abs(j-y2);
                else
                    board[i][j]=abs(i-x2)+abs(j-y2) + (i-x1)+(j-y1);

            }
        }
    }

    void print()
    {
        int i,j;
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
            {
                if(board[i][j]==-1)
                    cout<<" X ";
                else
                    cout<<" "<<board[i][j]<<" ";

            }
            cout<<"\n";
        }
    }

    void print(vector<int> g)
    {
        int arr[100][100],x,y;

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                arr[i][j]=board[i][j];
            }
        }

          for(int i=0;i<g.size();i++)
        {
            x=g[i]/m;
            y=g[i]%m;
            arr[x][y] = -10;
            // cout<<x<<" "<<y<<endl;
        }

       
       

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(arr[i][j]==-10)
                    cout<<" * ";
                else if(arr[i][j]==-1)
                    cout<<" X ";
                else
                    cout<<" "<<arr[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
   
    void output(vector<int> g)
    {    
        int x,y;
        cout<<"Path........."<<endl;
        cout<<endl;
         for(int i=0;i<g.size();i++)
        {
            x=g[i]/m;
            y=g[i]%m;
            cout<<x<<" "<<y<<endl;
        }
        
    }

    void input()
    {

        int x,y,i;
        cout<<"Size of board : ";
        cin>>n>>m;
        cout<<"Number of obstacles : ";
        cin>>obstacles;
        cout<<"Starting position : ";
        cin>>x1>>y1;
        cout<<"Ending position : ";
        cin>>x2>>y2;

        if(obstacles!=0)
        {
            cout<<"Obstacle positions : ";
            for(i=0;i<obstacles;i++)
            {
                cin>>x>>y;
                board[x][y]=-1;
            }

        }
    }





    void best_first_search()
    {

        int i,j,k,t1,t2,x,y;
        manhattan();
        cout<<"Matrix after calculating manhattan :\n";
        print();
        vector<int> close;
        priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>> > pq;
         priority_queue<pair<int,int>,vector<pair<int,int>>> o;
        t2=0;
        t1=x1*m+y1;
        visited[x1][y1]=true;
        pq.push(make_pair(board[x1][y1],t1));
         o.push(make_pair(board[x1][y1],t1));

        while(!pq.empty())
        {
           
            int dist=pq.top().first;
            int cor=pq.top().second;
            x=cor/m;
            y=cor%m;
            pq.pop();
            visited[x][y]=true;
            close.push_back(cor);
            if(x==x2 && y==y2)
            {
                cout<<"\n\nThere exist a path from source to destination\n\n";
                print(close);
               output(close);
                return;
            }

            if(x-1>=0 && !visited[x-1][y] && board[x-1][y]!=-1)
            {
                pq.push(make_pair(board[x-1][y],(x-1)*m+y));
                //o.push(make_pair(board[x-1][y],(x-1)*m+y));

            }

            if(y-1>=0 && !visited[x][y-1] && board[x][y-1]!=-1)
            {
                pq.push(make_pair(board[x][y-1],x*m+(y-1)));
                //o.push(make_pair(board[x][y-1],x*m+(y-1)));

            }

            if(x+1<n && !visited[x+1][y] && board[x+1][y]!=-1)
            {
                pq.push(make_pair(board[x+1][y],(x+1)*m+y));
                //o.push(make_pair(board[x+1][y],(x+1)*m+y));

            }

            if(y+1<m && !visited[x][y+1] && board[x][y+1]!=-1)
            {
                pq.push(make_pair(board[x][y+1],x*m+(y+1) ));
                //o.push(make_pair(board[x][y+1],x*m+(y+1) ));

            }


        }
        cout<<"\n\nPath not exist\n\n";

    }

};

int main()
{
    

    int  choice;
    cout<<"1.Best First Search"<<endl;
    cout<<"2.A*"<<endl;
    cin>>choice;
    if(choice==1)
    {
         lab3 obj1(true);
        obj1.input();
        cout<<"BFS............"<<endl;
       obj1.best_first_search();
    }
    else
    {
         lab3 obj2(false);
         obj2.input();
        cout<<"A*.............."<<endl;
       obj2.best_first_search();

    }
    

   
   
    return 0;
}
