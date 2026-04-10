#include <iostream>
#include <random>
using namespace std;

int main() {
    
    int n, k = 0;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);

    int num = dist(gen);

    cout << "Guess a number between 1 and 100:" << endl;

    do {
        cin >> n;
        k++;

        if (n > num) {
            cout << "Too big" << endl;
        } 
        else if (n < num) {
            cout << "#include <iostream>
#include <random>
using namespace std;

int main() {
    int n, k = 0;

    // Random number setup
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);

    int num = dist(gen);

    cout << "Guess a number between 1 and 100:" << endl;

    do {
        cin >> n;
        k++;

        if (n > num) {
            cout << "Too big" << endl;
        } 
        else if (n < num) {
            cout << "Too small" << endl;
        } 
        else {
            cout << "You did it in " << k << " moves!" << endl;
        }

    } while (n != num);

    return 0;
}" << endl;
        } 
        else {
            cout << "You did it in " << k << " moves!" << endl;
        }

    } while (n != num);

    return 0;
}