#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int number_needed(string a, string b)
{
    vector <int> counta (26, 0), countb (26, 0);

    for (int i = 0; i < a.length(); i++)
    {
        int index = a[i] - 97;
        counta[index]++;
    }

    for (int i = 0; i < b.length(); i++)
    {
        int index = b[i] - 97;
        countb[index]++;
    }

    int sum = 0;

    for (int i = 0; i < 26; i++)
    {
        //cout << counta[i] << " " << countb[i] << endl;
        int diff = abs(counta[i] - countb[i]);
        sum += diff;
    }

    return sum;
}

int main(){
    string a;
    cin >> a;
    string b;
    cin >> b;
    cout << number_needed(a, b) << endl;
    return 0;
}
