/*
 * sio_printf.c
 * Implementation of an async-signal-safe sio_printf function.
 */

#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdarg.h>

#include "csapp.h"
#include "sio_printf.h"


/* sio_reverse - Reverse a string (from K&R) */
static void sio_reverse(char *s, size_t len) {
  size_t i, j;
  for (i = 0, j = len - 1; i < j; i++, j--) {
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}


/* write_digits - write digit values of v in base b to string */
static size_t write_digits(uintmax_t v, char *s, unsigned char b) {
  size_t i = 0;
  do {
    unsigned char c = v % b;
    if (c < 10) {
      s[i++] = c + '0';
    }
    else {
      s[i++] = c - 10 + 'a';
    }
  } while ((v /= b) > 0);
  return i;
}


/* intmax_to_string - Convert an intmax_t to a base b string */
static size_t intmax_to_string(intmax_t v, char *s, unsigned char b) {
  bool neg = v < 0;
  size_t len;

  if (neg) {
    len = write_digits(-v, s, b);
    s[len++] = '-';
  }
  else {
    len = write_digits(v, s, b);
  }

  s[len] = '\0';
  sio_reverse(s, len);
  return len;
}


/* uintmax_to_string - Convert a uintmax_t to a base b string */
static size_t uintmax_to_string(uintmax_t v, char *s, unsigned char b) {
  size_t len = write_digits(v, s, b);
  s[len] = '\0';
  sio_reverse(s, len);
  return len;
}


/* sio_printf - Print format string to STDOUT_FILENO */
ssize_t sio_printf(const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  ssize_t ret = sio_vfprintf(STDOUT_FILENO, fmt, argp);
  va_end(argp);
  return ret;
}


/* sio_fprintf - Print format string to fileno */
ssize_t sio_fprintf(int fileno, const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  ssize_t ret = sio_vfprintf(fileno, fmt, argp);
  va_end(argp);
  return ret;
}


/* sio_vprintf - Print format string from vararg list to fileno */
ssize_t sio_vfprintf(int fileno, const char *fmt, va_list argp) {
  size_t pos = 0;
  ssize_t num_written = 0;

  while (fmt[pos] != '\0') {
    // String output of this iteration
    const char *str = NULL;  // String to output
    size_t len = 0;  // Length of string to output

    // Mark whether we've matched a format
    bool handled = false;

    // Int to string conversion
    char buf[128];
    char convert_type = '\0';
    union {
      uintmax_t u;
      intmax_t s;
    } convert_value = {.u = 0};

    // Handle format characters
    if (fmt[pos] == '%') {
      switch (fmt[pos + 1]) {

        // Character format
        case 'c':
          buf[0] = (char) va_arg(argp, int);
          buf[1] = '\0';
          str = buf;
          len = 1;
          handled = true;
          pos += 2;
          break;

        // String format
        case 's':
          str = va_arg(argp, char *);
          len = strlen(str);
          handled = true;
          pos += 2;
          break;

        // Escaped %
        case '%':
          str = &fmt[pos + 1];
          len = 1;
          handled = true;
          pos += 2;
          break;

        // Int types with no format specifier
        case 'd':
        case 'i':
          convert_type = 'd';
          convert_value.s = (intmax_t) va_arg(argp, int);
          pos += 2;
          break;
        case 'u':
          convert_type = 'u';
          convert_value.u = (uintmax_t) va_arg(argp, unsigned);
          pos += 2;
          break;
        case 'x':
          convert_type = 'x';
          convert_value.u = (uintmax_t) va_arg(argp, unsigned);
          pos += 2;
          break;

        // Int types with size format: long
        case 'l': {
          switch (fmt[pos + 2]) {
            case 'd':
            case 'i':
              convert_type = 'd';
              convert_value.s = (intmax_t) va_arg(argp, long);
              pos += 3;
              break;
            case 'u':
              convert_type = 'u';
              convert_value.u = (uintmax_t) va_arg(argp, unsigned long);
              pos += 3;
              break;
            case 'x':
              convert_type = 'x';
              convert_value.u = (uintmax_t) va_arg(argp, unsigned long);
              pos += 3;
              break;
          }
        }

        // Int types with size format: size_t
        case 'z': {
          switch (fmt[pos + 2]) {
            case 'd':
            case 'i':
              convert_type = 'd';
              convert_value.s = (intmax_t) va_arg(argp, ssize_t);
              pos += 3;
              break;
            case 'u':
              convert_type = 'u';
              convert_value.u = (uintmax_t) va_arg(argp, size_t);
              pos += 3;
              break;
            case 'x':
              convert_type = 'x';
              convert_value.u = (uintmax_t) va_arg(argp, size_t);
              pos += 3;
              break;
          }
        }

      }

      // Convert int type to string
      switch (convert_type) {
        case 'd':
          str = buf;
          len = intmax_to_string(convert_value.s, buf, 10);
          handled = true;
          break;
        case 'u':
          str = buf;
          len = uintmax_to_string(convert_value.u, buf, 10);
          handled = true;
          break;
        case 'x':
          str = buf;
          len = uintmax_to_string(convert_value.u, buf, 16);
          handled = true;
          break;
      }
    }

    // Didn't match a format above
    // Handle block of non-format characters
    if (!handled) {
      str = &fmt[pos];
      len = 1 + strcspn(&fmt[pos + 1], "%");
      pos += len;
    }

    // Write output
    if (len > 0) {
      ssize_t ret = rio_writen(fileno, (void *) str, len);
      if (ret == -1 || (size_t) ret != len) {
        return -1;
      }
      num_written += len;
    }
  }

  return num_written;
}


/* Sio_printf - wrapper for sio_printf */
ssize_t Sio_printf(const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  ssize_t ret = Sio_vfprintf(STDOUT_FILENO, fmt, argp);
  va_end(argp);
  return ret;
}


/* Sio_fprintf - wrapper for sio_fprintf */
ssize_t Sio_fprintf(int fileno, const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  ssize_t ret = Sio_vfprintf(fileno, fmt, argp);
  va_end(argp);
  return ret;
}


/* Sio_vfprintf - wrapper for sio_vfprintf */
ssize_t Sio_vfprintf(int fileno, const char *fmt, va_list argp) {
  ssize_t ret = sio_vfprintf(fileno, fmt, argp);
  if (ret < 0) {
    Sio_error("Sio_vfprintf error");
  }
  return ret;
}
