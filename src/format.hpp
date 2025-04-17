#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>
#include <mutex>
#include <ostream>
#include <unistd.h>

// Disable coloured output if no interactive terminal is found
#define GREEN (isatty(STDOUT_FILENO) ? "\033[32m" : "")
#define RED (isatty(STDOUT_FILENO) ? "\033[31m" : "")
#define CYAN (isatty(STDOUT_FILENO) ? "\033[36m" : "")
#define BOLD (isatty(STDOUT_FILENO) ? "\033[1m" : "")
#define RESET (isatty(STDOUT_FILENO) ? "\033[0m" : "")
#define ITALIC (isatty(STDOUT_FILENO) ? "\033[3m" : "")

static std::mutex io_lock;

#define LOG_VERBOSE(msg)                                                       \
  if (m_setup.logging_level >= LoggingLevel::Verbose) {                        \
    io_lock.lock();                                                            \
    std::cout << msg << std::endl;                                             \
    io_lock.unlock();                                                          \
  }
#define LOG_STANDARD(msg)                                                      \
  if (m_setup.logging_level >= LoggingLevel::Standard) {                       \
    io_lock.lock();                                                            \
    std::cout << msg << std::endl;                                             \
    io_lock.unlock();                                                          \
  }
#define LOG_QUIET(msg)                                                         \
  if (m_setup.logging_level >= LoggingLevel::Quiet) {                          \
    io_lock.lock();                                                            \
    std::cout << msg << std::endl;                                             \
    io_lock.unlock();                                                          \
  }
#define LOG_VERBOSE_NO_NEWLINE(msg)                                            \
  if (m_setup.logging_level >= LoggingLevel::Verbose) {                        \
    io_lock.lock();                                                            \
    std::cout << msg << std::flush;                                            \
    io_lock.unlock();                                                          \
  }
#define LOG_STANDARD_NO_NEWLINE(msg)                                           \
  if (m_setup.logging_level >= LoggingLevel::Standard) {                       \
    io_lock.lock();                                                            \
    std::cout << msg << std::flush;                                            \
    io_lock.unlock();                                                          \
  }
#define LOG_QUIET_NO_NEWLINE(msg)                                              \
  if (m_setup.logging_level >= LoggingLevel::Quiet) {                          \
    io_lock.lock();                                                            \
    std::cout << msg << std::flush;                                            \
    io_lock.unlock();                                                          \
  }

#endif
