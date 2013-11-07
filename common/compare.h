#ifndef ROBOHOCKEY_COMMON_COMPARE_H
#define ROBOHOCKEY_COMMON_COMPARE_H

#include <vector>

namespace RoboHockey
{
namespace Common
{
	class Point;
	class Circle;

	class Compare
	{
	public:
		Compare(double epsilon);

		bool isFuzzyEqual(double value1, double value2) const;
		bool isFuzzyEqual(const std::vector<double> &one, const std::vector<double> &two) const;
		bool isFuzzyEqual(const Point &one, const Point &two) const;
		bool isFuzzyEqual(const Circle &one, const Circle &two) const;
		bool isFuzzyGreater(double value1, double value2) const;
		bool isFuzzySmaller(double value1, double value2) const;
		bool isStrictFuzzyGreater(double value1, double value2) const;
		bool isStrictFuzzySmaller(double value1, double value2) const;

	private:
		 double m_epsilon;
	};
}
}

#endif
