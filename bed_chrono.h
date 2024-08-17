#ifndef __BED_CHRONO_H__
#define __BED_CHRONO_H__

// Conversion constants
#define MILLIS_PER_SECS    1000U
#define SECS_PER_MINUTE    60U
#define MILLIS_PER_MINUTE  (MILLIS_PER_SECS * SECS_PER_MINUTE)

// Utility macros for time conversion
#define CONVERT_MIN_TO_SEC(t_min)  ((t_min) * SECS_PER_MINUTE)

// Chrono status definitions
#define CHRONO_STATUS_RUNNING  0
#define CHRONO_STATUS_PAUSED   1
#define CHRONO_STATUS_STOPPED  2
#define CHRONO_STATUS_DEFAULT  CHRONO_STATUS_STOPPED

// Macro to start or resume the chrono
#define playChrono(chrono) startChrono(chrono)

// Chrono structure to manage timing
typedef struct {
    uint8_t status;                    // Current status of the chrono (running, paused, stopped)
    unsigned long elapsed_time;       // Accumulated time in milliseconds
    unsigned long start_time;         // Start time in milliseconds
} BED_Chrono;

// Function pointer for user-defined millis function
typedef unsigned long (*MillisFunction)();

// Default millis function, replace it as needed
MillisFunction millis_embeded = millis;  // By default, use the standard millis()

// Function to set a custom millis function
void setMillisFunction(MillisFunction customMillis) {
    millis_embeded = customMillis;
}

// Updates the chrono's elapsed time based on its status
void updateChrono(BED_Chrono &chrono) {
    if (chrono.status == CHRONO_STATUS_RUNNING) {
        chrono.elapsed_time += millis_embeded() - chrono.start_time;
        chrono.start_time = millis_embeded();
    } 
}

// Starts or resumes the chrono
void startChrono(BED_Chrono &chrono) {
    chrono.status = CHRONO_STATUS_RUNNING;
    chrono.start_time = millis_embeded();
}

// Starts the chrono from zero
void resetAndStartChrono(BED_Chrono &chrono) {
    startChrono(chrono);
    chrono.elapsed_time = 0;
}

// Pauses the chrono and updates the elapsed time
void pauseChrono(BED_Chrono &chrono) {
    updateChrono(chrono);
    chrono.status = CHRONO_STATUS_PAUSED;
}

// Stops the chrono and resets its values
void stopChrono(BED_Chrono &chrono) {
    chrono.status = CHRONO_STATUS_STOPPED;
    chrono.elapsed_time = 0;
    chrono.start_time = 0;
}

// Returns the elapsed time in milliseconds
unsigned long getChronoMillis(const BED_Chrono &chrono) {
    BED_Chrono tempChrono = chrono;
    updateChrono(tempChrono);
    return tempChrono.elapsed_time;
}

// Returns the elapsed time in seconds
unsigned long getChronoSeconds(const BED_Chrono &chrono) {
    return getChronoMillis(chrono) / MILLIS_PER_SECS;
}

// Splits the elapsed time in a BED_Chrono structure into hours, minutes, and seconds
void splitTime(const BED_Chrono &chrono, int &hours, int &minutes, int &seconds) {
    unsigned long total_seconds = getChronoSeconds(chrono);
    hours = total_seconds / 3600;
    minutes = (total_seconds % 3600) / 60;
    seconds = total_seconds % 60;
}

// Splits the elapsed time in a BED_Chrono structure into days, hours, minutes, and seconds
void splitTime(const BED_Chrono &chrono, int &days, int &hours, int &minutes, int &seconds) {
    unsigned long total_seconds = getChronoSeconds(chrono);
    days = total_seconds / (24 * 3600);
    total_seconds %= (24 * 3600);
    hours = total_seconds / 3600;
    minutes = (total_seconds % 3600) / 60;
    seconds = total_seconds % 60;
}

// Checks if the elapsed time in milliseconds has exceeded the given limit
bool hasExceededMillis(const BED_Chrono &chrono, unsigned long limitMillis) {
    return getChronoMillis(chrono) > limitMillis;
}

// Checks if the elapsed time in seconds has exceeded the given limit
bool hasExceededSeconds(const BED_Chrono &chrono, unsigned long limitSeconds) {
    return getChronoSeconds(chrono) > limitSeconds;
}

#endif // __BED_CHRONO_H__
