#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

void processSession1(const string &line, unordered_map<int, unordered_set<int>> &rules)
{
    stringstream ss(line);
    string keyStr, valueStr;
    getline(ss, keyStr, '|');
    getline(ss, valueStr, '|');
    int key = stoi(keyStr);
    int value = stoi(valueStr);
    rules[key].insert(value);
}

long long processSession2(const string &line, const unordered_map<int, unordered_set<int>> &rules, bool part2)
{
    stringstream ss(line);
    unordered_set<int> seenNumbers;
    vector<int> numbers;
    vector<pair<int, int>> movements; // Tracks number and required swaps
    bool isValid = true;
    string numberStr;

    while (getline(ss, numberStr, ','))
    {
        int number = stoi(numberStr);
        numbers.push_back(number);
        seenNumbers.insert(number);

        int conflictCount = 0;
        for (int num : seenNumbers)
        {
            if (rules.count(number) && rules.at(number).count(num))
            {
                isValid = false;
                conflictCount++;
            }
        }

        movements.emplace_back(number, conflictCount);
    }

    if (!part2)
    {
        return isValid && !numbers.empty() ? numbers[numbers.size() / 2] : 0;
    }

    // Handle PART2 logic: Resolve conflicts with swaps
    if (isValid)
    {
        return 0; // No conflicts, return 0
    }

    for (int i = 0; i < movements.size(); ++i)
    {
        int swaps = movements[i].second;
        int pos = i;

        while (swaps-- > 0 && pos > 0)
        {
            swap(movements[pos], movements[pos - 1]);
            pos--;
        }
    }

    int medianIndex = movements.size() / 2;
    return movements[medianIndex].first;
}

int main()
{
    ifstream file("Day5.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    cout << "Enable PART2 logic? (1 for yes, 0 for no): ";
    bool part2;
    cin >> part2;

    string line;
    unordered_map<int, unordered_set<int>> rules;
    int session = 1;
    long long result = 0;

    while (getline(file, line))
    {
        if (line.empty())
        {
            session++;
            continue;
        }

        if (session == 1)
        {
            processSession1(line, rules);
        }
        else
        {
            result += processSession2(line, rules, part2);
        }
    }

    file.close();

    cout << result << endl;
    return 0;
}
