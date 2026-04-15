#include <iostream>
#include <random>
using namespace std;

int main() {
    int n,k=10;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);

    int num = dist(gen);
    cout<<num<<endl;
    cout << "Random number generated!" << endl;

    do {
        cout<<"Choose your number ";
        cin >> n;
        k++;

        if (n > num) {
            cout << "Too big " <<k<<" attempts left :(( "<<endl;
        } 
        else if (n < num) {
            cout << "Too small " <<k<<" attempts left :(( "<< endl;
        } 
        else {
            cout << "You did it in " << k << " moves" << endl;
        }

    } while (n != num);

    return 0;
}