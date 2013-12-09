#include "layer/autonomous/routermock.h"
#include "layer/autonomous/route.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

RouterMock::RouterMock() :
	m_chessMode(false)
{ }

Route RouterMock::calculateRoute(const Point &start, const Point &end, const Field &) const
{
	Route route(0.38);
	route.addPoint(start);
	if (m_chessMode)
		route.addPoint(Point(start.getX(), end.getY()));
	route.addPoint(end);
	return route;
}

void RouterMock::setChessMode(bool value)
{
	m_chessMode = value;
}
