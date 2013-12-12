#ifndef ROBOHOCKEY_COMMON_QUADRATICEQUATION_H
#define ROBOHOCKEY_COMMON_QUADRATICEQUATION_H

#include <vector>

namespace RoboHockey
{
namespace Common
{
	class Compare;

	class QuadraticEquation
	{
	public:
		QuadraticEquation(double a, double b, double c);

		std::vector<double> getSolutions(const Compare &compare) const;

	private:
		double m_a;
		double m_b;
		double m_c;
	};
}
}

#endif


