#ifndef ROBOHOCKEY_COMMON_POINTDISTANCECOMPARE_H
#define ROBOHOCKEY_COMMON_POINTDISTANCECOMPARE_H

namespace RoboHockey
{
namespace Common
{

	class Point;

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


