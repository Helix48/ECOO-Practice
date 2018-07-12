#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

#define FILEDEF "DATA22.txt"
#define NUMCOMPETITIONS 10

using namespace std;

typedef vector <int> ivec;
typedef vector <string> svec;

/// ********** Function that solves problem **********
struct assignment
{
    int deadline;
    double weight;
};

void out_max_weight (vector <assignment> assignments)
{
    vector <bool> occupied (1000001, 0);
    double weight_sum = (double) 0;

    for (int i = assignments.size()-1; i >= 0; i--)
    {
        if (occupied[assignments[i].deadline] == false)
        {
            occupied[assignments[i].deadline] = true;
            weight_sum += assignments[i].weight;
        }
        else
        {
            for (int j = assignments[i].deadline-1; j >= 1; j--)
            {
                if (occupied[j] == false)
                {
                    occupied[j] = true;
                    weight_sum += assignments[i].weight;
                    break;
                }
            }
        }
    }
    cout << std::fixed << setprecision(4) << weight_sum << endl;

}

// Function that actually contains the recursion of quicksort
void quicksort_actual (vector <assignment> &unsorted, int subvec_left_index, int subvec_right_index)
{
    int rightward_mover = subvec_left_index, leftward_mover = subvec_right_index;
    double pivot_value = unsorted[(subvec_left_index + subvec_right_index) / 2].weight;

    // Swap until the right moving index has passed or is right of the left moving index (they have crossed)
    // By the end of this loop, all values less than or equal to pivot_value will be on the left of pivot_value
    // and all values greater than or equal to the pivot value will be on the right of the pivot value
    while (rightward_mover <= leftward_mover)
    {
        // Move the right moving index until it reaches a value that is greater than or equal to the pivot value
        // Since everything right of leftward_mover is greater than or equal to pivot_value,
        // the loop will exit immediately after the moving indices cross
        // (0, 1, ... , leftward_mover, rightward_mover, ... , n-1)
        while (unsorted[rightward_mover].weight < pivot_value)
        {
            rightward_mover++;
        }
        // Move the left moving index until it reaches a value that is less than or equal to the pivot value
        // Since everything left of rightward_mover is less than or equal to pivot_value,
        // the loop will exit immediately after the moving indices cross
        // (0, 1, ... , leftward_mover, rightward_mover, ... , n-1)
        while (unsorted[leftward_mover].weight > pivot_value)
        {
            leftward_mover--;
        }

        // Only swap if the movers have not crossed
        if (rightward_mover <= leftward_mover)
        {
            // Swap the two values at the indices of rightward mover and leftware mover
            double temp_value = unsorted[leftward_mover].weight;
            unsorted[leftward_mover].weight = unsorted[rightward_mover].weight;
            unsorted[rightward_mover].weight = temp_value;

            // Increase the two movers after the swap
            rightward_mover++;
            leftward_mover--;
        }
    }

    // Sort the two halves of the vector separately using the quicksort function recursively
    // This is to sort the sub vector from subvec_left_index to leftward_mover
    // Remember that leftward_mover has crossed and is just left of rightward_mover
    if (subvec_left_index < leftward_mover)
    {
        quicksort_actual(unsorted, subvec_left_index, leftward_mover);
    }
    // This is to sort the sub vector from rightward_mover to subvec_right_index
    // Remember that rightward_mover has crossed and is just right of leftward_mover
    if (rightward_mover < subvec_right_index)
    {
        quicksort_actual(unsorted, rightward_mover, subvec_right_index);
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

    for (int i = 0; i < NUMCOMPETITIONS; i++)
    {
        /// ********** Get input **********
        vector <assignment> assignments;
        int num_assign;
        infile >> num_assign;

        for (int j = 0; j < num_assign; j++)
        {
            int d;
            double w;

            infile >> d >> w;

            assignment ass;
            ass.deadline = d;
            ass.weight = w;
            assignments.push_back(ass);
            quicksort_actual(assignments, 0, assignments.size()-1);
        }

        /// ********** Call function that solves problem **********
        out_max_weight(assignments);

    }

    return 0;
}
