#include <stdio.h>
#include <assert.h>
#include <iostream>
using namespace std;

void removeDuplicates(char** instring) 
{
    if (NULL == instring) {
        return;
    }

    char char_seen[128];
    for (int i = 0; i < 128; i++) {
        char_seen[i] = 0;
    }
    
    char *cur = *instring;
    char *insertion_point = *instring;
    while(*instring != '\0') {
        assert((short)*cur < 128);
        //if I have seen it before, save this point in memory, so I can write here next time
        //I encounter a new unique character
        if (char_seen[*cur] == 0) {
            //If I haven't seen it before, add it to the string, and mark that I have now seen this character, and
            //update so I won't overwrite this position in the string in the future
            char_seen[*cur] = 1;
            *insertion_point = *cur;
            insertion_point++;
        }
        
        //move on to next char
        cur++;
    }
    *insertion_point = '\0';
}

int main() {
	char *input = "abdabbbccaddb";

	cout << "before removing dups: [ " << input << " ]" << endl;

	removeDuplicates(&input);

	cout << "after removing dups: [ " << input << " ]" << endl;

	return 0;
}
