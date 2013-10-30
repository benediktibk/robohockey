#ifndef ROBOHOCKEY_THREADING_SIGNALTEST_H
#define ROBOHOCKEY_THREADING_SIGNALTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Threading
{
	class SignalTest :
			public CPPUNIT_NS::TestFixture
	{
		 CPPUNIT_TEST_SUITE(SignalTest);
		 CPPUNIT_TEST(send_threadWaitingOnSignalAndThenCopiesValue_destinationHasValueSetAfterCreationOfThread);
		 CPPUNIT_TEST(reset_signalSent_signalNotSet);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void send_threadWaitingOnSignalAndThenCopiesValue_destinationHasValueSetAfterCreationOfThread();
		 void reset_signalSent_signalNotSet();
	};
}
}

#endif
