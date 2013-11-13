#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEMOCK_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEMOCK_H

#include "layer/dataanalysis/engine.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class EngineMock :
			public Engine
	{
	public:
		EngineMock();

		virtual void goToStraight(const Common::Point &position);
		virtual void updateSpeedAndRotation();
		virtual void stop();
		virtual void turnAround();
		virtual void turnToTarget(const Common::Point &position);
		virtual void lockForwardMovement();
		virtual void unlockForwardMovement();
		virtual bool tryingToTackleObstacle();

		unsigned int getCallsToGoToStraight() const;
		unsigned int getCallsToStop() const;
		unsigned int getCallsToUpdateSpeedAndMagnitude() const;
		unsigned int getCallsToTryingToTackleObstacle() const;
		unsigned int getCallsToTurnToTarget() const;
		unsigned int getCallsToTurnAround() const;
		unsigned int getCallsToLockForwardMovement() const;
		unsigned int getCallsToUnlockForwardMovement() const;
		void setTryingToTackleObstacle(bool value);

	private:
		unsigned int m_callsToGoToStraight;
		unsigned int m_callsToStop;
		unsigned int m_callsToUpdateSpeedAndMagnitude;
		unsigned int m_callsToTryingToTackleObstacle;
		unsigned int m_callsToTurnToTarget;
		unsigned int m_callsToTurnAround;
		unsigned int m_callsToLockForwardMovement;
		unsigned int m_callsToUnlockForwardMovement;
		bool m_tryingToTackleObstacle;
	};
}
}
}

#endif
