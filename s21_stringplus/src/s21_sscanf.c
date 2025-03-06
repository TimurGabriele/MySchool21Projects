#include "s21_string.h"

int s21_sscanf(const char* buffer, const char* format, ...) {
  int count = 0, check;
  const char* buf_n = buffer;
  Params parameters = {0, 0, 0};
  va_list factor;
  va_start(factor, format);
  for (; *format; format++) {
    if (*format == '%' && *(format - 1) != '%') {
      format++;
      parameters.star = asterisk(&format);
      parameters.width = width_define_s(&format);
      parameters.length = length_define(&format);
      check = formats_s(&buffer, &format, factor, &buf_n, parameters);
      if (check)
        count++;
      else if (!parameters.star)
        break;
    } else if (*format == *buffer)
      buffer++;
    else if (*buffer == ' ' || *buffer == '\n' || *buffer == '\t')
      buffer++;
  }
  va_end(factor);
  return count;
}

char length_define(const char** format) {
  char length = '0';
  if (**format == 'l') {
    *format += 1;
    length = 'l';
  } else if (**format == 'L') {
    *format += 1;
    length = 'L';
  } else if (**format == 'h') {
    *format += 1;
    length = 'h';
  }
  return length;
}

int asterisk(const char** format) {
  int res = 0;
  if (**format == '*') {
    *format += 1;
    res = 1;
  }
  return res;
}

int width_define_s(const char** format) {
  long int num = 0;
  Params nulls = {0, 0, 0};
  num_d(format, &num, 10, nulls);
  return num;
}

int formats_s(const char** buffer, const char** format, va_list factor,
              const char** buf_n, Params parameters) {
  int check = 0;
  if (**format == 'c') {
    check = format_c(buffer, factor, parameters);
  }
  if (**format == 'd') {
    check = format_d(buffer, factor, parameters);
  }
  if (**format == 's') {
    check = format_s(buffer, factor, parameters);
  }
  if (**format == 'f') {
    check = format_ef(buffer, factor, parameters, 0);
  }
  if (**format == 'n') {
    long int num = *buffer - *buf_n;
    d_memory_s(factor, num, parameters.length);
  }
  if (**format == 'o') {
    check = format_o(buffer, factor, parameters);
  }
  if (**format == 'u') {
    check = format_u(buffer, factor, parameters);
  }
  if (**format == 'x' || **format == 'X') {
    check = format_x(buffer, factor, parameters);
  }
  if (**format == 'i') {
    check = format_i(buffer, factor, parameters);
  }
  if (**format == 'p') {
    check = format_p(buffer, factor, parameters);
  }
  if (**format == 'e' || **format == 'E') {
    check = format_ef(buffer, factor, parameters, 0);
  }
  if (**format == 'g') {
    check = format_ef(buffer, factor, parameters, 1);
  }
  return check;
}

int format_c(const char** buffer, va_list factor, Params parameters) {
  int check = 0;
  if (!parameters.star) {
    void** value = va_arg(factor, void*);
    *(char*)value = **buffer;
    check = 1;
  }
  *buffer += 1;
  return check;
}

int format_s(const char** buffer, va_list factor, Params parameters) {
  int check = 0;
  char str[1024];
  if (**buffer != '\0') {
    get_str(buffer, str, parameters);
    check = 1;
  }
  if (check && !parameters.star) {
    void** value = va_arg(factor, void*);
    s21_strncpy((char*)value, str, s21_strlen(str));
    *((char*)value + s21_strlen(str)) = '\0';
    check = 1;
  } else
    check = 0;
  return check;
}

int format_p(const char** buffer, va_list factor, Params parameters) {
  unsigned long int num = 0;
  int check = num_x(buffer, &num, parameters);
  if (check && !parameters.star) {
    void** value = va_arg(factor, void*);
    *value = (void*)num;
  } else
    check = 0;
  return check;
}

int format_x(const char** buffer, va_list factor, Params parameters) {
  unsigned long int num = 0;
  int check = num_x(buffer, &num, parameters);
  if (check && !parameters.star)
    u_memory_s(factor, num, parameters.length);
  else
    check = 0;
  return check;
}

int format_i(const char** buffer, va_list factor, Params parameters) {
  int check = 0;
  if (**buffer == '0') {
    *buffer += 1;
    if (**buffer == 'x' || **buffer == 'X') {
      *buffer += 1;
      check = format_x(buffer, factor, parameters);
    } else
      check = format_o(buffer, factor, parameters);
  } else
    check = format_d(buffer, factor, parameters);
  return check;
}

int format_d(const char** buffer, va_list factor, Params parameters) {
  long int num = 0;
  int check = num_d(buffer, &num, 10, parameters);
  if (check && !parameters.star)
    d_memory_s(factor, num, parameters.length);
  else
    check = 0;
  return check;
}

