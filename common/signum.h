#ifndef ROBOHOCKEY_COMMON_SIGNUM_H
#define ROBOHOCKEY_COMMON_SIGNUM_H

template <typename T> int sgn(T val)
{
	return (T(0) < val) - (val < T(0));
}

#endif
