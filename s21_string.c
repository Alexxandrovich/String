#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t total = 0;
  s21_size_t flag = 1;
  for (s21_size_t t = 0; t < s21_strlen(str1) && flag != 0; t++) {
    for (s21_size_t p = 0; p < s21_strlen(str2); p++) {
      if (str1[t] == str2[p]) {
        flag = 0;
      }
    }
    if (flag) {
      ++total;
    }
  }
  return total;
}

int s21_strncmp(
    const char *str1, const char *str2,
    s21_size_t n)  // сравнивает не более первых n байтов(знаков) str1 и str2
{
  int result = 0;
  if (n) {
    const char *end = str1 + n;

    for (; result == 0 && str1 != end && (*str1 || *str2);
         result = *(str1++) - *(str2++))
      ;
  }

  return result;
}

int s21_memcmp(
    const void *str1, const void *str2,
    s21_size_t n)  // сравнивает не более первых n байтов(знаков) str1 и str2
{
  const unsigned char *s1 = str1, *s2 = str2;
  int flag = 0, result = 0;
  for (s21_size_t i = 0; (i < n) && (flag == 0); i++, s1++, s2++) {
    if (*s1 != *s2) {
      result = (*s1 < *s2) ? -1 : 1;
      flag++;
    }
  }
  return result;
}

char *s21_strncpy(char *dest, const char *src,
                  s21_size_t n)  // Копирует до n символов из строки, на которую
                                 // указывает src, в dest
{
  if (n) {
    s21_size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
      dest[i] = src[i];
    }
    for (; i < n; i++) {
      dest[i] = '\0';
    }
  }

  return dest;
}

void *s21_memcpy(void *dest, const void *src,
                 s21_size_t n)  // Копирует n символов из src в dest
{
  if (n) {
    char *tmp_dest = (char *)dest;
    const char *tmp_src = (char *)src;
    for (s21_size_t i = 0; i < n; ++i) *tmp_dest++ = *tmp_src++;
  }

  return dest;
}

void *s21_memset(void *str, int c,
                 s21_size_t n)  // заполняет str сиволом c  n байтов
{
  if (n) {
    if (str) {
      char *tmp_str = (char *)str;
      for (s21_size_t i = 0; i < n; i++) {
        *tmp_str++ = c;
      }
    }
  }

  return str;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;

  if (str) {
    for (int i = 0; str[i]; i++) {
      len++;
    }
  }

  return len;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *res = S21_NULL;
  char *ptr = (char *)str;

  for (s21_size_t i = 0; i < n && ptr && !res; i++, ptr++) {
    if (*ptr == c) {
      res = ptr;
    }
  }

  return res;
}

char *s21_strchr(const char *str, int c) {
  char *res = S21_NULL;

  for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
    if (str[i] == c) {
      res = (char *)str + i;
      break;
    }
  }

  return res;
}

char *s21_strrchr(const char *str, int c) {
  char *res = S21_NULL;
  s21_size_t len = s21_strlen(str);

  for (int i = len; i >= 0 && !res; i--) {
    if (str[i] == c) {
      res = (char *)str + i;
    }
  }

  return res;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = S21_NULL;

  for (; *str1 != '\0' && !res; str1++) {
    if (s21_strchr(str2, *str1)) {
      res = (char *)str1;
    }
  }

  return res;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = S21_NULL;
  s21_size_t hst_len = s21_strlen(haystack);
  s21_size_t ndl_len = s21_strlen(needle);

  if (hst_len >= ndl_len) {
    for (s21_size_t i = 0; i <= hst_len - ndl_len; i++) {
      int flag = 1;
      for (s21_size_t j = i, k = 0; needle[k]; k++, j++) {
        if (haystack[j] != needle[k]) {
          flag = 0;
          break;
        }
      }
      if (flag) {
        res = (char *)haystack + i;
        break;
      }
    }
  }
  return res;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t destLen = s21_strlen(dest);
  s21_size_t t = 0;
  for (t = 0; t < n && src[t] != '\0'; t++) {
    dest[destLen + t] = src[t];
  }
  dest[destLen + t] = '\0';
  return dest;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t res = 0;

  for (s21_size_t i = 0; str1[i]; i++) {
    s21_size_t ptr = 0;
    ptr = res;
    for (s21_size_t j = 0; str2[j]; j++) {
      if (str1[i] == str2[j]) {
        res++;
        break;
      }
    }
    if (ptr == res) break;
  }

  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char *tmp = S21_NULL;
  if (str) tmp = str;

  if (tmp) {
    str = tmp + s21_strspn(tmp, delim);
    tmp = str + s21_strcspn(str, delim);

    if (*tmp != '\0') {
      *tmp = '\0';
      tmp++;
    }
  }

  return *str != '\0' ? str : S21_NULL;
}

