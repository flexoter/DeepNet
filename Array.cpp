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
RawVector<T>& Array2d<T>::operator[] (size_t index) {
    return _data[index];
}

std::pair<bool, string> Array::CheckShapes(
        std::pair<size_t, size_t> first,
        std::pair<size_t, size_t> second) {
            string msg;
            msg.reserve(200);
            if (first != second) {
                string first_shape(
                    "(" + to_string(first.first)
                    + ", " + to_string(first.second) + ") ");
                string second_shape(
                    "(" + to_string(second.first)
                    + ", " + to_string(second.second) + ")");
                msg.append(string("Given arrays have different shapes: "));
                msg.append(first_shape);
                msg.append(second_shape);
                return make_pair(false, move(msg));
            }
            return make_pair(true, "");
        }

template<typename T>
Array2d<T> Array2d<T>::operator+(Array2d<T>& t_term) const {
    auto orig_shape = Shape();
    auto term_shape = t_term.Shape();
    auto [acc, error_msg] = CheckShapes(orig_shape, term_shape);
    if (!acc) {
        throw invalid_argument(error_msg);
    }
    Array2d<T> sum(orig_shape.first, orig_shape.second);
    for (size_t raw = 0; raw != orig_shape.first; raw++) {
        transform(_data[raw].begin(), _data[raw].end(), t_term[raw].begin(), sum[raw].begin(), std::plus<int>());
    }
    return sum;
}

template<typename T>
Array2d<T> Array2d<T>::operator-(Array2d<T>& t_term) const {
    auto orig_shape = Shape();
    auto term_shape = t_term.Shape();
    auto [acc, error_msg] = CheckShapes(orig_shape, term_shape);
    if (!acc) {
        throw invalid_argument(error_msg);
    }
    Array2d<T> sum(orig_shape.first, orig_shape.second);
    for (size_t raw = 0; raw != orig_shape.first; raw++) {
        transform(_data[raw].begin(), _data[raw].end(), t_term[raw].begin(), sum[raw].begin(), std::minus<int>());
    }
    return sum;
}

template<typename T>
Array2d<T> Array2d<T>::operator*(Array2d<T>& t_term) const {
    auto orig_shape = Shape();
    auto term_shape = t_term.Shape();
    auto [acc, error_msg] = CheckShapes(orig_shape, term_shape);
    if (!acc) {
        throw invalid_argument(error_msg);
    }
    Array2d<T> sum(orig_shape.first, orig_shape.second);
    for (size_t raw = 0; raw != orig_shape.first; raw++) {
        transform(_data[raw].begin(), _data[raw].end(), t_term[raw].begin(), sum[raw].begin(), std::multiplies<int>());
    }
    return sum;
}

template<typename T>
Array2d<T> Array2d<T>::operator/(Array2d<T>& t_term) const {
    auto orig_shape = Shape();
    auto term_shape = t_term.Shape();
    auto [acc, error_msg] = CheckShapes(orig_shape, term_shape);
    if (!acc) {
        throw invalid_argument(error_msg);
    }
    Array2d<T> sum(orig_shape.first, orig_shape.second);
    for (size_t raw = 0; raw != orig_shape.first; raw++) {
        transform(_data[raw].begin(), _data[raw].end(), t_term[raw].begin(), sum[raw].begin(), std::divides<int>());
    }
    return sum;
}

template<typename T>
void Array2d<T>::Fill(T filler) {
    for (auto& raw : _data) {
        fill(raw.begin(), raw.end(), filler);
    }
}

template<typename T>
Array2d<T> Array2d<T>::operator* (T c) {
    auto orig_shape = Shape();
    Array2d<T> product(orig_shape.first, orig_shape.second);
    Array2d<T> c_array(orig_shape.first, orig_shape.second);
    c_array.Fill(c);
    product = *this * c_array;
    return product;
}

template<typename T>
Array2d<T> Array2d<T>::operator+ (T c) {
    auto orig_shape = Shape();
    Array2d<T> sum(orig_shape.first, orig_shape.second);
    Array2d<T> c_array(orig_shape.first, orig_shape.second);
    c_array.Fill(c);
    sum = *this + c_array;
    return sum;
}

template<typename T>
Array2d<T> Array2d<T>::operator- (T c) {
    auto orig_shape = Shape();
    Array2d<T> sum(orig_shape.first, orig_shape.second);
    Array2d<T> c_array(orig_shape.first, orig_shape.second);
    c_array.Fill(c);
    sum = *this - c_array;
    return sum;
}

template<typename T>
Array2d<T> Array2d<T>::operator/ (T c) {
    auto orig_shape = Shape();
    Array2d<T> division(orig_shape.first, orig_shape.second);
    Array2d<T> c_array(orig_shape.first, orig_shape.second);
    c_array.Fill(c);
    division = *this / c_array;
    return division;
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

template<typename T>
void Array2d<T>::Transpose() {
    auto orig_shape = Shape();
    vector<vector<T> > transposed;
    transposed.reserve(orig_shape.second);
    for (size_t col = 0; col < orig_shape.second; col++) {
        vector<T> tmp;
        tmp.reserve(orig_shape.first);
        for (size_t raw = 0; raw < orig_shape.first; raw++) {
            tmp.push_back(_data[raw][col]);
        }
        transposed.push_back(tmp);
    }
    _data = transposed;
} 

template<typename T>
vector<RawVector<T> >& Array2d<T>::GetData() {
    return _data;
}

template<typename T>
Array2d<T> Array::MWProduct(Array2d<T>& left, Array2d<T>& right) {
    auto orig_shape = left.Shape();
    auto term_shape = right.Shape();
    auto [acc, error_msg] = CheckShapes(
        orig_shape, make_pair(term_shape.second, term_shape.first));
    if (!acc) {
        throw invalid_argument(error_msg);
    }
    Array2d<T> product(orig_shape.first, term_shape.second);
    auto& left_data = left.GetData();
    auto& right_data = right.GetData();
    right.Transpose();
    for (size_t left = 0; left < orig_shape.first; left++) {
        for (size_t right = 0; right < orig_shape.first; right++) {
            product[left][right] = 
            inner_product(
                left_data[left].begin(),
                left_data[left].end(),
                right_data[right].begin(), 0);
        }
    }
    return product;
}

int main() {
    Array2d<int> array1(2, 3);
    array1.Generate(0, 10);
    int k = 3;
    Array2d<int> array2(3, 2);
    array2.Generate(0, 10);
    try {
        cout << array1 << endl;
        cout << array2 << endl;
        auto array = MWProduct(array1, array2);
        cout << array.Shape() << endl;
        cout << array << endl;
    } catch(invalid_argument e) {
        cout << e.what() << endl;
    }
    return 0;
}