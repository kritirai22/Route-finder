#include<bits/stdc++.h>
#include<conio.h>

using namespace std;

//Constant variables declared
#define MAXN 20
const int INF = 1e7;

/*
2-D array to be used for
referning the weights between destinations
*/
int temp[MAXN][MAXN];

// Initializing the distance and
// Next array
class places{
public:
    string name;
    int fare;
    int closing_time;
};
places node[MAXN];

//map initialization
//here, 'INF' implies that the vertices are not connected via any path
vector<vector<int> > graph =
{
    {0,INF,INF,14,INF,INF,INF,INF,120,42,8,23,INF,INF,INF,INF,INF,INF,INF,INF},
    {INF,0,8,3,21,6,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
    {INF,8,0,INF,INF,INF,10,54,54,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
    {14,3,INF,0,13,INF,INF,INF,INF,INF,INF,15,41,INF,INF,INF,INF,INF,INF,INF},
    {INF,21,INF,13,0,29,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,13},
    {INF,9,INF,INF,29,0,27,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,33,INF},
    {INF,INF,10,INF,INF,27,0,15,INF,INF,INF,INF,INF,INF,INF,INF,INF,32,72,INF},
    {INF,INF,54,INF,INF,INF,15,0,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
    {120,INF,54,INF,INF,INF,INF,INF,0,32,INF,INF,INF,INF,INF,INF,INF,15,INF,INF},
    {42,INF,INF,INF,INF,INF,INF,INF,32,0,11,INF,INF,INF,66,INF,77,INF,INF,INF},
    {8,INF,INF,INF,INF,INF,INF,INF,INF,11,0,11,INF,INF,INF,INF,INF,INF,INF,INF},
    {23,INF,INF,15,INF,INF,INF,INF,INF,INF,11,0,INF,INF,26,INF,INF,INF,INF,INF},
    {INF,INF,INF,41,INF,INF,INF,INF,INF,INF,INF,INF,0,42,INF,INF,INF,INF,INF,INF},
    {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,42,0,26,INF,INF,INF,INF,INF},
    {INF,INF,INF,INF,INF,INF,INF,INF,INF,66,INF,26,INF,26,0,41,INF,INF,INF,INF},
    {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,41,0,INF,INF,INF,INF},
    {INF,INF,INF,INF,INF,INF,INF,INF,INF,77,INF,INF,INF,INF,INF,INF,0,12,INF,INF},
    {INF,INF,INF,INF,INF,INF,32,INF,15,INF,INF,INF,INF,INF,INF,INF,INF,0,INF,INF},
    {INF,INF,INF,INF,INF,33,72,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0,41},
    {INF,INF,INF,INF,13,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,41,0}
};

//functions
void initialise();
void print_graph();
void floydWarshall();
vector<string> constructing_path(int u,int v);
void print_path(vector<string>& path);
void path_finder();
int name_to_integer(string s);
void nearby();
void f1(int s,int p[],int n);
void visit_all_destinations();
void max_place_time_bound();

// Driver code
int main()
{
    //initilise the variables
    initialise();

    //call function for floyd warshall
    floydWarshall();

    //loop to repeat itself until the 'break' statement is called
    while(1)
    {
        system("cls");

        //menu
        cout<<"Route Finder"<<endl<<endl;
        cout<<"Enter Your Choice"<<endl;
        cout<<"1. Find best path from source to destination"<<endl;
        cout<<"2. Find best path to visit all the destinations you want "<<endl;
        cout<<"3. Visit maximum places (time bound)"<<endl;
        cout<<"4. Exit"<<endl;

        //call for functions using conditions
        int n;
        cin>>n;
        if(n==1)
            path_finder();
        else if(n==2)
            visit_all_destinations();
        else if(n==3)
            max_place_time_bound();
        else break;
        cout<<"\n\npress any return to main menu";
        getch();
    }
    //driver code ends
}

//function declaration
//To initialise the object of class 'places'
void initialise()
{
    //ticket price of the 20 places in the graph
    int prices[]={340,450,230,760,210,920,800,350,400,260,250,100,200,300,150,500,200,100,700,200};

    //closing time of the places in the graph
    int ct[]={24,9,10,2,12,10,11,10,10,12,9,1,24,10,9,5,9,8,6,7};

    //name list for the destinations
    vector<string> names={ "Marine Drive",
                "Bandra-Worli Sea Link",
                "Gateway of India",
                "Phoenix Marketcity",
                "Infiniti Mall",
                "Red Carpet Wax Museum",
                "Haji Ali Dargah",
                "Siddhivinayak Temple",
                "Chhatrapati Shivaji Terminus",
                "Sanjay Gandhi National Park",
                "ISKCON Temple",
                "Girgaon Chowpatty",
                "Shri Mahalakshmi Temple",
                "Powai Lake",
                "Nehru Center",
                "Kidzania",
                "Taraporewala Aquarium",
                "Veermata Jijabai Bhosale Zoo",
                "Essel World",
                "Juhu Beach"
            };

    //entering the values in the object of the class 'places'
    for(int i=0;i<MAXN;i++)
    {
            node[i].name=names[i];
            node[i].fare=prices[i];
            node[i].closing_time=ct[i];
    }

    //initilizing the global 'temp' 2-D array
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            if (graph[i][j] == INF)
            {
                //-1 impliment that the places/vertices are not connected
                temp[i][j] = -1;
            }
            else
            {
                //same value present in 'graph' has been passed otherwise
                temp[i][j] = j;
            }
        }
    }
}

//print the graph/map
void print_graph()
{
    for(int i=0;i<MAXN;i++)
    {
        for(int j=0;j<MAXN;j++)
        {
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
}

//standard Floyd Warshall Algorithm
void floydWarshall()
{
    for (int k = 0; k < MAXN; k++)
    {
        for (int i = 0; i < MAXN; i++)
        {
            for (int j = 0; j < MAXN; j++)
            {

                //if no path present in between
                if (graph[i][k] == INF|| graph[k][j] == INF)
                    continue;

                //change value if better option has been found
                if (graph[i][j] > graph[i][k]+ graph[k][j])
                {
                    graph[i][j] = graph[i][k]+ graph[k][j];
                    temp[i][j] = temp[i][k];
                }
            }
        }
    }
}

// to construct the shortest path between two values u and v
vector<string> constructing_path(int u,int v)
{
    //return empty array if no path present
    if (temp[u][v] == -1)
    {
        return {};
    }

    //storing the path in a vector
    vector<string> path={ node[u].name };
    while (u!=v)
    {
        u = temp[u][v];
        path.push_back(node[u].name);
    }
    return path;
}

//print the shortest obtained path
void print_path(vector<string>& path)
{
    int n = path.size();
    for (int i=0; i<n-1; i++)
    {
        cout<<path[i]<<" -> ";
    }
    cout << path[n - 1] << endl;
}

//function to find path
void path_finder()
{
    //declaring data members
    int s,d;
    string st,dt;
    vector<string> path;

    //taking source and destination from user
    cin.ignore();
    cout<<"ENTER SOURCE:";
    getline(cin,st);
    //cin.ignore();
    cout<<"ENTER DESTINATION:";
    getline(cin,dt);

    //converting location names to integer values to work in array
    s = name_to_integer(st);
    d = name_to_integer(dt);

    cout << "\nShortest path from "<<node[s].name<<" to "<<node[d].name<<" is\n\n ";

    //finding path
    path = constructing_path(s, d);

    //printing path
    print_path(path);
}

//to convert a entered string into integer values for further use
int name_to_integer(string s)
{
    /*
    for each distinct value of s
    an integer is given to program
    integer value represent the index of graph
    */
    if(s=="Marine Drive")
        return 0;
    else if(s=="Bandra-Worli Sea Link")
        return 1;
    else if(s=="Gateway of India")
        return 2;
    else if(s=="Phoenix Marketcity")
        return 3;
    else if(s=="Infiniti Mall")
        return 4;
    else if(s=="Red Carpet Wax Museum")
        return 5;
    else if(s=="Haji Ali Dargah")
        return 6;
    else if(s=="Siddhivinayak Temple")
        return 7;
    else if(s=="Chhatrapati Shivaji Terminus")
        return 8;
    else if(s=="Sanjay Gandhi National Park")
        return 9;
    else if(s=="ISKCON Temple")
        return 10;
    else if(s=="Girgaon Chowpatty")
        return 11;
    else if(s=="Shri Mahalakshmi Temple")
        return 12;
    else if(s=="Powai Lake")
        return 13;
    else if(s=="Nehru Center")
        return 14;
    else if(s=="Kidzania")
        return 15;
    else if(s=="Taraporewala Aquarium")
        return 16;
    else if(s=="Veermata Jijabai Bhosale Zoo")
        return 17;
    else if(s=="Essel World")
        return 18;
    else if(s=="Juhu Beach")
        return 19;
    //if the given string is not found, -1 is returned
    else
        return -1;

}



//function for finding path for n places starting from source s
void f1(int s,int p[],int n)
{
    //starting from source, printing location name
    cout<<node[s].name<<"->";

    //base condition
    int c=0;
    for(int i=0;i<n;i++)
    {
        if(p[i]==-1)
        {
            c++;
        }
    }
    if(c==n)
    {
        return;
    }

    //calculating next location
    int m=INT_MAX;
    int u=0;
    for(int i=0;i<n;i++)
    {
        if(graph[s][p[i]]<m && p[i]!=-1)
        {
            u=p[i];
            m=graph[s][p[i]];
        }
    }
    for(int i=0;i<n;i++)
    {
        if(p[i]==u){
            p[i]=-1;
        }
    }

    //recursion call
    f1(u,p,n);
}

//function for finding out the best path to visit all the destinations
void visit_all_destinations()
{
    //taking the starting location
    int s;
    string st;
    cin.ignore();
    cout<<"your location:";
    getline(cin,st);
    s = name_to_integer(st);

    //taking the number of places user want to visit
    int n;
    cout<<"No. of places you want to visit:";
    cin>>n;

    //takinng the places the user want to visit
    int p[n];
    string in;
    cout<<"Please enter the places:";
    cin.ignore();
    for(int i=0;i<n;i++)
    {
        getline(cin,in);
        p[i] = name_to_integer(in);
    }

    //solution
    cout<<"You can choose this path:";
    f1(s,p,n);
}

//visiting the maximum places with time bound condition
void max_place_time_bound()
{
    //declaring the data members
    vector<pair<int,int>> pp;
    int total=0;
    int m=0;

    //initilizing vector 'pp'
    for(int i=0;i<MAXN;i++)
    {
        if(node[i].closing_time>m)
        {
            m=node[i].closing_time;
        }
        pp.push_back(make_pair(node[i].fare,i));
    }

    //sorting pp
    sort(pp.begin(),pp.end());

    //filtering out all the undesired places and calculating the total charges
    int temp[m]={0};
    for(int i=0;i<MAXN;i++)
    {
        if(temp[node[pp[i].second].closing_time]==0)
        {
            total+=pp[i].first;
            temp[node[pp[i].second].closing_time]=pp[i].second+1;
        }
        else
        {
            int j=node[pp[i].second].closing_time;
            while(j--)
            {
                if(temp[j]==0)
                    {
                        temp[j]=pp[i].second+1;
                        total+=pp[i].first;
                        break;
                    }
            }
        }
    }

    //solution
    cout<<endl<<endl;
    cout<<"Total prize: "<<total<<endl;
    cout<<"\nYou can visit:\n";
    for(int i=0;i<m;i++)
    {
        if(temp[i]!=0)
        {
            cout<<node[temp[i]-1].name<<endl;
        }
    }
}


/* CODE END */
