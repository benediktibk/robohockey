#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_SONARMOCK_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_SONARMOCK_H

#include "layer/dataanalysis/sonar.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class SonarMock :
			public Sonar
	{
	public:
		SonarMock();

		virtual bool isObstacleDirectInFront(double speed) const;

		void setIsObstacleDirectInFront(bool value);

	private:
		bool m_isObstacleDirectInFront;
	};
}
}
}

#endif
