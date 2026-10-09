#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>

#define DEBOUNCE_MS   30u
#define HOLD_MS     2000u

typedef enum {
    BTN_NONE = 0,
    BTN_SHORT,
    BTN_HOLD
} btn_event_t;

typedef struct {
    bool     stable_pressed;
    bool     last_raw;
    uint32_t raw_change_ms;
    uint32_t press_start_ms;
    bool     hold_reported;
} button_t;

void        button_init(button_t *b, uint32_t now_ms);
btn_event_t button_update(button_t *b, bool raw_pressed, uint32_t now_ms);

#endif /* BUTTON_H */