char *s21_strerror(int errnum) {
  static char message[64];
  char *err_list[] = ERR_LIST;

  if (errnum >= 0 && errnum <= MAX_ERROR) {
    s21_sprintf(message, "%s", err_list[errnum]);
  } else {
#ifdef __APPLE__
    s21_sprintf(message, "Unknown error: %d", errnum);
#elif __linux__
    s21_sprintf(message, "Unknown error %d", errnum);
#endif
  }

  return message;
}

int format_parse_2(char **empty, format_scanf_type *tryout) {
  if (**empty != '%') return 1;
  (*empty)++;
  if (**empty == '*') {
    tryout->suppress = 1;
    (*empty)++;
  }
  tryout->width = s21_atoui(empty);
  if (is_char_in(**empty, "hlL")) {
    tryout->length = **empty;
    (*empty)++;
  }

  if (is_char_in(**empty, "diouxXfFeEgGaAcspn%")) {
    tryout->specifier = **empty;
    (*empty)++;
  }

  return tryout->specifier == '\0';
}

int is_char_in(char ch, char *ptr) {
  int result = 0;
  while (*ptr != '\0') {
    if (*ptr == ch) result = 1;
    ptr++;
  }
  return result;
}

int s21_atoui(char **str) {
  int result = 0;
  while (**str && **str >= '0' && **str <= '9') {
    result = result * 10 + (**str) - 48;
    (*str)++;
  }
  return result;
}

int find_spec_start(char **string_input, char **format_string) {
  int res = 0;
  while (res == 0 && **string_input != '\0' && **format_string != '\0' &&
         **format_string != '%') {
    if (is_white_space(**string_input) && is_white_space(**format_string)) {
      while (is_white_space(**string_input)) (*string_input)++;
      while (is_white_space(**format_string)) (*format_string)++;
      res = 0;
    } else if (!is_white_space(**string_input) &&
               is_white_space(**format_string)) {
      while (is_white_space(**format_string)) (*format_string)++;
      if (**format_string == '%')
        res = 0;
      else
        res = 1;
    } else if ((**string_input) == (**format_string)) {
      (*string_input)++;
      (*format_string)++;
      if ((**string_input) == '\0' || (**format_string) == '\0') res = 1;
    } else
      res = 1;
  }
  return res;
}

int is_white_space(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r' ||
         c == '\v';
}

long long parse_dec(char *line, int width, int *offset) {
  char *start = line;
  int minus = 0;
  if (width == 0) width = 1000000000;
  if (*line == '+') {
    width--;
    line++;
  } else if (*line == '-') {
    line++;
    width--;
    minus = 1;
  }

  long long number = 0;
  int end = 0;
  while (*line && !end && width) {
    if (*line >= '0' && *line <= '9')
      number = number * 10 + (*line) - 48;
    else
      end = 1;
    if (!end) line++;
    width--;
  }
  if (minus) number = -1 * number;
  *offset = line - start;
  return number;
}

