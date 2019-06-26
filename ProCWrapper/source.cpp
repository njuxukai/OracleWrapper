
#include "DBWrapper.h"
#include <iostream>

int main()
{
	auto db = DBWrapper::CreateWrapper();
	for (int i = 0; i < 1000; i++)
	{
		db->submit(i);
	}
	int x;
	std::cin >> x;
}