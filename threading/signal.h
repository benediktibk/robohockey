#ifndef ROBOHOCKEY_THREADING_SIGNAL_H
#define ROBOHOCKEY_THREADING_SIGNAL_H

namespace boost
{
	class condition_variable;
	class mutex;
}

namespace RoboHockey
{
namespace Threading
{
	class Signal
	{
	public:
		Signal();
		~Signal();

		void send();
		void reset();
		void wait();
		bool isSignalSent() const;

	private:
		boost::condition_variable *m_condition;
		boost::mutex *m_conditionMutex;
		boost::mutex *m_sendingMutex;
		bool m_sent;
	};
}
}

#endif
