#include "button.h"

void button_init(button_t *b, uint32_t now_ms)
{
    b->stable_pressed = false;
    b->last_raw       = false;
    b->raw_change_ms  = now_ms;
    b->press_start_ms = now_ms;
    b->hold_reported  = false;
}

btn_event_t button_update(button_t *b, bool raw_pressed, uint32_t now_ms)
{
    /* 1. Restart the debounce timer whenever the raw reading changes */
    if (raw_pressed != b->last_raw) {
        b->last_raw      = raw_pressed;
        b->raw_change_ms = now_ms;
    }

    /* 2. Accept a new stable level once raw has held steady long enough */
    if (raw_pressed != b->stable_pressed &&
        (now_ms - b->raw_change_ms) >= DEBOUNCE_MS) {

        b->stable_pressed = raw_pressed;

        if (b->stable_pressed) {
            b->press_start_ms = now_ms;     /* a press just began */
            b->hold_reported  = false;
        } else if (!b->hold_reported) {
            return BTN_SHORT;               /* released before a hold */
        }
    }

    /* 3. Report a hold once, while still pressed */
    if (b->stable_pressed && !b->hold_reported &&
        (now_ms - b->press_start_ms) >= HOLD_MS) {
        b->hold_reported = true;
        return BTN_HOLD;
    }

    return BTN_NONE;
}