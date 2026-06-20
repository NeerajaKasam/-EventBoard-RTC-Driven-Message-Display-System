# Event Board – RTC Driven Message Display System

## Overview

Event Board is a real-time embedded scheduling and information display system built using the LPC2148 ARM7 microcontroller. The project functions as an intelligent digital notice board capable of automatically displaying predefined event messages at specific times using the on-chip Real-Time Clock (RTC).

Unlike conventional notice boards that require manual updates, this system continuously monitors the current time and displays scheduled announcements automatically. To ensure complete visibility of lengthy messages on a 16x2 LCD, a scrolling display mechanism has been implemented.

The project also incorporates environmental monitoring through an LM35 temperature sensor connected to the LPC2148 ADC module. During non-event periods, the system displays the current date, time, and room temperature, making efficient use of the display.

For secure operation, an Admin Mode is provided through an external interrupt-based switch and password authentication using a 4x4 matrix keypad. Authorized users can modify RTC settings and enable or disable events without reprogramming the microcontroller.

This project demonstrates the integration of RTC, LCD, Keypad, ADC, External Interrupts, GPIO, Sensor Interfacing, and Menu-Driven Embedded Software Design in a single real-time embedded application.

---

## Objectives

- Automate event announcements using RTC-based scheduling.
- Display predefined messages at user-defined times.
- Implement a scrolling mechanism for long LCD messages.
- Monitor room temperature using an LM35 sensor.
- Provide secure password-protected administrative access.
- Allow runtime modification of RTC settings.
- Enable or disable scheduled messages dynamically.
- Demonstrate real-time embedded system design using LPC2148.

---

## Key Features

### Real-Time Event Scheduling
- Automatic event triggering using LPC2148 RTC.
- Scheduled message display without user intervention.
- Real-time date and time management.

### Intelligent LCD Display
- Event messages displayed automatically.
- Scrolling support for long messages.
- Time, date, and temperature display during idle mode.

### Secure Admin Mode
- Password-based authentication.
- External interrupt triggered access.
- Runtime system configuration.

### Event Management
- Enable individual events.
- Disable unwanted events.
- Select active schedules for the day.

### Temperature Monitoring
- LM35 sensor integration.
- ADC-based temperature acquisition.
- Continuous environmental monitoring.

### Status Indicators
- Green LED indicates active event display.
- Red LED indicates normal monitoring mode.
- Buzzer support for notifications.

---

## Hardware Components

| Component | Function |
|------------|------------|
| LPC2148 | Main Controller |
| RTC (Internal) | Time Management |
| 16x2 LCD | Message Display |
| 4x4 Matrix Keypad | User Input |
| LM35 Sensor | Temperature Measurement |
| ADC | Analog to Digital Conversion |
| External Switch | Admin Mode Entry |
| Green LED | Event Status Indicator |
| Red LED | Idle Status Indicator |
| Buzzer | Notification Device |
| Power Supply | System Power |

---

## Software Tools

- Embedded C
- Keil µVision
- Flash Magic
- Proteus Design Suite

---

## Block Diagram

<img width="750" height="450" alt="image" src="https://github.com/user-attachments/assets/035d7339-4bf2-41d6-98e6-11c13f15ebf0" />

### Block Description

The LPC2148 acts as the central controller of the system.

The RTC module maintains accurate date and time information used for event scheduling. The keypad and admin switch allow user interaction and secure access to configuration menus. The LCD displays system information and scheduled messages. The LM35 sensor provides room temperature data through the ADC module. Green and Red LEDs indicate the current operating mode of the system.

---

## Peripheral Interfaces Used

### RTC Interfacing

The LPC2148 contains an internal Real-Time Clock responsible for maintaining:

- Hours
- Minutes
- Seconds
- Day
- Date
- Month
- Year

The RTC continuously runs in the background and acts as the primary scheduler for event announcements.

---

### LCD Interfacing

A 16x2 alphanumeric LCD is used to display:

- Current Time
- Current Date
- Room Temperature
- Event Messages
- Password Prompts
- Configuration Menus
- Status Information

Since many event messages exceed 16 characters, a scrolling mechanism is implemented to display complete information.

---

### Keypad Interfacing

A 4x4 Matrix Keypad provides user interaction.

Functions include:

- Password Entry
- Menu Navigation
- RTC Editing
- Event Selection
- Event Activation
- Event Deactivation

---

### ADC Interfacing

The LPC2148 ADC module converts analog signals from the LM35 sensor into digital values.

ADC is used for:

- Temperature Monitoring
- Sensor Data Acquisition
- Environmental Monitoring

---

### LM35 Sensor Interfacing

The LM35 sensor provides an analog output proportional to temperature.

Characteristics:

- Linear output
- 10mV per °C
- No calibration required
- Direct ADC compatibility

Temperature values are processed and displayed on the LCD.

---

### External Interrupt Interfacing

An external switch is connected to an interrupt pin.

When pressed:

- Interrupt is generated.
- Normal operation pauses temporarily.
- Admin Mode is activated immediately.

This allows instant access to system settings.

---

### GPIO Interfacing

