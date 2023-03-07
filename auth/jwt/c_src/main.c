#include "mongoose/mongoose.h"
#include <caaa/bstrlib.h>
#include <caaa/dbg.h>
#include <server.h>

int main(int argc, char *argv[]) {
  m_jwt_server *srv = m_jwt_server_new(bfromcstr("0.0.0.0:8000"));
  check(srv != NULL, "Could not create the server");

  m_jwt_server_listen_serve(srv);
error:
  m_jwt_server_destroy(srv);
}
