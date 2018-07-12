#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#define FILEDEF "DATA11.txt"
#define NUMCOMPETITIONS 10

using namespace std;

typedef vector <int> ivec;
typedef vector <string> svec;

/// ********** Function that solves problem **********
struct amounts
{
    int carbon;
    int oxygen;
    int water;
    int sugar;
};



void output_max_oxygen (amounts solution, amounts photo, amounts respire)
{
    int max_oxygen = solution.oxygen;

    while (true)
    {
        while (true)
        {
            // do photosynthesis
            solution.carbon -= photo.carbon;
            solution.water -= photo.water;
            solution.oxygen += photo.oxygen;
            solution.sugar += photo.sugar;

            if (solution.carbon < 0 || solution.water < 0)
            {
                solution.carbon += photo.carbon;
                solution.water += photo.water;
                solution.oxygen -= photo.oxygen;
                solution.sugar -= photo.sugar;
                break;
            }
        }

        if (solution.oxygen <= max_oxygen)
        {
            break;
        }
        else
        {
            max_oxygen = solution.oxygen;
        }

        while (true)
        {
            // do respiration
            solution.oxygen -= respire.oxygen;
            solution.sugar -= respire.sugar;
            solution.carbon += respire.carbon;
            solution.water += respire.water;

            if (solution.oxygen < 0 || solution.sugar < 0)
            {
                solution.oxygen -= photo.oxygen;
                solution.sugar -= photo.sugar;
                solution.carbon += photo.carbon;
                solution.water += photo.water;
                break;
            }
        }
    }

    cout << max_oxygen << endl;
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

    for (int i = 0; i < NUMCOMPETITIONS; i++)
    {
        /// ********** Get input **********
        amounts initial, photo, respire;
        int c, o, w, s;
        infile >> c >> o >> w >> s;
        initial.carbon = c;
        initial.oxygen = o;
        initial.water = w;
        initial.sugar = s;

        infile >> c >> w >> s >> o;
        photo.carbon = c;
        photo.oxygen = o;
        photo.water = w;
        photo.sugar = s;

        infile >> s >> o >> c >> w;
        respire.carbon = c;
        respire.oxygen = o;
        respire.water = w;
        respire.sugar = s;


        /// ********** Call function that solves problem **********
        output_max_oxygen(initial, photo, respire);

    }

    return 0;
}
