#include "test_runner.h"
#include "profile.h"
#include "tests.h"

using namespace std;

int main() {
    LOG_DURATION("Total");
    TestRunner tr;
    RUN_TEST(tr, TestSplitIntoWords);
    RUN_TEST(tr, TestSerpFormat);
    RUN_TEST(tr, TestTop5);
    RUN_TEST(tr, TestHitcount);
    RUN_TEST(tr, TestRanking);
    RUN_TEST(tr, TestBasicSearch);
    RUN_TEST(tr, TestMidLoad);
    RUN_TEST(tr, TestHeavyLoad);
}
