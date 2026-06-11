# FOD Concepts in Wireless Charging

This document explains the basic concepts of **Foreign Object Detection (FOD)** used in wireless charging systems and how FOD-related parameters are represented in this simulation project.

---

## 1. What is FOD?

**FOD** stands for **Foreign Object Detection**.

In a wireless charging system, power is transferred from a **Power Transmitter (PTx)** to a **Power Receiver (PRx)** using magnetic coupling between coils.

A foreign object is any unwanted object placed near or between the transmitter and receiver coils.

Examples of foreign objects include:

- Coin
- Key
- Metal ring
- Screw
- Small metallic object

If a metallic object is present during wireless power transfer, part of the transmitted energy may be absorbed by that object and converted into heat.

FOD helps detect such abnormal objects or abnormal power loss conditions.

---

## 2. Why FOD is important

FOD is important for both **safety** and **efficiency**.

FOD helps prevent:

- Unwanted heating
- Power loss
- Unsafe charging
- Poor charging efficiency
- Damage to transmitter or receiver
- Unexpected system shutdown

A wireless charger should reduce power or stop charging when a possible foreign object is detected.

---

## 3. Basic wireless charging power flow

A simplified wireless charging system has two main blocks:

```text
PTx = Power Transmitter
PRx = Power Receiver
```

Power flow:

```text
PTx sends power through transmitter coil
        ↓
Magnetic field transfers energy
        ↓
PRx receives power through receiver coil
        ↓
PRx converts received power for load or battery charging
```

In an ideal condition, most of the transmitted power should be received by the receiver.

In a practical system, some power loss is always present.

---

## 4. TX Power

**TX Power** means the power estimated or measured at the transmitter side.

In this simulation project, TX power is represented in raw units of:

```text
10 mW
```

Example:

```text
txPower_10mW = 1
Actual TX Power = 1 × 10 mW = 10 mW
```

TX power is useful for understanding how much power the transmitter is attempting to deliver.

---

## 5. RX Power

**RX Power** means the power reported or estimated at the receiver side.

In this simulation project, RX power is also represented in raw units of:

```text
10 mW
```

Example:

```text
rxPower_10mW = 0
Actual RX Power = 0 × 10 mW = 0 mW
```

RX power is used to compare how much power was actually received compared to how much power was transmitted.

---

## 6. Power Loss

Power loss is the difference between transmitter power and receiver power.

Formula:

```text
Power Loss = TX Power - RX Power
```

Example:

```text
TX Power = 10 mW
RX Power = 0 mW

Power Loss = 10 mW - 0 mW
Power Loss = 10 mW
```

If power loss is much higher than expected, it may indicate:

- Poor coil alignment
- Metallic foreign object
- Low coupling efficiency
- Measurement error
- Abnormal operating condition

Power loss is one of the important values used in real-time FOD checking.

---

## 7. Calibrated Power

Raw power measurements may contain errors because of practical circuit limitations.

Possible sources of error include:

- ADC tolerance
- Current sensor offset
- Voltage divider tolerance
- Amplifier gain error
- Temperature variation
- PCB and coil losses
- Calibration mismatch

To improve accuracy, calibrated power values may be used.

Examples:

- Calibrated TX Power
- Calibrated RX Power
- Calibrated TX Loss Power

Calibrated values help improve the accuracy of power loss calculation and FOD decisions.

---

## 8. Q Factor

**Q Factor** means **Quality Factor**.

In a wireless charging transmitter, the transmitter coil and resonant capacitor form a resonant circuit.

```text
Transmitter coil + resonant capacitor = resonant tank
```

Q factor indicates the quality of this resonant circuit.

Simple meaning:

```text
High Q Factor = lower loss and better resonance
Low Q Factor  = higher loss or abnormal condition
```

Q factor is useful for detecting changes in the coil environment.

---

## 9. Q Factor and FOD

Q factor is especially useful for **Open FOD**.

If a metal object is near the transmitter coil, the resonant behavior of the coil may change. This can cause the measured Q factor to shift from its normal value.

Example:

```text
Normal Q Factor   = 1470
Measured Q Factor = much lower than expected
```

This may indicate:

- Possible foreign object
- Abnormal coil loading
- Unexpected loss in resonant circuit

So Q factor helps detect foreign objects before or during charging.

