#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    int test_cases = 1000; 
    
    for (int i = 1; i <= test_cases; i++) {
        system("data.exe > data.in"); 
        system("my.exe < data.in > my.out"); 
        system("baoli.exe < data.in > baoli.out"); 
        
        if (system("fc my.out baoli.out > nul")) { 
            cout << "\nWrong Answer found on test " << i << "!\n";
            cout << "Check data.in for the testcase.\n";
            break; 
        } else {
            cout << "Test " << i << " AC\n";
        }
    }
    
    return 0;
}