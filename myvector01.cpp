#include <cstddef>
#include <iostream>
#include <string>

/*
Generic Iterator class with direct <T>, i.e., Iterator<T>
*/
template <typename T>
class Iterator {
 public:
  explicit Iterator(T* ptr) : ptr_(ptr) {}

  // Q: Iterator<T> vs Iterator
  Iterator<T>& operator++() {
    ++ptr_;
    return *this;
  }
  // Q: Iterator<T> vs Iterator
  //   bool operator==(Iterator other) { return this->ptr_ == other.ptr_; }
  bool operator==(Iterator<T> other) { return this->ptr_ == other.ptr_; }
  bool operator!=(Iterator<T> other) { return !(*this == other); }
  T& operator*() { return *ptr_; }

 private:
  T* ptr_;
};

template <typename T>
class MyVector01 {
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

  Iterator<T> begin() {
    // Q: how to resolve -- returning reference to a local object
    return Iterator<T>(ptr_);
  }
  Iterator<T> end() { return Iterator<T>(ptr_ + size_); }

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
  for (auto e : v) {
    cout << e << ", ";
  }
  cout << endl;
}

void run() {
  cout << "!!!start printing ==================" << endl;
  MyVector01<std::string> vector;
  vector.PushBack("a");
  vector.PushBack("b");
  vector.PushBack("c");

  print(vector);
  cout << "!!!end printing ==================" << endl;
}
}  // namespace

int main() { run(); }