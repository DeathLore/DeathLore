#ifndef OG_TIMER_H
#define OG_TIMER_H

#define _POSIX_C_SOURCE 199309L
#include <time.h>

/**
 * @brief Structure that contains info for making timer.
 *
 * @param start_time timers beginning
 * @param current_time time when we checks passed time
 * @param delay after what time timer have to work
 */
typedef struct {
  struct timespec start_time;
  struct timespec current_time;
  struct timespec delay;
} OG_timer_t;

/**
 * @brief Starting timer
 *
 * @param[out] initd_timer timer that would be initialised
 * @param[in] delay_sec how many seconds have to be passed
 * @param[in] delay_nsec how many nano seconds have to be passed (sec 1e-9)
 */
void init_timer(OG_timer_t* initd_timer, int delay_sec, int delay_nsec);
/**
 * @brief Checking timer. If delay passed - timer expires.
 *
 * @param[in] timer_to_check timer who's info used to check time difference.
 * @return char - if time passed returns 'y'; else 'n'.
 */
char check_timer(OG_timer_t timer_to_check);
/**
 * @brief Checking timer. If delay passed - timer starts again with the same
 * delay and start_time when function restarted.
 *
 * @param[in, out] timer_to_check timer who's info used to check time difference
 * and restarts.
 * @return char - if time passed returns 'y'; else 'n'.
 */
char check_timer_for_loops(OG_timer_t* timer_to_check);

/**
 * @brief Takes difference between to timesec values.
 *
 * @param[out] result difference result
 * @param[in] operand_1 minuend value
 * @param[in] operand_2 subtrahend value
 */
void timespec_variables_difference(struct timespec* result,
                                   struct timespec operand_1,
                                   struct timespec operand_2);

#endif