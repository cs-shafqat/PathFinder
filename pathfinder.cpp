#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <stdlib.h>

using namespace std;

const int IDIM = 10; // horizontal size of the squares
const int JDIM = 10; // vertical size size of the squares
const int NDIR = 4; // number of possible directions to go at any position
const int MAX_SPEED = 20; // Max speed of Car
int speed = 0; // initial speed of car
int nextSpeed; // speed calculation for next node.

// NDIR = 4
const int iDir[NDIR] = {1, 0, -1, 0};
const int jDir[NDIR] = {0, 1, 0, -1};

//2D square matrix
int squares[IDIM][JDIM] ={
		                    {0,0,0,1,0,0,1,0,0,0},
		                    {0,1,0,0,1,1,1,0,0,0},
		                    {1,0,0,0,0,0,0,0,0,0},
		                    {0,0,0,0,1,0,0,0,0,0},
		                    {0,0,0,0,0,1,0,0,0,1},
		                    {0,0,1,0,0,0,0,0,1,0},
		                    {0,1,0,0,0,1,0,0,0,1},
		                    {1,0,0,0,1,0,0,0,0,0},
		                    {0,0,0,0,1,0,0,1,0,0},
		                    {0,0,1,0,0,0,1,0,0,1}
 		                    };

// list of closed (check-out) nodes
int closedNodes[IDIM][JDIM];

// list of open (not-yet-checked-out) nodes
int openNodes[IDIM][JDIM];

// map of directions (0: East, 1: North, 2: West, 3: South) 
int dirMap[IDIM][JDIM];

// starting and ending positions
int iStart,jStart;
int iEnd,jEnd;
int flag=1,flag1=1;

// random function
int random_value()
{
	int x = ( rand() * rand() ) % 9;
	return (x>=0)?x:-x;
}

// Initialize static process
void static_initial()
{
	// print square
	cout<<endl;
    for(int i = 0; i < IDIM; i++) {
        for(int j = 0; j < JDIM; j++) {
            cout<< squares[i][j]<<"  " ;
        }
        cout<<endl;
    }
	cout<<endl;
	//flag will true for first time and then false
	if(flag)
	{
		cout <<"enter source x-cordinates ";
		cin >> iStart;
		cout <<"enter source y-cordinates ";
		cin >> jStart;
	}
	else
	{
		if(flag1)
		{
			iStart = iEnd;
			jStart = jEnd;
		}
		else
		{
			flag1=1;
		}
	}
	
	//if source is blocked
	while(squares[iStart][jStart] == 1)
	{
		cout<< "This source is blocked, Once Again"<<endl;
		cout <<"enter source x-cordinates ";
		cin >> iStart;
		cout <<"enter source y-cordinates ";
		cin >> jStart;
	}
	cout <<"enter destination x-cordinates ";
	cin >> iEnd;
	cout <<"enter destination y-cordinates ";
	cin >> jEnd;
	
	//if Destination is blocked 
	while(squares[iEnd][jEnd] == 1)
	{
		cout<< "This destination is blocked, Once Again"<<endl;
		cout <<"enter destination x-cordinates ";
		cin >> iEnd;
		cout <<"enter destination y-cordinates ";
		cin >> jEnd;
	}
	
	//source and destination can not be equal
	while(iEnd == iStart && jEnd == jStart)
	{
		cout<< "source and destination can not be equal, Once Again"<<endl;
		cout <<"enter destination x-cordinates ";
		cin >> iEnd;
		cout <<"enter destination y-cordinates ";
		cin >> jEnd;
	}
	
	return;
} 
// Initialize dynamic process
void dynamic_initial()
{
	int i,j,n=0;
	
	// reset the Node lists (0)
    for(j = 0; j < JDIM; j++) {
        for(i = 0; i < IDIM; i++) {
            squares[i][j] = 0;
        }
    }
    //flag will true for first time and then false.
    if(flag)
	{
		iStart = random_value();
		jStart = random_value();
	}
	else
	{
		if(flag1)
		{
			iStart = iEnd;
			jStart = jEnd;
		}
		else
		{
			flag1=1;
		}
	}
	
	//ensure that source and destination are not equal.
	do
	{
		iEnd   = random_value();
		jEnd   = random_value();
	}
	while(iEnd == iStart && jEnd == jStart);
	
	//create 20 obstacles randomly for dynamic process.
	while(n < 20)
	{
		i = random_value();
	    j = random_value();
	    if(!((i == iStart && j == jStart) || (i == iEnd && j == jEnd)))
	     {
			 if(squares[i][j] == 0)
			 {
				squares[i][j] = 1;
				n++;
			 }
		 }
	}
}
 // speed calculation function
