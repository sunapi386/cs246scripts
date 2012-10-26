#include <iostream>
#include <string>
using namespace std;

int main () {
	string str;
	cout << "Name:  ";
	getline (cin, str);
	cout << "You are: " << str << endl;
}



/*
// EXAMPLE: NEW
// operator new[] example
#include <iostream>
#include <memory>
#include <new>
using namespace std;

struct myclass {myclass() {cout <<"myclass constructed\n";}};

int main () {
  // uses first version:
  int * p1 = new int[5];

  // uses second version:
  int * p2 = new (nothrow) int[4];

  // uses third version:
  pair <myclass*,ptrdiff_t> p3 = get_temporary_buffer<myclass>(3);
  new (p3.first) myclass[3];   // calls constructors
  return_temporary_buffer(p3.first);

  return 0;
}
*/
