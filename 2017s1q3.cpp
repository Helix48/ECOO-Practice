#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>

#define FILEDEF "DATAXX.txt"
#define NUMCOMPETITIONS 5

using namespace std;

typedef vector <int> ivec;
typedef vector <string> svec;

struct factor
{
    int prime;
    int expon;
};

bool is_prime (int num)
{
    if (num == 2)
    {
        return true;
    }
    if (num % 2 == 0)
    {
        return false;
    }

    for (int i = 3; i <= pow(num, 0.5f) ; i += 2)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

vector <int> generate_primes ()
{
    vector <int> primes;

    for (int i = 2; i < 1000000; i++)
    {
        if (is_prime(i))
        {
            primes.push_back(i);
        }
    }

    return primes;
}

unordered_map <int, int> prime_factorize (vector <int> primes, int num, int M)
{
    unordered_map <int, int> num_factorized;

    for (int i = 0; i < primes.size(); i++)
    {
        int exp = 0;

        while (num % primes[i] == 0)
        {
            exp++;
            num /= primes[i];
        }

        num_factorized[primes[i]] = exp*M;

        if (primes[i] > num)
        {
            break;
        }
    }

    return num_factorized;
}

/// ********** Function that solves problem **********
int output_min_n (vector <int> primes, unordered_map <int, int> KM_factorized)
{
    int num = 1;

    while (true)
    {
        unordered_map <int, int> num_factorized = prime_factorize(primes, num, 1);

        unordered_map <int, int> :: iterator itr;

        for (itr = num_factorized.begin(); itr != num_factorized; itr++)
        {
            int prime = itr->first;
            if (KM_factorized.find(prime) != KM_factorized.end())
            {
                KM_factorized->first -= num_factorized[itr]
            }
        }
    }

}

int main()
{
    // Declare variables and vector
    ifstream infile;

    string fileName = FILEDEF;

    // Get file name
    infile.open (fileName.c_str(), ifstream::in);

    // Make sure file is openable
    if (!infile.is_open())
    {
        cout << "Could not open " << fileName << endl;
        return 0;
    }

    vector <int> primes = generate_primes ();

    /*
 vector <factor> q = prime_factorize(primes, 12);
    for (int i = 0; i < q.size(); i++)
    {
        cout << q[i].prime << " " << q[i].expon << endl;
    }

    */

    for (int i = 0; i < NUMCOMPETITIONS; i++)
    {
        /// ********** Get input **********
        int K, M;
        infile >> K >> M;

        /// ********** Call function that solves problem **********
        unordered_map <int, int> KM_factorized = prime_factorize(primes, K, M);


    }
    return 0;
}
