#include "esp_log.h"

#include "amp/opus_decoder.h"

static const char *TAG = "app";

void app_main() {
  amp_opus_decoder_cfg_t cfg = {
      .channel = 1,
      .rate = AMP_OPUS_DEC_SAMPLE_RATE_8,
  };
  amp_opus_decoer_handle_t dec;
  amp_opus_decoder_init(&cfg, &dec);
  ESP_LOGI(TAG, "hello");
}
