#include "Unittest.h"

#include <vector>
#include <sstream>
#include <stdexcept>

bool Segment3DUnittest::run(std::string& err_str)
{
	const std::vector<std::pair<Segment3D, Segment3D>> pairs_of_segemnts = 
	{ 
		std::make_pair(Segment3D(Point3D(1, 0, 1), Point3D(1, 1, 1)), Segment3D(Point3D(1, 1, -1), Point3D(1, 0, -1))), 
		std::make_pair(Segment3D(Point3D(1, 0, 1), Point3D(1, 1, 1)), Segment3D(Point3D(1, 1, 0), Point3D(0, 1, 0))),
		std::make_pair(Segment3D(Point3D(1, 0, 1), Point3D(1, 1, 1)), Segment3D(Point3D(1.5, 0.5, 1), Point3D(0.5, 0.5, 1))),
		std::make_pair(Segment3D(Point3D(1, 0, 1), Point3D(1, 1, 1)), Segment3D(Point3D(1, 1, 1), Point3D(0, 1, 0))),
		std::make_pair(Segment3D(Point3D(1, 0, 1), Point3D(1, 1, 1)), Segment3D(Point3D(1.5, 0.5, 0.5), Point3D(0.5, 0.5, 0.5))),
		std::make_pair(Segment3D(Point3D(1, 0, 1), Point3D(1, 1, 1)), Segment3D(Point3D(2, -1, 1), Point3D(100, 2, 0))),
		std::make_pair(Segment3D(Point3D(1, 0, 1), Point3D(1, 1, 1)), Segment3D(Point3D(1, 0, 0), Point3D(1, 1, 0))),
		std::make_pair(Segment3D(Point3D(1, 0, 1), Point3D(1, 1, 1)), Segment3D(Point3D(1.5, 0, 0), Point3D(1, 1, 0))),
		std::make_pair(Segment3D(Point3D(1, 0, 1), Point3D(1, 1, 1)), Segment3D(Point3D(1, 0, 0), Point3D(0, 1, 1))),
		std::make_pair(Segment3D(Point3D(1, 0, 1), Point3D(1, 1, 1)), Segment3D(Point3D(1, 0, 1), Point3D(1, 1, 1))),
		std::make_pair(Segment3D(Point3D(1, 0, 1), Point3D(1, 1, 1)), Segment3D(Point3D(1, -5, 1), Point3D(1, 5, 1)))
	};

	const std::vector<double> etalon_squared_distances = { 4, 1, 0, 0, 0.25, 2, 1, 1, 0.5, 0, 0};

	if (pairs_of_segemnts.size() != etalon_squared_distances.size())
	{
		throw std::range_error("pairs_of_segemnts size is not equal to etalon_squared_distances size");
	}

	for (int i = 0; i < pairs_of_segemnts.size() && i < etalon_squared_distances.size(); ++i)
	{
		const double squared_distance = pairs_of_segemnts[i].first.squared_distance_to(pairs_of_segemnts[i].second);

		if (squared_distance != etalon_squared_distances[i])
		{
			std::stringstream ss;
			ss << "Mismatch on subtest no " << i + 1 << ": expected to retrieve " << etalon_squared_distances[i] << ", but got " << squared_distance;
			err_str = ss.str();

			return false;
		}
	}

    return true;
}
