#define _POSIX_C_SOURCE 200112L
#include <signal.h>
#include <stddef.h>

int signals_block() {
  int code = 0;
  sigset_t signal_set;

  code = sigemptyset(&signal_set);
  if (!code) code = sigaddset(&signal_set, SIGWINCH);
  if (!code) code = sigaddset(&signal_set, SIGINT);
  if (!code) code = sigprocmask(SIG_BLOCK, &signal_set, NULL);
  return code;
}

int signals_unblock() {
  int code = 0;
  sigset_t signal_set;
  code = sigemptyset(&signal_set);
  if (!code) code = sigaddset(&signal_set, SIGWINCH);
  if (!code) code = sigprocmask(SIG_UNBLOCK, &signal_set, NULL);
  return code;
}

void set_signal_handler(void (*handler)(int, void *, void *)) {
  // void (*right_handler)(int, siginfo_t *, void *) = handler;
  struct sigaction action;
  action.sa_flags = SA_SIGINFO;
  action.sa_sigaction = (void (*)(int, siginfo_t *, void *))handler;
  sigaction(SIGWINCH, &action, NULL);
}
