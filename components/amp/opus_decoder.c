#include <stdlib.h>

#include "opus.h"

#include "amp/opus_decoder.h"
#include "playlist.h"

struct amp_opus_decoder_t {
  amp_playlist_handle_t provider;
  OpusDecoder *dec;
  uint32_t sample_rate;
  uint8_t channel;
};

static void amp_opus_dec_task(void *args) {}

esp_err_t amp_opus_decoder_init(amp_opus_decoder_cfg_t *cfg,
                                amp_opus_decoer_handle_t *dec) {
  int dec_size = opus_decoder_get_size(cfg->channel);
  amp_opus_decoer_handle_t decoder = malloc(sizeof(struct amp_opus_decoder_t));
  if (!decoder) {
    return ESP_ERR_NO_MEM;
  }
  esp_err_t ret = ESP_FAIL;
  OpusDecoder *_dec = malloc(dec_size);
  if (!_dec) {
    ret = ESP_ERR_NO_MEM;
    goto _cleanup;
  }
  if (opus_decoder_init(_dec, cfg->rate, cfg->channel) != OPUS_OK) {
    goto _cleanup;
  }
  opus_decoder_ctl(_dec, OPUS_SET_APPLICATION(OPUS_APPLICATION_VOIP));
  decoder->sample_rate = cfg->rate;
  decoder->channel = cfg->channel;
  decoder->dec = _dec;
  *dec = decoder;
  return ESP_OK;

_cleanup:
  if (_dec) {
    free(_dec);
  }
  return ret;
}

void amp_opus_decoder_deinit(amp_opus_decoer_handle_t dec) {
  if (!dec) {
    return;
  }
  if (dec->dec) {
    opus_decoder_destroy(dec->dec);
  }
  free(dec);
}
