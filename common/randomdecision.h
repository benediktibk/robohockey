#ifndef ROBOHOCKEY_COMMON_RANDOMDECISION_H
#define ROBOHOCKEY_COMMON_RANDOMDECISION_H

namespace RoboHockey
{
namespace Common
{
class RandomDecision
{
public:
	RandomDecision(double possibilityForTrue);

	bool decide() const;

private:
	double m_possibilityForTrue;
};
}
}

#endif
