#include "topItVector.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>

int testDefaultVector()
{
    topit::Vector< int > v;
    return v.isEmpty();
}

bool testVectorWithValue()
{
    topit::Vector< int > v;
    v.pushBack(1);

}

bool testCopyConstructor(){
    topit::Vector< int > v;
    v.pushBack(1);
    topit::Vector< int > yav = v;
    bool isAllEqual = v.getSize() == yav.getSize();
    for(size_t i = 0; isAllEqual && i < v.getSize(); ++i){
        isAllEqual = isAllEqual && (v[i] == yav[i]);
    }
    return isAllEqual;
}

bool testElementAccess(){
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(2);
    return v[0] == 1 && v[1] == 2;
}


int main()
{
    using test_t = bool(*)();
    using pair_t = std::pair<const char*, test_t>;
    pair_t tests[] = {
        {"Default vector is empty", testDefaultVector},
        {"Vector with any value is not empty", testVectorWithValue},
        {"Inbound access elenets", testElementAccess},
        {"Sizes must be equal as elements", testCopyConstructor}
    };
    const size_t count = sizeof(tests) / sizeof(pair_t);
    std::cout<<std::boolalpha;
    bool pass = true;
    for(size_t i = 0; i < count; ++i)
    {
        bool res = tests[i].second();
        std::cout<<res<<" :";
        std::cout<< tests[i].first<<"\n";
        pass = pass && res;
    }
    std::cout<<pass<<": RESULT\n";
}