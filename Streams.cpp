#include "Array.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace Array;

template<typename T, typename U>
ostream& operator<< (ostream& os, const pair<T, U>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename T>
ostream& operator<< (ostream& os, const vector<T>& v) {
    os << "[ ";
    for (const auto& el: v) {
        os << el << " ";
    }
    os << "]";
    return os;
}

template<typename T>
ostream& operator<< (ostream& os, const Array2d<T>& a) {
    for (const auto& raw: a) {
        os << raw << endl;
    }
    return os;
}