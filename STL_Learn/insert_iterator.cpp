#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <set>
#include <deque>
#include <string>
using namespace std;

template<typename T>
void  PRINT_CONTAINER(const T& container, const std::string& PROMOT="")
{
    cout << PROMOT << " ";
    for(const auto& elem : container)
    {
        cout << elem << " ";
    }
    cout << endl;
}


int main()
{
    list<int> coll_1 = {1,2,3,4,5,6,7,8};
    vector<int> coll_2;
    // back_insert 可以自动将目标容器扩大且在容器后方插入
    copy(coll_1.cbegin(), coll_1.cend(), back_inserter(coll_2));
    PRINT_CONTAINER(coll_2, "vector: ");
    deque<int>coll_3;
    copy(coll_1.cbegin(), coll_1.cend(), front_inserter(coll_3));
    PRINT_CONTAINER(coll_2, "deque: ");
    set<int>coll_4;
    copy(coll_1.cbegin(), coll_1.cend(), inserter(coll_4, coll_4.begin()));
    PRINT_CONTAINER(coll_2, "set: ");

    return 0;
}
