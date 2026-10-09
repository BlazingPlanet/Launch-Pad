#include "pad_sm.h"

static void enter(pad_sm_t *sm, pad_state_t s, uint32_t now_ms)
{
    sm->state = s;
    sm->state_entry_ms = now_ms;
}

void pad_sm_init(pad_sm_t *sm, uint32_t now_ms)
{
    enter(sm, PAD_DISARMED, now_ms);
}

void pad_sm_update(pad_sm_t *sm, btn_event_t btn, uint32_t now_ms)
{
    uint32_t elapsed = now_ms - sm->state_entry_ms;

    switch (sm->state) {
    case PAD_DISARMED:
        if (btn == BTN_SHORT) enter(sm, PAD_ARMED, now_ms);
        break;

    case PAD_ARMED:
        if (btn == BTN_SHORT)     enter(sm, PAD_DISARMED, now_ms);
        else if (btn == BTN_HOLD) enter(sm, PAD_COUNTDOWN, now_ms);
        break;

    case PAD_COUNTDOWN:
        if (btn != BTN_NONE)              enter(sm, PAD_DISARMED, now_ms);
        else if (elapsed >= COUNTDOWN_MS) enter(sm, PAD_FIRING, now_ms);
        break;

    case PAD_FIRING:
        if (elapsed >= PYRO_PULSE_MS) enter(sm, PAD_DONE, now_ms);
        break;

    case PAD_DONE:
        break;

    default:
        enter(sm, PAD_DONE, now_ms);
        break;
    }
}

pad_outputs_t pad_sm_outputs(const pad_sm_t *sm, uint32_t now_ms)
{
    pad_outputs_t out = {0};
    uint32_t elapsed = now_ms - sm->state_entry_ms;

    switch (sm->state) {
    case PAD_DISARMED:
        out.led_green = true;
        break;

    case PAD_ARMED:
        out.led_red = true;
        break;

    case PAD_COUNTDOWN: {
        uint32_t remaining = (elapsed < COUNTDOWN_MS) ? (COUNTDOWN_MS - elapsed) : 0u;
        out.led_red = ((elapsed / BLINK_PERIOD_MS) % 2u) == 0u;
        if (remaining <= BUZZER_START_MS) {
            out.buzzer = (elapsed % 1000u) < 500u;
        }
        out.servos_retracted = (remaining <= RETRACT_OFFSET_MS);
        break;
    }

    case PAD_FIRING:
        out.pyro             = true;
        out.servos_retracted = true;
        out.led_red          = true;
        break;

    case PAD_DONE:
        out.servos_retracted = true;
        out.led_green = ((elapsed / 1000u) % 2u) == 0u;
        out.led_red   = !out.led_green;
        break;

    default:
        break;
    }

    return out;
}

const char *pad_state_name(pad_state_t s)
{
    switch (s) {
    case PAD_DISARMED:  return "DISARMED";
    case PAD_ARMED:     return "ARMED";
    case PAD_COUNTDOWN: return "COUNTDOWN";
    case PAD_FIRING:    return "FIRING";
    case PAD_DONE:      return "DONE";
    default:            return "UNKNOWN";
    }
}