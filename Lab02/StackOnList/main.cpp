#include <iostream>
#include "List.h"
#include "Stack.h"
#include <stack>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	std::stack<int> STLStack;
	Stack myStack;

	cout << std::boolalpha;
	cout << "Stl stack isEmpty(): " << STLStack.empty() << endl;
	cout << "my stack isEmpty(): " << myStack.IsEmpty() << endl;

	cout << endl;

	cout << "Stl stack: push(1) " << endl;
	STLStack.push(1);
	cout << "Stl stack: push(2) " << endl;
	STLStack.push(2);

	cout << "my stack: push(1) " << endl;
	myStack.Push(1);
	cout << "my stack: push(2) " << endl;
	myStack.Push(2);

	cout << endl;
	cout << "Stl stack isEmpty(): " << STLStack.empty() << endl;
	cout << "my stack isEmpty(): " << myStack.IsEmpty() << endl;
	cout << endl;

	cout << "Stl stack: pop() " << STLStack.top() << endl;
	STLStack.pop();
	cout << "Stl stack: pop() " << STLStack.top() << endl;
	STLStack.pop();

	cout << "my stack: pop() " << myStack.Pop() << endl;
	cout << "my stack: pop() " << myStack.Pop() << endl;

	cout << endl;

	cout << "Stl stack isEmpty(): " << STLStack.empty() << endl;
	cout << "my stack isEmpty(): " << myStack.IsEmpty() << endl;

	return 0;
}
