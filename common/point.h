#ifndef ROBOHOCKEY_COMMON_POINT_H
#define ROBOHOCKEY_COMMON_POINT_H

#include <ostream>

namespace RoboHockey
{
namespace Common
{
class Point
{
public:
	Point();
	Point(double x, double y);

	void setX(double value);
	double getX() const;
	void setY(double value);
	double getY() const;

	bool operator==(const Point &point) const;
	Point operator*(double value) const;
	Point operator/(double value) const;
	Point operator+(const Point &point) const;
	Point operator-(const Point &point) const;
	void operator*=(double value);
	bool fuzzyEqual(const Point &point, double epsilon) const;

private:
	double m_x;
	double m_y;
};
}
}

std::ostream& operator<<(std::ostream &stream, const RoboHockey::Common::Point &point);

#endif
