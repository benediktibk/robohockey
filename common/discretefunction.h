#ifndef ROBOHOCKEY_COMMON_DISCRETEFUNCTION_H
#define ROBOHOCKEY_COMMON_DISCRETEFUNCTION_H

#include <vector>
#include <list>

namespace RoboHockey
{
namespace Common
{
	class Compare;

	class DiscreteFunction
	{
	public:
		DiscreteFunction(int start, int end);

		void setValue(int x, double y);
		double getValue(int x) const;
		void suppressNoise();
		void differentiate(double stepSize);
		bool withinRange(int x) const;
		std::list<int> getPositionsWithValuesAbove(double value) const;
		std::list<int> getPositionsWithValuesBelow(double value) const;
		double getMinimumInRange(int start, int end) const;

		void operator*=(double value);

		static bool compareValues(const Compare &compare, const DiscreteFunction &one, const DiscreteFunction &two);

	private:
		void applyCore(const std::vector<double> &core);
		size_t getVectorPosition(int x) const;

	private:
		int m_start;
		int m_end;
		std::vector<double> m_values;
		std::vector<double> m_coreNoiseSuppression;
		std::vector<double> m_coreDifferentiation;

	};
}
}

#endif
