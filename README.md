# Multifunctional Strikeball Device

This device was developed for use in strikeball games.

### Hardware components

- ESP32-C3
- 2 transistors
- 2 push buttons (Select / Confirm)
- 6 LEDs (2 red, 4 green)
- Siren
- Igniter
- PIR motion sensor

Detailed wiring and connections are provided in the electronic schematic (PDF).

## Operating principle

The device uses two buttons:
- Select button — mode selection
- Confirm button — mode confirmation and start

When the device is powered on, the LEDs start running up and down, indicating that the device is waiting for user input.

Pressing the Select button starts the mode selection process.
The number of active LEDs corresponds to the selected mode number.

Pressing the Confirm button starts the selected mode.

## Available modes

The device supports four operating modes:

- Base Mode (Siren + Igniter)
- Siren Only
- Igniter Only
- Timer Mode (+ Igniter)

After confirming any mode, the device starts a 5-minute arming countdown.

## Base Mode (Siren + Igniter)

After the countdown is finished, the PIR sensor begins monitoring for motion.

If motion is detected:

- the siren is activated for 10 seconds
- the igniter is triggered

After the siren and igniter are turned off, the device returns to standby mode.

## Siren Only Mode

After the countdown, the PIR sensor monitors for motion.

If motion is detected, the siren is activated for 10 seconds.

After the siren is turned off, the device returns to standby mode.

## Igniter Only Mode

After the countdown, the PIR sensor monitors for motion.

If motion is detected, the igniter is triggered.

After activation, the device returns to standby mode.

## Timer Mode

After selecting and confirming Timer Mode, the user can choose the timer duration.

The number of active LEDs represents a time multiplier:
- each LED corresponds to 10 minutes

Example:
3 LEDs × 10 minutes = 30 minutes

After confirming the timer value:
- the device performs the initial arming countdown
- then starts the main timer countdown

When the timer expires, the igniter is triggered.

### ***FOR EDUCATIONAL AND GAME USE ONLY***
