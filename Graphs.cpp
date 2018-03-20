#include<bits/stdc++.h>
using namespace std;

void DFS(int **edges, int V, bool *isVisited, int sv){
	cout<<sv<<" ";
	isVisited[sv]=1;

	for(int i=0;i<V;i++){
		if(!isVisited[i] && edges[sv][i])
			DFS(edges,V,isVisited,i);
	}
}

void DFS(int **edges, int V){
	bool *isVisited=new bool[V];
	for (int i = 0; i < V; ++i){
		isVisited[i]=0;
	}

	for (int i = 0; i < V; ++i){
		if(!isVisited[i]){
			DFS(edges, V, isVisited, i);
          cout<<endl;
        }
	}

	delete isVisited;
}

void BFS(int **edges, int V, bool *isVisited,int sv){ //sv= starting value
	queue<int> q;
	q.push(sv);
	isVisited[sv]=1;

	while(!q.empty()){
		int frontValue=q.front();
		q.pop();
		cout<<frontValue<<" ";

		for (int i = 0; i < V; ++i){
			if(edges[frontValue][i] && !isVisited[i]){
				isVisited[i]=1;
				q.push(i);
			}
		}
	}
}

void BFS(int **edges, int V){
	bool *isVisited=new bool[V];
	for (int i = 0; i < V; ++i){
		isVisited[i]=0;
	}

	for (int i = 0; i < V; ++i){
		if(!isVisited[i])
			BFS(edges,V,isVisited,i);
	}

}

bool hasPath(int **edges, int V, int sv,int val2, bool *isVisited ){ 
	if(sv==val2)
		return true;

	isVisited[sv]=true;

	for(int i=0;i<V;i++){
		if(edges[sv][i] && !isVisited[i]){
			if(hasPath(edges,V,i,val2,isVisited))
				return true;
		}
	}
	return false;
}

bool hasPath(int **edges, int V, int val1,int val2 ){ 
	bool *isVisited=new bool[V];
	for (int i = 0; i < V; ++i){
		isVisited[i]=0;
	}

	bool ans=hasPath(edges,V,val1,val2,isVisited);
	return ans;
}

bool printPathDFS(int **edges,int V,int sv,int v2, bool *isVisited){
	isVisited[sv]=true;	
	if(sv==v2){
		cout<<sv<<" ";
		return true;
	}	

	bool toPrint=false;
	for (int i = 0; i < V; ++i){
		if(edges[sv][i] && !isVisited[i]){
			if(printPathDFS(edges,V,i,v2,isVisited)){
				toPrint=true;
				break;
			}
		}
	}

	if(toPrint)
		cout<<sv<<" ";

	return toPrint;
}

void printPathDFS(int **edges,int V,int v1,int v2){  
	bool *isVisited=new bool[V];
	for (int i = 0; i < V; ++i){
		isVisited[i]=0;
	}

	//no need to check for different components as we start searching with v1 i.e in specific component if present ok otherwise no path 
	printPathDFS(edges,V,v1,v2,isVisited);

	delete [] isVisited;	
}

void printPathBFS(int **edges,int V,int v1,int v2){  
	bool *isVisited=new bool[V];
	for (int i = 0; i < V; ++i){
		isVisited[i]=0;
	}

	unordered_map<int,int> hash; //value,source
	queue<int> q;
	hash[v1]=v1;
	isVisited[v1]=1;
	q.push(v1);

	bool isFound=false;
	while(!q.empty() && !isFound){
		int element=q.front();
		q.pop();

		for(int i=0;i<V;i++){
			if(edges[element][i] && !isVisited[i]){
				isVisited[i]=1;
				q.push(i);
				hash[i]=element;
				if(i==v2){
					isFound=true;
					break;
				}
			}
		}
	}

	if(isFound){
		int currValue=v2;
		while(currValue!=v1){
			cout<<currValue<<" ";
			currValue=hash[currValue];
		}
		cout << v1;
	}
	delete [] isVisited;	
}

