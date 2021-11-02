#pragma once

#include <climits>
#include <iostream>
#include <stdexcept>
#include <vector>

//-----------------------------------------------------------
// class definitions
//-----------------------------------------------------------

/**
 * Templated min-heap class.
 */
template <class T> class MinHeap {

private:
  /**
   * Private inner class representing items in the min-heap.
   */
  class Node {
  public:
    /**
     * Default constructor.
     */
    Node() {}

    /**
     * Construct a new Node with the specified value and key.
     *
     * \param d Data value to store in the min-heap.
     * \param k Integer key value used for ordering in the heap.
     */
    Node(const T &d, int k) : data(d), key(k) {}

    /** Data value stored in this node. */
    T data;

    /** Key value used for ordering. */
    int key;
  };

public:
  /**
   * Create a new min-heap.
   */
  MinHeap();

  /**
   * Create a new min-heap just like an existing one.
   *
   * \param Existing min-heap to copy from.
   */
  MinHeap(const MinHeap<T> &heap) { copy(heap); }

  /**
   * Destructor. Free the memory used by the min-heap.
   */
  ~MinHeap();

  /**
   * Remove all of the elements from the min-heap.
   */
  void clear();

  /**
   * Insert an element with a specific key value into the min-heap.
   *
   * \param val Element to insert.
   * \param key Key value associated with val.
   */
  void insert(const T &val, int key);

  /**
   * Determine if this min-heap is empty.
   *
   * \return True if the heap is empty, false otherwise.
   */
  bool isEmpty() const { return vec.size() == 1u; }

  /**
   * Override of the stream insertion operator for MinHeap objects.
   *
   * \param out ostream object to output to, e.g., cout
   *
   * \param heap Heap to output
   *
   * \return the out ostream object
   */
  friend std::ostream &operator<<(std::ostream &out, const MinHeap<T> &heap) {
    out << "[";
    unsigned n = heap.size();
    if (n == 0u) {
      out << "]";
    } else {
      for (unsigned i = 1u; i < n; i++) {
        out << heap.vec.at(i)->data << ", ";
      }
      out << heap.vec.at(n)->data;
      out << "]";
    }
    return out;
  }

  /**
   * Override of the assignment operator for MinHeap objects.
   *
   * \param heap MinHeap to copy from
   * \return Reference to this MinHeap, for chaining purposes.
   */
  MinHeap<T> &operator=(const MinHeap<T> &heap);

  /**
   * Remove the smallest element from the min-heap.
   *
   * \return Smallest element from the heap.
   */
  T removeMin();

  /**
   * Get the number of elements in the min-heap.
   *
   * \return Number of elements in the heap.
   */
  unsigned size() const {
    return vec.size() - 1u;
    ;
  }

private:
  /** STL vector serving as the array for this heap. */
  std::vector<MinHeap<T>::Node *> vec;

  /**
   * Copy the contents of one min-heap into this one.
   *
   * \param heap Min-heap to copy from.
   */
  void copy(const MinHeap<T> &heap);

  /**
   * Decrease the key for heap element i to a new value.
   *
   * \param i Index of element to modify.
   * \param key New key value for element i.
   */
  void heapDecreaseKey(unsigned i, int key);

  /**
   * Determine the index of an element's left child.
   *
   * \param i Index of parent element.
   * \return Index of i's left child.
   */
  inline unsigned left(unsigned i) { return i << 1; }

  /**
   * Reinforce the min-heap property.
   *
   * \param i Index to begin the process.
   */
  void minHeapify(unsigned i);

  /**
   * Determine the index of the parent of an element.
   *
   * \param i Index of child element.
   * \return Index of i's parent.
   */
  inline unsigned parent(unsigned i) { return i >> 1; }

  /**
   * Determine the index of an element's right child.
   *
   * \param i Index of parent element.
   * \return Index of i's right child.
   */
  inline unsigned right(unsigned i) { return (i << 1) + 1u; }

  /**
   * Swap two elements in the heap's backing array.
   *
   * \param i Index of one element to swap.
   * \param j Index of the other element to swap.
   */
  void swap(unsigned i, unsigned j);
};

//-----------------------------------------------------------
// function implementations
//-----------------------------------------------------------

/*
 * Implementation of the Heap constructor.
 */
template <class T> MinHeap<T>::MinHeap() {
  // add a default node to the vector, consuming location 0,
  // so our math can use index 1 as the start
  vec.push_back(new MinHeap<T>::Node());
}

/*
 * Destructor implementation.
 */
template <class T> MinHeap<T>::~MinHeap() {
  // free all "useful" elements...
  clear();

  // then the filler at location 0
  delete vec[0];
}

/*
 * Implementation of the clear() function.
 */
template <class T> void MinHeap<T>::clear() {
  auto i = vec.begin();
  i++; // skip placeholder at location 0
  while (i != vec.end()) {
    delete *i;
    i++;
  }
}

/*
 * Implementation of the copy() function.
 */
template <class T> void MinHeap<T>::copy(const MinHeap<T> &heap) {
  auto i = heap.vec.cbegin();
  while (i != heap.vec.cend()) {
    vec.push_back(new MinHeap<T>::Node((*i)->data, (*i)->key));
    i++;
  }
}

/*
 * Implementation of heapDecreaseKey() function.
 */
template <class T> void MinHeap<T>::heapDecreaseKey(unsigned i, int key) {
  if (key > vec[i]->key) {
    throw std::out_of_range("New key greater than original in"
                            "MinHeap::heapDecreaseKey()");
  }

  vec[i]->key = key;
  unsigned p = parent(i);
  while (i > 1 && vec[p]->key > vec[i]->key) {
    swap(i, p);
    i = p;
    p = parent(i);
  }
}

/*
 * Implementation of insert() function.
 */
template <class T> void MinHeap<T>::insert(const T &val, int key) {
  vec.push_back(new MinHeap<T>::Node(val, INT_MAX));
  heapDecreaseKey(size(), key);
}

/*
 * Implementation of the minHeapify() function.
 */
template <class T> void MinHeap<T>::minHeapify(unsigned i) {
  unsigned le = left(i);
  unsigned ri = right(i);
  unsigned smallest = i;

  if (le < size() && vec[le]->key < vec[i]->key) {
    smallest = le;
  }
  if (ri < size() && vec[ri]->key < vec[smallest]->key) {
    smallest = ri;
  }

  if (smallest != i) {
    swap(i, smallest);
    minHeapify(smallest);
  }
}

/*
 * Implementation of assignment operator.
 */
template <class T> MinHeap<T> &MinHeap<T>::operator=(const MinHeap<T> &heap) {
  // delete existing min-heap contents
  clear();
  delete vec[0];

  // copy existing min-heap
  copy(heap);
}

/*
 * Implementation of the removeMin() function.
 */
template <class T> T MinHeap<T>::removeMin() {
  // prevent removes from empty heaps
  if (size() == 0u) {
    throw std::out_of_range("Empty heap in Heap::removeMin()");
  }

  // save smallest value
  T min = vec[1]->data;

  // overwrite smallest with last element, then re-heapify
  delete vec[1];
  vec[1] = vec[size()];
  minHeapify(1);
  vec.pop_back();

  // send back smallest value
  return min;
}

/**
 * Implementation of the swap() function.
 */
template <class T> void MinHeap<T>::swap(unsigned i, unsigned j) {
  typename MinHeap<T>::Node *t = vec[i];
  vec[i] = vec[j];
  vec[j] = t;
}
