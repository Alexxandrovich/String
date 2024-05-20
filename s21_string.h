#ifndef S21_STRING_H
#define S21_STRING_H
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#define S21_NULL (void *)0
typedef unsigned long s21_size_t;

typedef struct Params {
  int flag_right;
  int flag_plus;
  int flag_space;
  int flag_description;
  int flag_width;
  int width;
  int description;
  int flag_short;
  int flag_long;
} Params;

int s21_sprintf(char *str, const char *format, ...);
void i_to_str(long int n, char *str, int *j, Params *params, int direct,
              int *count_return);
void f_to_str(long double f, char *str, int *j, Params *params, int direct,
              int *count_return);
int count_digits(long int n);
void init_struct_flags(Params *params);
void flags_width_desc(char *str, int *j, Params *params, int *count_space,
                      int sign, int first, int *count_return);
void min_cat(char *str, int *j, const char *x, Params *params,
             int *count_return);
int own_atoi(const char *str, int *i);
void char_to_str(char *str, int *j, Params *params, char x, int *count_return);
void str_to_str(char *str, int *j, Params *params, char *x, int *count_return);
int is_short_spec(int c);
void parse(Params *params, int *count_return, char *str, const char *format,
           int *j, va_list args);

int s21_atoi(const char *str);
void *s21_trim(const char *src, const char *trim_chars);
int is_trim_chars(char c, const char *trim_chars);
void begin_trim(const char *src, int *j, const char *trim_chars);
int is_end_trim(const char *src, int *k, const char *trim_chars);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void add_str(const char *str, char **out, int *i);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);

typedef struct struct_format_scanf {
  int suppress;
  int width;
  char length;
  char specifier;
} format_scanf_type;

s21_size_t s21_strcspn(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);

s21_size_t s21_strlen(const char *str);
void *s21_memchr(const void *str, int c, s21_size_t n);
char *s21_strchr(const char *str, int c);
char *s21_strrchr(const char *str, int c);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strerror(int errnum);
char *s21_strtok(char *str, const char *delim);

int find_spec_start(char **string_input, char **format_string);
int is_white_space(char c);

long long parse_hex(char *line, int width, int *offset);
long long parse_oct(char *line, int width, int *offset);
long long parse_dec(char *line, int width, int *offset);
int parse_string(char **line, format_scanf_type opt, char *dest);
int parse_char(char **line, char *ch);
int parse_ldouble(char *line, long double *ld, int width, int *offset);
int is_char_in(char ch, char *ptr);
void skip_white_spaces(char **line);
int format_parse_2(char **empty, format_scanf_type *tryout);
int s21_atoui(char **str);
int s21_sscanf(const char *str, const char *format, ...);

int scan_d(char **str, va_list arg, format_scanf_type opt);
int scan_o(char **str, va_list arg, format_scanf_type opt);
int scan_x(char **str, va_list arg, format_scanf_type opt);
int scan_i(char **str, va_list arg, format_scanf_type opt);
int scan_ld(char **str, va_list arg, format_scanf_type opt);
int scan_s(char **str, va_list arg, format_scanf_type opt);
int scan_c(char **str, va_list arg);
void scan_n(const char *str, va_list arg, const char *st);
int scan_p(char **str, va_list arg, format_scanf_type opt);

// int s21_ato_i(char *str);

