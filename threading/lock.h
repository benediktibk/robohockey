#ifndef ROBOHOCKEY_THREADING_LOCK_H
#define ROBOHOCKEY_THREADING_LOCK_H

namespace RoboHockey
{
namespace Threading
{
	class Mutex;

	class Lock
	{
	public:
		Lock(Mutex &mutex);
		~Lock();

	private:
		Mutex &m_mutex;
	};
}
}

#endif
