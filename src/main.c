/*
 * main.c
 * Entry point for Wireless Charging UART Monitoring System Simulation
 */

#include <stdio.h>
#include "uart_monitor.h"

int main(void)
{
    printf("Wireless Charging UART Monitoring System Simulation\n");

    /*
     * Initialize the simulated UART monitoring data.
     * This clears the system parameter bytes and sets default values.
     */
    UARTMonitor_Init();

    /*
     * Update the simulated wireless charging system parameters.
     * This fills values such as Q factor, TX power, RX power,
     * battery voltage, rail voltage, current, and charger phase.
     */
    UARTMonitor_UpdateSystemData();

    /*
     * Create a simulated UART read response.
     *
     * UART_CMD_READ_PARAMS = 0x72
     * SYS_PARAM_START_ADDR = 0x00
     * SYS_PARAM_LENGTH     = 0x1D, 29 bytes
     *
     * This simulates a GUI requesting all system parameters.
     */
    UARTMonitor_CreateReadResponse(SYS_PARAM_START_ADDR, SYS_PARAM_LENGTH);

    /*
     * Print decoded values like a GUI would display.
     */
    UARTMonitor_PrintDecodedValues();

    return 0;
}