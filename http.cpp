#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef enum {
  PARSE_OK = 0,
  PARSE_ERR_NO_METHOD,
  PARSE_ERR_BAD_METHOD,
  PARSE_ERR_NO_PATH,
  PARSE_ERR_BAD_PATH,
  PARSE_ERR_NO_VERSION,
  PARSE_ERR_BAD_VERSION,
  PARSE_ERR_UNSUPPORTED_VERSION
} ParseResult;

typedef enum { M_GET, M_HEAD, M_POST, M_UNKNOWN } Method;

typedef enum { HTTP_V0_9, HTTP_V_1, BAD_VERSION, UNSUPPORTED_VERSION } Version;

Method method_parser(const char *method);
char *path_parser(char *path);
Version version_parser(char *version);

ParseResult request_line_parser(char *request_line, Method *method, char **path,
                                Version *version) {
  char *str_method = strtok(request_line, " ");
  if (!str_method)
    return PARSE_ERR_NO_METHOD;

  *method = method_parser(str_method);
  if (*method == M_UNKNOWN)
    return PARSE_ERR_BAD_METHOD;

  char *str_path = strtok(NULL, " ");
  if (!str_path)
    return PARSE_ERR_NO_PATH;
  *path = path_parser(str_path);
  if (!*path)
    return PARSE_ERR_BAD_PATH;

  char *str_version = strtok(NULL, " \r\n");
  if (!str_version)
    return PARSE_ERR_NO_VERSION;
  *version = version_parser(str_version);
  if (*version == BAD_VERSION)
    return PARSE_ERR_BAD_VERSION;
  if (*version == UNSUPPORTED_VERSION)
    return PARSE_ERR_UNSUPPORTED_VERSION;

  return PARSE_OK;
}

Method method_parser(const char *method) {
  if (strcmp(method, "GET") == 0)
    return M_GET;
  if (strcmp(method, "HEAD") == 0)
    return M_HEAD;
  if (strcmp(method, "POST") == 0)
    return M_POST;
  return M_UNKNOWN;
}

Version version_parser(const char *version) {
  if (strlen(version) != 8)
    return BAD_VERSION;
  if (version[0] != 'H' || version[1] != 'T' || version[2] != 'T' ||
      version[3] != 'P' || version[4] != '/' || !isdigit(version[5]) ||
      version[6] != '.' || !isdigit(version[7]))
    return BAD_VERSION;
  if (version[5] == '1' && version[7] == '0')
    return HTTP_V_1;
  if (version[5] == '0' && version[7] == '9')
    return HTTP_V0_9;
  return UNSUPPORTED_VERSION;
}
