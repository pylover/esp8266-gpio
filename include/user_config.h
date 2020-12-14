#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

#define USE_OPTIMIZE_PRINTF
#define WIFI_ENABLE_SOFTAP  true


// Available IO     IO      Init State          Usage
#define GPIO0        0  //  Low (400ms 2.8V)    IO
#define GPIO1        1  //                      UART0 TX
#define GPIO2        2  //  High                IO
#define GPIO3        3  //  High                IO 
#define GPIO4        4  //  High                IO
#define GPIO5        5  //  Low                 IO  
//                   6
//                   7
//                   8
//                   9
#define GPIO10      10  //    
//                  11
#define GPIO12      12  // 
#define GPIO13      13  // 
#define GPIO14      14  // 
#define GPIO15      15  //
#define GPIO16      16  //



#endif

/*
#define PERIPHS_IO_MUX_MTDO_U           (PERIPHS_IO_MUX + 0x10)
#define FUNC_GPIO15                     3
#define FUNC_U0RTS                      4
#define PERIPHS_IO_MUX_U0TXD_U          (PERIPHS_IO_MUX + 0x18)
#define FUNC_U0TXD                      0
#define FUNC_GPIO1                      3
#define PERIPHS_IO_MUX_SD_CLK_U         (PERIPHS_IO_MUX + 0x1c)
#define FUNC_SDCLK                      0
#define FUNC_SPICLK                     1
#define PERIPHS_IO_MUX_SD_DATA0_U       (PERIPHS_IO_MUX + 0x20)
#define FUNC_SDDATA0                    0
#define FUNC_SPIQ                       1
#define FUNC_U1TXD                      4
#define PERIPHS_IO_MUX_SD_DATA1_U       (PERIPHS_IO_MUX + 0x24)
#define FUNC_SDDATA1                    0
#define FUNC_SPID                       1
#define FUNC_U1RXD                      4
#define FUNC_SDDATA1_U1RXD              7
#define PERIPHS_IO_MUX_SD_DATA2_U       (PERIPHS_IO_MUX + 0x28)
#define FUNC_SDDATA2                    0
#define FUNC_SPIHD                      1
#define FUNC_GPIO9                      3
#define PERIPHS_IO_MUX_SD_CMD_U         (PERIPHS_IO_MUX + 0x30)
#define FUNC_SDCMD                      0
#define FUNC_SPICS0                     1
#define FUNC_U1TXD_BK                   2
#define FUNC_U0TXD_BK                   4
*/
