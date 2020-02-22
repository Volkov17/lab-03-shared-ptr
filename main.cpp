#include <iostream>
#include "shared.h"

int main() {
    using std::cout;
    using std::endl;
    SharedPtr<int>p1(new int (5));
    cout << "*p1 = " << *p1 <<endl; //+

    SharedPtr<int>p2(p1);
    cout << "count of SharedPtr = " << p1.use_count() << endl; //-

    SharedPtr<int> sp1(new int(8));
    SharedPtr<int> sp2(new int(10));
    sp1.swap(sp2);
    cout << "*sp1 = " << *sp1 << endl; //+

    SharedPtr<int> sp(new int(5));
    cout << "*sp.get() = " << *sp.get() << std::endl;
    cout << "*sp = " << *sp << endl;
    sp.reset();
    cout << "(bool)sp = " << (bool)sp << endl;

    SharedPtr<int> sp5(new int(8));
    sp5.reset(new int(10));
    std::cout << "*sp = " << *sp5 << endl;

    return 0;
}
