#ifndef HANDLERS_H_
#define HANDLERS_H_

#include "mongoose/mongoose.h"

void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
void def(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

#endif // HANDLERS_H_
