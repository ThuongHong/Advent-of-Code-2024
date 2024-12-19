#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

map<string, bool> patterns;
map<pair<string, int>, int> memo; // Cache for (design, index) pairs

int check(const string &design, int i)
{
    if (i >= design.size())
    {
        patterns[design] = true;
        return 1;
    }

    // Check memo
    pair<string, int> state = {design, i};
    if (memo.find(state) != memo.end())
    {
        return memo[state];
    }

    // Iterate forward instead of backward for better cache locality
    for (int j = i; j < design.size(); j++)
    {
        string sub = design.substr(i, j - i + 1);
        if (patterns.find(string(sub)) != patterns.end())
        {
            if (check(design, j + 1))
            {
                memo[state] = 1;
                return 1;
            }
        }
    }

    memo[state] = 0;
    return 0;
}

int main()
{
    ifstream file("Day19.txt");
    string line;
    bool session_2 = false;
    int res = 0;
    while (getline(file, line))
    {
        if (line == "")
        {
            session_2 = true;
            continue;
        }
        if (!session_2)
        {
            stringstream ss(line);
            string pattern;
            while (getline(ss, pattern, ','))
            {
                if (pattern[0] == ' ')
                    pattern = pattern.substr(1);
                patterns[pattern] = true;
            }
        }
        else
        {
            res += check(line, 0);
        }
    }

    file.close();

    cout << "Part 1: " << res << endl;

    return 0;
}