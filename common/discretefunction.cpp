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
	m_coreNoiseSuppressionBig.resize(5);
	m_coreNoiseSuppressionSmall.resize(3);
	m_coreNoiseSuppressionBig[0] = 1.0/9;
	m_coreNoiseSuppressionBig[1] = 2.0/9;
	m_coreNoiseSuppressionBig[2] = 3.0/9;
	m_coreNoiseSuppressionBig[3] = 2.0/9;
	m_coreNoiseSuppressionBig[4] = 1.0/9;
	m_coreNoiseSuppressionSmall[0] = 1.0/4;
	m_coreNoiseSuppressionSmall[1] = 2.0/4;
	m_coreNoiseSuppressionSmall[2] = 1.0/4;
	m_coreDifferentiation.resize(3);
	m_coreDifferentiation[0] = -0.5;
	m_coreDifferentiation[1] = 0;
	m_coreDifferentiation[2] = 0.5;
}

void DiscreteFunction::setValue(int x, double y)
{
	assert(withinRange(x));
	m_values[getVectorPosition(x)] = y;
}

double DiscreteFunction::getValue(int x) const
{
	assert(withinRange(x));
	return m_values[getVectorPosition(x)];
}

void DiscreteFunction::suppressNoise()
{
	applyCore(m_coreNoiseSuppressionSmall, m_start, m_end);
}

void DiscreteFunction::suppressNoiseInRange(int start, int end)
{
	assert(end >= start);
	assert(withinRange(start));
	assert(withinRange(end));
	size_t range = end - start;
	if (range >= m_coreNoiseSuppressionBig.size() + 2)
		applyCore(m_coreNoiseSuppressionBig, start, end);
	else if (range >= m_coreNoiseSuppressionSmall.size() + 2)
		applyCore(m_coreNoiseSuppressionSmall, start, end);
}

void DiscreteFunction::differentiate(double stepSize)
{
	assert(m_values.size() > 2);
	assert(stepSize != 0);
	applyCore(m_coreDifferentiation, m_start, m_end);
	if (stepSize != 1)
		*this *= (1/stepSize);
	m_values[0] = m_values[1];
	*(m_values.end() - 1) = *(m_values.end() - 2);
}

void DiscreteFunction::applyCore(const vector<double> &core, int start, int end)
{
	const size_t coreSize = core.size();
	assert(end >= start);
	assert(static_cast<size_t>(end - start) >= coreSize);
	vector<double> values = m_values;
	const size_t startInVector = getVectorPosition(start);
	const size_t endInVector = getVectorPosition(end);
	const size_t loopEnd = endInVector - coreSize/2;
	assert(coreSize%2 == 1);

	for (size_t i = startInVector + coreSize/2; i <= loopEnd; ++i)
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

list<int> DiscreteFunction::getPositionsWithValuesAbove(double value) const
{
	list<int> result;

	for (int i = m_start; i <= m_end; ++i)
		if (getValue(i) > value)
			result.push_back(i);

	return result;
}

list<int> DiscreteFunction::getPositionsWithValuesBelow(double value) const
{
	list<int> result;

	for (int i = m_start; i <= m_end; ++i)
		if (getValue(i) < value)
			result.push_back(i);

	return result;
}

double DiscreteFunction::getMinimumInRange(int start, int end) const
{
	assert(start <= end);
	assert(start >= m_start);
	assert(end <= m_end);

	double minimum = getValue(start);

	for (int i = start + 1; i <= end; ++i)
		minimum = min(minimum, getValue(i));

	return minimum;
}

double DiscreteFunction::getMeanValueInRange(int start, int end) const
{
	double result = 0;

	for (int i = start; i <= end; ++i)
		result += getValue(i);

	return result/(end - start + 1);
}

void DiscreteFunction::operator*=(double value)
{
	for (vector<double>::iterator i = m_values.begin(); i != m_values.end(); ++i)
		*i *= value;
}

bool DiscreteFunction::compareValues(const Compare &compare, const DiscreteFunction &one, const DiscreteFunction &two)
{
	return compare.isFuzzyEqual(one.m_values, two.m_values);
}

size_t DiscreteFunction::getVectorPosition(int x) const
{
	return static_cast<size_t>(x - m_start);
}
