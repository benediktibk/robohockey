#include "common/quadraticequation.h"

using namespace std;
using namespace RoboHockey::Common;

QuadraticEquation::QuadraticEquation(double a, double b, double c) :
	m_a(a),
	m_b(b),
	m_c(c)
{ }

vector<double> QuadraticEquation::getSolutions(const Compare &/*compare*/) const
{
	vector<double> solutions;
	return solutions;
}
