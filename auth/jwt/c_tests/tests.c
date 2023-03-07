#include <caaa/bstrlib.h>
#include <munit/munit.h>
#include <server.h>

static struct tagbstring t_lisn = bsStatic("0.0.0.0:8000");

static MunitResult test_new_destroy(const MunitParameter params[], void *data) {
  m_jwt_server *srv = m_jwt_server_new(&t_lisn);

  munit_assert_not_null(srv);
  munit_assert_not_null(srv->mgr);

  munit_assert_false(bstrcmp(&t_lisn, srv->listen_addr) != 0);

  m_jwt_server_destroy(srv);
  return MUNIT_OK;
}
