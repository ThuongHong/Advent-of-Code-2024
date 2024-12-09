#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

void part1(vector<ll> line);
void part2(vector<ll> line);
vector<ll> convert(string s);

int main()
{
    ifstream file("Day9.txt");
    string s;
    file >> s;
    file.close();
    // cout << s << "\n\n";
    vector<ll> line = convert(s);

    part1(line);
    part2(line);

    return 0;
}

void part1(vector<ll> line)
{
    ll left = 0, right = line.size() - 1;
    while (true)
    {
        while (line[left] != -1)
            left++;
        while (line[right] == -1)
            right--;
        if (left >= right)
            break;
        swap(line[left++], line[right--]);
    }
    ll res = 0;
    for (ll i = 0; line[i] >= 0; i++)
    {
        res += (i * line[i]);
    }
    cout << "Part 1: " << res << "\n";
}

void part2(vector<ll> line)
{
    ll left_start = 0, left_end = 0;
    ll right_start, right_end = line.size() - 1;
    ll cur_id = line.size() - 1;
    unordered_set<int> visited;
    while (true)
    {
        while (line[right_end] == -1)
            right_end--;
        right_start = right_end;
        while (line[right_start - 1] == line[right_end])
            right_start--;
        visited.insert(line[right_end]);
        while (true)
        {
            while (line[left_start] != -1)
                left_start++;
            left_end = left_start;
            while (line[left_end + 1] == -1 && (right_end - right_start) > (left_end - left_start))
                left_end++;
            if (left_end >= right_start)
                break;
            if (left_end - left_start == right_end - right_start) // if the two parts are equal
            {
                ll i = left_start;
                ll j = right_start;
                while (i <= left_end)
                {
                    swap(line[i++], line[j++]);
                }
                break;
            }

            left_start = left_end + 1;
        }
        left_start = 0;
        right_end = right_start - 1;
        while (visited.find(line[right_end]) != visited.end())
        {
            right_end--;
        }
        if (line[right_end] == 0)
            break;
    }

    ll res = 0;
    for (ll i = 0; i < line.size(); i++)
    {
        if (line[i] == -1)
            continue;
        res += (i * line[i]);
    }
    cout << "Part 2: " << res << "\n";
}

vector<ll> convert(string s)
{
    vector<ll> a;
    ll id = 0;
    bool flag = true;
    for (ll i = 0; i < s.size(); i++)
    {
        if (s[i] > '9' || s[i] < '0')
            continue;
        ll n = s[i] - '0';
        if (flag)
        {
            while (n--)
                a.push_back(id);
            id++;
        }
        else
        {
            while (n--)
                a.push_back(-1);
        }
        flag = !flag;
    }
    return a;
}