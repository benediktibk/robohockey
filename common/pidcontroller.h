#ifndef ROBOHOCKEY_COMMON_PIDCONTROLLER_H
#define ROBOHOCKEY_COMMON_PIDCONTROLLER_H

namespace RoboHockey
{
namespace Common
{
	class Watch;
	class StopWatch;

	class PIDController
	{
	public:
		PIDController(double Kp, double Ki, double Kd, const Watch &watch);
		~PIDController();

		double evaluate(double input);
		void resetTo(double value);

	private:
		const double m_Kp;
		const double m_Ki;
		const double m_Kd;
		double m_integratorState;
		double m_lastInput;
		StopWatch *m_stopWatch;
	};
}
}

#endif


