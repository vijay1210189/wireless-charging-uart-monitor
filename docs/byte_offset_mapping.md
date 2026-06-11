# Byte Offset Mapping

This document explains how wireless charging system parameters are mapped into UART bytes.

## What is a byte offset?

A byte offset is the position of a byte inside a data array or UART frame.

Offset counting starts from `0`.

Example:

```text
Offset 0 = first byte
Offset 1 = second byte
Offset 2 = third byte
