#ifndef ROBOHOCKEY_LAYER_VIEW_ROBOTDRIVERLOOP_H
#define ROBOHOCKEY_LAYER_VIEW_ROBOTDRIVERLOOP_H

#include <QtCore/QObject>
#include <QtCore/QTimer>

namespace RoboHockey
{
namespace Layer
{
namespace View
{
	class RobotDriver;

	class RobotDriverLoop :
			public QObject
	{
		Q_OBJECT
	public:
		RobotDriverLoop(RobotDriver &driver);

	signals:

	public slots:
		void callUpdateAndRestart();

	private:
		int m_intervalInMilliSeconds;
		RobotDriver &m_driver;
		QTimer m_timer;
	};
}
}
}

#endif
