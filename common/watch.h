#ifndef ROBOHOCKEY_COMMON_WATCH_H
#define ROBOHOCKEY_COMMON_WATCH_H

#include <boost/timer.hpp>

namespace RoboHockey
{
namespace Common
{
    class Watch
    {
    public:
        Watch();
        double getTime();
        void restart();

    private:
        boost::timer m_start;
    };
}
}
#endif // WATCH_H