#if defined(__APPLE__)
#define MAX_ERROR 106
#define ERR_LIST                                                               \
  {                                                                            \
    "Undefined error: 0", "Operation not permitted",                           \
        "No such file or directory", "No such process",                        \
        "Interrupted system call", "Input/output error",                       \
        "Device not configured", "Argument list too long",                     \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource deadlock avoided", "Cannot allocate memory",                 \
        "Permission denied", "Bad address", "Block device required",           \
        "Resource busy", "File exists", "Cross-device link",                   \
        "Operation not supported by device", "Not a directory",                \
        "Is a directory", "Invalid argument", "Too many open files in system", \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain", "Result too large", \
        "Resource temporarily unavailable", "Operation now in progress",       \
        "Operation already in progress", "Socket operation on non-socket",     \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol family",                     \
        "Address already in use", "Can't assign requested address",            \
        "Network is down", "Network is unreachable",                           \
        "Network dropped connection on reset",                                 \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available", "Socket is already connected",            \
        "Socket is not connected", "Can't send after socket shutdown",         \
        "Too many references: can't splice", "Operation timed out",            \
        "Connection refused", "Too many levels of symbolic links",             \
        "File name too long", "Host is down", "No route to host",              \
        "Directory not empty", "Too many processes", "Too many users",         \
        "Disc quota exceeded", "Stale NFS file handle",                        \
        "Too many levels of remote in path", "RPC struct is bad",              \
        "RPC version wrong", "RPC prog. not avail", "Program version wrong",   \
        "Bad procedure for program", "No locks available",                     \
        "Function not implemented", "Inappropriate file type or format",       \
        "Authentication error", "Need authenticator", "Device power is off",   \
        "Device error", "Value too large to be stored in data type",           \
        "Bad executable (or shared library)", "Bad CPU type in executable",    \
        "Shared library version mismatch", "Malformed Mach-o file",            \
        "Operation canceled", "Identifier removed",                            \
        "No message of desired type", "Illegal byte sequence",                 \
        "Attribute not found", "Bad message", "EMULTIHOP (Reserved)",          \
        "No message available on STREAM", "ENOLINK (Reserved)",                \
        "No STREAM resources", "Not a STREAM", "Protocol error",               \
        "STREAM ioctl timeout", "Operation not supported on socket",           \
        "Policy not found", "State not recoverable", "Previous owner died",    \
        "Interface output queue is full"                                       \
  }

#elif defined(__linux__)
#define MAX_ERROR 133
#define ERR_LIST                                                               \
  {                                                                            \
    "Success", "Operation not permitted", "No such file or directory",         \
        "No such process", "Interrupted system call", "Input/output error",    \
        "No such device or address", "Argument list too long",                 \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource temporarily unavailable", "Cannot allocate memory",          \
        "Permission denied", "Bad address", "Block device required",           \
        "Device or resource busy", "File exists", "Invalid cross-device link", \
        "No such device", "Not a directory", "Is a directory",                 \
        "Invalid argument", "Too many open files in system",                   \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain",                     \
        "Numerical result out of range", "Resource deadlock avoided",          \
        "File name too long", "No locks available",                            \
        "Function not implemented", "Directory not empty",                     \
        "Too many levels of symbolic links", "Unknown error 41",               \
        "No message of desired type", "Identifier removed",                    \
        "Channel number out of range", "Level 2 not synchronized",             \
        "Level 3 halted", "Level 3 reset", "Link number out of range",         \
        "Protocol driver not attached", "No CSI structure available",          \
        "Level 2 halted", "Invalid exchange", "Invalid request descriptor",    \
        "Exchange full", "No anode", "Invalid request code", "Invalid slot",   \
        "Unknown error 58", "Bad font file format", "Device not a stream",     \
        "No data available", "Timer expired", "Out of streams resources",      \
        "Machine is not on the network", "Package not installed",              \
        "Object is remote", "Link has been severed", "Advertise error",        \
        "Srmount error", "Communication error on send", "Protocol error",      \
        "Multihop attempted", "RFS specific error", "Bad message",             \
        "Value too large for defined data type", "Name not unique on network", \
        "File descriptor in bad state", "Remote address changed",              \
        "Can not access a needed shared library",                              \
        "Accessing a corrupted shared library",                                \
        ".lib section in a.out corrupted",                                     \
        "Attempting to link in too many shared libraries",                     \
        "Cannot exec a shared library directly",                               \
        "Invalid or incomplete multibyte or wide character",                   \
        "Interrupted system call should be restarted", "Streams pipe error",   \
        "Too many users", "Socket operation on non-socket",                    \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol", "Address already in use",  \
        "Cannot assign requested address", "Network is down",                  \
        "Network is unreachable", "Network dropped connection on reset",       \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available",                                           \
        "Transport endpoint is already connected",                             \
        "Transport endpoint is not connected",                                 \
        "Cannot send after transport endpoint shutdown",                       \
        "Too many references: cannot splice", "Connection timed out",          \
        "Connection refused", "Host is down", "No route to host",              \
        "Operation already in progress", "Operation now in progress",          \
        "Stale file handle", "Structure needs cleaning",                       \
        "Not a XENIX named type file", "No XENIX semaphores available",        \
        "Is a named type file", "Remote I/O error", "Disk quota exceeded",     \
        "No medium found", "Wrong medium type", "Operation canceled",          \
        "Required key not available", "Key has expired",                       \
        "Key has been revoked", "Key was rejected by service", "Owner died",   \
        "State not recoverable", "Operation not possible due to RF-kill",      \
        "Memory page has hardware error"                                       \
  }
#endif

#endif
