#include <vector>

using namespace std;

vector<vector<int>> toMat(const int& n)
{
    vector<int> foo;
    vector<vector<int>> res;
    foo.push_back(n);
    res.push_back(foo);

    return res;
}