vector<int>* getPathBFS(int** edges, int n, int sv, int ev) {
	queue<int> bfsQ;
	bool * visited = new bool[n];
	for (int i = 0; i < n; i++) {
		visited[i] = false;
	}
	bfsQ.push(sv);
	visited[sv] = true;
	bool done = false;
	unordered_map<int, int> parent;
	while (!bfsQ.empty() && !done) {
		int front = bfsQ.front();
		bfsQ.pop();
		for (int i = 0; i < n; i++) {
			if (edges[front][i] && !visited[i]) {
				parent[i] = front;
				bfsQ.push(i);
				visited[i] = true;
				if (i == ev) {
					done = true;
					break;
				}
			}
		}
	}
	delete [] visited;
	if (!done) {
		return NULL;
	} else {
		vector<int>* output = new vector<int>();
		int current = ev;
		output->push_back(ev);
		while (current != sv) {
			current = parent[current];
			output->push_back(current);
		}
		return output;
	}
}

vector<int>* getPathHelper(int** edges, int n, int sv, int ev, bool* visited) {
	if (sv == ev) {
		vector<int>* output = new vector<int>();
		output->push_back(ev);
		return output;
	}
	visited[sv] = true;
	for (int i = 0; i < n; i++) {
		if (edges[sv][i] && !visited[i]) {
			vector<int>* smallOutput = getPathHelper(edges, n, i, ev, visited);
			if (smallOutput != NULL) {
				smallOutput->push_back(sv);
				return smallOutput;
			}
		}
	}
	return NULL;
}

vector<int>* getPathDFS(int** edges, int n, int sv, int ev) {
	bool * visited = new bool[n];
	for (int i = 0; i < n; i++) {
		visited[i] = false;
	}
	vector<int>* output = getPathHelper(edges, n, sv, ev, visited);
	delete [] visited;
	return output;
}


bool isConnected(int **edges, int V){
	bool *isVisited=new bool[V];
	for (int i = 0; i < V; ++i){
		isVisited[i]=0;
	}
	
	DFS(edges,V,isVisited,0);
	for (int i = 0; i < V; ++i){
		if(!isVisited[i]){
			delete [] isVisited;
			return false;
		}
	}
	delete [] isVisited;
	return true;	
}

void getDFS(int **edges, int V, bool* isVisited, vector<int> *ans,int sv){
	ans->push_back(sv);
	isVisited[sv]=1;

	for (int i = 0; i < V; ++i){
		if(!isVisited[i] && edges[sv][i]){
			getDFS(edges,V,isVisited,ans,i);
		}
	}
}

vector<int>* getDFS(int **edges, int V, bool *isVisited, int sv){
	vector<int> *ans=new vector<int>();;
	getDFS(edges,V,isVisited,ans,sv);
	return ans;
}

vector<vector<int>*>* returnAllComponents(int **edges,int V){
	vector<vector<int>*>* ans=new vector<vector<int>*>();
	bool *isVisited=new bool[V];
	for (int i = 0; i < V; ++i){
		isVisited[i]=0;
	}

	for (int i = 0; i < V; ++i){
		if(!isVisited[i]){
			ans->push_back(getDFS(edges,V,isVisited,i));
		}
	}

	return ans;
}

void printAllComponents(int **edges, int V){
	vector<vector<int>*>* ans=returnAllComponents(edges,V);

	for (int i = 0; i < ans->size(); ++i){
		
		// sort(ans->at(i), ans->at(i) + ans->at(i)->size());
		sort(ans->at(i)->begin(), ans->at(i)->end());

		for (int j = 0; j < ans->at(i)->size(); ++j){
			cout << ans->at(i)->at(j)<<" ";
		}
		cout<<endl;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);    
#ifndef ONLINE_JUDGE
    // for getting input from input.txt
	freopen("input.txt", "r", stdin);
    // for writing output to output.txt
	freopen("output.txt", "w", stdout);
#endif
///////////////////////////////////////////////////////////////////////////////



	int V,E;
	cin>>V>>E;

	int **edges=new int*[V];
	for (int i = 0; i < V; ++i){
		edges[i]=new int[V];
		for (int j = 0; j < V; ++j){
			edges[i][j]=0;
		}
	}

	for (int i = 0; i < E; ++i){
		int f,s;
		cin>>f>>s;
		edges[f][s]=1;
		edges[s][f]=1;
	}
/*
	cout<<"LIST:\n\n";
	for(int i = 0; i < V; i++){
		for(int j = 0; j < V; j++){			
			cout<<edges[i][j]<<" ";
		}
		cout<<endl;
	}
*/

	printAllComponents(edges,V);


//deallocation
	for (int i = 0; i < V; ++i){
		delete [] edges[i];
	}
	delete [] edges;
}