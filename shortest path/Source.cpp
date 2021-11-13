#include<iostream>
#include<conio.h>
#include<fstream>
#include<vector>
#include<Windows.h>
using namespace std;
void gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE != hConsole)
	{
		pos.X = x;
		pos.Y = y;

		SetConsoleCursorPosition(hConsole, pos);
	}
}
class Vertex
{
public:
	Vertex(int, int, Vertex, Vertex);
	Vertex(int, int,int vn =-1);
	Vertex();
	Vertex* getNext(){ return next; }
	void setNext(Vertex*n){ next = n; }
	int getrowNumber(){ return rowNumber; }
	int getcolumnNumber(){ return columnNumber; }
	int getVertexNo(){ return VertexNo; }
	int getDistance(){ return distance; }
	string getColor(){ return color; }
	int getParent(){ return parent; }
	void setDistance(int d){ distance = d; }
	void setColor(string c){ color = c; }
	void setParent(int p){ parent = p; }
	void setInfo(int r, int c, int vn){ rowNumber = r; columnNumber = c; VertexNo = vn; }
private:
	int rowNumber;
	int columnNumber;
	int VertexNo;
	Vertex *next;
	int parent;
	string color;
	int distance;
};
class LinkList{
public:
	LinkList();
	void addToList(int, int, int);
	Vertex *first;
	Vertex *endP;

};
LinkList::LinkList(){
	endP = new Vertex();
	first = new Vertex();
}
void LinkList::addToList(int i, int j, int k){
	Vertex* temp = new Vertex(i, j, k);
	endP->setNext(temp);
	endP = endP->getNext();
	
}
class Map {
	friend class Graph;
private:
	int rowMap;
	int columnMap;


public:
	void setSize(int, int);
	char	**map;
	Map(int row, int column);
	void readMap(int row, int column);
	void findPath(int,int, Graph &);
	bool printPath(int s, int v, Graph& g,int n,vector<int>&);
	void printMap(int,int);
	void printMap2(int, int);
 	void showPath(vector<int>, Graph& g);
};
class Graph{
	friend class LinkedList;
public:
	Graph(int );
	LinkList *lists;
	void creatAdjacencyLists(int, int, Map &);
};
Graph::Graph( int n){
	lists = new LinkList[n];

}
class Queue
{
public:
	Queue(int);
	~Queue();
	bool isFull();
	bool isEmpty();
	bool enQueue(Vertex);
	Vertex dequeue();
	void printelement();

private:
	Vertex *queue;
	int size;
	int head;
	int tail;

};
Queue::Queue(int s =100)
{
	size = s+1;
	head = 0;
	tail = 0;
	queue = new Vertex[size];
}
Queue::~Queue()
{

}
bool Queue::isFull(){
	//if (size == tail + 1)
	if (head==(tail+1)%size)
		return true;
	else return false;

}
bool Queue::isEmpty(){
	if (head == tail)
		return true;
	else return false;

}
bool Queue::enQueue(Vertex element){
	if (!isFull()){
		queue[tail] = element;
		tail = (tail + 1) % size;
		return true;
	}
	else return false;

}
Vertex Queue::dequeue(){
	Vertex result;
	if (!isEmpty()){
		result = queue[head];
		head = (head + 1)%size;
	}
		return result;

	
}
Vertex::Vertex(int r,int c,int vn )
{
	VertexNo = vn;
	rowNumber = r;
	columnNumber = c;
	next = NULL;
	parent = -1;
	color = "white";
	distance = 10000000000;
}
Vertex::Vertex(){
	rowNumber = -1;
	columnNumber = -1;
	VertexNo = -1;
	next = NULL;
	parent = -1;
	color = "white";
	distance = 1000000000;

}
Map::Map(int r, int c){
	rowMap = r;
	columnMap = c;
map= new  char *[c+2];
for (int i = 0; i <=c+2; i++)
	map[i] = new char [r+2];
}
void Map::setSize(int r, int c){
	rowMap = r;
	columnMap = c;
}
void Map::readMap( int row,int column){
	ifstream rFile1("map1.txt", ios::in);
	int temp;
	for (int i = 1; i <= row; i++){
		for (int j = 1; j <= column; j++){
			rFile1 >> temp;
			if (temp == 3 || temp == 1 || temp ==17)
				temp = '.';
			else temp = '#';
			map[i][j]=(char)temp;
		}
	}
	for (int i = 0; i <= row+1; i++){
		map[i][0] ='#';
		map[i][column + 1] = '#';
	}
	for (int i = 0; i <= column + 1; i++){
		map[0][i] = '#';
		map[row + 1][i] = '#';

	}
}
void Map::showPath(vector<int> p, Graph& g){
	int n = p.size();
	for (int i =n-1; i>=0; i--){
		gotoxy(g.lists[p[i]].first->getcolumnNumber(), g.lists[p[i]].first->getrowNumber());
		Sleep(200);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << "*";
	}

}
void Graph::creatAdjacencyLists(int row, int column,Map & m){
	 int k = 1;
	 int VtxNo;
		for (int i = 1; i <= row; i++){
			for (int j = 1; j <= column; j++){
				LinkList l;
				if (m.map[i][j] != '#' ){
					l.first->setInfo(i, j, k);
					l.endP = l.first;
					if (m.map[i][j + 1] !='#') {
						VtxNo = (i - 1)*column + j + 1;
						l.addToList(i, j + 1, VtxNo);
					

					}
					if (m.map[i + 1][j] != '#'){
						VtxNo = (i)*column + j;
						l.addToList(i + 1, j, VtxNo);
					

					}
					
					if (m.map[i - 1][j] != '#' ){

						VtxNo = (i - 2)*column + j;
						l.addToList(i - 1, j, VtxNo);
					
					}
					
					if (m.map[i][j - 1] != '#' ){

						VtxNo = (i - 1)*column + j - 1;
						l.addToList(i, j - 1, VtxNo);
					}

					lists[k] = l;
				}
				k++;
			}
			
		}
}
void Map::findPath(int s,int e,Graph& g){

	Vertex u;
	g.lists[s].first->setDistance(0);
	g.lists[s].first->setParent(-1);
	if (g.lists[s].first->getVertexNo() == -1){
		 cout << "The coordinates are an obstacle";
		 return;
	}
	Queue queue(rowMap*columnMap);
	queue.enQueue(*(g.lists[s]).first);
	
	while (!queue.isEmpty()){

		u = queue.dequeue();

		int uNo = u.getVertexNo();
		Vertex v = u;
		while (v.getNext() != NULL){
			v = *v.getNext();
			int vNo = v.getVertexNo();
			if (g.lists[vNo].first->getColor() == "white"){
				g.lists[vNo].first->setColor("Gray");
				g.lists[vNo].first->setDistance(u.getDistance() + 1);

				g.lists[vNo].first->setParent(uNo);
				if (vNo == e)
					return;
				queue.enQueue(*g.lists[vNo].first);
			}
			
		}
		g.lists[u.getVertexNo()].first->setColor("black");
	}
}
 bool Map::printPath(int s, int v, Graph& g, int n, vector <int> &p){
	if (s == v){
		cout << s<<" ";
		p[0] = s;
	}
	else if (g.lists[v].first->getParent() == -1){
		if (g.lists[v].first->getVertexNo() == -1){
			cout << "The coordinates are an obstacle"<<endl;
			return false;
		}
		else{
			cout << "not path from" << s << "to" << v<<endl;
			return false;
		}
	}
	else{
		p.resize(n+1);
		printPath(s, g.lists[g.lists[v].first->getParent()].first->getVertexNo(), g,n+1,p);
		cout << v<<" ";
		p[n] = v;
		return true;
	}
	
}
void Map:: printMap(int rowMax,int columnMax){
	map[rowMax - 1][columnMax - 1] = '.';
	cout << "\t ";
for (int i = 0; i <= columnMax; i++)
	cout << i%10;
	cout << endl;
	for (int i = 0; i <= rowMax+1; i++){
	cout << i<<"\t";
		for (int j = 0; j <= columnMax+1; j++){
			cout <<map[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
void Map::printMap2(int rowMax, int columnMax){
	map[rowMax - 1][columnMax - 1] = '.';
	
	for (int i = 0; i <= rowMax + 1; i++){
		
		for (int j = 0; j <= columnMax + 1; j++){
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
void main(){
	vector <int>p(2, -1);
	vector<int> path;
	bool eP = true;
	int X1, Y1, VertexNo1,VertexNo2,X2,Y2;
	int row; int column;
	cout << "enter row"<<endl;
	cin >> row;
	cout << endl;
	cout << "enter column" << endl;
		cin >> column;
	cout << endl;
	Graph graph(row*column);
	Map m(row, column);
	int n = row*column;
	m.readMap(row, column);
	m.printMap(row, column);
	cout << "Please enter your starting point coordinates" << endl;
	cin >> X1 >> Y1;
	VertexNo1 = (X1 - 1)*column + Y1;
	cout << "Please enter the coordinates of the end point" << endl;
	cin >> X2 >> Y2;
	VertexNo2 = (X2 - 1)*column + Y2;
	_getch();
	system("cls");
	//m.readMap(row, column);
	m.printMap2(row, column);
	graph.creatAdjacencyLists(row, column,m);
	m.findPath(VertexNo1,VertexNo2, graph);
 eP=m.printPath(VertexNo1, VertexNo2, graph,1,p);
if (eP==true)
	m.showPath(p, graph);
	_getch();
}