GPIO pins are used for:

- LCD Communication
- Keypad Scanning
- LED Control
- Buzzer Control
- Switch Monitoring

---

## System Operation

### 1. System Startup

After power-on, the LPC2148 initializes:

- RTC
- LCD
- ADC
- GPIO
- Keypad
- External Interrupt
- LEDs
- Buzzer

All event schedules are loaded into memory.

---

### 2. Normal Monitoring Mode

The system continuously:

- Reads RTC Time
- Reads RTC Date
- Reads Temperature
- Displays Information
- Checks Scheduled Events

Example LCD Display:

```text
Time : 09:45:20

Temp : 28°C
```

During this state:

- Red LED = ON
- Green LED = OFF

---

### 3. Event Display Mode

Whenever the current RTC time matches a scheduled event:

- Corresponding event is selected.
- LCD scrolling starts.
- Event message is displayed.
- Green LED turns ON.

Example Event:

```text
ARM Workshop on External Interrupts
in LAB1 at 10 AM
```

During this state:

- Green LED = ON
- Red LED = OFF

---

## Admin Mode

Admin Mode is activated using an external interrupt switch.

### Authentication Process

User must enter a valid password.

Example:

```text
Enter Password
****
```

If correct:

```text
Access Granted
```

If incorrect:

```text
Access Denied
```

Only authenticated users can access system settings.

---

## RTC Configuration Menu

Authorized users can modify:

- Hour
- Minute
- Second
- Date
- Day
- Month
- Year

Example:

```text
Current Time : 09:20

New Time : 09:30
```

The updated values are written directly into RTC registers.

---

## Event Configuration Menu

The administrator can:

- Select Event Number
- Enable Event
- Disable Event
- Exit Configuration

This provides flexibility without changing source code.

---

## Event Data Structure

```c
#define TOTAL_MESSAGES 10

typedef struct
{
    unsigned char hour;
    unsigned char minute;
    char text[80];
    unsigned char enabled;
} Message;
```

### Structure Members

| Field | Description |
|----------|------------|
| hour | Event Hour |
| minute | Event Minute |
| text | Event Message |
| enabled | Event Status Flag |

---

## Default Event Schedule

```c
{7,45,"Good Morning! Classes Start Soon",1}

{13,45,"C Programming Session in Classroom Number 2",1}

{10,15,"C Module Theory Exam in 4th Floor Lab1",1}

{10,15,"C Module Lab Exam in Lab2 and Middle Lab at 10:30AM",1}

{12,45,"Lunch Break from 1PM to 2PM",1}

{9,45,"ARM Workshop on External Interrupts in LAB1 at 10AM",1}

{9,45,"ARM Kit Issue Time from 10AM to 10:30AM",1}

{15,15,"Only 15 Minutes Break Time for Next ARM Session",1}

{17,00,"Revise Today's Class Programs at Home",1}

{17,45,"End of Day - See You Tomorrow",1}
```

Initially all events are enabled.

---

## Project Flow

1. Initialize all peripherals.
2. Read current RTC date and time.
3. Acquire temperature from LM35.
4. Display system information.
5. Compare RTC time with event schedules.
6. Check whether event is enabled.
7. Display scrolling event message if match occurs.
8. Turn ON Green LED during event display.
9. Display clock and temperature otherwise.
10. Turn ON Red LED during idle mode.
11. Monitor external interrupt switch.
12. Enter Admin Mode when interrupt occurs.
13. Authenticate user.
14. Allow RTC and event configuration.
15. Return to Normal Mode.

---

## Project Directory Structure

```text
EventBoard/
│
├── main.c
│
├── rtc.c
├── rtc.h
├── rtc_defines.h
│
├── lcd.c
├── lcd.h
├── lcd_defines.h
│
├── adc.c
├── adc.h
├── adc_defines.h
│
├── kpm.c
├── kpm.h
├── kpm_defines.h
│
├── admin.c
├── admin.h
│
├── delay.c
├── delay.h
│
├── pin_connect_block.c
├── pin_connect_block.h
│
├── defines.h
├── interrupts_defines.h
├── types.h
│
└── README.md
```

---

## Learning Outcomes

This project provided practical experience in:

- Embedded C Programming
- LPC2148 ARM7 Architecture
- RTC Programming
- LCD Interfacing
- Matrix Keypad Scanning
- ADC Programming
- Sensor Interfacing
- LM35 Temperature Monitoring
- GPIO Programming
- External Interrupt Handling
- Real-Time Embedded Systems
- Event Scheduling Techniques
- Menu-Driven Application Development
- Modular Firmware Design

---

## Applications

- Digital Notice Boards
- Educational Institutions
- Classroom Announcement Systems
- Training Centers
- Office Information Displays
- Industrial Information Panels
- Event Reminder Systems
- Smart Scheduling Applications

---

## Future Enhancements

- EEPROM-Based Event Storage
- UART-Based Event Updates
- Bluetooth Connectivity
- GSM Notification Support
- IoT Dashboard Integration
- Wi-Fi-Based Configuration
- Mobile Application Control
- Cloud Event Scheduling

---
