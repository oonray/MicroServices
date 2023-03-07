#include "handlers.h"
#include "mongoose/mongoose.h"

void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
error:
  def(c, ev, ev_data, fn_data);
}
void def(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  mg_http_reply(c, 404, "", "Not Found");
}
