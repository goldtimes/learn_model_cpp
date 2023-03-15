#include <iostream>
#include <algorithm>
#include <vector>

using  namespace std;

int square(int value)
{
    return value * value;
}

void print_value(int value)
{
    cout << value << " ";
}

int main()
{
    vector<int> coll_1{1,2,3,4,5,6,7};
    vector<int> dist_coll;
    cout << "for each: ";
    for_each(coll_1.cbegin(), coll_1.cend(), print_value);
    cout << endl;
    cout << "transform: ";
    // transform 将容器的值，通过某个函数，转换到另一个容器中
    std::transform(coll_1.cbegin(), coll_1.cend(), back_inserter(dist_coll), square);
    for_each(dist_coll.cbegin(), dist_coll.cend(), print_value);


    return 0;
}