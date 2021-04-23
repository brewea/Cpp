#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type

// GENERIC -- these shouldn't need to be changed...
unordered_map<string, bool> 		   visited;// have we queued up this state?
unordered_map<string, string> 		   pred;  // predecessor state we came from
unordered_map<string, int> 			   dist;  // distance from source node
unordered_map<string, vector<string> > nbrs;  // vector of neighboring states


//Implement breadth-first search, refer to Lab 10
// GENERIC (breadth-first search, outward from source_node)
void search(string &source_node)
{
  queue<string> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
	while (!to_visit.empty()) 
	{
		string curnode = to_visit.front();
		to_visit.pop();
		for (string n : nbrs[curnode])
		{
			if (!visited[n]) 
			{
				pred[n] = curnode;
				dist[n] = 1 + dist[curnode];
				visited[n] = true;
				to_visit.push(n);	
			}	
		}
	}
}

void createGraph(void)
{
	ifstream file("wordlist05.txt");
	string temp;

	while (file >> temp)
	{
		V.push_back(temp);
	}

	for (string word : V)
	{
		for (int i = 0; i < word.length(); i++)
		{
			for (char j = 'a'; j <= 'z'; j++)
			{
				temp = word;
				temp.at(i) = j;
				nbrs[word].push_back(temp);
			}
		}
	}
}

int makePath(string &s, string &t, int &steps, vector<string> &p)
{
	if (pred.find(t) == pred.end())	{return 0;}
	
	if (s.compare(t) != 0)
	{
		steps = 1 + makePath(s, pred[t], steps, p);
		p.push_back(t);
		return steps;
	}
	else
	{
		p.push_back(t);
		return 0;
	}
}

void wordLadder(string s, string t, int &steps, vector<string> &p)
{
	//Implement this function
	createGraph();
	search(s);
	steps = makePath(s,t,steps,p);
}



int main(void)
{
	int steps = 0;
	string s, t;
	vector<string> path;

	cout << "Source: ";
	cin >> s;

	cout << "Target: ";
	cin >> t;

	wordLadder(s, t, steps, path);

	if (steps == 0)
	{
		cout << "No path!\n";
	}
	else
	{
		cout << "Steps: " << steps << "\n\n";
		for (int i=0; i<path.size(); i++)
		{
			cout << path[i] << endl;
		}
	}
	return 0;
}
