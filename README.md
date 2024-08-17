# Embedded_Chrono
Time Management Library for Embedded Systems

This library provides easy-to-use functions for managing time in embedded projects. With `chrono.h`, you can:

- Track elapsed time with a customizable `Chrono` structure.
- Start, pause, and stop timing operations.
- Convert elapsed time into hours, minutes, seconds, or days.
- Check if a specified time limit has been exceeded.
- Use a custom function for time retrieval.

Ideal for projects requiring precise time management and time-based events.


This file provides functionality to handle timing operations using a custom `Chrono` structure.
Features include:

1. **Time Conversion**:
   - Constants for milliseconds, seconds, and minutes.
   - Macros for converting time units.

2. **Chrono Status Definitions**:
   - Defines for different states of the chrono (running, paused, stopped).

3. **Chrono Management**:
   - `updateChrono()`: Updates elapsed time.
   - `startChrono()`: Starts or resumes the chrono.
   - `resetAndStartChrono()`: Resets and starts the chrono.
   - `pauseChrono()`: Pauses the chrono.
   - `stopChrono()`: Stops and resets the chrono.

4. **Time Retrieval**:
   - `getChronoMillis()`: Gets elapsed time in milliseconds.
   - `getChronoSeconds()`: Gets elapsed time in seconds.

5. **Time Splitting**:
   - `splitTime()`: Splits elapsed time into hours, minutes, seconds, and optionally days.

6. **Time Exceeded Checks**:
   - `hasExceededMillis()`: Checks if the elapsed time has exceeded a given millisecond limit.
   - `hasExceededSeconds()`: Checks if the elapsed time has exceeded a given second limit.

7. **Custom Millis Function**:
   - Allows setting a custom function to get the current time in milliseconds.

Usage example includes initialization, starting, updating, and stopping the chrono, and checking if time limits have been exceeded.