int parse_ldouble(char *line, long double *ld, int width, int *offset) {
  *ld = 0;
  char *start = line;
  int minus = 0;
  if (width == 0) width = 1000000000;
  if (*line == '+') {
    width--;
    line++;
  } else if (*line == '-') {
    line++;
    width--;
    minus = 1;
  }
  int end = 0;
  while (*line && !end && width) {
    if (*line >= '0' && *line <= '9') {
      (*ld) = (*ld) * 10 + (*line) - 48;
    } else
      end = 1;
    if (!end) line++;
    width--;
  }
  if (*line == '.' && width) {
    line++;
    end = 0;
    long double ten_mult = 10;
    while (*line && !end && width) {
      if (*line >= '0' && *line <= '9') {
        (*ld) = (*ld) + ((*line) - 48) / ten_mult;
        ten_mult *= 10;
      } else
        end = 1;
      if (!end) line++;
      width--;
    }
  }
  if (width && (*line == 'e' || *line == 'E')) {
    end = 0;
    line++;
  }
  char e_sign = '+';
  if (width && (*line == '+' || *line == '-')) {
    e_sign = *line;
    line++;
    width--;
  }
  int e_num = 0;
  while (*line && !end && width) {
    if (*line >= '0' && *line <= '9') {
      e_num = e_num * 10 + (*line) - 48;
    } else
      end = 1;
    if (!end) line++;
    width--;
  }
  if (e_sign == '+') {
    for (int i = 0; i < e_num; i++) *ld = (*ld) * 10;
  } else {
    for (int i = 0; i < e_num; i++) *ld = (*ld) / 10;
  }
  if (minus) (*ld) = -1 * (*ld);
  *offset = line - start;
  return 0;
}

long long parse_oct(char *line, int width, int *offset) {
  char *start = line;
  int minus = 0;
  if (width == 0) width = 1000000000;
  if (*line == '+') {
    width--;
    line++;
  } else if (*line == '-') {
    line++;
    width--;
    minus = 1;
  }

  long long number = 0;
  int end = 0;
  while (*line && !end && width) {
    if (*line >= '0' && *line <= '7')
      number = (number << 3) + (*line) - 48;
    else
      end = 1;
    if (!end) line++;
    width--;
  }
  if (minus) number = -1 * number;
  *offset = line - start;
  return number;
}

long long parse_hex(char *line, int width, int *offset) {
  char *start = line;
  while (is_white_space(*line)) line++;
  int minus = 0;
  if (width == 0) width = 1000000000;
  if (*line == '+') {
    width--;
    line++;
  } else if (*line == '-') {
    line++;
    width--;
    minus = 1;
  }

  if (((width > 1) && *line == '0' && *(line + 1) == 'x') ||
      ((width > 1) && *line == '0' && (*(line + 1) == 'X'))) {
    line += 2;
    width -= 2;
  }
  long long number = 0;
  int end = 0;
  while (*line && !end && width) {
    if (*line >= '0' && *line <= '9')
      number = (number << 4) + (*line) - 48;
    else if (*line >= 'a' && *line <= 'f')
      number = (number << 4) + (*line) - 87;
    else if (*line >= 'A' && *line <= 'F')
      number = (number << 4) + (*line) - 55;
    else
      end = 1;
    if (!end) line++;
    width--;
  }
  if (minus) number = -1 * number;
  *offset = line - start;
  return number;
}

int parse_string(char **line, format_scanf_type opt, char *dest) {
  int width = opt.width;
  if (width == 0) width = 1000000;
  char *start_white_space = *line;
  while (width > 0 && **line != '\0' && !is_white_space(**line)) {
    if (opt.suppress == 0) {
      *dest = **line;
      dest++;
    }
    (*line)++;
    (width)--;
  }
  if (opt.suppress == 0) *dest = '\0';
  return (*line) - start_white_space;
}

int parse_char(char **line, char *ch) {
  if (**line == '\0')
    return 0;
  else {
    *ch = **line;
    (*line)++;
    return 1;
  }
}

int s21_sscanf(const char *str, const char *format, ...) {
  int result = 0;
  char *format_start = (char *)str;
  char *format_p = (char *)format;
  char *str_p = (char *)str;
  int error = 0;
  va_list arg;
  va_start(arg, format);
  format++;
  while (error == 0 && *format) {
    format_scanf_type options = {
        .suppress = 0, .width = 0, .length = '\0', .specifier = '\0'};
    find_spec_start(&str_p, &format_p);
    if (!format_parse_2(&format_p, &options)) {
      switch (options.specifier) {
        case '%':
          if (*str_p == '%')
            str_p++;
          else
            error = 1;
          break;
        case 'd':
        case 'u':
          result += scan_d(&str_p, arg, options);
          break;
        case 'o':
          result += scan_o(&str_p, arg, options);
          break;
        case 'X':
        case 'x':
          result += scan_x(&str_p, arg, options);
          break;
        case 'i':
          result += scan_i(&str_p, arg, options);
          break;
        case 'f':
        case 'e':
        case 'g':
        case 'E':
        case 'G':
          result += scan_ld(&str_p, arg, options);
          break;
        case 's':
          result += scan_s(&str_p, arg, options);
          break;
        case 'c':
          result += scan_c(&str_p, arg);
          break;
        case 'n':
          scan_n(str_p, arg, format_start);
          break;
        case 'p':
          result += scan_p(&str_p, arg, options);
          break;
      }
    } else {
      error = 1;
    }
    if (options.suppress == 0 && options.specifier != '%' &&
        options.specifier != 'n')
      format++;
  }
  va_end(arg);

  return result;
}

