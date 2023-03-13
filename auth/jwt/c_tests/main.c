#include "tests.h"
#include <munit/munit.h>

static MunitTest all_tests[] = {
    // TEST 01
    {(char *)"New/Destroy server", test_new_destroy, NULL, NULL},
    {(char *)"New/Destroy htpasswd line", test_new_destroy_htpasswd_line, NULL,
     NULL},
    {(char *)"New/Destroy htpasswd", test_new_destroy_htpasswd, NULL, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_SUITE_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"jwt server tests", all_tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
