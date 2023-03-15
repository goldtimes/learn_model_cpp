#include <algorithm>
#include <iterator> // 输出迭代器
#include <list>
#include <iostream>
#include <set>

using namespace std;

int main()
{
    list<int> coll;
    for (int i = 1; i <=6; ++i)
    {
        coll.push_back(i);
        coll.push_front(i);
    }
    copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
    // remove并不改变容器的大小，而是讲元素往前移动，覆盖掉3,返回的是没有3元素的容器尾部
    cout << "remove: ";
    list<int>::iterator  end = remove(coll.begin(), coll.end(), 3);
    copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "被删除的个数: " << distance(end,coll.end()) << endl;

    coll.erase(end, coll.end());
    copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;


    set<int> sets = {1,2,3,4,5,6,7,8};
    copy(sets.cbegin(), sets.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
    //返回的不是被删除的数，而是删除的个数
    int num = sets.erase(3);
    cout << "删除的元素个数: " << num << endl;
    return 0;
}