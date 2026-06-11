/*
 * uart_monitor.c
 * UART packet simulation for Wireless Charging UART Monitoring System
 */

#include <stdio.h>
#include "uart_monitor.h"

/* Global system parameter storage */
static SystemParamsUnion_t g_systemParams;

/* UART transmit buffer simulation */
static uint8_t g_uartTxBuffer[UART_TX_BUFFER_SIZE];

/*
 * Split a 16-bit value into high byte and low byte.
 *
 * Example:
 * value = 0x0577
 * highByte = 0x05
 * lowByte  = 0x77
 */
static void SplitUint16(uint16_t value, uint8_t *highByte, uint8_t *lowByte)
{
    *highByte = (uint8_t)(value >> 8);
    *lowByte = (uint8_t)(value & 0xFFu);
}

void UARTMonitor_Init(void)
{
    for (uint8_t i = 0u; i < SYS_PARAM_LENGTH; i++)
    {
        g_systemParams.bytes[i] = 0u;
    }

    g_systemParams.params.selectedCoil = 1u;
    g_systemParams.params.chargeStatus = 0u;
    g_systemParams.params.chargerPhase = CHARGER_PHASE_DEFAULT;
}

void UARTMonitor_UpdateSystemData(void)
{
    uint16_t qFactor = 1470u;
    uint16_t resonantFreq_10Hz = 250u;
    uint16_t txPower_10mW = 1u;
    uint16_t rxPower_10mW = 0u;
    uint16_t calTxPower_10mW = 0u;
    uint16_t calRxPower_10mW = 150u;
    uint16_t lossPower_10mW = txPower_10mW - rxPower_10mW;
    uint16_t calTxLossPower_10mW = 0u;
    uint16_t current_mA = 228u;
    uint16_t batteryVoltage_10mV = 1399u;
    uint16_t railVoltage_10mV = 283u;

    g_systemParams.params.selectedCoil = 1u;
    g_systemParams.params.chargeStatus = 2u;

    g_systemParams.params.errorFlagsHH = 0u;
    g_systemParams.params.errorFlagsHL = 0u;
    g_systemParams.params.errorFlagsLH = 0u;
    g_systemParams.params.errorFlagsLL = 0u;

    SplitUint16(qFactor,
                &g_systemParams.params.qFactorHigh,
                &g_systemParams.params.qFactorLow);

    SplitUint16(resonantFreq_10Hz,
                &g_systemParams.params.resonantFreqHigh,
                &g_systemParams.params.resonantFreqLow);

    SplitUint16(txPower_10mW,
                &g_systemParams.params.txPowerHigh,
                &g_systemParams.params.txPowerLow);

    SplitUint16(rxPower_10mW,
                &g_systemParams.params.rxPowerHigh,
                &g_systemParams.params.rxPowerLow);

    SplitUint16(calTxPower_10mW,
                &g_systemParams.params.calibratedTxPowerHigh,
                &g_systemParams.params.calibratedTxPowerLow);

    SplitUint16(calRxPower_10mW,
                &g_systemParams.params.calibratedRxPowerHigh,
                &g_systemParams.params.calibratedRxPowerLow);

    SplitUint16(lossPower_10mW,
                &g_systemParams.params.lossPowerHigh,
                &g_systemParams.params.lossPowerLow);

    SplitUint16(calTxLossPower_10mW,
                &g_systemParams.params.calibratedTxLossPowerHigh,
                &g_systemParams.params.calibratedTxLossPowerLow);

    SplitUint16(current_mA,
                &g_systemParams.params.currentHigh,
                &g_systemParams.params.currentLow);

    SplitUint16(batteryVoltage_10mV,
                &g_systemParams.params.batteryVoltageHigh,
                &g_systemParams.params.batteryVoltageLow);

    SplitUint16(railVoltage_10mV,
                &g_systemParams.params.railVoltageHigh,
                &g_systemParams.params.railVoltageLow);

    g_systemParams.params.chargerPhase = CHARGER_PHASE_PING;
}

