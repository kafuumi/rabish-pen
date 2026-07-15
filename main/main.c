#include "esp_log.h"

#include "amp/opus_decoder.h"

static const char *TAG = "app";

void app_main() {
  amp_opus_decoder_init();
  ESP_LOGI(TAG, "hello");
}
