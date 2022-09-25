#include <cstddef>
#include <iostream>
#include <string>

/*
Generic Iterator class referecing typename of MyVector class, i.e., MyIterator<MyVector01<T>>
*/
template <typename Vector>
class MyIterator {
  using ValueType = typename Vector::ValueType;

 public:
  explicit MyIterator(ValueType* ptr) : ptr_(ptr) {}

  MyIterator operator++() {
    ++ptr_;
    return *this;
  }
  bool operator==(MyIterator other) { return this->ptr_ == other.ptr_; }
  bool operator!=(MyIterator other) { return !(*this == other); }
  ValueType& operator*() { return *ptr_; }

 private:
  ValueType* ptr_;
};

template <typename T>
class MyVector01 {
 public:
  using Iterator = MyIterator<MyVector01<T>>;
  using ValueType = T;

 public:
  MyVector01() {}
  explicit MyVector01(size_t init_capacity) { Resize(init_capacity); }

  size_t Size() { return size_; }

  void PushBack(const T& element) {
    if (size_ == capacity_) {
      Resize(capacity_ + capacity_ / 2 + 2);
    }
    ptr_[size_] = element;
    size_++;
  }

  T& operator[](size_t index) { return ptr_[index]; }

  Iterator begin() { return Iterator(ptr_); }
  Iterator end() { return Iterator(ptr_ + size_); }

 private:
  void Resize(size_t new_capacity) {
    T* newBlock = new T[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
      newBlock[i] = std::move(ptr_[i]);
    }
    delete[] ptr_;
    ptr_ = newBlock;
    capacity_ = new_capacity;
  }

 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  T* ptr_ = nullptr;
};

namespace {
using std::cout;
using std::endl;

template <typename T>
void print(MyVector01<T> v) {
  for (const auto& e : v) {
    cout << e << ", ";
  }
  cout << endl;
}

void run() {
  cout << "!!!start printing ==================" << endl;
  MyVector01<std::string> vector;
  vector.PushBack("abc");
  vector.PushBack("abc");
  vector.PushBack("abc");

  print(vector);
  cout << "!!!end printing ==================" << endl;
}
}  // namespace

int main() { run(); }