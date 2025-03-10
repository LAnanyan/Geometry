#ifndef Unittest_h_defined
#define Unittest_h_defined

#include "Segment3D.h"

#include <string>

class Unittest
{
public:

	virtual ~Unittest() = default;

public:

	virtual bool run(std::string& err_str) = 0;
};

class Segment3DUnittest : public Unittest
{
public:

	bool run(std::string& err_str) override;
};

#endif // !Unittest_h_defined