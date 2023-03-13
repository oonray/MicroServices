#ifndef SERVER_H_
#define SERVER_H_

#include <bstring/bstrlib.h>
#include <caaa/dbg.h>
#include <handlers.h>
#include <mongoose/mongoose.h>

typedef void (*handler)(struct mg_connection *c, int ev, void *ev_data,
                        void *fn_data);

typedef struct m_jwt_server {
  struct mg_mgr *mgr;
  bstring listen_addr;
  handler handler;
} m_jwt_server;

m_jwt_server *m_jwt_server_new(bstring listen_addr);
void m_jwt_server_destroy(m_jwt_server *srv);
void m_jwt_server_listen_serve(m_jwt_server *srv);

#endif // SERVER_H_
