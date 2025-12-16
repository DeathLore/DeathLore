#include "./OG_timer.h"

void OG_timer_init(OG_timer_t* const initd_timer, const int delay_sec, const int delay_nsec) {
  clock_gettime(CLOCK_MONOTONIC, &initd_timer->start_time);
  clock_gettime(CLOCK_MONOTONIC, &initd_timer->current_time);
  initd_timer->delay.tv_nsec = delay_nsec;
  initd_timer->delay.tv_sec = delay_sec;
}

char check_timer_for_loops(OG_timer_t* const timer_to_check) {
  char result_value = 'n';
  clock_gettime(CLOCK_MONOTONIC, &timer_to_check->current_time);
  struct timespec time_difference;
  timespec_variables_difference(&time_difference, timer_to_check->current_time,
                                timer_to_check->start_time);

  if (timer_to_check->delay.tv_sec != 0) {
    if (time_difference.tv_sec == timer_to_check->delay.tv_sec &&
        time_difference.tv_nsec >= timer_to_check->delay.tv_nsec) {
      clock_gettime(CLOCK_MONOTONIC, &timer_to_check->start_time);

      result_value = 'y';
    } else if (time_difference.tv_sec > timer_to_check->delay.tv_sec) {
      clock_gettime(CLOCK_MONOTONIC, &timer_to_check->start_time);

      result_value = 'y';
    }
  } else {
    if (time_difference.tv_sec > timer_to_check->delay.tv_sec ||
        time_difference.tv_nsec >= timer_to_check->delay.tv_nsec) {
      clock_gettime(CLOCK_MONOTONIC, &timer_to_check->start_time);

      result_value = 'y';
    }
  }

  return result_value;
}

char check_timer(OG_timer_t* const timer_to_check) {
  char result_value = 'n';
  clock_gettime(CLOCK_MONOTONIC, &timer_to_check->current_time);
  struct timespec time_difference;
  timespec_variables_difference(&time_difference, timer_to_check->current_time,
                                timer_to_check->start_time);

  if (timer_to_check->delay.tv_sec != 0) {
    if (time_difference.tv_sec == timer_to_check->delay.tv_sec &&
        time_difference.tv_nsec >= timer_to_check->delay.tv_nsec)
      result_value = 'y';
    else if (time_difference.tv_sec > timer_to_check->delay.tv_sec)
      result_value = 'y';

  } else {
    if (time_difference.tv_sec > timer_to_check->delay.tv_sec ||
        time_difference.tv_nsec >= timer_to_check->delay.tv_nsec)
      result_value = 'y';
  }
  return result_value;
}

void timespec_variables_difference(struct timespec* const result,
                                   struct timespec const x,
                                   struct timespec const y) {
  result->tv_sec = x.tv_sec - y.tv_sec;
  result->tv_nsec = x.tv_nsec - y.tv_nsec;

  // Normalize if negative
  if (result->tv_nsec < 0) {
    --(result->tv_sec);
    result->tv_nsec += 1000000000; // 1 sec to nsec
  }
}