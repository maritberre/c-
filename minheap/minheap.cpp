#include <iostream>
#include <cmath>
#include <assert.h>
using std::cout;
using std::endl;

const int INPUT_SIZE = 10;
const int INITIAL_HEAP_SIZE = 100;

// A simple print function
void print(int *input)
{
    for ( int i = 0; i < INPUT_SIZE; i++ )
        cout << input[i] << " ";
    cout << endl;
}

class Heap 
{
	int *a;
	int capacity;
	int size;

public:
	Heap() {
		a = new int(INITIAL_HEAP_SIZE);
		capacity = INITIAL_HEAP_SIZE;
		size = 0;
	}
	~Heap() {
		delete a;
	}
	
	int parentIdx(int childIdx) {
		return childIdx/2 + (childIdx%2 - 1);
	}

	int leftChildIdx(int parentIdx) {
		return parentIdx*2 + 1;
	}
	
	int rightChildIdx(int parentIdx) {
		return parentIdx*2 + 2;
	}
	
	void swap(int left, int right) {
		assert(left >= 0 && right >= 0);
		int tmp = a[left];
		a[left] = a[right];
		a[right] = tmp;
	}
		
	int insert(int x) {
	
		if (size == capacity) {
			return -1;
		}
	
		a[size] = x;
		size++;
		
		// compare the node with its parent, if smaller than parent, then swap the two		
		int i = size - 1;
		int parentOfI = parentIdx(i); // i's parent
		
		while (i >= 0 && parentOfI >= 0) {
			if (a[i] < a[parentOfI]) {
				swap(i, parentOfI);

				// for subsequent iteration
				i = parentOfI;
				parentOfI = parentIdx(parentOfI);
			} else {
				// done - nothing to be done
				break;
			}
		}
		
		return 0;
	}
	
	int remove() {
		int ret = a[0];
		a[0] = a[size-1];
		size--;
		
		int i = 0;
		int leftChildOfI = leftChildIdx(i);
		int rightChildOfI = rightChildIdx(i);
		
		while(i < size && leftChildOfI < size) {
			if (a[i] > a[rightChildOfI] || a[i] > a[rightChildOfI]) {
				if (a[rightChildOfI] < a[leftChildOfI]) {
					swap(i, rightChildOfI);
					i = rightChildOfI;
				} else { 
					swap(i, leftChildOfI);
					i = leftChildOfI;
				}
				rightChildOfI = rightChildIdx(i);
				leftChildOfI = leftChildIdx(i); 
			} else {
				// done
				break;
			}
		}
		
		return ret;
	}
	
	void print() {
		if (size == 0) {
			cout << "The heap is empty." << endl;
			return;
		}
		cout << "Root: " << a[0] << endl;
		int i = 1;
		int level = 1;
		int total_num_children_at_this_level = 1;
		while (i < size) {
			cout << "Level " << level << ": "; 
			total_num_children_at_this_level *= 2;
			for (int j = 0; j < total_num_children_at_this_level && i < size; j++) {
				cout << a[i++] << " ";
			}
			cout << endl;
			level++;
		}
	}
};


int main()
{
    int input[INPUT_SIZE] = {500, 700, 800, 100, 300, 200, 900, 400, 1000, 600};
	//int input[INPUT_SIZE] = {500, 100, 800, 100, 300, 200, 900, 400, 1000, 600};

	Heap myHeap;
	
	for (int i = 0; i < INPUT_SIZE; i++) {
		myHeap.insert(input[i]);
		cout << endl << "After inserting " << input[i] << ":" << endl;
		myHeap.print();
	}
     
    for (int i = INPUT_SIZE-1; i >= 0; i--) {
		int item_removed = myHeap.remove();
		cout << endl << "After removing " << item_removed << ":" << endl;
		myHeap.print();
	}
     
    cout << "Input:  ";
    print(input);
    cout << "Output: ";
    print(input);
    return 0;
}