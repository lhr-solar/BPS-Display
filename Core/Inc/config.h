/* Copyright (c) 2020 UT Longhorn Racing Solar */

/** config.h
 * Config file to hold any aliases/constants referenced by multiple files
 * Not specific to a single board/unit
 */

//--------------------------------------------------------------------------------
// Battery Pack layout

// Number of battery modules
#define NUM_BATTERY_MODULES				31
// Number of temperature sensors
#define NUM_TEMPERATURE_SENSORS			(2*NUM_BATTERY_MODULES)