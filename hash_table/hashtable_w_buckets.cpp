#include <iostream>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::for_each;

const int NUM_BUCKETS=10;

class HashTable {

	struct Item {
		int key;
		int val;
	};
	
	struct Bucket {
		vector<Item> items;
	};

	Bucket table[NUM_BUCKETS];
	
	int primaryHash(int key) {
		return key % NUM_BUCKETS;
	}
		
	public:
	HashTable() {
	}
		
	void insert(int key, int val) {
		
		Item item;
		item.key = key;
		item.val = val;
		
		if (key < 0) {
			// assert or log error
			return;
		}
		
		int hash = primaryHash(key);
		table[hash].items.push_back(item);
	}

	int lookup(int key) {
		int hash = primaryHash(key);
		int ret = -1;
		
		for (auto it = table[hash].items.begin(); it != table[hash].items.end(); it++) {
			if (it->key == key) {
				ret = it->val;
				break;
			}
		}
		return ret;	
	}

	
	int remove(int key) {
		int hash = primaryHash(key);
		int ret = -1;
		for (auto it = table[hash].items.begin(); it != table[hash].items.end(); it++) {
			if (it->key == key) {
				ret = it->val;
				table[hash].items.erase(it);
				break;
			}
		}
		return ret;
	}
	
	void print() {
		for (int i = 0; i < NUM_BUCKETS; i++) {
			if(table[i].items.size() == 0) {
				continue;
			}
			cout << "Stored in bucket " << i << ": " << endl;
			for (auto it = table[i].items.begin(); it != table[i].items.end(); it++) {
				cout << "\tkey[" << it->key << "], val[" << it->val << "]" << endl;
			}  
		}		
	}
};

int main() 
{
	HashTable myhash;
	int input[] = {2, 4, 5, 6, 8, 100000, 2034, 5420};
	for (auto const &i : input) {
		for (int j = 0; j < 3; j++ ) {
			myhash.insert(i*j, i);
			cout << endl << "After inserting key[" << i << "], val[" << i << "]:" << endl;
			myhash.print();
		}
	}
	for (auto const &i : input) {
		for (int j = 0; j < 3; j++ ) {
			myhash.remove(i*j);
			cout << endl << "After removing key[" << i << "], val[" << i << "]:" << endl;
			myhash.print();
		}
	}
}


