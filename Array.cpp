#include "Array.h"

#include "Streams.cpp"

#include <iostream>
#include <random>
#include <string>

using namespace std;
using namespace Array;

template<typename T>
pair<size_t, size_t> Array2d<T>::Shape() const {
    return _size;
}

template<typename T>
Array2d<T> Array2d<T>::operator+(const Array2d<T>& t_term) const {
    auto orig_shape = Shape();
    auto term_shape = t_term.Shape();
    if (orig_shape != term_shape) {
        string first_shape(
            "(" + to_string(orig_shape.first)
            + ", " + to_string(orig_shape.second) + ")");
        string second_shape(
            "(" + to_string(term_shape.first)
            + ", " + to_string(term_shape.second) + ")");
        throw invalid_argument(
            "Given arrays have different shapes: "
            + first_shape + " " + second_shape);
    }
    Array2d<T> sum(orig_shape.first, orig_shape.second);
    // TODO:
    // implement operator[] for Array2d
    for (size_t raw = 0; raw != orig_shape.first; raw++) {
        transform(_data[raw].begin(), _data[raw].end(), t_term[raw].begin(), sum[raw].begin(), std::plus<int>());
    }
    return sum;
}

template<typename T>
typename std::vector<RawVector<T> >::const_iterator 
Array2d<T>::begin() const {
    return _data.begin();
}

template<typename T>
typename std::vector<RawVector<T> >::const_iterator 
Array2d<T>::end() const {
    return _data.end();
}

template<typename T>
typename std::vector<RawVector<T> >::iterator 
Array2d<T>::begin() {
    return _data.begin();
}

template<typename T>
typename std::vector<RawVector<T> >::iterator 
Array2d<T>::end() {
    return _data.end();
}

template<typename T>
void Array2d<T>::Generate(size_t start, size_t end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> uniform(start, end);
    for (auto& raw: _data) {
        for_each(raw.begin(), raw.end(), [&uniform, &gen] (T& el) -> void { el = uniform(gen); });
    }
}

int main() {
    Array2d<int> array1(3, 3);
    array1.Generate(0, 100);
    Array2d<int> array2(3, 3);
    array2.Generate(0, 100);
    auto array = array1 + array2;
    cout << array.Shape() << endl;   
    cout << array << endl;
    return 0;
}