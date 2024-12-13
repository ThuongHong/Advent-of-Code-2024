#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

typedef long long ll;

ll processPart1(string line1, string line2, string line3)
{
    regex button(R"(Button [A|B]: X\+(\d+), Y\+(\d+))");
    regex prize(R"(Prize: X=(\d+), Y=(\d+))");

    ll x_a = 0, y_a = 0, x_b = 0, y_b = 0, x_target = 0, y_target = 0;

    // Match for line1
    sregex_iterator iter1(line1.begin(), line1.end(), button);
    sregex_iterator end;
    if (iter1 != end)
    {
        smatch match = *iter1;
        x_a = stoll(match[1].str());
        y_a = stoll(match[2].str());
    }

    // Match for line2
    sregex_iterator iter2(line2.begin(), line2.end(), button);
    if (iter2 != end)
    {
        smatch match = *iter2;
        x_b = stoll(match[1].str());
        y_b = stoll(match[2].str());
    }

    // Match for line3
    sregex_iterator iter3(line3.begin(), line3.end(), prize);
    if (iter3 != end)
    {
        smatch match = *iter3;
        x_target = stoll(match[1].str());
        y_target = stoll(match[2].str());
    }

    // Solve the system of linear equations
    double denominator = x_a * y_b - x_b * y_a;
    double a = (x_target * y_b - x_b * y_target) / denominator;
    double b = (x_a * y_target - x_target * y_a) / denominator;

    // cout << "Solution found: a = " << a << ", b = " << b << endl;
    if (a == ll(a) && b == ll(b) && a <= 100 && b <= 100)
        return a * 3 + b;

    return 0;
}

ll processPart2(string line1, string line2, string line3)
{
    regex button(R"(Button [A|B]: X\+(\d+), Y\+(\d+))");
    regex prize(R"(Prize: X=(\d+), Y=(\d+))");

    ll x_a = 0, y_a = 0, x_b = 0, y_b = 0, x_target = 0, y_target = 0;

    // Match for line1
    sregex_iterator iter1(line1.begin(), line1.end(), button);
    sregex_iterator end;
    if (iter1 != end)
    {
        smatch match = *iter1;
        x_a = stoll(match[1].str());
        y_a = stoll(match[2].str());
    }

    // Match for line2
    sregex_iterator iter2(line2.begin(), line2.end(), button);
    if (iter2 != end)
    {
        smatch match = *iter2;
        x_b = stoll(match[1].str());
        y_b = stoll(match[2].str());
    }

    // Match for line3
    sregex_iterator iter3(line3.begin(), line3.end(), prize);
    if (iter3 != end)
    {
        smatch match = *iter3;
        x_target = stoll(match[1].str());
        y_target = stoll(match[2].str());
    }

    // Solve the system of linear equations
    x_target += 10000000000000;
    y_target += 10000000000000;
    double denominator = x_a * y_b - x_b * y_a;
    double a = (x_target * y_b - x_b * y_target) / denominator;
    double b = (x_a * y_target - x_target * y_a) / denominator;

    // cout << "Solution found: a = " << a << ", b = " << b << endl;
    if (a == ll(a) && b == ll(b))
        return a * 3 + b;

    return 0;
}

int main()
{
    ifstream file("Day13.txt");
    string line1, line2, line3, tmp;

    ll res1 = 0, res2 = 0;
    while (!file.eof())
    {
        getline(file, line1);
        getline(file, line2);
        getline(file, line3);
        getline(file, tmp);
        res1 += processPart1(line1, line2, line3);
        res2 += processPart2(line1, line2, line3);
    }

    file.close();

    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;

    return 0;
}
