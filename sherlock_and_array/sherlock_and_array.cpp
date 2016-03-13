#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int T;
    cin >> T;
   
    //unsigned int *A = new unsigned int(N); 
    for (int i = 0; i < T; i++) {
        unsigned long int N;
        cin >> N;
        unsigned int *A = new unsigned int(N);
        unsigned int left_sum = 0, right_sum = 0;
        bool found = false;
        for(int j = 0; j < N; j++) {
            cin >> A[j];
            left_sum += A[j];
        }
        for(int j=N-1; j >=0; j--) {
            left_sum -= A[j];
            if (left_sum == right_sum) {
                found = true;
                break;
            }
            //cout << "left sum is " << left_sum;
            //cout << " , right sum is " << right_sum << endl;
            right_sum += A[j];
        }
        if (found == true) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
	delete[] A;
    }
    //delete[] A;
    
    return 0;
}

