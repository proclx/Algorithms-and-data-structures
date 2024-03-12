#include <iostream>
#include "Set.h"

int main()
{
	Set A;
	A.Add('a');
	A.Add('a');
	A.Add('A');
	A.PrintSet();
	Set B;
	B.AddSet(A);
	B.PrintSet();
	B.RemoveSet(A);
	B.PrintSet();
	return 0;
}