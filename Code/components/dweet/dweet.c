#include <string.h>
#include <stdlib.h>

#include "esp_log.h"

#include "esp_tls.h"
#include "esp_crt_bundle.h"

static const char *TAG = "dweet";

static void https_get_request(esp_tls_cfg_t cfg, char *url, char *host);


void dweet_send(char *thing, char *key, char *value)
{
    esp_tls_cfg_t cfg = {
        .crt_bundle_attach = esp_crt_bundle_attach,
    };
    char url[256];

    (void)sprintf(url, "https://dweet.io/dweet/for/%s?%s=%s", thing, key, value);
    https_get_request(cfg, url, "dweet.io");
}


static void https_get_request(esp_tls_cfg_t cfg, char *url, char *host)
{
    char buf[512];
    int ret, len;

    len = sprintf(buf, "GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: esp-idf/1.0 esp32\r\n\r\n", url, host);

    struct esp_tls *tls = esp_tls_conn_http_new(url, &cfg);

    if (tls != NULL) 
    {
        ESP_LOGI(TAG, "Connection established...");
        size_t written_bytes = 0;
    do {
        ret = esp_tls_conn_write(tls,
                                 buf + written_bytes,
                                 len - written_bytes);
        if (ret >= 0) {
            ESP_LOGI(TAG, "%d bytes written", ret);
            written_bytes += ret;
        } else if (ret != ESP_TLS_ERR_SSL_WANT_READ  && ret != ESP_TLS_ERR_SSL_WANT_WRITE) {
            ESP_LOGE(TAG, "esp_tls_conn_write  returned: [0x%02X](%s)", ret, esp_err_to_name(ret));
            break;
        }
    } while (written_bytes < len);
    } 
    else 
    {
        ESP_LOGE(TAG, "Connection failed...");
    }

    esp_tls_conn_delete(tls);
    ESP_LOGI(TAG, "Connection closed.");
}