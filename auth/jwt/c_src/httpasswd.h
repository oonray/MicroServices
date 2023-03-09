#ifndef HTTPASSWD_H_
#define HTTPASSWD_H_

#include <caaa/bstrlib.h>
#include <caaa/fileio.h>

typedef struct m_jwt_htpasswd {
  bstring name;
  ioStream *stream;
  bstring data;
} m_jwt_htpasswd;

m_jwt_htpasswd *m_jwt_htpasswd_new(bstring name);
void m_jwt_htpasswd_destroy(m_jwt_htpasswd *htp);

#endif // HTTPASSWD_H_
