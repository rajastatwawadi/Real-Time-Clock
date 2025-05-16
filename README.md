# Real Time Clock
This project implements a Real-Time Clock (RTC) system using the 8051 microcontroller and the **MCP7940N** RTC IC. The system communicates over the **I2C protocol**, implemented **from scratch in Embedded C**, and displays the time and date on a **16x2 LCD**.

### Features

- Real-time clock and calendar using **MCP7940N RTC IC**
- Timekeeping with seconds, minutes, hours, day, date, month, and year
- I2C communication protocol implemented **manually (bit-banging)**
- Interfaced with **16x2 character LCD** for live display
- Developed in **Embedded C** using **8051 microcontroller**

### Hardware Components

- 8051 Microcontroller (e.g., AT89C052D)
- MCP7940N RTC IC
- 16x2 Character LCD
- Pull-up resistors (4.7kΩ) for I2C lines (SDA, SCL)
- Connecting wires, breadboard or PCB

### Software Stack

- **Language**: Embedded C  
- **Toolchain**: Keil µVision
- **Programmer**: 8051 Elnec programmer
