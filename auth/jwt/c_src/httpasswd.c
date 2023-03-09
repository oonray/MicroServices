#include "httpasswd.h"

m_jwt_htpasswd *m_jwt_htpasswd_new(bstring name) {
  m_jwt_htpasswd *file = calloc(1, sizeof(m_jwt_htpasswd));
  check(file != NULL, "Could not allocate");

  file->name = name;
  check(IoFileStream_DirectoryExists(file->name) == 0,
        "Must create htfile prior to reading it");

  file->stream = NewIoStreamFile(file->name, FILEFD, 0);
  check(file->stream != NULL, "Could not create file stream");

  IoStreamIoRead(file->stream);
  file->data = IoStreamBuffRead(file->stream);
  check(file->data != NULL, "Could not read the stream buffer");
  DestroyIoStream(file->stream);

  return file;
error:
  m_jwt_htpasswd_destroy(file);
  return NULL;
}

void m_jwt_htpasswd_destroy(m_jwt_htpasswd *htp) {
  if (htp->stream != NULL)
    DestroyIoStream(htp->stream);
  if (htp->data != NULL)
    bdestroy(htp->data);
  if (htp->name != NULL)
    bdestroy(htp->name);
  if (htp != NULL)
    free(htp);
}