int scan_c(char **str, va_list arg) {
  char *c_ptr = va_arg(arg, char *);
  return parse_char(str, c_ptr);
}

void scan_n(const char *str, va_list arg, const char *st) {
  int *i_ptr = va_arg(arg, int *);
  *i_ptr = str - st;
}

int scan_p(char **str, va_list arg, format_scanf_type opt) {
  while (is_white_space(**str)) (*str)++;
  int offset = 0;

  s21_size_t p_tmp = (s21_size_t)parse_hex((char *)(*str), opt.width, &offset);
  if (opt.suppress != 1) {
    s21_size_t *i_ptr = va_arg(arg, s21_size_t *);
    *i_ptr = p_tmp;
  }
  *str = *str + offset;
  int result = offset > 0;
  if (opt.suppress == 1) result = 0;
  return result;
}

int scan_s(char **str, va_list arg, format_scanf_type opt) {
  while (is_white_space(**str) && (**str) != '\0') (*str)++;
  int result = 1;
  if (opt.suppress == 1) {
    char *tmp = S21_NULL;
    parse_string(str, opt, tmp);
    result = 0;
  } else {
    char *c_ptr = va_arg(arg, char *);
    result = parse_string(str, opt, c_ptr);
  }
  return result > 0;
}

int scan_d(char **str, va_list arg, format_scanf_type opt) {
  while (is_white_space(**str)) (*str)++;
  int offset = 0;

  if (opt.length == '\0') {
    int i_tmp = (int)parse_dec((char *)(*str), opt.width, &offset);
    if (opt.suppress != 1) {
      int *i_ptr = va_arg(arg, int *);
      *i_ptr = i_tmp;
    }
  } else if (opt.length == 'h') {
    short is_tmp = (short)parse_dec((char *)(*str), opt.width, &offset);
    if (opt.suppress != 1) {
      short *i_ptr = va_arg(arg, short *);
      *i_ptr = is_tmp;
    }
  } else if (opt.length == 'l') {
    long il_tmp = (long)parse_dec((char *)(*str), opt.width, &offset);
    if (opt.suppress != 1) {
      long *i_ptr = va_arg(arg, long *);
      *i_ptr = il_tmp;
    }
  } else if (opt.length == 'L') {
    long long ill_tmp =
        (long long)parse_dec((char *)(*str), opt.width, &offset);
    if (opt.suppress != 1) {
      long long *i_ptr = va_arg(arg, long long *);
      *i_ptr = ill_tmp;
    }
  }
  *str = *str + offset;
  int result = offset > 0;
  if (opt.suppress == 1) result = 0;
  return result;
}

int scan_o(char **str, va_list arg, format_scanf_type opt) {
  while (is_white_space(**str)) (*str)++;
  int offset = 0;

  if (opt.length == '\0') {
    int i_tmp = (int)parse_oct((char *)(*str), opt.width, &offset);
    if (opt.suppress != 1) {
      int *i_ptr = va_arg(arg, int *);
      *i_ptr = i_tmp;
    }
  } else if (opt.length == 'h') {
    short is_tmp = (short)parse_oct((char *)(*str), opt.width, &offset);
    if (opt.suppress != 1) {
      short *i_ptr = va_arg(arg, short *);
      *i_ptr = is_tmp;
    }
  } else if (opt.length == 'l') {
    long il_tmp = (long)parse_oct((char *)(*str), opt.width, &offset);
    if (opt.suppress != 1) {
      long *i_ptr = va_arg(arg, long *);
      *i_ptr = il_tmp;
    }
  } else if (opt.length == 'L') {
    long long ill_tmp =
        (long long)parse_oct((char *)(*str), opt.width, &offset);
    if (opt.suppress != 1) {
      long long *i_ptr = va_arg(arg, long long *);
      *i_ptr = ill_tmp;
    }
  }
  *str = *str + offset;
  int result = offset > 0;
  if (opt.suppress == 1) result = 0;
  return result;
}

