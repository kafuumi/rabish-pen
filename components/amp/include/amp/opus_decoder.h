#if !defined(_OPUS_DECODER_H_)
#define _OPUS_DECODER_H_

#include "esp_err.h"

#include "amp/audio_types.h"

typedef struct amp_opus_decoder_t *amp_opus_decoer_handle_t;

enum amp_opus_dec_sample_rate {
  AMP_OPUS_DEC_SAMPLE_RATE_8 = 8000,
  AMP_OPUS_DEC_SAMPLE_RATE_16 = 16000,
};

typedef struct {
  enum amp_opus_dec_sample_rate rate;
  enum amp_audio_channel channel;
} amp_opus_decoder_cfg_t;

esp_err_t amp_opus_decoder_init(amp_opus_decoder_cfg_t *cfg,
                                amp_opus_decoer_handle_t *dec);

#endif // _OPUS_DECODER_H_
