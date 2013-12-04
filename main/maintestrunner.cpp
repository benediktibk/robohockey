#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CPPUNIT_NS;
using namespace std;

int main (int, char**)
{
	 TestResult testResult;
	 TestResultCollector collectedResults;
	 BriefTestProgressListener progress;
	 TestRunner testRunner;
     CompilerOutputter compilerOutputter (&collectedResults, cerr);

	 testResult.addListener(&collectedResults);
	 testResult.addListener(&progress);
	 testRunner.addTest(TestFactoryRegistry::getRegistry().makeTest());
	 testRunner.run(testResult);
	 compilerOutputter.write();

	 return collectedResults.wasSuccessful () ? 0 : 1;
}