int scan_x(char **str, va_list arg, format_scanf_type opt) {
  while (is_white_space(**str)) (*str)++;
  int offset = 0;
  if (opt.length == '\0') {
    int i_tmp = (int)parse_hex((char *)(*str), opt.width, &offset);
    if (opt.suppress != 1) {
      int *i_ptr = va_arg(arg, int *);
      *i_ptr = i_tmp;
    }
  } else if (opt.length == 'h') {
    short is_tmp = (short)parse_hex((char *)(*str), opt.width, &offset);
    if (opt.suppress != 1) {
      short *s_ptr = va_arg(arg, short *);
      *s_ptr = is_tmp;
    }
  } else if (opt.length == 'l') {
    long il_tmp = (long)parse_hex((char *)(*str), opt.width, &offset);
    if (opt.suppress != 1) {
      long *l_ptr = va_arg(arg, long *);
      *l_ptr = il_tmp;
    }
  } else if (opt.length == 'L') {
    long long ill_tmp =
        (long long)parse_hex((char *)(*str), opt.width, &offset);
    if (opt.suppress != 1) {
      long long *ll_ptr = va_arg(arg, long long *);
      *ll_ptr = ill_tmp;
    }
  }
  *str = *str + offset;
  int result = offset > 0;
  if (opt.suppress == 1) result = 0;
  return result;
}

int scan_i(char **str, va_list arg, format_scanf_type opt) {
  int result = 0;
  if (**str == '0') {
    if (*(1 + *str) == 'X' || *(1 + *str) == 'x') {
      result = scan_x(str, arg, opt);
    } else {
      result = scan_o(str, arg, opt);
    }
  } else {
    result = scan_d(str, arg, opt);
  }
  return result;
}

int scan_ld(char **str, va_list arg, format_scanf_type opt) {
  while (is_white_space(**str)) (*str)++;
  int offset = 0;
  if (opt.length == '\0') {
    long double i_tmp;
    parse_ldouble((char *)(*str), &i_tmp, opt.width, &offset);
    if (opt.suppress != 1) {
      float *i_ptr = va_arg(arg, float *);
      *i_ptr = (float)i_tmp;
    }
  } else if (opt.length == 'l') {
    long double il_tmp;
    parse_ldouble((char *)(*str), &il_tmp, opt.width, &offset);
    if (opt.suppress != 1) {
      double *l_ptr = va_arg(arg, double *);
      *l_ptr = (double)il_tmp;
    }
  } else if (opt.length == 'L') {
    long double ill_tmp;
    parse_ldouble((char *)(*str), &ill_tmp, opt.width, &offset);
    if (opt.suppress != 1) {
      long double *ll_ptr = va_arg(arg, long double *);
      *ll_ptr = ill_tmp;
    }
  }
  *str = *str + offset;
  int result = offset > 0;
  if (opt.suppress == 1) result = 0;
  return result;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  Params *params = (Params *)(malloc(sizeof(Params)));
  init_struct_flags(params);

  int j = 0;
  int count_return = 0;

  if (format == S21_NULL || str == S21_NULL) {
    count_return = -1;
  } else {
    parse(params, &count_return, str, format, &j, args);
    str[j] = '\0';
  }

  va_end(args);

  free(params);

  return count_return;
}

void i_to_str(long int n, char *str, int *j, Params *params, int direct,
              int *count_return) {
  int sign = n < 0 ? -1 : 1;

  if (sign < 0) {
    n = -n;
  }

  long int m = n;

  int count = count_digits(n);
  int count_space = params->width - count;

  int first = 1;

  if (!direct) {
    if (params->flag_description && count < params->description) {
      count_space = params->width - params->description;
    }

    if (params->flag_description && !params->description && !n)
      count_space += 1;
    flags_width_desc(str, j, params, &count_space, sign, first, count_return);

    if (params->flag_description) {
      int count_zero = params->description - count;
      for (int i = 0; i < count_zero; i++) {
        str[*j] = '0';
        *j += 1;
        *count_return += 1;
      }
    }
  }

  for (int i = 0; i < count; i++) {
    if (direct || !params->flag_description || params->description != 0 ||
        m != 0) {
      str[*j] = n / (long int)(pow(10, count - 1 - i)) + '0';
      n %= (long int)(pow(10, count - i - 1));
      *j += 1;
      *count_return += 1;
    }
  }

  first = 0;

  if (!direct) {
    flags_width_desc(str, j, params, &count_space, sign, first, count_return);
  }
}

