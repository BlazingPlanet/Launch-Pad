#include "servo.h"

void servo_init(servo_t *s, int32_t engaged_us, int32_t retracted_us, uint32_t now_ms)
{
    s->engaged_us    = engaged_us;
    s->retracted_us  = retracted_us;
    s->current_us    = engaged_us;
    s->last_ms       = now_ms;
    s->last_moved_ms = now_ms;
}

uint32_t servo_update(servo_t *s, bool retract, uint32_t now_ms)
{
    int32_t  target = retract ? s->retracted_us : s->engaged_us;
    uint32_t dt     = now_ms - s->last_ms;
    s->last_ms = now_ms;

    /* 1. Ramp current_us toward the target */
    int32_t max_step = (int32_t)(dt * SERVO_SLEW_US_PER_MS);
    int32_t diff     = target - s->current_us;

    if (diff != 0) {
        if (diff >  max_step) diff =  max_step;
        if (diff < -max_step) diff = -max_step;
        s->current_us   += diff;
        s->last_moved_ms = now_ms;
    }

    /* 2. Once retracted and settled, stop sending pulses */
    if (retract && s->current_us == target &&
        (now_ms - s->last_moved_ms) >= SERVO_SETTLE_MS) {
        return 0u;
    }

    return (uint32_t)s->current_us;
}