void spead_func(string path, int n = -1, int pos = -1)
{
	if(pos == -1) // initially speed at source node
	{
		nextSpeed = 5;
	}
	else if((unsigned)pos+1 == path.length()) // speed at destination
	{
		nextSpeed = 0;
	}
	else  // Calculate increase/decrease of speed with respect to nodes
	{
		char c = path.at(pos+1);
		int n1 = atoi(&c);
		if(n == n1)
		{
			if(speed == MAX_SPEED)
			{
				nextSpeed = speed;
			}
			else
			{
				nextSpeed += 5;
			}
		}
		else
		{
			nextSpeed = 5;
		}
	}
	cout<< "Speed : "<<speed<<" -> "<<nextSpeed<<endl;
	speed = nextSpeed; // updated speed
}

//Print funcion
void pathPrint(string path, int f=1)
{
	cout <<endl<< "Grid Size (IDIM,JDIM): "<< IDIM<< "," << JDIM << endl;
    cout << "Start: " << iStart<<","<< jStart << endl;
    cout << "Finish: " << iEnd<<","<< jEnd << endl;
    if(f)
    {
		cout<<endl;
		for(int i = 0; i < IDIM; i++) {
			for(int j = 0; j < JDIM; j++) {
				cout<< squares[i][j]<<"  " ;
			}
			cout<<endl;
		}
	}
	
	cout<<endl;
	
	//check whether path is block or not.
	if(path == "")
	{
		cout<< "Path is Blocked means There is no path to reach destination\n\n";
		flag1=0;
	}
	else
	{
		cout << "map of directions (0: East, 1: North, 2: West, 3: South) \n";
		cout << "path: " << path << endl;
		unsigned int m;
		int n;
		char c;
		int i = iStart;
		int j = jStart;
		f =0;
		//print path according to east,west, north and south
		for(m = 0; m <= path.length(); m++)
		{
			if(f == 0)
			{
				cout <<endl<< "--> ("<<i<<" , "<<j<<" ) \t";
				spead_func(path);
				f = 1;
			}
			else
			{
				c = path.at(m-1);
				n = atoi(&c);
				if(n == 0)
				{
					i+=iDir[0];
					j+=jDir[0];
					cout << "--> ("<<i<<" , "<<j<<" ) \t";
					spead_func(path, n, m-1);
				}
				else if(n == 1)
				{
					i+=iDir[1];
					j+=jDir[1];
					cout << "--> ("<<i<<" , "<<j<<" ) \t";
					spead_func(path, n, m-1);
				}
				else if(n == 2)
				{
					i+=iDir[2];
					j+=jDir[2];
					cout << "--> ("<<i<<" , "<<j<<" ) \t";
					spead_func(path, n, m-1);
				}
				else if(n == 3)
				{
					i+=iDir[3];
					j+=jDir[3];
					cout << "--> ("<<i<<" , "<<j<<" ) \t";
					spead_func(path, n, m-1);
				}
			}
		}
	}
	return;
}

struct Location
{
    int row, col;

    Location()
    {
        row = col = 0;
    };

    Location(int r, int c)
    {
        row = r;
        col = c;
    };
};


