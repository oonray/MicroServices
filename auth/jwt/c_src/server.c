#include "server.h"
#include "mongoose/mongoose.h"

m_jwt_server *m_jwt_server_new(bstring listen_addr) {
  m_jwt_server *srv = calloc(1, sizeof(m_jwt_server));
  check(srv != NULL, "Could not allocate jwt server");

  srv->listen_addr = listen_addr;

  srv->mgr = calloc(1, sizeof(struct mg_mgr));
  check(srv->mgr != NULL, "Could not allocate jwt server");
  mg_mgr_init(srv->mgr);
  return srv;

error:
  m_jwt_server_destroy(srv);
  return NULL;
}

void m_jwt_server_destroy(m_jwt_server *srv) {
  if (srv->mgr != NULL)
    mg_mgr_free(srv->mgr);
  if (srv != NULL)
    free(srv);
}

void m_jwt_server_listen_serve(m_jwt_server *srv) {
  mg_listen(srv->mgr, bdata(srv->listen_addr), fn, NULL);
  log_info("Listening on %s", bdata(srv->listen_addr));
  for (;;)
    mg_mgr_poll(srv->mgr, 1000);
}
