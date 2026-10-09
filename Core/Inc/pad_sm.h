#ifndef PAD_SM_H
#define PAD_SM_H

#include <stdint.h>
#include <stdbool.h>
#include "button.h"

#define COUNTDOWN_MS        60000u
#define BUZZER_START_MS     10000u
#define RETRACT_OFFSET_MS       0u
#define PYRO_PULSE_MS        1000u
#define BLINK_PERIOD_MS       250u

typedef enum {
    PAD_DISARMED = 0,
    PAD_ARMED,
    PAD_COUNTDOWN,
    PAD_FIRING,
    PAD_DONE
} pad_state_t;

typedef struct {
    bool led_green;
    bool led_red;
    bool buzzer;
    bool servos_retracted;
    bool pyro;
} pad_outputs_t;

typedef struct {
    pad_state_t state;
    uint32_t    state_entry_ms;
} pad_sm_t;

void          pad_sm_init(pad_sm_t *sm, uint32_t now_ms);
void          pad_sm_update(pad_sm_t *sm, btn_event_t btn, uint32_t now_ms);
pad_outputs_t pad_sm_outputs(const pad_sm_t *sm, uint32_t now_ms);
const char   *pad_state_name(pad_state_t s);

#endif /* PAD_SM_H */