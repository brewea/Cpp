/*
 * Name: Carter Brewer
 * Date Submitted: 4/15/2021
 * Assignment Name: MinHeap Implementation Using a Vector
 */

#include <iostream>
#include "minHeap.h"
#include <string>
#include <vector>
#include <math.h>
using namespace std;

minHeap::minHeap(vector<int> data)
{
	int length = data.size();
	int lengthHeap;
	//heap = data;
	for (int i = 0; i < length; ++i)
	{
		heap.push_back(data.at(i));
		//lengthHeap = heap.size();
		//siftUp(lengthHeap-1);
	}
	lengthHeap = heap.size();
	for (int i = lengthHeap-1; i >= 0; i--)
	{
		siftDown(i);
	}
	
}
void minHeap::siftUp(int pos)
{

	if (pos >= 0)
	{
		int parent = floor((pos-1)/2);
		if(heap.at(parent) > heap.at(pos) && pos >= 0 && parent >= 0)
		{
			swap(heap.at(pos), heap.at(parent));
			siftUp(parent);
		}
	}
	
    
}

void minHeap::siftDown(int pos)
{
	int length = heap.size();
	int LChild = 2*pos + 1;
	int RChild = 2*pos + 2;
	int tempM = pos;

	if (LChild < length && heap.at(LChild) < heap.at(pos))
	{
		tempM = LChild;
	}
	if (RChild < length && heap.at(RChild) < heap.at(tempM))
	{
		tempM = RChild;
	}
	if(tempM != pos)
	{
		swap(heap.at(pos), heap.at(tempM));
		siftDown(tempM);
	}
	
}

void minHeap::insert(int value)
{
	
	heap.push_back(value);
	int length = heap.size();
	siftUp(length-1);
}

int minHeap::removeMin()
{
	
	int length = heap.size();
	int root = heap.at(0);
    if(length == 0){ return 0;}
    
	// take last value and put in root
	heap.at(0) = heap.at(length-1);
    heap.pop_back();
	length = heap.size();

	// bubble down
    siftDown(0);
	return root;
}

int main()
{
vector<int> input={1,2,3,4,5,11,12,13,14,15};
vector<int> test={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
vector<int> heapTest;
for (int i=9; i>0; i--) swap(input[i], input[rand()%i]);
minHeap h(input);
h.insert(6);
h.insert(10);
h.insert(7);
h.insert(9);
h.insert(8);
for (int i=0; i<15; i++) heapTest.push_back(h.removeMin());
	return 0;
}
