#ifndef SERVO_H
#define SERVO_H

#include <stdint.h>
#include <stdbool.h>

#define SERVO_SLEW_US_PER_MS   4u    /* ramp speed: higher = faster   */
#define SERVO_SETTLE_MS      300u    /* wait this long, then let go   */

typedef struct {
    int32_t  engaged_us;
    int32_t  retracted_us;
    int32_t  current_us;      /* pulse we're commanding right now  */
    uint32_t last_ms;         /* time of the previous update       */
    uint32_t last_moved_ms;   /* last time current_us changed      */
} servo_t;

void     servo_init(servo_t *s, int32_t engaged_us, int32_t retracted_us, uint32_t now_ms);
uint32_t servo_update(servo_t *s, bool retract, uint32_t now_ms);

#endif /* SERVO_H */