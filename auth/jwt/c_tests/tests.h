#include <bstring/bstrlib.h>
#include <caaa/dbg.h>
#include <httpasswd.h>
#include <munit/munit.h>
#include <openssl/aes.h>
#include <server.h>

static struct tagbstring t_lisn = bsStatic("0.0.0.0:8000");
static struct tagbstring t_htfile = bsStatic("../c_tests/htpass.test");
static struct tagbstring t_pass = bsStatic("password123");

char *ALGO_U[] = (char *[]){
    "alex",
    "alex1",
    "alex2",
};

char *ALGO_P[] = (char *[]){
    "$2y$05$tVC.a/FSPgDUhRGpwQ.wmOx7u461rAnWPuInvSLV1.Ad3mCalvcoa",
    "$apr1$USozhgOS$1Sq1jkg4jvKiB5gWdsnnx1",
    "{SHA}y/2sYAj5yrQIN4TL0YdPdmGNKpc=",
};

static MunitResult test_new_destroy(const MunitParameter params[], void *data) {
  m_jwt_server *srv = m_jwt_server_new(&t_lisn);

  munit_assert_not_null(srv);
  munit_assert_not_null(srv->mgr);

  munit_assert_false(bstrcmp(&t_lisn, srv->listen_addr) != 0);

  m_jwt_server_destroy(srv);
  return MUNIT_OK;
error:
  return MUNIT_FAIL;
}

static MunitResult test_new_destroy_htpasswd(const MunitParameter params[],
                                             void *data) {

  m_jwt_htpasswd *file = m_jwt_htpasswd_new(&t_htfile);
  munit_assert_not_null(file);

  m_jwt_htpasswd_destroy(file);

  return MUNIT_OK;
error:
  return MUNIT_FAIL;
}

static MunitResult test_new_destroy_htpasswd_line(const MunitParameter params[],
                                                  void *data) {
  m_jwt_htpasswd *file = m_jwt_htpasswd_new(&t_htfile);
  munit_assert_not_null(file);

  m_jwt_htpasswd_line *line = (m_jwt_htpasswd_line *)file->lines->contents[0];
  log_info("%s, %s, %s", bdata(line->user), bdata(line->password->type),
           bdata(line->password_s));

  return MUNIT_OK;
error:
  return MUNIT_FAIL;
}
