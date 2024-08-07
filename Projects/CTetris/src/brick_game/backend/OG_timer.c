#include "OG_timer.h"

void init_timer(OG_timer_t* initd_timer, int delay_sec, int delay_nsec) {
  clock_gettime(CLOCK_MONOTONIC, &initd_timer->start_time);
  clock_gettime(CLOCK_MONOTONIC, &initd_timer->current_time);
  initd_timer->delay.tv_nsec = delay_nsec;
  initd_timer->delay.tv_sec = delay_sec;
}

char check_timer_for_loops(OG_timer_t* timer_to_check) {
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

char check_timer(OG_timer_t timer_to_check) {
  char result_value = 'n';
  clock_gettime(CLOCK_MONOTONIC, &timer_to_check.current_time);
  struct timespec time_difference;
  timespec_variables_difference(&time_difference, timer_to_check.current_time,
                                timer_to_check.start_time);

  if (timer_to_check.delay.tv_sec != 0) {
    if (time_difference.tv_sec == timer_to_check.delay.tv_sec &&
        time_difference.tv_nsec >= timer_to_check.delay.tv_nsec)
      result_value = 'y';
    else if (time_difference.tv_sec > timer_to_check.delay.tv_sec)
      result_value = 'y';

  } else {
    if (time_difference.tv_sec > timer_to_check.delay.tv_sec ||
        time_difference.tv_nsec >= timer_to_check.delay.tv_nsec)
      result_value = 'y';
  }
  return result_value;
}

void timespec_variables_difference(struct timespec* result,
                                   struct timespec operand_1,
                                   struct timespec operand_2) {
  if (operand_1.tv_nsec - operand_2.tv_nsec < 0) {
    result->tv_sec = operand_1.tv_sec - operand_2.tv_sec - 1;
    result->tv_nsec = 1000000000 + operand_1.tv_nsec - operand_2.tv_nsec;
  } else {
    result->tv_sec = operand_1.tv_sec - operand_2.tv_sec;
    result->tv_nsec = operand_1.tv_nsec - operand_2.tv_nsec;
  }
}