void UARTMonitor_CreateReadResponse(uint8_t startAddress, uint8_t length)
{
    uint8_t safeLength = length;

    if (startAddress >= SYS_PARAM_LENGTH)
    {
        safeLength = 0u;
    }
    else if ((startAddress + length) > SYS_PARAM_LENGTH)
    {
        safeLength = SYS_PARAM_LENGTH - startAddress;
    }

    g_uartTxBuffer[0] = UART_CMD_READ_PARAMS;
    g_uartTxBuffer[1] = startAddress;
    g_uartTxBuffer[2] = safeLength;

    for (uint8_t i = 0u; i < safeLength; i++)
    {
        g_uartTxBuffer[i + 3u] = g_systemParams.bytes[startAddress + i];
    }

    printf("\nUART Response Bytes:\n");

    for (uint8_t i = 0u; i < (uint8_t)(safeLength + 3u); i++)
    {
        printf("Response[%02u] = 0x%02X\n", i, g_uartTxBuffer[i]);
    }
}

void UARTMonitor_PrintDecodedValues(void)
{
    uint16_t qFactor =
        ((uint16_t)g_systemParams.params.qFactorHigh << 8) |
        g_systemParams.params.qFactorLow;

    uint16_t txPower_10mW =
        ((uint16_t)g_systemParams.params.txPowerHigh << 8) |
        g_systemParams.params.txPowerLow;

    uint16_t rxPower_10mW =
        ((uint16_t)g_systemParams.params.rxPowerHigh << 8) |
        g_systemParams.params.rxPowerLow;

    uint16_t lossPower_10mW =
        ((uint16_t)g_systemParams.params.lossPowerHigh << 8) |
        g_systemParams.params.lossPowerLow;

    uint16_t current_mA =
        ((uint16_t)g_systemParams.params.currentHigh << 8) |
        g_systemParams.params.currentLow;

    uint16_t batteryVoltage_10mV =
        ((uint16_t)g_systemParams.params.batteryVoltageHigh << 8) |
        g_systemParams.params.batteryVoltageLow;

    uint16_t railVoltage_10mV =
        ((uint16_t)g_systemParams.params.railVoltageHigh << 8) |
        g_systemParams.params.railVoltageLow;

    printf("\nDecoded GUI Values:\n");
    printf("Q Factor          : %u\n", qFactor);
    printf("TX Power          : %u mW\n", txPower_10mW * 10u);
    printf("RX Power          : %u mW\n", rxPower_10mW * 10u);
    printf("Power Loss        : %u mW\n", lossPower_10mW * 10u);
    printf("Current           : %u mA\n", current_mA);
    printf("Battery Voltage   : %u mV\n", batteryVoltage_10mV * 10u);
    printf("Rail Voltage      : %u mV\n", railVoltage_10mV * 10u);
    printf("Charger Phase     : %s\n",
           UARTMonitor_GetChargerPhaseName(g_systemParams.params.chargerPhase));
}

const char* UARTMonitor_GetChargerPhaseName(uint8_t phase)
{
    switch (phase)
    {
        case CHARGER_PHASE_DEFAULT:
            return "DEFAULT";

        case CHARGER_PHASE_PING:
            return "PING";

        case CHARGER_PHASE_CONFIG:
            return "CONFIG";

        case CHARGER_PHASE_NEGOTIATION:
            return "NEGOTIATION";

        case CHARGER_PHASE_POWER_TRANSFER:
            return "POWER TRANSFER";

        case CHARGER_PHASE_RENEGOTIATION:
            return "RENEGOTIATION";

        case CHARGER_PHASE_CLOAK:
            return "CLOAK";

        case CHARGER_PHASE_ERROR:
            return "ERROR";

        default:
            return "UNKNOWN";
    }
}
