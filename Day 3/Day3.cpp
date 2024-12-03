#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

long long processLine(const string &line, const regex &rgx)
{
    long long result = 0;
    bool flag = true;
    sregex_iterator iter(line.begin(), line.end(), rgx);
    sregex_iterator end;

    while (iter != end)
    {
        smatch match = *iter;
        // cout << match.str() << "\n";
        if (match.str() == "do()")
        {
            flag = true; // Enable multiplication
        }
        else if (match.str() == "don't()")
        {
            flag = false; // Disable multiplication
        }
        else
        {
            string x = match[2].str();
            string y = match[3].str();
            if (!x.empty() && !y.empty()) // Check if x and y are valid
            {
                result += flag ? stoll(x) * stoll(y) : 0;
            }
        }
        iter++;
    }
    return result;
}

int main()
{
    ifstream file("Day3.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    long long totalSum = 0;

    regex rgx("(do\\(\\)|don't\\(\\)|mul\\((\\d{1,3}),(\\d{1,3})\\))");

    while (getline(file, line))
    {
        // cout << line << endl;
        totalSum += processLine(line, rgx);
    }

    file.close();
    cout << "Total Sum: " << totalSum << endl;

    return 0;
}
