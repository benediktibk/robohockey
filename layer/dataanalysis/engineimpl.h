#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINEIMPL_H

#include "layer/dataanalysis/engine.h"
#include "common/point.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Engine;
	class Odometry;
}

namespace DataAnalysis
{
	class EngineImpl :
			public Engine
	{
	public:
		EngineImpl(Hardware::Engine &engine, Hardware::Odometry &odometry);

		virtual void goToStraight(const Common::Point &position);
		virtual void updateSpeedAndMagnitude();
		virtual void stop();

	private:
		void turnOnly(double targetOrientation, double currentOrientation);
		void driveAndTurn(const Common::Point &currentPosition, double targetOrientation, double currentOrientation);
		double calculateOrientationDifference(double targetOrientation, double currentOrientation) const;

	private:
		Hardware::Engine &m_engine;
		Hardware::Odometry &m_odometry;
		Common::Point m_target;
		bool m_enabled;
		bool m_rotationReached;
	};
}
}
}

#endif
