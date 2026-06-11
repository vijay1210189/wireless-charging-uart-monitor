# Wireless Charging UART Monitoring System Simulation

This repository contains a **C-based simulation of UART parameter monitoring for a wireless charging system**.

The project demonstrates how embedded system parameters can be packed into UART bytes, transmitted as a response frame, and decoded into GUI-style monitoring values.

This is an educational simulation project and does not contain proprietary production firmware.

---

## Project Overview

Wireless charging systems monitor several real-time parameters such as transmitter power, receiver power, battery voltage, rail voltage, Q factor, resonant frequency, current, power loss, and charger phase.

In an embedded system, these values are often packed into byte arrays and sent to a PC-based GUI or serial monitor using UART communication.

This project simulates that process using standard C.

The simulated data flow is:

```text
System parameter values
        ↓
High-byte / low-byte conversion
        ↓
System parameter byte array
        ↓
UART response frame
        ↓
Decoded GUI-style output
```

---

## Key Features

- Simulates UART-based parameter monitoring
- Demonstrates byte offset mapping
- Demonstrates high-byte and low-byte splitting
- Simulates system parameter response frame
- Includes charger phase tracking
- Includes FOD-related monitoring concepts
- Prints decoded GUI-style values
- Written in portable C for easy compilation and learning

---

## Concepts Demonstrated

This project demonstrates the following embedded systems concepts:

- UART frame structure
- UART command and response handling
- Byte-level data packing
- Byte offset mapping
- High-byte and low-byte conversion
- Use of `struct` and `union`
- Charger phase monitoring
- Foreign Object Detection, FOD, related parameters
- GUI-style decoding of embedded data

---

## Repository Structure

```text
wireless-charging-uart-monitor/
│
├── README.md
├── src/
│   ├── main.c
│   ├── uart_monitor.c
│   └── uart_monitor.h
│
├── docs/
│   ├── byte_offset_mapping.md
│   ├── charger_phases.md
│   └── fod_concepts.md
│
├── .gitignore
└── LICENSE
```

---

## UART Frame Format

The simulated UART read response uses this format:

```text
Response[0] = Command
Response[1] = Start Address
Response[2] = Length
Response[3] = Data Offset 0
Response[4] = Data Offset 1
...
```

In this project:

```text
Read command        = 0x72
Start address       = 0x00
System data length  = 0x1D, 29 bytes
```

So the simulated GUI read command is:

```text
0x72 0x00 0x1D
```

The response contains:

```text
3 header bytes + 29 data bytes = 32 bytes
```

---

## System Parameter Mapping

The system parameters are stored as UART bytes.

Some values are larger than one byte, so they are split into:

```text
High byte + Low byte
```

Example:

```text
Battery voltage raw value = 1399
1399 decimal = 0x0577

High byte = 0x05
Low byte  = 0x77
```

The decoded value is:

```text
Battery voltage = 1399 × 10 mV
Battery voltage = 13990 mV
```

The full byte offset mapping is documented here:

```text
docs/byte_offset_mapping.md
```

---

## Charger Phase Tracking

The project includes a one-byte parameter called:

```text
chargerPhase
```

This parameter represents the current wireless charging protocol phase.

Supported charger phases:

```text
0x00 = DEFAULT
0x01 = PING
0x02 = CONFIG
0x03 = NEGOTIATION
0x04 = POWER TRANSFER
0x05 = RENEGOTIATION
0x06 = CLOAK
0x07 = ERROR
```

In this project:

```text
chargerPhase data offset = 28
```

If the full UART response includes three header bytes:

```text
chargerPhase response index = 31
```

More details are documented here:

```text
docs/charger_phases.md
```

---

## FOD-Related Monitoring

FOD stands for:

```text
Foreign Object Detection
```

Wireless charging systems use FOD-related parameters to detect abnormal conditions such as metallic foreign objects or unexpected power loss.

This project includes FOD-related monitoring concepts such as:

- Q factor
- Resonant frequency
- TX power
- RX power
- Power loss
- Calibrated power values

More details are documented here:

```text
docs/fod_concepts.md
```

---

## How to Run

### Option 1: Compile using GCC

From the project root folder, run:

```bash
gcc src/main.c src/uart_monitor.c -o uart_monitor
```

Then run:

```bash
./uart_monitor
```

On Windows, run:

```bash
uart_monitor.exe
```

---

## Expected Output

The program prints a simulated UART response and decoded GUI-style values.

Example decoded output:

```text
Wireless Charging UART Monitoring System Simulation

UART Response Bytes:
Response[00] = 0x72
Response[01] = 0x00
Response[02] = 0x1D
...

Decoded GUI Values:
Q Factor          : 1470
TX Power          : 10 mW
RX Power          : 0 mW
Power Loss        : 10 mW
Current           : 228 mA
Battery Voltage   : 13990 mV
Rail Voltage      : 2830 mV
Charger Phase     : PING
```

---

## Main Source Files

### `main.c`

Entry point of the simulation.

It calls:

```c
UARTMonitor_Init();
UARTMonitor_UpdateSystemData();
UARTMonitor_CreateReadResponse(SYS_PARAM_START_ADDR, SYS_PARAM_LENGTH);
UARTMonitor_PrintDecodedValues();
```

---

### `uart_monitor.h`

Contains:

- UART constants
- command values
- system parameter length
- charger phase enum
- system parameter structure
- union for byte access
- function declarations

---

### `uart_monitor.c`

Contains:

- sample system parameter updates
- high-byte and low-byte splitting
- UART response generation
- decoded output printing
- charger phase name conversion

---

## Learning Outcomes

Through this project, the following concepts are practiced:

- Embedded C structure design
- UART packet simulation
- Data packing and unpacking
- Byte offset mapping
- High-byte and low-byte handling
- Charger phase monitoring
- FOD-related monitoring concepts
- Documentation of embedded system logic

---

## Disclaimer

This repository is an educational simulation created to demonstrate embedded UART monitoring concepts for wireless charging systems.

It does not contain proprietary company source code, confidential files, internal project files, or production firmware.

---

## License

This project is released under the MIT License.
