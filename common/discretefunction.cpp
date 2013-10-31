#include "common/discretefunction.h"
#include "common/compare.h"
#include <assert.h>

using namespace RoboHockey::Common;
using namespace std;

DiscreteFunction::DiscreteFunction(int start, int end) :
	m_start(start),
	m_end(end)
{
	m_values.resize(m_end - m_start + 1);
	m_coreNoiseSuppression.resize(5);
	m_coreNoiseSuppression[0] = 1.0/9;
	m_coreNoiseSuppression[1] = 2.0/9;
	m_coreNoiseSuppression[2] = 3.0/9;
	m_coreNoiseSuppression[3] = 2.0/9;
	m_coreNoiseSuppression[4] = 1.0/9;
	m_coreDifferentiation.resize(3);
	m_coreDifferentiation[0] = -1;
	m_coreDifferentiation[1] = 0;
	m_coreDifferentiation[2] = 1;
}

void DiscreteFunction::setValue(int x, double y)
{
	assert(withinRange(x));
	m_values[getVectorPosition(x)] = y;
}

double DiscreteFunction::getValue(int x)
{
	assert(withinRange(x));
	return m_values[getVectorPosition(x)];
}

void DiscreteFunction::suppressNoise()
{
	applyCore(m_coreNoiseSuppression);
}

void DiscreteFunction::differentiate()
{
	applyCore(m_coreDifferentiation);
}

void DiscreteFunction::applyCore(const vector<double> &core)
{
	vector<double> values = m_values;
	const size_t coreSize = core.size();
	const size_t loopEnd = m_values.size() - 1 - coreSize/2;
	assert(coreSize%2 == 1);

	for (size_t i = coreSize/2; i <= loopEnd; ++i)
	{
		double value = 0;
		for (size_t j = 0; j < coreSize; ++j)
			value += core[j]*m_values[i - coreSize/2 + j];
		values[i] = value;
	}

	m_values = values;
}

bool DiscreteFunction::withinRange(int x) const
{
	return x >= m_start && x <= m_end;
}

bool DiscreteFunction::compareValues(const Compare &compare, const DiscreteFunction &one, const DiscreteFunction &two)
{
	return compare.isFuzzyEqual(one.m_values, two.m_values);
}

size_t DiscreteFunction::getVectorPosition(int x) const
{
	return static_cast<size_t>(x - m_start);
}
