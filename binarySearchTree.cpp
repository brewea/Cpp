/*
 * Name: Carter Brewer
 * Date Submitted: 26 March 2021	
 * Lab Section: 002
 * Assignment Name: Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

using namespace std;

struct Node {
  int key;
  int size;
  Node *left;
  Node *right;
  Node (int k) { key = k; size = 1; left = right = nullptr; }
};

//-----------------------------------fix_size--------------------------------//
void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

//-----------------------------------*insert--------------------------------//
// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}

//-----------------------------inorder_traversal-----------------------------//
// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr) return inorder;
  inorder=inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs=inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}

//-----------------------------------*find--------------------------------//
// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k)
{
  //Implement Node *find(Node *T, int k)
  if (T != nullptr)
  {
	  if (k < T->key)
	  {
		  T = find(T->left, k);
	  }
	  else if (k > T->key)
	  {
		  T = find(T->right, k);
	  }
  }
	
  return T;
}

//-----------------------------------*select--------------------------------//
// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
	assert(T!=nullptr && r>=0 && r<T->size);
	//Implement Node *select(Node *T, int r)
	int sizeCurrentNode;
	
	if (T->left != nullptr)	
	{
		sizeCurrentNode = T->left->size;
		if (r < sizeCurrentNode){T = select(T->left, r);}
		else if(r > sizeCurrentNode){T = select(T->right, r - sizeCurrentNode - 1);
		}
	}

	else
	{
		sizeCurrentNode = 0;
		if (r < sizeCurrentNode){T = select(T->left, r);}
		else if(r > sizeCurrentNode)
		{
			T = select(T->right, r - sizeCurrentNode - 1);
		}
	}
	return T;
}

//-----------------------------------*join--------------------------------//
// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node *join(Node *L, Node *R)
{
	// choose either the root of L or the root of R to be the root of the joined tree
	// (where we choose with probabilities proportional to the sizes of L and R)
	
	//Implement Node *join(Node *L, Node *R)
	double newRoot = rand() % 101 / 100.0; 
	vector<int> orderedL = inorder_traversal(L);
	vector<int> orderedR = inorder_traversal(R);

	// Right is new Root
	if (newRoot > .5)
	{
		for (int i = 0; i < orderedL.size(); i++)
		{
			R = insert(R, orderedL[i]);
		}
		return R;
	}

	// Left is new root
	else
	{
		for (int i = 0; i < orderedR.size(); i++)
		{
			L = insert(L, orderedR[i]);
		}
		return L;
	}
}

//----------------------------------*remove----------------------------------//
// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
  	assert(T != nullptr);
  
	//Implement Node *remove(Node *T, int k)
	if (T == nullptr)	 { return T;						}
	else if (k < T->key) { T->left = remove(T->left, k); 	}
	else if (k > T->key) { T->right = remove(T->right, k); 	}
	else if (T->left == nullptr)
	{
		Node *holder = T->right;
		delete(T);
		return holder;
	}
	else if (T->right == nullptr)
	{
		Node *holder = T->left;
		delete(T);
		return holder;
	}
	else
	{
		T = join(T->left, T->right);
	}
	T->size--;
	return T;
}

//----------------------------------split------------------------------------//
// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{
	//Implement void split(Node *T, int k, Node **L, Node **R)
	*L = nullptr;
	*R = nullptr;
	if (T == nullptr)	 { cout << "There is nothing here\n"; }
	vector<int> ordered = inorder_traversal(T);

	for (int i = 0; i < ordered.size(); i++)
	{
		if (ordered[i] <= k)
		{
			*L = insert(*L, ordered[i]);
		}
		else if (ordered[i] > k)
		{
			*R = insert(*R, ordered[i]);
		}
	}
}

//------------------------------*insert_random-------------------------------//
// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k)
{
  // If k is the Nth node inserted into T, then:
  // with probability 1/N, insert k at the root of T
  // otherwise, insert_random k recursively left or right of the root of T
  
	//Implement Node *insert_random(Node *T, int k)
	
	if(T != nullptr)
	{
		int randomNum = rand() % T->size;
		// insert using recursion
		if (randomNum != 0)
		{
			T = insert(T, k);
		}

		// new root
		else
		{
			Node *L, *R;
			split(T, k, &L, &R);
			T = insert(T, k);
		}
	}
	else T = insert(T, k);
	return T;
}

//-------------------------------printVector--------------------------------//
void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

//----------------------------------MAIN--------------------------------//
int main(void)
{
  vector<int> inorder;
  vector<int> A(10,0);
  
  // put 0..9 into A[0..9] in random order
  for (int i=0; i<10; i++) {A[i] = i;}
  for (int i=9; i>0; i--) {swap(A[i], A[rand()%i]);}
  cout << "Contents of A (to be inserted into BST):\n";
  printVector(A);
  
  // insert contents of A into a BST
  Node *T = nullptr;
  for (int i=0; i<10; i++) 
  {
	  T = insert(T, A[i]);
  }
  
  // print contents of BST (should be 0..9 in sorted order)
  cout << "Contents of BST (should be 0..9 in sorted order):\n";
  inorder=inorder_traversal(T);
  printVector(inorder);


	cout << "\n\n";
  // test select
  for (int i=0; i<10; i++) 
  {
    Node *result = select(T, i);
    if (!result || result->key != i) 
	{
		cout << "Select test failed for select(" << i << ")!\n";
	}
  }

  // test find: Elements 0..9 should be found; 10 should not be found
  cout << "Elements 0..9 should be found; 10 should not be found:\n";
  for (int i=0; i<11; i++) 
    if (find(T,i)) {cout << i << " found\n";}
    else {cout << i << " not found\n";}

  // test split
  Node *L, *R;
  split(T, 4, &L, &R);
  cout << "Contents of left tree after split (should be 0..4):\n";
  inorder=inorder_traversal(L);
  printVector(inorder);
  cout << "Left tree size " << L->size << "\n";
  cout << "Contents of right tree after split (should be 5..9):\n";
  inorder=inorder_traversal(R);
  printVector(inorder);
  cout << "Right tree size " << R->size << "\n";
    
  // test join
  T = join(L, R);
  cout << "Contents of re-joined tree (should be 0..9)\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  cout << "Tree size " << T->size << "\n";
  
  // test remove
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  for (int i=0; i<10; i++) 
  {
    T = remove(T, A[i]);
    cout << "Contents of tree after removing " << A[i] << ":\n";
    inorder=inorder_traversal(T);
    printVector(inorder);
    if (T != nullptr)
      cout << "Tree size " << T->size << "\n";
  }

  // test insert_random
  cout << "Inserting 1 million elements in order; this should be very fast...\n";
  for (int i=0; i<1000000; i++) T = insert_random(T, i);
  cout << "Tree size " << T->size << "\n";
  cout << "Done\n";
  
  return 0;
}
