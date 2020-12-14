
// Internal 
#include "user_config.h"
#include "partition.h"
#include "wifi.h"
#include "params.h" 
#include "debug.h"

// SDK
#include <ets_sys.h>
#include <osapi.h>
#include <mem.h>
#include <user_interface.h>
#include <driver/uart.h>
#include <upgrade.h>
#include <c_types.h>
#include <ip_addr.h> 
#include <gpio.h>

static ETSTimer t;
static Params params;
static int cpin = 0;

#define __version__     "0.1.0"

//#define defaultiosetup(num, mux, func) \
//    PIN_FUNC_SELECT(mux, func)

//    PIN_PULLUP_EN(mux); \
//    GPIO_OUTPUT_SET(GPIO_ID_PIN(num), 1)

#define togglepin(num) \
    GPIO_OUTPUT_SET(GPIO_ID_PIN(num), !GPIO_INPUT_GET(GPIO_ID_PIN(num)))

typedef enum {
    PU_UNCHANGED,
    PU_EN,
    PU_DIS
} pullup_t;


typedef struct {
    uint8_t     num;
    uint32_t    mux;
    uint32_t    func;
    pullup_t    pullup;
    uint8_t     init;
} io_t;


#define TOTAL      10 
static io_t ios[TOTAL+1] = {
    {0,  PERIPHS_IO_MUX_GPIO0_U,    FUNC_GPIO0,  PU_UNCHANGED  , 0},
   //1,  PERIPHS_IO_MUX_U0TXD_U,    FUNC_GPIO1,  PU_UNCHANGED  , 0}.
    {2,  PERIPHS_IO_MUX_GPIO2_U,    FUNC_GPIO2,  PU_UNCHANGED  , 0},
    {3,  PERIPHS_IO_MUX_U0RXD_U,    FUNC_GPIO3,  PU_UNCHANGED  , 0},
    {4,  PERIPHS_IO_MUX_GPIO4_U,    FUNC_GPIO4,  PU_UNCHANGED  , 0},
    {5,  PERIPHS_IO_MUX_GPIO5_U,    FUNC_GPIO5,  PU_UNCHANGED  , 0},
    {10, PERIPHS_IO_MUX_SD_DATA3_U, FUNC_GPIO10, PU_EN         , 0},
    {12, PERIPHS_IO_MUX_MTDI_U,     FUNC_GPIO12, PU_UNCHANGED  , 0},
    {13, PERIPHS_IO_MUX_MTCK_U,     FUNC_GPIO13, PU_DIS        , 0},
    {14, PERIPHS_IO_MUX_MTMS_U,     FUNC_GPIO14, PU_DIS        , 0},
    {15, PERIPHS_IO_MUX_MTDO_U,     FUNC_GPIO15, PU_EN         , 0},
    {NULL}
};


static int g16;

void ICACHE_FLASH_ATTR 
toggle(void *a) {
    togglepin(ios[cpin].num);
    g16 = !g16; 
    gpio16_output_set(g16);
    
    if (!GPIO_INPUT_GET(GPIO_ID_PIN(ios[cpin].num))) {
        if (++cpin == TOTAL) {
            cpin = 0;
        }
    }
}


void initio() {
    int i;
    io_t io;

    for (i = 0; i < TOTAL; i++) {
        io = ios[i];
        PIN_FUNC_SELECT(io.mux, io.func);
        
        if (io.pullup == PU_EN) {
            PIN_PULLUP_EN(io.mux);
        }
        else if (io.pullup == PU_DIS) {
            PIN_PULLUP_DIS(io.mux);
        }
        GPIO_OUTPUT_SET(GPIO_ID_PIN(io.num), io.init);
    }
   
    gpio16_output_conf();
    gpio16_output_set(0);

    os_timer_disarm(&t); 
    os_timer_setfn(&t, (os_timer_func_t *)toggle, NULL);
    os_timer_arm(&t, 500, 1);
}


void wifi_connect_cb(uint8_t status) {
    if(status == STATION_GOT_IP) {
        INFO("WIFI Connected...\r\n");
    } else {
    }
}


void user_init(void) {
    //system_uart_swap();
    //uart_init(BIT_RATE_115200, BIT_RATE_115200);
    //os_delay_us(60000);
    
    uart_div_modify(UART0, UART_CLK_FREQ / BIT_RATE_115200);
    uart_rx_intr_disable(UART0);
    uart_rx_intr_disable(UART1);

    bool ok = params_load(&params);
    if (!ok) {
        ERROR("Cannot load Params\r\n");
#if !WIFI_ENABLE_SOFTAP
        return;
#endif
        if(!params_defaults(&params)) {
            ERROR("Cannot save params\r\n");
            return;
        }
    }
    
    params_print(&params);
    
    // Disable wifi led before infrared
    wifi_status_led_uninstall();
    wifi_start(&params, wifi_connect_cb);
    
    webadmin_start();
    initio();
}


void ICACHE_FLASH_ATTR user_pre_init(void)
{
    if(!system_partition_table_regist(at_partition_table, 
                sizeof(at_partition_table)/sizeof(at_partition_table[0]),
                SPI_FLASH_SIZE_MAP)) {
        FATAL("system_partition_table_regist fail\r\n");
        while(1);
    }
}

