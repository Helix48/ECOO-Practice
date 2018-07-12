#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Welcome to Rock Paper Scissors" << endl;
    string a;
    cin >> a;

    int result = rand() % 3;
    switch (result)
    {
    case 0:
        cout << "Rock" << endl;
        break;
    case 1:
        cout << "Paper" << endl;
        break;
    case 2:
        cout << "Scissors" << endl;
        break;

    default:
        break;
    }
    return 0;
}
