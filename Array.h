#ifndef H_ARRAY
#define H_ARRAY

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace Array {
    
    template<typename T> 
    using RawVector = std::vector<T>;

    template<typename T>
    class Array2d {

        public:
            Array2d()
            : _data(0)
            , _size(std::make_pair(0u, 0u))
            {
            }
            Array2d(size_t t_raws, size_t t_cols)
            : _size(std::make_pair(t_raws, t_cols))
            {
                _data.resize(t_raws);
                for (auto& raw: _data) {
                    raw.resize(t_cols);
                }
            }
            Array2d(typename std::vector<RawVector<T> > array)
            : _size(make_pair(array.size(), array[0].size()))
            , _data(move(array))
            {
            }
            std::vector<std::vector<T> >&
            GetData();
            void Transpose();
            void Fill(T filler);
            RawVector<T>& operator[] (size_t t_index);
            void Generate(size_t start, size_t end);
            typename std::vector<RawVector<T> >::const_iterator 
            begin() const;
            typename std::vector<RawVector<T> >::const_iterator 
            end() const;
            typename std::vector<RawVector<T> >::iterator 
            begin();
            typename std::vector<RawVector<T> >::iterator
            end();
            std::pair<size_t, size_t> Shape() const;
            Array2d operator+ (Array2d& t_term) const;
            Array2d operator- (Array2d& t_term) const;
            Array2d operator* (Array2d& t_term) const;
            Array2d operator/ (Array2d& t_term) const;
            Array2d operator/ (T t_term);
            Array2d operator+ (T t_term);
            Array2d operator- (T t_term);
            Array2d operator* (T t_term);
        private:
            std::vector<std::vector<T> > _data;
            std::pair<size_t, size_t> _size;
    };

    template<typename T>
    Array2d<T> MWProduct(Array2d<T>& left, Array2d<T>& right);
    std::pair<bool, std::string> CheckShapes(
        std::pair<size_t, size_t> first,
        std::pair<size_t, size_t> second);

}; // namespace Arry 

#endif //H_ARRAY
