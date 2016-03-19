#include <iostream>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::for_each;

const int MAX_HASH_SIZE=100;

class HashTable {

	struct Item {
		int key;
		int val;
	};

	Item table[MAX_HASH_SIZE];
	bool available[MAX_HASH_SIZE];
	
	int primaryHash(int key) {
		return key % MAX_HASH_SIZE;
	}
	
	int secondaryHash(int key) {
		return ((key + 7) % MAX_HASH_SIZE);
	}
	
	public:
	HashTable() {
		for(int i = 0; i < MAX_HASH_SIZE; i++) {
			available[i] = true;
		}
	}
		
	int insert(int key, int val) {
		
		Item item;
		item.key = key;
		item.val = val;
		
		int hash = primaryHash(key);
		if (available[hash]) {
			table[hash] = item;
			available[hash] = false;
			return 0;
		} else {
			hash = secondaryHash(key);
			if (available[hash]) {
				table[hash] = item;
				available[hash] = false;
				return 0;	
			}
		}
		return -1;
	}

	int lookup(int key) {
		int hash = primaryHash(key); 
		if (!available[hash] && table[hash].key == key) {
			return table[hash].val;
		} else {
			hash = secondaryHash(key);
			if (!available[hash] && table[hash].key == key) {
				return table[hash].val;
			}
		}
		return -1;	
	}

	
	int remove(int key) {
		int hash = primaryHash(key); 
		if (!available[hash] && table[hash].key == key) {
			available[key] = true;
			return 0;
		} else {
			hash = secondaryHash(key);
			if (!available[hash] && table[hash].key == key) {
				available[key] = true;
				return 0;
			}
		}
		return -1;
	}
	
	void print() {
		for (int i = 0; i < MAX_HASH_SIZE; i++) {
			if (!available[i]) {
				cout << "Stored at hash " << i << ": key[" << table[i].key << "], val[" << table[i].val << "]" << endl;
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
			myhash.insert(i, i);
			cout << endl << "After inserting key[" << i << "], val[" << i << "] for the " << j << "th time:" << endl;
			myhash.print();
		}
	}
}


