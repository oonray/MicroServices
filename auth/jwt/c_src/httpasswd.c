#include "httpasswd.h"
#include "bstring/bstrlib.h"
#include <caaa/vector.h>

m_jwt_htpasswd *m_jwt_htpasswd_new(bstring name) {
  m_jwt_htpasswd *file = calloc(1, sizeof(m_jwt_htpasswd));
  check(file != NULL, "Could not allocate");

  file->name = name;
  check(IoFileStream_FileExists(file->name) == 0,
        "Must create htfile prior to reading it");

  file->lines = Vector_New(sizeof(m_jwt_htpasswd_line), 5);
  check(file->lines != NULL, "lines not created")

      file->stream = NewIoStreamFile(file->name, O_RDWR, 0);
  check(file->stream != NULL, "Could not create file stream");

  IoStreamIoRead(file->stream);
  bstring data = IoStreamBuffRead(file->stream);
  struct bstrList *lines = bsplit(data, '\n');

  for (int i = 0; i < lines->qty; i++) {
    m_jwt_htpasswd_line *line = m_jwt_htpasswd_line_new(lines->entry[i]);
    Vector_Push(file->lines, line);
  }

  return file;
error:
  m_jwt_htpasswd_destroy(file);
  return NULL;
}

void m_jwt_htpasswd_destroy(m_jwt_htpasswd *htp) {
  if (htp->stream != NULL)
    DestroyIoStream(htp->stream);
  if (htp->name != NULL)
    bdestroy(htp->name);
  if (htp->lines != NULL)
    Vector_Destroy(htp->lines);
  if (htp != NULL)
    free(htp);
}

m_jwt_htpasswd_line *m_jwt_htpasswd_line_new(bstring line) {
  m_jwt_htpasswd_line *ln = calloc(1, sizeof(m_jwt_htpasswd_line));
  check(ln != NULL, "Cold not allocate line");

  struct bstrList *usr_pass = bsplit(line, ':');
  check(usr_pass->qty == 2, "Malformed line should be 2 got %d", usr_pass->qty);

  ln->user = usr_pass->entry[0];
  check(ln->user != NULL, "user is null");

  ln->password_s = usr_pass->entry[1];
  check(ln->password_s != NULL, "pass string is null");

  ln->password = m_jwt_htpasswd_line_get_pass_type(ln->password_s);
  check(ln->password != NULL, "pass is null");

  return ln;
error:
  return NULL;
}

void m_jwt_htpasswd_line_destroy(m_jwt_htpasswd_line *line) {
  if (line->password)
    m_jwt_htpasswd_line_password_destroy(line->password);
  if (line->user != NULL)
    bdestroy(line->user);
  if (line->password_s != NULL)
    bdestroy(line->password_s);
  if (line->password)
    m_jwt_htpasswd_line_password_destroy(line->password);
  free(line);
}

m_jwt_htpasswd_line_password *m_jwt_htpasswd_line_get_pass_type(bstring pass) {
  for (int i = A_BCRYPT; i < A_LAST; i++) {
    bstring data = bfromcstr(ALGO_S[i]);
    if (bstrnicmp(data, pass, blength(data)) == 0) {
      m_jwt_htpasswd_line_password *pa =
          calloc(1, sizeof(m_jwt_htpasswd_line_password));
      check(pa != NULL, "Could not allocate pass");

      pa->data = pass;
      pa->type = data;
      pa->crypt = i;

      return pa;
    }
  }
error:
  return NULL;
}

void m_jwt_htpasswd_line_password_destroy(m_jwt_htpasswd_line_password *pass) {
  if (pass->type != NULL)
    free(pass->type);
  if (pass->data != NULL)
    free(pass->data);
  free(pass);
}
