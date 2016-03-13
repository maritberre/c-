#include <stdio.h>
#include <assert.h>
#include <iostream>
using namespace std;

void removeDuplicates(std::string &instring) 
{
	std::string unique_string = "";

	char char_seen[128];
    	for (int i = 0; i < 128; i++) {
        	char_seen[i] = 0;
    	}

	for(string::iterator it = instring.begin(); it != instring.end(); it++) {
		assert((short)*it < 128);
        //if I have seen it before, save this point in memory, so I can write here next time
        //I encounter a new unique character
        	if (char_seen[*it] == 0) {
            	//If I haven't seen it before, add it to the string, and mark that I have now seen this character, and
            	//update so I won't overwrite this position in the string in the future
            	char_seen[*it] = 1;
            	unique_string.append(1,*it);
            	//insertion_point++;
        	}

	}

	instring.assign(unique_string);  	
}

int main() {
	std::string input= "abdabbbccaddb";

	cout << "before removing dups: [ " << input << " ]" << endl;

	removeDuplicates(input);

	cout << "after removing dups: [ " << input << " ]" << endl;

	return 0;
}