class Node
{
    // current position
    int rPos;
    int cPos;

    // total distance already travelled to reach the node
    int GValue;

    // FValue = GValue + remaining distance estimate
    int FValue;  // smaller FValue gets priority

    public:
        Node(const Location &loc, int g, int f) 
            {rPos = loc.row; cPos = loc.col; GValue = g; FValue = f;}
    
		Location getLocation() const {return Location(rPos,cPos);}
        int getGValue() const {return GValue;}
        int getFValue() const {return FValue;}

        void calculateFValue(const Location& locDest)
        {
             FValue = GValue + getHValue(locDest) * 10; 
        }

        
        void updateGValue(const int & i) // i: direction
        {
            GValue += 10;
        }
        
        // Estimation function for the remaining distance to the goal.
        const int & getHValue(const Location& locDest) const
        {
            static int rd, cd, d;
            rd = locDest.row - rPos;
            cd = locDest.col - cPos;         

            // Manhattan distance
            d = abs(rd) + abs(cd);
            return(d);
        }

	// Determine FValue (in the priority queue)
	friend bool operator<(const Node & a, const Node & b)
	{
	    return a.getFValue() > b.getFValue();
	}
};

                       // A-star algorithm
                                           
                                           
// The path returned is a string of direction digits.
string pathFind( const Location &locStart, const Location &locFinish)
{
    // list of open (not-yet-checked-out) nodes
    static priority_queue<Node> q[2]; 

    // q index
    static int qi; 

    static Node* pNode1;
    static Node* pNode2;
    static int i, j, row, col, iNext, jNext;
    static char c;
    qi = 0;

    // reset the Node lists (0 = ".")
    for(j = 0; j < JDIM; j++) {
        for(i = 0; i < IDIM; i++) {
            closedNodes[i][j] = 0;
            openNodes[i][j] = 0;
        }
    }

    // create the start node and push into list of open nodes
    pNode1 = new Node(locStart, 0, 0); 
    pNode1->calculateFValue(locFinish);    
    q[qi].push(*pNode1);
 
    // A* search
    while(!q[qi].empty()) {
        // get the current node w/ the lowest FValue
        // from the list of open nodes
        pNode1 = new Node( q[qi].top().getLocation(), 
                     q[qi].top().getGValue(), q[qi].top().getFValue());

        row = (pNode1->getLocation()).row; 
	col = pNode1->getLocation().col;
	//cout << "row, col=" << row << "," << col << endl;

	// remove the node from the open list
        q[qi].pop(); 
        openNodes[row][col] = 0;

        // mark it on the closed nodes list
        closedNodes[row][col] = 1;

        // stop searching when the goal state is reached
        if(row == locFinish.row && col == locFinish.col) {
		
		cout << endl;

	    // generate the path from finish to start from dirMap
            string path = "";
            while(!(row == locStart.row && col == locStart.col)) {
                j = dirMap[row][col];
                c = '0' + (j + NDIR/2) % NDIR;
                path = c + path;
                row += iDir[j];
                col += jDir[j];
            }

            // garbage collection
            delete pNode1;

            // empty the leftover nodes
            while(!q[qi].empty()) q[qi].pop();           
            return path;
        }

        // generate moves in all possible directions
        for(i = 0; i < NDIR; i++) {
            iNext = row + iDir[i]; 
	    jNext = col + jDir[i];

	    // if not wall (obstacle) nor in the closed list
            if(!(iNext < 0 || iNext > IDIM - 1 || jNext < 0 || jNext > JDIM - 1 || 
			squares[iNext][jNext] == 1 || closedNodes[iNext][jNext] == 1)) {
               
		// generate a child node
                pNode2 = new Node( Location(iNext, jNext), pNode1->getGValue(), pNode1->getFValue());
                pNode2->updateGValue(i);
                pNode2->calculateFValue(locFinish);

                // if it is not in the open list then add into that
                if(openNodes[iNext][jNext] == 0) {
                    openNodes[iNext][jNext] = pNode2->getFValue();
                    q[qi].push(*pNode2);
                    // mark its parent node direction
                    dirMap[iNext][jNext] = (i + NDIR/2) % NDIR;
                }

		// already in the open list
                else if(openNodes[iNext][jNext] > pNode2->getFValue()) {
                    // update the FValue info
                    openNodes[iNext][jNext] = pNode2->getFValue();

                    // update the parent direction info,  mark its parent node direction
                    dirMap[iNext][jNext] = (i + NDIR/2) % NDIR;

                    // replace the node by emptying one q to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(q[qi].top().getLocation().row == iNext && 
                        q[qi].top().getLocation().col == jNext)) {                
                        q[1 - qi].push(q[qi].top());
                        q[qi].pop();       
                    }

		    // remove the wanted node
                    q[qi].pop(); 
                    
                    // empty the larger size q to the smaller one
                    if(q[qi].size() > q[1 - qi].size()) qi = 1 - qi;
                    while(!q[qi].empty()) {                
                        q[1 - qi].push(q[qi].top());
                        q[qi].pop();       
                    }
                    qi = 1 - qi;

		    // add the better node instead
                    q[qi].push(*pNode2); 
                }
                else delete pNode2; 
            }
        }
        delete pNode1; 
    }
    // no path found
    return ""; 
}
//Function for writing path in file
void writePath(int a, int b, int x, int y, string p)
{
	fstream file; 
	file.open("path.txt",ios::out|ios::app);
	
	file<<a<<endl //source x co-ordinate
		<<b<<endl //source y co-ordinate
		<<x<<endl //Target x co-ordinate
		<<y<<endl //Target y co-ordinate
		<<p<<endl;//write the path
		
    file.close();
	return;
}
// Search path from function
string searchPath(int a1, int b1, int x1, int y1)
{
	string p;
	char data[2];
	int a,b,x,y;

	fstream file;
	file.open("path.txt",ios::in);
	if(file) //check whether file exist or not.
	{
		//search from whole file
		while(!file.eof())
		{
			file.getline(data,2);
			a = atoi(data);
			file.getline(data,2);
			b = atoi(data);
			file.getline(data,2);
			x = atoi(data);
			file.getline(data,2);
			y = atoi(data);
			getline(file,p);
			if(a==a1 && b==b1 && x==x1 && y==y1)
			{
				//no path is given to go toward target
				if(p == "")
				{
					return "yes";
				}
				return p;
			}
		}
	}
	
   	file.close();
	return "";
}

