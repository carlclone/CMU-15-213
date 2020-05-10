/*
 * sio_printf.h - Prototypes for an async-signal-safe printf function.
 *
 * This file provides reentrant and async-signal-safe implementations of
 * printf and associated functions.
 *
 * The provided functions write directly to a file descriptor (using the
 * `rio_writen` function from csapp). In particular, sio_printf writes to
 * `STDOUT_FILENO`. However, since these writes are unbuffered, these
 * functions are not very efficient.
 *
 * The only supported format specifiers are the following:
 *   Int types: %d, %i, %u, %x (with size specifiers l, z)
 *   Others: %c, %s, %%
 */

#include <unistd.h>

/*
 * sio_printf - Prints output to `STDOUT_FILENO` according to the format
 * string `fmt`, and a variable number of input arguments.
 * Returns the number of bytes written, or -1 on error.
 */
ssize_t sio_printf(const char *fmt, ...)
  __attribute__ ((format (printf, 1, 2)));

/*
 * sio_fprintf - Prints output to a file descriptor `fileno` according to
 * the format string `fmt`, and a variable number of input arguments.
 * Returns the number of bytes written, or -1 on error.
 */
ssize_t sio_fprintf(int fileno, const char *fmt, ...)
  __attribute__ ((format (printf, 2, 3)));

/*
 * sio_vfprintf - Prints output to a file descriptor `fileno` according to
 * the format string `fmt`, and a varargs list `argp`.
 * Returns the number of bytes written, or -1 on error.
 */
ssize_t sio_vfprintf(int fileno, const char *fmt, va_list argp)
  __attribute__ ((format (printf, 2, 0)));


/* Sio_printf - wrapper for sio_printf */
ssize_t Sio_printf(const char *fmt, ...)
  __attribute__ ((format (printf, 1, 2)));

/* Sio_fprintf - wrapper for sio_fprintf */
ssize_t Sio_fprintf(int fileno, const char *fmt, ...)
  __attribute__ ((format (printf, 2, 3)));

/* Sio_vfprintf - wrapper for sio_vfprintf */
ssize_t Sio_vfprintf(int fileno, const char *fmt, va_list argp)
  __attribute__ ((format (printf, 2, 0)));

