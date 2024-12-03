#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

// Parse a line into a vector of integers
vector<int> parseLine(const string &line)
{
    stringstream ss(line);
    vector<int> numbers;
    int number;
    while (ss >> number)
        numbers.push_back(number);

    return numbers;
}

// Check if a sequence is inherently safe (O(N))
bool isSafeSequence(const vector<int> &numbers)
{
    int n = numbers.size();
    if (n < 2)
        return false;

    bool isIncreasing = numbers[1] > numbers[0];
    for (int i = 1; i < n; i++)
    {
        if (abs(numbers[i] - numbers[i - 1]) > 3)
            return false;

        if (isIncreasing && numbers[i] <= numbers[i - 1])
            return false;

        if (!isIncreasing && numbers[i] >= numbers[i - 1])
            return false;
    }
    return true;
}

// Check if the sequence can be safe with at most one removal (O(N))
bool isSafeWithDampener(const vector<int> &numbers)
{
    int n = numbers.size();
    if (n < 2)
        return false;

    // Try to remove one element and check the sequence
    for (int i = 0; i < n; i++)
    {
        vector<int> newNumbers;
        // Remove element at position i
        for (int j = 0; j < n; j++)
        {
            if (j != i)
                newNumbers.push_back(numbers[j]);
        }
        if (isSafeSequence(newNumbers))
            return true;
    }

    return false;
}

int main()
{
    ifstream file("Day2.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    long long safeSequenceCount = 0;

    while (getline(file, line))
    {
        vector<int> numbers = parseLine(line);
        if (numbers.empty()) // Skip invalid or empty lines
            continue;

        // Part 1
        // if (isSafeSequence(numbers))
        //     ++safeSequenceCount;

        // Part 2
        if (isSafeSequence(numbers) || isSafeWithDampener(numbers))
            ++safeSequenceCount;
    }

    file.close();
    cout << "Total safe sequences: " << safeSequenceCount << endl;

    return 0;
}
