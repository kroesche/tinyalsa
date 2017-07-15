/* hw-params.h
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

#ifndef TINYALSA_HW_PARAMS_H
#define TINYALSA_HW_PARAMS_H

enum pcm_format;

enum pcm_param;

struct pcm_params;

struct snd_pcm_hw_params;

void snd_pcm_hw_params_init(struct snd_pcm_hw_params *p);

void param_set_mask(struct snd_pcm_hw_params *p, int n, unsigned int bit);

void param_set_min(struct snd_pcm_hw_params *p, int n, unsigned int val);

unsigned int param_get_min(const struct snd_pcm_hw_params *p, int n);

unsigned int param_get_max(const struct snd_pcm_hw_params *p, int n);

void param_set_int(struct snd_pcm_hw_params *p, int n, unsigned int val);

unsigned int param_get_int(struct snd_pcm_hw_params *p, int n);

unsigned int pcm_format_to_alsa(enum pcm_format format);


struct pcm_params *pcm_params_get(unsigned int card, unsigned int device,
                                  unsigned int flags);

void pcm_params_free(struct pcm_params *pcm_params);

int pcm_param_to_alsa(enum pcm_param param);

const struct pcm_mask *pcm_params_get_mask(const struct pcm_params *pcm_params,
                                     enum pcm_param param);

unsigned int pcm_params_get_min(const struct pcm_params *pcm_params,
                                enum pcm_param param);

unsigned int pcm_params_get_max(const struct pcm_params *pcm_params,
                                enum pcm_param param);

#endif