void f_to_str(long double f, char *str, int *j, Params *params, int direct,
              int *count_return) {
  int sign = f < 0 ? -1 : 1;

  if (sign < 0) {
    f = -f;
  }

  int degree = 6;

  if (params->flag_description) {
    degree = params->description;
  }

  if (degree >= 18) {
    degree = 18;
  }

  long double round = 0.5 * pow(10, -degree);
  f += round;

  long int int_part = (long int)(f);
  long double dec_part = f - int_part;

  int count_int_part = count_digits(int_part);
  int count_space = params->width - count_int_part - degree - 1;

  if (!degree) count_space++;

  int first = 1;

  flags_width_desc(str, j, params, &count_space, sign, first, count_return);

  long int int_dec_part = (long int)(dec_part * pow(10, degree));
  i_to_str(int_part, str, j, params, direct, count_return);

  if (degree) {
    str[*j] = '.';
    *j += 1;
    *count_return += 1;
  }

  int count_dec_part = count_digits(int_dec_part);
  while (count_dec_part < degree) {
    str[*j] = '0';
    *j += 1;
    count_dec_part++;
    *count_return += 1;
  }

  if (degree) i_to_str(int_dec_part, str, j, params, direct, count_return);

  first = 0;

  flags_width_desc(str, j, params, &count_space, sign, first, count_return);
}

int count_digits(long int n) {
  int count = 0;

  do {
    count++;
  } while (((n /= 10)));

  return count;
}

void init_struct_flags(Params *params) {
  params->flag_right = 1;
  params->flag_plus = 0;
  params->flag_space = 0;
  params->flag_description = 0;
  params->flag_width = 0;
  params->width = 0;
  params->description = 0;
  params->flag_short = 0;
  params->flag_long = 0;
}

void flags_width_desc(char *str, int *j, Params *params, int *count_space,
                      int sign, int first, int *count_return) {
  if (first) {
    if ((params->flag_space || params->flag_plus || sign < 0)) {
      *count_space -= 1;
    }

    if (params->flag_right && *count_space > 0) {
      for (int i = 0; i < *count_space; i++) {
        str[*j] = ' ';
        *j += 1;
        *count_return += 1;
      }
    }

    if (sign < 0) {
      str[*j] = '-';
      *j += 1;
      *count_return += 1;
    } else if (params->flag_plus) {
      str[*j] = '+';
      *j += 1;
      *count_return += 1;
    } else if (params->flag_space) {
      str[*j] = ' ';
      *j += 1;
      *count_return += 1;
    }
  } else {
    if (!params->flag_right && *count_space > 0) {
      for (int i = 0; i < *count_space; i++) {
        str[*j] = ' ';
        *j += 1;
        *count_return += 1;
      }
    }
  }
}

void min_cat(char *str, int *j, const char *x, Params *params,
             int *count_return) {
  int i = 0;
  int count = -1;
  if (params->flag_description) {
    count = 0;
  }

  while (x[i] != '\0' && count < params->description) {
    str[*j] = x[i];
    *j += 1;
    i++;
    *count_return += 1;
    if (params->flag_description) count++;
  }
}

int s21_atoi(const char *str) {
  int result = 0;
  int i = 0;
  while (str[i] && str[i] >= '0' && str[i] <= '9') {
    result = result * 10 + str[i] - 48;
    i++;
  }
  return result;
}

int own_atoi(const char *str, int *i) {
  int j = 0;
  while (str[j] == '0') {
    *i += 1;
    j++;
  }

  return s21_atoi(&str[j]);
}

