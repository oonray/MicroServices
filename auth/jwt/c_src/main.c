#include "mongoose/mongoose.h"
#include <caaa/argparse.h>
#include <caaa/bstrlib.h>
#include <caaa/dbg.h>
#include <server.h>

ArgumentParser *args = NULL;
m_jwt_server *srv = NULL;

int parse_args(int argc, char *argv[]) {
  args = Argparse_New_Argument_Parser(bfromcstr("JWT Token Server"),
                                      bfromcstr(argv[0]));

  check(args != NULL, "Could not create parser");

  check(Argparse_Add_String(args, "-H", "host", "0.0.0.0",
                            "The host to bind to") > 0,
        "Could not add host arg");
  check(Argparse_Add_Int(args, "-P", "port", "8080", "The port to bind to") > 0,
        "Could not add port arg");

  check(Argparse_Add_String(args, "-Hp", "host_file", ".htpasswd",
                            "The htpass file to atuh to") > 0,
        "Could not add host_file arg");

  check(Argparse_Parse(args, argc, argv) == 0, "Could not parse args");
  return 0;
error:
  return 1;
}

int main(int argc, char *argv[]) {
  check(parse_args(argc, argv) == 0, "Couls not parse arguments");

  Argument *host = Argparse_Get(args, bfromcstr("host"));
  check(host->value != NULL, "Could not get host value");

  Argument *port = Argparse_Get(args, bfromcstr("port"));
  check(port->value != NULL, "Could not get port value");

  bstring bind = bformat("%s:%s", bdata(host->value), bdata(port->value));
  log_info("Try to listen on %s", bdata(bind));

  srv = m_jwt_server_new(bind);

  check(srv != NULL, "Could not create the server");

  m_jwt_server_listen_serve(srv);
error:
  if (args != NULL) {
    Argparse_Destroy(args);
  }
  if (srv != NULL) {
    m_jwt_server_destroy(srv);
  }
}
