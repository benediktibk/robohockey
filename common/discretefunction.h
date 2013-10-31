#ifndef ROBOHOCKEY_COMMON_DISCRETEFUNCTION_H
#define ROBOHOCKEY_COMMON_DISCRETEFUNCTION_H

#include <vector>

namespace RoboHockey
{
namespace Common
{
	class DiscreteFunction
	{
	public:
		DiscreteFunction(int start, int end);

		void setValue(int x, double y);
		double getValue(int x);
		void suppressNoise();
		void differentiate();
		bool withinRange(int x) const;

		bool operator==(const DiscreteFunction &rhs) const;

	private:
		void applyCore(const std::vector<double> &core);
		size_t getVectorPosition(int x) const;

	private:
		const int m_start;
		const int m_end;
		std::vector<double> m_values;
		std::vector<double> m_coreNoiseSuppression;
		std::vector<double> m_coreDifferentiation;

	};
}
}

#endif
