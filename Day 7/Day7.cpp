#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath> // For std::pow

using namespace std;

typedef long long ll;

bool part1(const vector<ll> &nums, ll target, int idx, ll cur)
{
    if (idx == nums.size())
    {
        return cur == target;
    }

    ll multiplier = static_cast<ll>(pow(10, to_string(nums[idx]).length()));

    // Explore addition, multiplication
    return part1(nums, target, idx + 1, cur + nums[idx]) ||
           part1(nums, target, idx + 1, cur * nums[idx]);
}

bool part2(const vector<ll> &nums, ll target, int idx, ll cur)
{
    if (idx == nums.size())
    {
        return cur == target;
    }

    ll multiplier = static_cast<ll>(pow(10, to_string(nums[idx]).length()));

    // Explore addition, multiplication, and concatenation
    return part2(nums, target, idx + 1, cur + nums[idx]) ||
           part2(nums, target, idx + 1, cur * nums[idx]) ||
           part2(nums, target, idx + 1, cur * multiplier + nums[idx]);
}

int main()
{
    ifstream file("Day7.txt");
    if (!file.is_open())
    {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    string line;
    ll res1 = 0, res2 = 0;

    while (getline(file, line))
    {
        stringstream ss(line);
        string header;
        vector<ll> nums;

        // Parse the target value
        if (!getline(ss, header, ':'))
        {
            cerr << "Error: Invalid line format." << endl;
            continue;
        }

        ll target = stoll(header);

        // Parse the list of numbers
        ll val;
        while (ss >> val)
        {
            nums.push_back(val);
        }

        // Process the parsed data
        if (part1(nums, target, 0, 0))
        {
            res1 += target;
        }
        if (part2(nums, target, 0, 0))
        {
            res2 += target;
        }
    }

    file.close();

    cout << "Part 1: " << res1 << "\n";
    cout << "Part 2: " << res2 << "\n";

    return 0;
}
