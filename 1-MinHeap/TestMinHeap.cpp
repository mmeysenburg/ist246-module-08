#include "MinHeap.h"
#include <cstdlib>
#include <iostream>
#include <string>

int main() {
  using namespace std;

  MinHeap<string> heap;

  cout << "Heap size: " << heap.size() << endl;
  cout << heap << endl;

  heap.insert("job c", 3);
  cout << "Heap size: " << heap.size() << endl;
  cout << heap << endl;

  heap.insert("job a", 1);
  cout << "Heap size: " << heap.size() << endl;
  cout << heap << endl;

  heap.insert("job e", 5);
  cout << "Heap size: " << heap.size() << endl;
  cout << heap << endl;

  heap.insert("job b", 2);
  cout << "Heap size: " << heap.size() << endl;
  cout << heap << endl;

  heap.insert("job d", 4);
  cout << "Heap size: " << heap.size() << endl;
  cout << heap << endl;

  heap.insert("RUSH!", -5);
  cout << "Heap size: " << heap.size() << endl;
  cout << heap << endl;

  MinHeap<string> heap1(heap);

  string s = heap.removeMin();
  cout << "Removed " << s << endl;
  cout << "Heap size: " << heap.size() << endl;
  cout << heap << endl;

  while (!heap.isEmpty()) {
    s = heap.removeMin();
    cout << "Removed " << s << endl;
    cout << "Heap size: " << heap.size() << endl;
    cout << heap << endl;
  }

  cout << "Copy constructor heap size: " << heap1.size() << endl;
  cout << heap1 << endl;
  cout << heap << endl;

  MinHeap<int> *pHeap = new MinHeap<int>();
  srand(68333);
  for (int i = 0; i < 15; i++) {
    int x = rand() % 200;
    pHeap->insert(x, x);
  }
  cout << "Dynamic heap size: " << pHeap->size() << endl;
  cout << *pHeap << endl;

  MinHeap<int> heap2 = *pHeap;

  delete pHeap;

  cout << "Assignment operator heap size: " << heap2.size() << endl;
  cout << heap2 << endl;

  return EXIT_SUCCESS;
}