int format_o(const char** buffer, va_list factor, Params parameters) {
  long int num = 0;
  int check = num_d(buffer, &num, 8, parameters);
  if (check && !parameters.star)
    u_memory_s(factor, num, parameters.length);
  else
    check = 0;
  return check;
}

int format_u(const char** buffer, va_list factor, Params parameters) {
  long int num = 0;
  int check = num_d(buffer, &num, 10, parameters);
  if (check && !parameters.star)
    u_memory_s(factor, num, parameters.length);
  else
    check = 0;
  return check;
}

int format_ef(const char** buffer, va_list factor, Params parameters,
              int format_g) {
  long int num = 0;
  long double float_num = 0;
  int check = num_d(buffer, &num, 10, parameters);
  float_num = num;
  num_f(buffer, &float_num, parameters);
  if ((format_g && **buffer == 'e') || (!format_g && **buffer == 'e')) {
    *buffer += 1;
    num = 0;
    if (num_d(buffer, &num, 10, parameters))
      float_num *= pow(10, num);
    else
      *buffer -= 1;
  }
  if (check && !parameters.star)
    f_memory_s(factor, float_num, parameters.length);
  else
    check = 0;
  return check;
}

void d_memory_s(va_list factor, long int num, char length) {
  if (length == 'l') {
    long int* value = va_arg(factor, long int*);
    *value = (long int)num;
  } else if (length == 'h') {
    short* value = va_arg(factor, short*);
    *value = (short)num;
  } else {
    int* value = va_arg(factor, int*);
    *value = (int)num;
  }
}

void u_memory_s(va_list factor, long int num, char length) {
  if (length == 'l') {
    unsigned long int* value = va_arg(factor, unsigned long int*);
    *value = (unsigned long int)num;
  } else if (length == 'h') {
    unsigned short* value = va_arg(factor, unsigned short*);
    *value = (unsigned short)num;
  } else {
    unsigned int* value = va_arg(factor, unsigned int*);
    *value = (unsigned int)num;
  }
}

void f_memory_s(va_list factor, long double num, char length) {
  if (length == 'L') {
    long double* value = va_arg(factor, long double*);
    *value = (long double)num;
  } else if (length == 'l') {
    double* value = va_arg(factor, double*);
    *value = (double)num;
  } else {
    float* value = va_arg(factor, float*);
    *value = (float)num;
  }
}

int num_d(const char** buffer, long int* num, int sys, Params parameters) {
  int minus = 0, check = 0;
  if (*num == 0) {
    if (**buffer == '-') {
      minus = 1;
      *buffer += 1;
    } else if (**buffer == '+')
      *buffer += 1;
    for (int i = 1; **buffer >= '0' && **buffer <= '0' + sys;
         i++, *buffer += 1) {
      check = 1;
      *num = *num * sys + (**buffer - '0');
      if (parameters.width && i == parameters.width) break;
    }
    if (minus) *num *= -1;
  }
  return check;
}

void num_f(const char** buffer, long double* float_num, Params parameters) {
  double num = 0;
  if (**buffer == '.') {
    *buffer += 1;
    for (int i = 1; **buffer >= '0' && **buffer <= '9'; i++, *buffer += 1) {
      double digit = (**buffer - '0');
      digit = round(digit);
      num += digit * pow(10, -i);
      if (parameters.width && i == parameters.width) break;
    }
  }
  *float_num += num;
}

int num_x(const char** buffer, unsigned long int* num, Params parameters) {
  int check = 0, minus = 0;
  if (**buffer == '-') {
    *buffer += 1;
    minus = 1;
  }
  int i = 1;
  for (; (**buffer >= '0' && **buffer <= '9') ||
         (**buffer >= 'A' && **buffer <= 'F') ||
         (**buffer >= 'a' && **buffer <= 'f');
       i++, *buffer += 1) {
    check = 1;
    int x;
    if (**buffer >= '0' && **buffer <= '9') x = **buffer - 48;
    if (**buffer >= 'A' && **buffer <= 'Z') x = **buffer - 55;
    if (**buffer >= 'a' && **buffer <= 'z') x = **buffer - 87;
    *num = *num * 16 + x;
    if (parameters.width && i == parameters.width) break;
  }
  if (i > 18) {
    *num = 0;
    const char* big_num = "fffffffffffffffff";
    check = num_x(&big_num, num, parameters);
  }
  if (minus) *num *= -1;
  return check;
}

void get_str(const char** buffer, char* str, Params parameters) {
  int i = 0;
  while (**buffer != ' ' && **buffer != '\n' && **buffer != '\t' &&
         **buffer != '\0') {
    *str = **buffer;
    *buffer += 1;
    str++;
    i++;
    if (parameters.width && i == parameters.width) break;
  }
  *str = '\0';
}
