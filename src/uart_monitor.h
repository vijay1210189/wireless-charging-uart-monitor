#ifndef UART_MONITOR_H
#define UART_MONITOR_H

#include <stdint.h>

/*
 * Wireless Charging UART Monitoring System Simulation
 *
 * This header defines:
 * - UART frame constants
 * - charger phase enum
 * - system parameter structure
 * - union for byte access
 * - function declarations
 */

/* UART buffer sizes */
#define UART_RX_BUFFER_SIZE      (64u)
#define UART_TX_BUFFER_SIZE      (64u)

/* UART command values */
#define UART_CMD_READ_PARAMS     (0x72u)
#define UART_CMD_WRITE_PARAMS    (0x77u)

/* System parameter address map */
#define SYS_PARAM_START_ADDR     (0x00u)
#define SYS_PARAM_LENGTH         (0x1Du)   /* 29 bytes */

/* Tuning parameter address map */
#define TUN_PARAM_START_ADDR     (0x20u)
#define TUN_PARAM_LENGTH         (0x16u)   /* 22 bytes */

/* Charger phase values */
typedef enum
{
    CHARGER_PHASE_DEFAULT        = 0x00,
    CHARGER_PHASE_PING           = 0x01,
    CHARGER_PHASE_CONFIG         = 0x02,
    CHARGER_PHASE_NEGOTIATION    = 0x03,
    CHARGER_PHASE_POWER_TRANSFER = 0x04,
    CHARGER_PHASE_RENEGOTIATION  = 0x05,
    CHARGER_PHASE_CLOAK          = 0x06,
    CHARGER_PHASE_ERROR          = 0x07
} ChargerPhase_t;

/* System parameters sent to GUI as UART bytes */
typedef struct
{
    uint8_t selectedCoil;
    uint8_t chargeStatus;

    uint8_t errorFlagsHH;
    uint8_t errorFlagsHL;
    uint8_t errorFlagsLH;
    uint8_t errorFlagsLL;

    uint8_t qFactorHigh;
    uint8_t qFactorLow;

    uint8_t resonantFreqHigh;
    uint8_t resonantFreqLow;

    uint8_t txPowerHigh;
    uint8_t txPowerLow;

    uint8_t rxPowerHigh;
    uint8_t rxPowerLow;

    uint8_t calibratedTxPowerHigh;
    uint8_t calibratedTxPowerLow;

    uint8_t calibratedRxPowerHigh;
    uint8_t calibratedRxPowerLow;

    uint8_t lossPowerHigh;
    uint8_t lossPowerLow;

    uint8_t calibratedTxLossPowerHigh;
    uint8_t calibratedTxLossPowerLow;

    uint8_t currentHigh;
    uint8_t currentLow;

    uint8_t batteryVoltageHigh;
    uint8_t batteryVoltageLow;

    uint8_t railVoltageHigh;
    uint8_t railVoltageLow;

    uint8_t chargerPhase;
} SystemParams_t;

/*
 * Union allows the same system parameters to be accessed in two ways:
 * 1. As named fields using params
 * 2. As raw bytes using bytes[]
 */
typedef union
{
    uint8_t bytes[SYS_PARAM_LENGTH];
    SystemParams_t params;
} SystemParamsUnion_t;

/* Function declarations */
void UARTMonitor_Init(void);
void UARTMonitor_UpdateSystemData(void);
void UARTMonitor_CreateReadResponse(uint8_t startAddress, uint8_t length);
void UARTMonitor_PrintDecodedValues(void);
const char* UARTMonitor_GetChargerPhaseName(uint8_t phase);

#endif /* UART_MONITOR_H */
``
