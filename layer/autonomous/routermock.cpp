#include "layer/autonomous/routermock.h"
#include "common/robotposition.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

RouterMock::RouterMock() :
	m_chessMode(false),
	m_routeSet(false)
{ }

Route RouterMock::calculateRoute(
		const RobotPosition &start, const RobotPosition &end, const FieldPositionChecker &, const Angle &, double, bool,
		const vector<Circle> &, const vector<Circle> &) const
{
	if (m_routeSet)
		return m_route;

	Route route(0.38);
	route.addPoint(start.getPosition());
	if (m_chessMode)
		route.addPoint(Point(start.getPosition().getX(), end.getPosition().getY()));
	route.addPoint(end.getPosition());
	return route;
}

vector<Circle> RouterMock::filterObstacles(
		const vector<Circle> &softObstacles, const vector<Circle> &hardObstacles, const Point &) const
{
	vector<Circle> result = softObstacles;
	result.insert(result.end(), hardObstacles.begin(), hardObstacles.end());
	return result;
}

void RouterMock::setChessMode(bool value)
{
	m_chessMode = value;
}

void RouterMock::setRoute(const Point &one, const Point &two, const Point &three)
{
	m_routeSet = true;
	m_route = Route(0.38);
	m_route.addPoint(one);
	m_route.addPoint(two);
	m_route.addPoint(three);
}
