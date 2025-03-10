#include "Unittest.h"

#include <memory>
#include <iostream>

int main()
{
	try
	{
		std::unique_ptr<Unittest> unit_test_uptr = std::make_unique<Segment3DUnittest>();

		std::string err_str;
		if (!unit_test_uptr->run(err_str))
		{
			std::cout << "The test failed, reason: " << err_str << "\n";
			return 1;
		}

		std::cout << "The test passed successfully\n";
	}
	catch (const std::exception& ex)
	{
		std::cout << "An exception occured: " << ex.what() << std::endl;

		return -1;
	}
	catch (...)
	{
		std::cout << "An unknown exception occured" << std::endl;

		return -1;
	}

	return 0;
}