#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP 100
typedef char Data;
typedef struct {
	Data data;
	int priority;
} HNode;
typedef struct {
	HNode items[MAX_HEAP + 1];
	int num;//힙 노드 갯수
} Heap;
// Make a heap empty.
void InitHeap(Heap * pheap);
// check whether a heap is empty.
bool IsEmpty(Heap* pheap);
// Check whether a heap is full.
bool IsFull(Heap* pheap);
// Insert a node to the heap.
void Insert(Heap* pheap, Data data, int priority);
// Remove the maximum data from the heap.
Data Delete(Heap* pheap);
// Get a parent index for a given index.
int GetParent(int idx);
// Get a left child index for a given index.
int GetLChild(int idx);
// Get a right child index for a given index.
int GetRChild(int idx);
// Get a child index with high priority between two child nodes.
int GetHighPrioityChild(Heap* pheap, int idx);
// Make a heap empty.
void InitHeap(Heap* pheap)
{
	pheap->num = 0;
}
// check whether a heap is empty.
bool IsEmpty(Heap* pheap)
{
	return pheap->num == 0;
}
// Check whether a heap is full.
bool IsFull(Heap* pheap)
{
	return pheap->num == MAX_HEAP;
}
void Insert(Heap* pheap, Data data, int priority)
{
	HNode newNode;
	int idx = pheap->num + 1;
	if (IsFull(pheap)) exit(1);
	// Compare the new node with its parent.
	while (idx > 1) {
		int parent = GetParent(idx);
		if (priority > pheap->items[parent].priority) {
			pheap->items[idx] = pheap->items[parent];
			idx = parent;
		}
		else break;
	}
	newNode.data = data;
	newNode.priority = priority;
	pheap->items[idx] = newNode;
	pheap->num++;
}
Data Delete(Heap* pheap)//힙의 최댓값을 삭제하는 함수
{
	Data max = pheap->items[1].data;
	HNode last = pheap->items[pheap->num];
	int parent = 1, child;
	// Compare the root with its child nodes.
	while (child = GetHighPrioityChild(pheap, parent)) {
		if (last.priority < pheap->items[child].priority) {
			pheap->items[parent] = pheap->items[child];
			parent = child;
		}
		else break;
	}
	pheap->items[parent] = last;
	pheap->num--;
	return max;
}
int GetHighPrioityChild(Heap* pheap, int idx)
{
	if (GetLChild(idx) > pheap->num) // No child nodes exist.
		return 0;
	else if (GetLChild(idx) == pheap->num) // Exist a left child only.
		return GetLChild(idx);
	else // Choose a child node with the highest priority.
	{
		int left = GetLChild(idx), right = GetRChild(idx);
		if (pheap->items[left].priority > pheap->items[right].priority)
			return left;
		else
			return right;
	}
}
// Get a parent index for a given index.
int GetParent(int idx)
{
	return idx / 2;
}
// Get a left child index for a given index.
int GetLChild(int idx)
{
	return idx * 2;
}
// Get a right child index for a given index.
int GetRChild(int idx)
{
	return idx * 2 + 1;
}
    return node;
}
void inorder(btnode* node) {
    btnode* cur = leftmost(node);
    while (cur != NULL) {
        printf("%d ", cur->item);
        if (cur->istheaded) cur = cur->right_child;
        else {
            cur = leftmost(cur->right_child);
        }
    }
}
