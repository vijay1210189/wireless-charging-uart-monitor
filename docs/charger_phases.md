# Charger Phases

This document explains the `chargerPhase` parameter used in the Wireless Charging UART Monitoring System Simulation.

## What is Charger Phase?

`chargerPhase` represents the current operating stage of a wireless charging system.

A wireless charger does not immediately start full power transfer. It usually moves through multiple stages such as detection, configuration, negotiation, and power transfer.

The `chargerPhase` parameter helps show where the charger currently is in the charging sequence.

## Why Charger Phase is useful

Monitoring charger phase is useful for debugging.

For example:

```text
If the system is stuck in PING      → receiver may not be detected
If the system is stuck in CONFIG    → configuration packet issue may exist
If the system is stuck in NEGOTIATION → power negotiation may be failing
If the system reaches POWER TRANSFER → actual charging has started
If the system enters ERROR          → a fault condition occurred
