# Launch Pad Wiring

## Black Pill pins

| Pin | Connects to |
|---|---|
| PB12 | 100 Ω → green LED long leg; short leg → GND |
| PB13 | 100 Ω → red LED long leg; short leg → GND |
| PB10 | BTN header |
| PA6 | S1 header, signal |
| PA7 | S2 header, signal |
| PB1 | 100 Ω → buzzer MOSFET gate |
| PB0 | 100 Ω → pyro MOSFET gate |
| PC13 | Onboard heartbeat LED (no wiring) |
| 5V | + rail |
| GND | − rail |
| 3V3 | Not connected. Never feed power into this pin. |
| SWDIO / SWCLK / GND | ST-Link (3.3V wire off when board has other power) |

## Power

| From | To |
|---|---|
| Battery 1 (2S) | UBEC input |
| UBEC 5V out | + rail |
| UBEC GND | − rail |
| Battery 2 (2S) + | Fuse → clip A (18 AWG, off the board) |
| Battery 2 (2S) − | Pyro MOSFET source leg (18 AWG) |

All grounds share the − rail. Both − rails are jumpered together.

## MOSFETs (IRLB8721)

Printed side facing you, legs down: **Gate, Drain, Source**, left to right. The metal tab is the drain.

| Leg | Buzzer MOSFET | Pyro MOSFET |
|---|---|---|
| Gate | 100 Ω ← PB1; 10k → − rail | 100 Ω ← PB0; 10k → − rail |
| Drain | BUZ header (−) | 18 AWG, soldered to leg → clip B |
| Source | − rail | 18 AWG, soldered to leg → Battery 2 −; thin jumper → − rail |

## Headers

| Label | Pins | Plug in |
|---|---|---|
| BTN | PB10, GND | Button cable, either way around |
| S1 | −, +5V, PA6 | Servo 1: brown −, red +, orange signal |
| S2 | −, +5V, PA7 | Servo 2: brown −, red +, orange signal |
| BUZ | + rail (+), buzzer FET drain (−) | Buzzer red to +, black to − |

## Rules

- Never connect USB-C and the UBEC at the same time.
- Igniter current runs through the 18 AWG wires only, never the Perma-Proto strips.
- Plug in Battery 2 last at the pad. Unplug it first before touching the igniter.
