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
#include <bitset>
using namespace std;

// Reflects what each node represents...
// int with each bit == 0 left of river, bit == 1 right of river
typedef int state;

// Bit position representation for wolf/goat/cabbage/me
bool bit(int x, int i) { return (x>>i) & 1; }
const int wolf=0, goat=1, cabbage=2, me=3;

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state> > nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from curnode)
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
      if (!visited[n]) 
      {
        pred[n] = curnode;
        dist[n] = 1 + dist[curnode];
        visited[n] = true;
        to_visit.push(n);
      }
  }
}

string state_string(state s)
{
  string items[4] = { "wolf", "goat", "cabbage", "you" }, result = "";
  for (int i=0; i<4; i++)
    if (!bit(s, i)) result += items[i] + " ";
  result += " |river| ";
  for (int i=0; i<4; i++)
    if (bit(s, i)) result += items[i] + " ";
  return result;
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << state_string(t) << "\n";
  } else {
    cout << "Initial state: " << state_string(s) << "\n";
  }
}

string neighbor_label(int s, int t)
{
  string items[3] = { "wolf", "goat", "cabbage" }, which_cross;
  if (bit(s,me) == bit(t,me)) return "must cross river";  // must cross river
  int cross_with = 0;
  for (int i=0; i<3; i++) {
    if (bit(s,i) != bit(t,i) && bit(s,i)==bit(s,me)) { cross_with++; which_cross = items[i]; }
    if (bit(s,i) != bit(t,i) && bit(s,i)!=bit(s,me)) return "";
  }
  if (cross_with > 1) return "";
  if (cross_with == 0) return "Cross alone";
  else return "Cross with " + which_cross;
}

// make sure nobody gets eaten
int allowedCrossing(bitset<4> item)
{
  
  if (item[wolf] == item[goat])
  {
    if (item[me] == item[wolf] && item[me] == item[goat])
    {
      return 1;
    }
  }

  
  else if (item[goat] == item[cabbage])
  {
    
    if (item[me] == item[goat] && item[me] == item[cabbage])
    {
      return 1;
    }
  }
  else return 1;
  return 0;
  
}
void build_graph(void)
{
  //Implement this function

  // Setup states using bitset for ease of access and bitset functions
  bitset<4> startingBitSet("0000");
  bitset<4> bitSetIterator;
  bitset<4> endingBitSet("1111");
  bitset<4> nextBitSet;

  int currentState, nxtState; 

  // Cycle through different variations
  while (bitSetIterator != endingBitSet)
  {
    for (int i = 0; i < 4; i++)
    {
      if (bitSetIterator[me] == bitSetIterator[i])
      {
        nextBitSet = bitSetIterator;

        // Literally flips the bitset / i.e. 0001 -> 1000
        nextBitSet[me].flip();

        if (i != me){nextBitSet[i].flip();}

        // Make sure nobody gets eaten. If its safe....
        if (allowedCrossing(nextBitSet))
        {

          //to_ulong does the math to change a bitset back to an int
          currentState = bitSetIterator.to_ulong();
          nxtState = nextBitSet.to_ulong();
          nbrs[currentState].push_back(nxtState);
          edge_label[make_pair(currentState, nxtState)] = neighbor_label(currentState,nxtState);
        }
      }
    }
    // Go to next state
    bitSetIterator = bitSetIterator.to_ulong() + 1;
  }
}

int main(void)
{
  build_graph();

  state start = 0, end = 15;
  // cout << "\n\nMAIN PRINTOUT BELOW" << endl;
  search(start);
  if (visited[end])
    print_path (start, end);
  else
    cout << "No path!\n";
  
  return 0;
}
