#include <munit/munit.h>
#include <stdlib.h>

static MunitTest test_suite_tests[] = {
    //-------------------------------------------------//
    //-------------------------------------------------//
    //-------------------------------------------------//
    // TEST 01
    {/* The name is just a unique human-readable way to identify the
      * test. You can use it to run a specific test if you want, but
      * usually it's mostly decorative. */
     (char *)"New/Destroy tests",
     /* You probably won't be surprised to learn that the tests are
      * functions. */
     test_new_destroy, MUNIT_TEST_OPTION_NONE, NULL},
    //-------------------------------------------------//
    //-------------------------------------------------//
    //-------------------------------------------------//
    //
    //-------------------------------------------------//
    //-------------------------------------------------//
    //-------------------------------------------------//
    ////END
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
//-------------------------------------------------//
//-------------------------------------------------//
//-------------------------------------------------//

/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
static const MunitSuite test_suite = {
    /* This string will be prepended to all test names in this suite;
     * for example, "/example/rand" will become "/µnit/example/rand".
     * Note that, while it doesn't really matter for the top-level
     * suite, NULL signal the end of an array of tests; you should use
     * an empty string ("") instead. */
    (char *)"jwt server tests",
    /* The first parameter is the array of test suites. */
    test_suite_tests,
    /* In addition to containing test cases, suites can contain other
     * test suites.  This isn't necessary in this example, but it can be
     * a great help to projects with lots of tests by making it easier
     * to spread the tests across many files.  This is where you would
     * put "other_suites" (which is commented out above). */
    NULL,
    /* An interesting feature of µnit is that it supports automatically
     * running multiple iterations of the tests.  This is usually only
     * interesting if you make use of the PRNG to randomize your tests
     * cases a bit, or if you are doing performance testing and want to
     * average multiple runs.  0 is an alias for 1. */
    -1,
    /* Just like MUNIT_TEST_OPTION_NONE, you can provide
     * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
    MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, (void *)"µnit", argc, argv);
}
