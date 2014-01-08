#ifndef ROBOHOCKEY_COMMON_POINTDISTANCECOMPARE_H
#define ROBOHOCKEY_COMMON_POINTDISTANCECOMPARE_H

#include "common/point.h"


namespace RoboHockey
{
namespace Common
{

	class PointDistanceCompare
	{
		public:
			PointDistanceCompare(const Common::Point &position);

			bool operator() (const Common::Point &one, const Common::Point &two) const;

		private:
			Common::Point m_position;
	};
}
}

#endif


