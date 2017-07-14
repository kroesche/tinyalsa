/* pcm.h
**
** Copyright 2011, The Android Open Source Project
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of The Android Open Source Project nor the names of
**       its contributors may be used to endorse or promote products derived
**       from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY The Android Open Source Project ``AS IS'' AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL The Android Open Source Project BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
** CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
** LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
** OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
** DAMAGE.
*/

/** @file */

#ifndef TINYALSA_PCM_H
#define TINYALSA_PCM_H

#if defined(__cplusplus)
extern "C" {
#endif

enum pcm_format;

/** Encapsulates the hardware and software parameters of a PCM.
 * @ingroup libtinyalsa-pcm
 */
struct pcm_config;

struct pcm_config *pcm_config_malloc(void);

void pcm_config_free(struct pcm_config *config);

int pcm_config_get_channels(const struct pcm_config *config, unsigned int *channels);

int pcm_config_get_rate(const struct pcm_config *config, unsigned int *rate);

int pcm_config_get_period_size(const struct pcm_config *config, unsigned int *period_size);

int pcm_config_get_period_count(const struct pcm_config *config, unsigned int *period_count);

int pcm_config_get_format(const struct pcm_config *config, enum pcm_format *format);

int pcm_config_get_start_threshold(const struct pcm_config *config, unsigned int *start_threshold);

int pcm_config_get_stop_threshold(const struct pcm_config *config, unsigned int *stop_threshold);

int pcm_config_get_silence_threshold(const struct pcm_config *config, unsigned int *silence_threshold);

int pcm_config_set_channels(struct pcm_config *config, unsigned int channels);

int pcm_config_set_rate(struct pcm_config *config, unsigned int rate);

int pcm_config_set_period_size(struct pcm_config *config, unsigned int period_size);

int pcm_config_set_period_count(struct pcm_config *config, unsigned int period_count);

int pcm_config_set_format(struct pcm_config *config, enum pcm_format format);

int pcm_config_set_start_threshold(struct pcm_config *config, unsigned int start_threshold);

int pcm_config_set_stop_threshold(struct pcm_config *config, unsigned int stop_threshold);

int pcm_config_set_silence_threshold(struct pcm_config *config, unsigned int silence_threshold);

#if defined(__cplusplus)
}  /* extern "C" */
#endif

#endif

