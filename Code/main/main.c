#include <stdlib.h>
#include "dweet.h"
#include "protocol_examples_common.h"
#include "nvs_flash.h"
#include "esp_err.h"
#include "esp_event.h"


void app_main(void)
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());

    //xTaskCreate(&https_request_task, "https_get_task", 8192, NULL, 5, NULL);
    dweet_send("jbdhsuk", "hello", "world");
}
