#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

typedef long long ll;

map<string, ll> patterns;
map<pair<string, ll>, ll> memo; // Cache for (design, index) pairs

ll check(const string &design, ll i)
{
    if (i >= design.size())
    {
        return 1;
    }

    // Check memo
    pair<string, ll> state = {design, i};
    if (memo.find(state) != memo.end())
    {
        return memo[state];
    }

    // Iterate forward instead of backward for better cache locality
    ll cnt = 0;
    for (ll j = i; j < design.size(); j++)
    {

        string sub = design.substr(i, j - i + 1);
        if (patterns.find(string(sub)) != patterns.end())
        {
            cnt += check(design, j + 1);
        }
    }

    memo[state] = cnt;
    return cnt;
}

int main()
{
    ifstream file("Day19.txt");
    string line;
    bool session_2 = false;
    ll res = 0;
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

    cout << "Part 2: " << res << endl;

    return 0;
}