#ifndef ROBOHOCKEY_THREADING_MUTEX_H
#define ROBOHOCKEY_THREADING_MUTEX_H

namespace boost
{
	class mutex;
}

namespace RoboHockey
{
namespace Threading
{
	class Mutex
	{
	public:
		Mutex();
		~Mutex();

		void lock();
		void unlock();
		bool isLocked();

	private:
		boost::mutex *m_mutex;
	};
}
}

#endif