void char_to_str(char *str, int *j, Params *params, char x, int *count_return) {
  if (params->flag_plus || params->flag_space) {
    params->flag_plus = 0;
    params->flag_space = 0;
  }
  int count_space = params->width - 1;
  int sign = 1;
  int first = 1;
  flags_width_desc(str, j, params, &count_space, sign, first, count_return);
  str[*j] = x;
  *j += 1;
  *count_return += 1;
  first = 0;
  flags_width_desc(str, j, params, &count_space, sign, first, count_return);
}

void str_to_str(char *str, int *j, Params *params, char *x, int *count_return) {
  if (params->flag_plus || params->flag_space) {
    params->flag_plus = 0;
    params->flag_space = 0;
  }
  str[*j] = '\0';

  if (x == S21_NULL) {
    x = "(null)";
    if (params->flag_description && params->description < 6) {
      params->flag_description = 0;
      x = "";
    }
  }

  int length = s21_strlen(x);
  int count_space = params->width - length;

  if (params->flag_description) {
    if (length > params->description) {
      count_space = params->width - params->description;
    }
  }

  int sign = 1;
  int first = 1;
  flags_width_desc(str, j, params, &count_space, sign, first, count_return);
  min_cat(str, j, x, params, count_return);

  first = 0;
  flags_width_desc(str, j, params, &count_space, sign, first, count_return);
}

int is_short_spec(int c) {
  return c == 'i' || c == 'd' || c == 'o' || c == 'u' || c == 'x' || c == 'X' ||
         c == 'c' || c == 's';
}

void parse(Params *params, int *count_return, char *str, const char *format,
           int *j, va_list args) {
  int flag = 0;
  int i = 0;
  while (format[i]) {
    if (format[i] == '%' || flag) {
      int direct = 0;
      flag = 0;
      if (format[i] == '%') i++;
      switch (format[i]) {
        case 'c': {
          int x = va_arg(args, int);
          char_to_str(str, j, params, x, count_return);
          init_struct_flags(params);
          break;
        }
        case 'd': {
          if (params->flag_long == 1) {
            long int lx = va_arg(args, long int);
            i_to_str(lx, str, j, params, direct, count_return);
          } else {
            int x = va_arg(args, int);
            if (params->flag_short) x = (short int)x;
            i_to_str(x, str, j, params, direct, count_return);
          }
          init_struct_flags(params);
          break;
        }
        case 'f': {
          double x = va_arg(args, double);
          direct = 1;
          f_to_str(x, str, j, params, direct, count_return);
          init_struct_flags(params);
          break;
        }
        case 's': {
          char *x = va_arg(args, char *);
          str_to_str(str, j, params, x, count_return);
          init_struct_flags(params);
          break;
        }
        case 'u': {
          if (params->flag_plus || params->flag_space) {
            params->flag_plus = 0;
            params->flag_space = 0;
          }

          if (params->flag_long == 1) {
            unsigned long int lx = va_arg(args, unsigned long int);
            i_to_str(lx, str, j, params, direct, count_return);
          } else {
            unsigned int x = va_arg(args, unsigned int);
            if (params->flag_short) x = (unsigned short int)x;
            i_to_str(x, str, j, params, direct, count_return);
          }

          init_struct_flags(params);
          break;
        }
        case 'h': {
          if (is_short_spec(format[i + 1])) {
            params->flag_short = 1;
            flag = 1;
          }
          break;
        }
        case 'l': {
          if (is_short_spec(format[i + 1])) {
            params->flag_long = 1;
            flag = 1;
          }
          break;
        }
        case '%': {
          str[*j] = '%';
          *j += 1;
          *count_return += 1;
          init_struct_flags(params);
          break;
        }
        case '-': {
          params->flag_right = 0;
          flag = 1;
          break;
        }
        case '+': {
          params->flag_plus = 1;
          flag = 1;
          break;
        }
        case ' ': {
          params->flag_space = 1;
          flag = 1;
          break;
        }
        case '.': {
          params->flag_description = 1;
          flag = 1;
          break;
        }
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
          if (params->flag_width == 0 && params->flag_description == 0) {
            params->width = own_atoi(&format[i], &i);
            i += count_digits(params->width) - 1;
            params->flag_width = 1;
          } else {
            char c = format[i];
            params->description = own_atoi(&format[i], &i);
            if (count_digits(params->description) > 1 || c != '0')
              i += count_digits(params->description) - 1;
            else
              i--;
            params->flag_description = 1;
          }
          flag = 1;

          break;
        }
        default: {
          str[*j] = format[i];
          *j += 1;
          *count_return += 1;
          break;
        }
      }
    } else {
      str[*j] = format[i];
      *j += 1;
      *count_return += 1;
    }
    i++;
  }
}