---

## 10. Open FOD

**Open FOD** is usually performed before full power transfer starts.

Open FOD may use:

- Q factor
- Resonant frequency
- Coil response

Purpose:

```text
Detect possible foreign object before charging begins
```

If the measured Q factor or resonant frequency is outside the expected range, the system may avoid starting power transfer.

---

## 11. Real FOD

**Real FOD** is performed during power transfer.

Real FOD may use:

- TX power
- RX power
- Power loss
- Calibrated power values
- Threshold values

Purpose:

```text
Detect abnormal power loss while charging is active
```

If power loss is greater than the allowed threshold, the system may reduce or stop power transfer.

---

## 12. Resonant Frequency

Resonant frequency indicates the natural operating frequency of the coil-capacitor resonant circuit.

In this simulation project, resonant frequency is represented in raw units of:

```text
10 Hz
```

Example:

```text
resonantFreq_10Hz = 250
Actual resonant frequency = 250 × 10 Hz = 2500 Hz
```

A change in resonant frequency may indicate:

- Coil condition change
- Foreign object influence
- Component tolerance variation
- Alignment change

---

## 13. FOD-related parameters in this project

This project includes several parameters that are useful for FOD-related monitoring.

| Parameter | Description |
|---|---|
| `qFactorHigh` / `qFactorLow` | Q factor value split into high byte and low byte |
| `resonantFreqHigh` / `resonantFreqLow` | Resonant frequency split into high byte and low byte |
| `txPowerHigh` / `txPowerLow` | Transmitter power split into high byte and low byte |
| `rxPowerHigh` / `rxPowerLow` | Receiver power split into high byte and low byte |
| `lossPowerHigh` / `lossPowerLow` | Power loss split into high byte and low byte |
| `calibratedTxPowerHigh` / `calibratedTxPowerLow` | Calibrated transmitter power |
| `calibratedRxPowerHigh` / `calibratedRxPowerLow` | Calibrated receiver power |
| `calibratedTxLossPowerHigh` / `calibratedTxLossPowerLow` | Calibrated transmitter loss power |

---

## 14. Simulation values used in this project

The simulation uses the following sample raw values:

```text
qFactor = 1470
resonantFreq_10Hz = 250
txPower_10mW = 1
rxPower_10mW = 0
lossPower_10mW = 1
current_mA = 228
batteryVoltage_10mV = 1399
railVoltage_10mV = 283
```

Decoded values:

```text
Q Factor        = 1470
Resonant Freq   = 2500 Hz
TX Power        = 10 mW
RX Power        = 0 mW
Power Loss      = 10 mW
Current         = 228 mA
Battery Voltage = 13990 mV
Rail Voltage    = 2830 mV
```

---

## 15. Example FOD interpretation

Example condition:

```text
TX Power = 10 mW
RX Power = 0 mW
Power Loss = 10 mW
```

Interpretation:

```text
The transmitter is sending power, but the receiver is not reporting received power.
```

Possible reasons:

- Receiver not present
- Poor coupling
- Receiver communication not active
- Foreign object or abnormal loss
- Simulation test condition

In a real wireless charging system, this condition would be evaluated along with thresholds, calibration values, Q factor, and system state.

---

## 16. Relationship between Q Factor and Power Loss

Both Q factor and power loss can support FOD decisions.

```text
Q Factor   → useful before charging or during coil condition checking
Power Loss → useful during active power transfer
```

Simple comparison:

| Method | Usually Used For | Main Idea |
|---|---|---|
| Q Factor monitoring | Open FOD | Detect abnormal coil or resonant behavior |
| Power loss monitoring | Real FOD | Compare transmitted power and received power |

---

## 17. Summary

FOD is a safety feature used in wireless charging systems to detect possible foreign objects or abnormal power loss.

This simulation demonstrates FOD-related monitoring using:

- Q factor
- Resonant frequency
- TX power
- RX power
- Power loss
- Calibrated power values

These values help a GUI or monitoring system understand whether wireless charging is operating normally or whether abnormal conditions may exist.

---

## 18. Disclaimer

This project is an educational simulation created to demonstrate embedded UART monitoring concepts for wireless charging systems.

This repository does not contain proprietary production firmware, confidential company source code, or internal project files.
```
