#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <deque>

using namespace std;

typedef long long ll;

ll Part1(string line);
ll Part2(string line);
ll dp(string num, int curBlink);
map<pair<string, int>, ll> memo;

int main()
{
    ifstream file("Day11.txt");
    string line;
    getline(file, line);
    file.close();

    // cout << "Part 1: " << Part1(line) << endl;
    cout << "Part 2: " << Part2(line) << endl;

    return 0;
}

ll Part1(string line)
{
    int maxBlink = 25;

    deque<pair<string, int>> s;
    string temp;
    stringstream ss(line);
    while (ss >> temp)
    {
        s.push_back({temp, 0});
    }

    ll res = 0;
    while (!s.empty())
    {
        string curNum = s.front().first;
        int curBlink = s.front().second;
        s.pop_front();
        if (curBlink == maxBlink)
        {
            res++;
        }
        else if (curNum == "0")
        {
            s.push_front({"1", curBlink + 1});
        }
        else if (curNum.size() % 2 == 0)
        {
            string first_half = curNum.substr(0, curNum.size() / 2);
            string second_half = curNum.substr(curNum.size() / 2);
            while (second_half.size() > 1 && second_half[0] == '0')
            {
                second_half = second_half.substr(1);
            }

            s.push_front({second_half, curBlink + 1});
            s.push_front({first_half, curBlink + 1});
        }
        else
        {
            ll nextNum = stoll(curNum) * 2024;
            s.push_front({to_string(nextNum), curBlink + 1});
        }
    }

    return res;
}

ll Part2(string line)
{
    int maxBlink = 75;

    string temp;
    stringstream ss(line);
    ll res = 0;
    while (ss >> temp)
    {
        res += dp(temp, maxBlink);
    }
    return res;
}

ll dp(string num, int curBlink)
{
    if (curBlink == 0)
        return 1;

    if (memo.find({num, curBlink}) != memo.end())
        return memo[{num, curBlink}];

    if (num == "0")
    {
        ll res = dp("1", curBlink - 1);

        memo[{num, curBlink}] = res;
        return res;
    }

    if (num.size() % 2 == 0)
    {
        string first_half = num.substr(0, num.size() / 2);
        string second_half = num.substr(num.size() / 2);
        while (second_half.size() > 1 && second_half[0] == '0')
            second_half = second_half.substr(1);

        ll res1 = dp(second_half, curBlink - 1);
        ll res2 = dp(first_half, curBlink - 1);

        memo[{num, curBlink}] = res1 + res2;
        return res1 + res2;
    }

    ll nextNum = stoll(num) * 2024;
    ll res = dp(to_string(nextNum), curBlink - 1);

    memo[{num, curBlink}] = res;
    return res;
}