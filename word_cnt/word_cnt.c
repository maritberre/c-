#include <stdio.h>

int num_words(char *sentence) 
{
	char *cur;
	int last_char_was_space = 1;
	int word_ctr = 0;

	cur = sentence;
	printf("cur[0] is %c\n",cur[0]);
	printf("*cur is %c\n",*cur);
	while(*cur != '\0') {
		if (cur[0] == ' ' || cur[0] == '\t' || cur[0] == '\r') {
			if (last_char_was_space != 1) {
				word_ctr++;
			}	
			last_char_was_space = 1;	
		} else {
			last_char_was_space = 0;
		}
			cur++;
	}
	cur--;
	if (cur[0] != ' ' && cur[0] != '\t' && cur[0] != '\r') {
		word_ctr++;
	}

	return word_ctr;
}

int main() {
	char *input1 = "hello", *input2 = "hello  ", *input3 = "hello ", *input4 = " ", *input5 = " hello", *input6 = "  hello", *input7 = "  hello   hello   ";
	int result = 0; 
	result = num_words(input1);
	printf("number of words in [%s] is %d\n",input1,result);
	result = num_words(input2);
        printf("number of words in [%s] is %d\n",input2,result);
        result = num_words(input3);
        printf("number of words in [%s] is %d\n",input3,result);
        result = num_words(input4);
        printf("number of words in [%s] is %d\n",input4,result);
        result = num_words(input5);
        printf("number of words in [%s] is %d\n",input5,result);
        result = num_words(input6);
        printf("number of words in [%s] is %d\n",input6,result);	
	result = num_words(input7);
        printf("number of words in [%s] is %d\n",input7,result);
	return 0;
}
