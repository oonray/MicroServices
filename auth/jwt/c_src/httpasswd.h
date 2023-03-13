#ifndef HTTPASSWD_H_
#define HTTPASSWD_H_

#include <bstring/bstrlib.h>
#include <caaa/fileio.h>
#include <caaa/vector.h>

typedef enum ALGO {
  A_BCRYPT,
  A_MD5,
  A_SHA1,
  A_LAST,
} ALGO;

static char *ALGO_S[3] = (char *[]){
    "$2y$",
    "$apr1$",
    "{SHA}",
};

typedef struct m_jwt_htpasswd_line_password {
  int crypt;
  bstring type;
  bstring data;
} m_jwt_htpasswd_line_password;

typedef struct m_jwt_htpasswd_line {
  bstring user;
  bstring password_s;
  m_jwt_htpasswd_line_password *password;
} m_jwt_htpasswd_line;

typedef struct m_jwt_htpasswd {
  bstring name;
  ioStream *stream;
  Vector *lines;
} m_jwt_htpasswd;

m_jwt_htpasswd *m_jwt_htpasswd_new(bstring name);
void m_jwt_htpasswd_destroy(m_jwt_htpasswd *htp);

m_jwt_htpasswd_line *m_jwt_htpasswd_line_new(bstring line);
void m_jwt_htpasswd_line_destroy(m_jwt_htpasswd_line *line);

m_jwt_htpasswd_line_password *m_jwt_htpasswd_line_get_pass_type(bstring pass);

void m_jwt_htpasswd_line_password_destroy(m_jwt_htpasswd_line_password *pass);

#endif // HTTPASSWD_H_