int main()
{
	char option,q;
	cout<< "Enter (s) for Static or (d) for Dynamic:",
	cin>> option;
	
	
	if(option == 's' || option == 'S')
	{
		do
		{
			static_initial();
			
			string path = searchPath(iStart, jStart, iEnd, jEnd);
			if(path == "")
			{
				// get the path
				path = pathFind(Location(iStart, jStart), Location(iEnd, jEnd));
				pathPrint(path,0);
				writePath(iStart, jStart,iEnd, jEnd,path);
			}
			else if(path == "yes")
			{
				pathPrint("",0);
				cout<<"\n path is already saved, BUT no path \n";
			}
			else
			{
				pathPrint(path,0);
				cout<<"\n path is already saved \n"; 
			}
			
			flag = 0;
			cout<< "\nif you want to continue press 'y' else 'n' : ",
			cin>> q;
		}
		while(q == 'y' || q == 'Y');
	}
	else if(option == 'd' || option == 'D')
	{
		do
		{
			dynamic_initial();
			// get the path
			string path = pathFind(Location(iStart, jStart), Location(iEnd, jEnd));
			
			pathPrint(path);
			flag = 0;
			cout<< "\nif you want to continue press 'y' else 'n' : ",
			cin>> q;
		}
		while(q == 'y' || q == 'Y');
	}
	else
	{
		cout<< "Wrong input.";
	}

    return(0);
}
