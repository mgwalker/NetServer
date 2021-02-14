#define __NS_VERBOSE
#include "NetServer.h"
#include <iostream>
using namespace std;

void main()
{
	NetServer ns;
	ns.Listen(7942);
	cout << "Hello world." << endl;
}