void *s21_trim(const char *src, const char *trim_chars) {
  void *res = S21_NULL;
  if (src != S21_NULL && trim_chars != S21_NULL) {
    int i = 0;
    char *out = (char *)(malloc(sizeof(char)));
    out[i] = '\0';

    int j = 0;
    char c = 0;
    int flag = 0;
    int k = -1;
    begin_trim(src, &j, trim_chars);
    while ((c = src[j]) != '\0' && !flag) {
      int flag_trim_char = 0;
      if (!is_trim_chars(c, trim_chars) || j < k) {
        char *s;
        out[i] = c;
        s = (char *)(realloc(out, (i + 2) * sizeof(char)));
        i++;
        out = s;
      } else {
        k = j;
        flag = is_end_trim(src, &k, trim_chars);
        flag_trim_char = 1;
      }
      if (!flag_trim_char) j++;
    }

    out[i] = '\0';
    res = out;
  }

  return res;
}

int is_trim_chars(char c, const char *trim_chars) {
  int flag = 0;
  int i = 0;

  while (!flag && trim_chars[i]) {
    if (c == trim_chars[i]) flag = 1;
    i++;
  }

  return flag;
}

void begin_trim(const char *src, int *j, const char *trim_chars) {
  int flag = 0;
  while (src[*j] && !flag) {
    if (is_trim_chars(src[*j], trim_chars)) {
      *j += 1;
    } else {
      flag = 1;
    }
  }
}

int is_end_trim(const char *src, int *k, const char *trim_chars) {
  int flag = 1;
  while (src[*k] && flag) {
    if (!is_trim_chars(src[*k], trim_chars)) {
      flag = 0;
    }
    *k += 1;
  }

  return flag;
}

void add_str(const char *str, char **out, int *i) {
  int j = 0;
  while (str[j]) {
    (*out)[*i] = str[j];
    *out = (char *)(realloc(*out, (*i + 2) * sizeof(char)));
    *i += 1;
    j++;
  }
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  void *res = S21_NULL;

  if (src != S21_NULL && str != S21_NULL && start_index <= s21_strlen(src)) {
    char *out = (char *)(malloc(sizeof(char)));
    int i = 0;
    out[i] = '\0';
    s21_size_t j = 0;
    int flag = 0;
    while (src[j]) {
      if (j == start_index && !flag) {
        add_str(str, &out, &i);
        flag = 1;
      } else {
        char *s;
        out[i] = src[j];
        s = (char *)(realloc(out, (i + 2) * sizeof(char)));
        i++;
        out = s;
        flag = 0;
      }

      if (!flag) j++;
    }

    if (j == start_index) {
      add_str(str, &out, &i);
    }

    out[i] = '\0';
    res = out;
  }

  return res;
}

void *s21_to_lower(const char *str) {
  void *res = S21_NULL;

  if (str != S21_NULL) {
    char *out = (char *)(malloc(sizeof(char)));
    int i = 0;
    out[i] = '\0';
    char c = 0;

    while ((c = str[i]) != '\0') {
      if (c >= 'A' && c <= 'Z') {
        c += 32;
      }
      char *s;
      out[i] = c;
      s = (char *)(realloc(out, (i + 2) * sizeof(char)));
      out = s;
      i++;
    }

    out[i] = '\0';
    res = out;
  }

  return res;
}

void *s21_to_upper(const char *str) {
  void *res = S21_NULL;

  if (str != S21_NULL) {
    char *out = (char *)(malloc(sizeof(char)));
    int i = 0;
    out[i] = '\0';
    char c = 0;

    while ((c = str[i]) != '\0') {
      if (c >= 'a' && c <= 'z') {
        c -= 32;
      }

      out[i] = c;
      char *s;
      s = (char *)(realloc(out, (i + 2) * sizeof(char)));
      out = s;
      i++;
    }

    out[i] = '\0';
    res = out;
  }

  return res;
}
