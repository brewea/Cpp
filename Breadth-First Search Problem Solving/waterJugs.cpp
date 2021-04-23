/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state> > nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

// Fill A and B
void fill(state *iteratingState, state *nextState)
{
	int A = 3, B = 4;
	// Fill A
	*nextState = make_pair(A, iteratingState->second);
	if (iteratingState != nextState)
	{
		nbrs[*iteratingState].push_back(*nextState);
		edge_label[make_pair(*iteratingState, *nextState)] = actions[0];
	}

	// Fill B
	*nextState = make_pair(iteratingState->first, B);
	if (iteratingState != nextState)
	{
		nbrs[*iteratingState].push_back(*nextState);
		edge_label[make_pair(*iteratingState, *nextState)] = actions[1];
	}
}

// Empty A and B
void empty(state *iteratingState, state *nextState)
{
	// Empty A
	*nextState = make_pair(0, iteratingState->second);
	if (iteratingState != nextState)
	{
		nbrs[*iteratingState].push_back(*nextState);
		edge_label[make_pair(*iteratingState, *nextState)] = actions[2];
	}

	// Empty B
	*nextState = make_pair(iteratingState->first, 0);
	if (iteratingState != nextState)
	{
		nbrs[*iteratingState].push_back(*nextState);
		edge_label[make_pair(*iteratingState, *nextState)] = actions[3];
	}
}

// Pour both A into B and B into A
void pour(state *iteratingState, state *nextState, int &A2, int &B2)
{
	int A = 3, B = 4;
	A2 = iteratingState->first;
	B2 = iteratingState->second;

	// A into B
	if (iteratingState->second < B)
	{
		while (A2 > 0 && B2 < B)
		{
			A2--;
			B2++;
		}

		*nextState = make_pair(A2, B2);
		if (iteratingState != nextState)
		{
			nbrs[*iteratingState].push_back(*nextState);
			edge_label[make_pair(*iteratingState, *nextState)] = actions[4];
		}
	}

	// B into A
	A2 = iteratingState->first;
	B2 = iteratingState->second;
	if (iteratingState->first < A)
	{
		while (A2 < A && B2 > 0)
		{
			A2++;
			B2--;
		}

		*nextState = make_pair(A2, B2);
		if (iteratingState != nextState)
		{
			nbrs[*iteratingState].push_back(*nextState);
			edge_label[make_pair(*iteratingState, *nextState)] = actions[5];
		}
	}
}

// Just sends starting states to the changeState function and iterates
void build_graph(void)
{
  //Implement this function
  int A = 3, B = 4;
  int A2, B2;
  state currState = make_pair(0,0);
  state *iteratingState = &currState;
  state nxt;
  state endState = make_pair(A,B);

  
  while (*iteratingState != endState)
  {
		// Fill
		fill(iteratingState, &nxt);

		// Empty
		empty(iteratingState, &nxt);
		
		//Pour
		pour(iteratingState, &nxt, A2, B2);

		// iterate
		if (iteratingState->second == B)
		{
			*iteratingState = make_pair(iteratingState->first + 1, 0);
		}
		else 
		{
			*iteratingState = make_pair(iteratingState->first, iteratingState->second + 1);
		}
  }
  
}

int main(void)
{
  build_graph();

  state start = make_pair(0,0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
  search (start);
  if (visited[make_pair(-1,-1)]) 
    print_path (start, pred[make_pair(-1,-1)]);
  else
    cout << "No path!\n";
  
  return 0;
}
