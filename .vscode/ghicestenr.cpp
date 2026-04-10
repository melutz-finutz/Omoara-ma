#include <iostream>
#include <random>
using namespace std;

int main() {
    int n, k = 0;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);

    int num = dist(gen);
    cout << "Random number generated!" << endl;

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
            cout << "You did it in " << k << " moves" << endl;
        }

    } while (n != num);

    return 0;
}