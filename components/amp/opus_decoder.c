#include <stdlib.h>

#include "opus.h"

#include "amp/opus_decoder.h"

esp_err_t amp_opus_decoder_init() {
  int dec_size = opus_decoder_get_size(1);
  OpusDecoder *dec = malloc(dec_size);

  opus_decoder_init(dec, 16000, 1);
  return ESP_OK;
}
