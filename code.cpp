#include<bits/stdc++.h>
#include"trie.cpp"
#include<conio.h>

using namespace std;

//Constant variables declared
#define MAXN 20
const int INF = 1e7;

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

//DELHI NCR PLACES 
vector<string> names={ "Mehrauli",
    "Badarpur",
    "Greater Kailash 2",
    "Palika Bazaar",
    "India Gate",
    "Rajouri Garden",
    "Hauz Khas Enclave",
    "Sarojini Nagar",
    "Connaught Place",
    "Saket",
    "Indirapuram",
    "Govindpuri",
    "Sadar Bazaar",
    "Pitam Pura",
    "Noida",
    "Karol Bagh",
    "Tilaknagar",
    "Vijaynagar",
    "Electronic City",
    "Jahangirpuri"
};

//functions
void initialise();
void print_places();
void print_graph();
void floydWarshall();
vector<string> constructing_path(int u,int v);
void print_path(vector<string>& path);
void path_finder(Trie T);
int name_to_integer(string s);
void nearby();
void f1(int s,int p[],int n);
void visit_all_destinations(Trie T);
void max_place_time_bound();
bool check_number(string str);

// Driver code
int main(){

    // initialising Trie
    Trie T;
    for (string name : names) {
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        T.insert(name);
    }

    //initilise the variables
    initialise();
    
    //call function for floyd warshall
    floydWarshall();

    //loop to repeat itself until the 'break' statement is called
    while(1)
    {
        //menu
        cout<<endl<<endl<<endl;
        cout<<"  d88888b db    db d8888b. db       .d88b.  d8888b. d88888b      d8b   db     .o88b.    d8888b. \n";
        cout<<"  88'     `8b  d8' 88  `8D 88      .8P  Y8. 88  `8D 88'          888o  88    d8P  Y8    88  `8D \n";
        cout<<"  88ooooo  `8bd8'  88oodD' 88      88    88 88oobY' 88ooooo      88V8o 88    8P         88oobY' \n";
        cout<<"  88~~~~~  .dPYb.  88~~~   88      88    88 88`8b   88~~~~~      88 V8o88    8b         88`8b   \n";
        cout<<"  88.     .8P  Y8. 88      88booo. `8b  d8' 88 `88. 88.          88  V888 db Y8b  d8 db 88 `88. \n";
        cout<<"  Y88888P YP    YP 88      Y88888P  `Y88P'  88   YD Y88888P      VP   V8P VP  `Y88P' VP 88   YD \n";
        cout<<endl<<endl;
        cout<<"Enter Your Choice"<<endl<<endl;
        cout<<"1. Available destinations of NCR"<<endl;
        cout<<"2. Find best path from source to destination"<<endl;
        cout<<"3. Find best path to visit all the destinations you want "<<endl;
        cout<<"4. Visit maximum places (time bound)"<<endl;
        cout<<"5. Exit"<<endl<<endl;
        cout<< "Your choice is : ";

        //call for functions using conditions
        int n;
        cin>>n;
        if(n==1)
            print_places();
        else if(n==2)
            path_finder(T);
        else if(n==3)
            visit_all_destinations(T);
        else if(n==4)
            max_place_time_bound();
        else break;
        cout<<"\n\npress any return to main menu";
        getch();
        system("cls");
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

void print_places(){
    cout<<"Here is the available destinations list:"<<endl;

    for (string name : names) {
        string s = name;
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        cout<<name_to_integer(s)+1<<". "<<name<<endl;
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

void path_finder(Trie T)
{
    //declaring data members
    int s,d;
    string ss,dd;
    string st,dt;
    vector<string> path;
   
    //taking source and destination from user
    cin.ignore();
    cout<<"ENTER SOURCE:  ";
    bool ok1 = false;
    do{
        ok1 = false;
        getline(cin,st);
        if(check_number(st)) {
            ok1 = true;
            cout<<"Enter valid source..";
        }
    }while(ok1);
    
    for (string w : T.search_pre(st))
    {
        cout<<name_to_integer(w)<<". "<<w<<"\n";
    }
    cout<<"\nCHOOSE A NUMBER: ";
    bool ok2 = false;
    do{
        ok2=false;
        getline(cin,ss);
        if(check_number(ss)) continue;
        else {
            ok2=true;
            cout<<"Enter valid input number..";
        }
    }while(ok2);
    
    cin.ignore();
    cout<<"ENTER DESTINATION:  ";
    bool ok3 = false;
    do{
        ok3 = false;
        getline(cin,dt);
        if(check_number(dt)) {
            ok3 = true;
            cout<<"Enter valid destination..";
        }
    }while(ok3);

    for (string w : T.search_pre(dt))
    {
        cout<<name_to_integer(w)<<". "<<w<<"\n";
    }
    cout<<"\nCHOOSE A NUMBER: ";
    bool ok4 = false;
    do{
        ok4=false;
        getline(cin,dd);
        if(check_number(dd)) continue;
        else {
            ok4=true;
            cout<<"Enter valid input number..";
        }
    }while(ok4);  

    //converting location names to integer values to work in array
    s=stoi(ss);
    d=stoi(dd);

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
    for (int i=0; i<20; i++) {
        string name = names[i];
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        if(s==name){
            return i;
        }
    }
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
void visit_all_destinations(Trie T)
{
    system("cls");
    cout<<endl<<endl<<endl;
    cout<<"****** Explore N.C.R ********"<<endl<<endl<<endl;
    //taking the starting location
    int s,d;
    string ss,dd,st;
    cin.ignore();
    cout<<"your location : ";
    bool ok1 = false;
    do{
        ok1 = false;
        getline(cin,st);
        if(check_number(st)) {
            ok1 = true;
            cout<<"Enter valid location name..";
        }
    }while(ok1);
    
    for (string w : T.search_pre(st))
    {
        cout<<name_to_integer(w)<<". "<<w<<"\n";
    }
    cout<<endl;
    cout<<"\nCHOOSE A NUMBER: ";
    bool ok2 = false;
    do{
        ok2=false;
        getline(cin,ss);
        if(check_number(ss)) continue;
        else {
            ok2=true;
            cout<<"Enter valid input number..";
        }
    }while(ok2);
    s=stoi(ss);
    cin.ignore();
    //taking the number of places user want to visit
    int n;
    cout<<endl<<endl<<endl;
    cout<<"No. of places you want to visit : ";
    cin>>n;
    system("cls");
    cout<<endl<<endl<<endl;
    cout<<"******  Explore N.C.R ********"<<endl<<endl<<endl;
    //takinng the places the user want to visit
    int p[n];
    string in;
    
    for(int i=0;i<n;i++)
    {
        cout<<"Please enter the place "<< i+1 <<" : " << endl<<endl;
        cin.ignore();
        bool ok1 = false;
        do{
        ok1 = false;
        getline(cin,in);
        if(check_number(in)) {
            ok1 = true;
            cout<<"Enter valid location name..";
            }
        }while(ok1);
        for (string w : T.search_pre(in)){
            cout<<name_to_integer(w)<<". "<<w<<"\n";
        }
        cout<<"\nCHOOSE A NUMBER: ";
        bool ok2 = false;
        do{
            ok2=false;
            getline(cin,dd);
            if(check_number(dd)) continue;
            else {
            ok2=true;
            cout<<"Enter valid input number..";
            }
        }while(ok2);
        d=stoi(dd);
        cout<<endl<<endl;
        p[i]= d;
    }

    //solution
    system("cls");
    cout<<endl<<endl<<endl;
    cout<<"******  Explore N.C.R ********"<<endl<<endl<<endl;
    cout<<"You can choose this path : "<<endl<<endl;
    f1(s,p,n);
    cout<<endl<<endl;
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

bool check_number(string str) {
   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false)
      return false;
      return true;
}

/* CODE END */
