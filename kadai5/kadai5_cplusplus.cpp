#include <iostream>
#include <array>
#include <iomanip>

// 親のイテレータを返す関数
template<class RandomAccessIterator>
inline RandomAccessIterator parent(RandomAccessIterator first, RandomAccessIterator itr)
{
  return first + (std::distance(first, itr) + 1) / 2 - 1;
}
// 左側の子のイテレータを返す関数
template<class RandomAccessIterator>
inline RandomAccessIterator left_child(RandomAccessIterator first, RandomAccessIterator itr)
{
  return first + (std::distance(first, itr) + 1) * 2 - 1;
}
// 右側の子のイテレータを返す関数
template<class RandomAccessIterator>
inline RandomAccessIterator right_child(RandomAccessIterator first, RandomAccessIterator itr)
{
  return ::left_child(first, itr) + 1;
}
// 比較関数
template<class T>
inline bool default_compare(const T& a, const T& b)
{
  return a < b;
}
template<class T, class RandomAccessIterator, class Compare>
void push_heap(const T& value, RandomAccessIterator first, RandomAccessIterator last, Compare cmp);
template<class T, class RandomAccessIterator>
inline void push_heap(const T& value, RandomAccessIterator first, RandomAccessIterator last)
{
  ::push_heap(value, first, last, ::default_compare);
}
template<class RandomAccessIterator, class Compare>
void delete_maximum(RandomAccessIterator first, RandomAccessIterator last, Compare cmp);
template<class RandomAccessIterator>
inline void delete_maximum(RandomAccessIterator first, RandomAccessIterator last)
{
  ::delete_maximum(first, last, ::default_compare);
}
template<class RandomAccessIterator, class Compare>
void heap_sort(RandomAccessIterator first, RandomAccessIterator last, Compare cmp);
template<class RandomAccessIterator>
inline void heap_sort(RandomAccessIterator first, RandomAccessIterator last)
{
  ::heap_sort(first, last, ::default_compare<decltype(*first)>);
}

template<class T, class RandomAccessIterator, class Compare>
void push_heap(const T& value, RandomAccessIterator first, RandomAccessIterator last, Compare cmp)
{
  for (; first < last && cmp(*::parent(first, last), *last);
       last = ::parent(first, last)) {
    std::swap(*last, *parent(first, last));
  }
}

template<class RandomAccessIterator, class Compare>
void delete_maximum(RandomAccessIterator first, RandomAccessIterator last, Compare cmp)
{
  std::swap(*first, *(last - 1));
  --last;

  for (auto i = first; i != last; ++i) {
    auto l_ch   = ::left_child(first, i);
    auto r_ch   = ::right_child(first, i);
    auto target = i;

    if (l_ch >= last)                       return;        // 子を持つかどうかを判定
    if (cmp(*i, *l_ch))                     target = l_ch; // 親子の値を比較
    if (r_ch < last && cmp(*target, *r_ch)) target = r_ch; // 子が2つの場合
    if (target == i)                        return;
    std::swap(*i, *target);                                // 親子の値を交換
  }
}

template<class RandomAccessIterator, class Compare>
void heap_sort(RandomAccessIterator first, RandomAccessIterator last, Compare cmp)
{
  // データをヒープに並べる
  for (auto i = first + 1; i != last; ++i) {
    ::push_heap(*i, first, i, cmp);
  }
  // ヒープからデータを取り出し、末尾に並べていく
  for (auto i = last; i != first; --i) {
    ::delete_maximum(first, i, cmp);
  }
}

int main()
{
  std::array<int, 10> data = {17, 39, 1, 9, 5, 24, 2, 11, 23, 6};
  auto                i = data.begin();

  ::heap_sort(data.begin(), data.end()); // ヒープソートの実行

  for(; i != data.end() - 1; ++i) {
    std::cout << std::setw(2) << *i << ", ";
  }
  std::cout << std::setw(2) << *i << std::endl;

  return 0;
}

