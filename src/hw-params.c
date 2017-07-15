/* hw-params.c
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

#include "hw-params.h"

#include <tinyalsa/pcm.h>
#include <tinyalsa/pcm-format.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <sound/asound.h>
#include <sys/ioctl.h>
#include <unistd.h>

int param_is_mask(int p)
{
    return (p >= SNDRV_PCM_HW_PARAM_FIRST_MASK) &&
        (p <= SNDRV_PCM_HW_PARAM_LAST_MASK);
}

int param_is_interval(int p)
{
    return (p >= SNDRV_PCM_HW_PARAM_FIRST_INTERVAL) &&
        (p <= SNDRV_PCM_HW_PARAM_LAST_INTERVAL);
}

const struct snd_interval *param_get_interval(const struct snd_pcm_hw_params *p, int n)
{
    return &(p->intervals[n - SNDRV_PCM_HW_PARAM_FIRST_INTERVAL]);
}

struct snd_interval *param_to_interval(struct snd_pcm_hw_params *p, int n)
{
    return &(p->intervals[n - SNDRV_PCM_HW_PARAM_FIRST_INTERVAL]);
}

struct snd_mask *param_to_mask(struct snd_pcm_hw_params *p, int n)
{
    return &(p->masks[n - SNDRV_PCM_HW_PARAM_FIRST_MASK]);
}

void param_set_mask(struct snd_pcm_hw_params *p, int n, unsigned int bit)
{
    if (bit >= SNDRV_MASK_MAX)
        return;
    if (param_is_mask(n)) {
        struct snd_mask *m = param_to_mask(p, n);
        m->bits[0] = 0;
        m->bits[1] = 0;
        m->bits[bit >> 5] |= (1 << (bit & 31));
    }
}

void param_set_min(struct snd_pcm_hw_params *p, int n, unsigned int val)
{
    if (param_is_interval(n)) {
        struct snd_interval *i = param_to_interval(p, n);
        i->min = val;
    }
}

unsigned int param_get_min(const struct snd_pcm_hw_params *p, int n)
{
    if (param_is_interval(n)) {
        const struct snd_interval *i = param_get_interval(p, n);
        return i->min;
    }
    return 0;
}

unsigned int param_get_max(const struct snd_pcm_hw_params *p, int n)
{
    if (param_is_interval(n)) {
        const struct snd_interval *i = param_get_interval(p, n);
        return i->max;
    }
    return 0;
}

void param_set_int(struct snd_pcm_hw_params *p, int n, unsigned int val)
{
    if (param_is_interval(n)) {
        struct snd_interval *i = param_to_interval(p, n);
        i->min = val;
        i->max = val;
        i->integer = 1;
    }
}

unsigned int param_get_int(struct snd_pcm_hw_params *p, int n)
{
    if (param_is_interval(n)) {
        struct snd_interval *i = param_to_interval(p, n);
        if (i->integer)
            return i->max;
    }
    return 0;
}

void snd_pcm_hw_params_init(struct snd_pcm_hw_params *p)
{
    int n;

    memset(p, 0, sizeof(*p));
    for (n = SNDRV_PCM_HW_PARAM_FIRST_MASK;
         n <= SNDRV_PCM_HW_PARAM_LAST_MASK; n++) {
            struct snd_mask *m = param_to_mask(p, n);
            m->bits[0] = ~0;
            m->bits[1] = ~0;
    }
    for (n = SNDRV_PCM_HW_PARAM_FIRST_INTERVAL;
         n <= SNDRV_PCM_HW_PARAM_LAST_INTERVAL; n++) {
            struct snd_interval *i = param_to_interval(p, n);
            i->min = 0;
            i->max = ~0;
    }
    p->rmask = ~0U;
    p->cmask = 0;
    p->info = ~0U;
}

unsigned int pcm_format_to_alsa(enum pcm_format format)
{
    switch (format) {

    case PCM_FORMAT_S8:
        return SNDRV_PCM_FORMAT_S8;

    default:
    case PCM_FORMAT_S16_LE:
        return SNDRV_PCM_FORMAT_S16_LE;
    case PCM_FORMAT_S16_BE:
        return SNDRV_PCM_FORMAT_S16_BE;

    case PCM_FORMAT_S24_LE:
        return SNDRV_PCM_FORMAT_S24_LE;
    case PCM_FORMAT_S24_BE:
        return SNDRV_PCM_FORMAT_S24_BE;

    case PCM_FORMAT_S24_3LE:
        return SNDRV_PCM_FORMAT_S24_3LE;
    case PCM_FORMAT_S24_3BE:
        return SNDRV_PCM_FORMAT_S24_3BE;

    case PCM_FORMAT_S32_LE:
        return SNDRV_PCM_FORMAT_S32_LE;
    case PCM_FORMAT_S32_BE:
        return SNDRV_PCM_FORMAT_S32_BE;
    };
}

/** Gets the hardware parameters of a PCM, without created a PCM handle.
 * @param card The card of the PCM.
 *  The default card is zero.
 * @param device The device of the PCM.
 *  The default device is zero.
 * @param flags Specifies whether the PCM is an input or output.
 *  May be one of the following:
 *   - @ref PCM_IN
 *   - @ref PCM_OUT
 * @return On success, the hardware parameters of the PCM; on failure, NULL.
 * @ingroup libtinyalsa-pcm
 */
struct pcm_params *pcm_params_get(unsigned int card, unsigned int device,
                                  unsigned int flags)
{
    struct snd_pcm_hw_params *params;
    char fn[256];
    int fd;

    snprintf(fn, sizeof(fn), "/dev/snd/pcmC%uD%u%c", card, device,
             flags & PCM_IN ? 'c' : 'p');

    fd = open(fn, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "cannot open device '%s'\n", fn);
        goto err_open;
    }

    params = calloc(1, sizeof(struct snd_pcm_hw_params));
    if (!params)
        goto err_calloc;

    snd_pcm_hw_params_init(params);
    if (ioctl(fd, SNDRV_PCM_IOCTL_HW_REFINE, params)) {
        fprintf(stderr, "SNDRV_PCM_IOCTL_HW_REFINE error (%d)\n", errno);
        goto err_hw_refine;
    }

    close(fd);

    return (struct pcm_params *)params;

err_hw_refine:
    free(params);
err_calloc:
    close(fd);
err_open:
    return NULL;
}

/** Frees the hardware parameters returned by @ref pcm_params_get.
 * @param pcm_params Hardware parameters of a PCM.
 *  May be NULL.
 * @ingroup libtinyalsa-pcm
 */
void pcm_params_free(struct pcm_params *pcm_params)
{
    struct snd_pcm_hw_params *params = (struct snd_pcm_hw_params *)pcm_params;

    if (params)
        free(params);
}

int pcm_param_to_alsa(enum pcm_param param)
{
    switch (param) {
    case PCM_PARAM_ACCESS:
        return SNDRV_PCM_HW_PARAM_ACCESS;
    case PCM_PARAM_FORMAT:
        return SNDRV_PCM_HW_PARAM_FORMAT;
    case PCM_PARAM_SUBFORMAT:
        return SNDRV_PCM_HW_PARAM_SUBFORMAT;
    case PCM_PARAM_SAMPLE_BITS:
        return SNDRV_PCM_HW_PARAM_SAMPLE_BITS;
    case PCM_PARAM_FRAME_BITS:
        return SNDRV_PCM_HW_PARAM_FRAME_BITS;
    case PCM_PARAM_CHANNELS:
        return SNDRV_PCM_HW_PARAM_CHANNELS;
    case PCM_PARAM_RATE:
        return SNDRV_PCM_HW_PARAM_RATE;
    case PCM_PARAM_PERIOD_TIME:
        return SNDRV_PCM_HW_PARAM_PERIOD_TIME;
    case PCM_PARAM_PERIOD_SIZE:
        return SNDRV_PCM_HW_PARAM_PERIOD_SIZE;
    case PCM_PARAM_PERIOD_BYTES:
        return SNDRV_PCM_HW_PARAM_PERIOD_BYTES;
    case PCM_PARAM_PERIODS:
        return SNDRV_PCM_HW_PARAM_PERIODS;
    case PCM_PARAM_BUFFER_TIME:
        return SNDRV_PCM_HW_PARAM_BUFFER_TIME;
    case PCM_PARAM_BUFFER_SIZE:
        return SNDRV_PCM_HW_PARAM_BUFFER_SIZE;
    case PCM_PARAM_BUFFER_BYTES:
        return SNDRV_PCM_HW_PARAM_BUFFER_BYTES;
    case PCM_PARAM_TICK_TIME:
        return SNDRV_PCM_HW_PARAM_TICK_TIME;
    default:
        return -1;
    }
}

/** Gets a mask from a PCM's hardware parameters.
 * @param pcm_params A PCM's hardware parameters.
 * @param param The parameter to get.
 * @return If @p pcm_params is NULL or @p param is not a mask, NULL is returned.
 *  Otherwise, the mask associated with @p param is returned.
 * @ingroup libtinyalsa-pcm
 */
const struct pcm_mask *pcm_params_get_mask(const struct pcm_params *pcm_params,
                                     enum pcm_param param)
{
    int p;
    struct snd_pcm_hw_params *params = (struct snd_pcm_hw_params *)pcm_params;
    if (params == NULL) {
        return NULL;
    }

    p = pcm_param_to_alsa(param);
    if (p < 0 || !param_is_mask(p)) {
        return NULL;
    }

    return (const struct pcm_mask *)param_to_mask(params, p);
}

/** Get the minimum of a specified PCM parameter.
 * @param pcm_params A PCM parameters structure.
 * @param param The specified parameter to get the minimum of.
 * @returns On success, the parameter minimum.
 *  On failure, zero.
 */
unsigned int pcm_params_get_min(const struct pcm_params *pcm_params,
                                enum pcm_param param)
{
    struct snd_pcm_hw_params *params = (struct snd_pcm_hw_params *)pcm_params;
    int p;

    if (!params)
        return 0;

    p = pcm_param_to_alsa(param);
    if (p < 0)
        return 0;

    return param_get_min(params, p);
}

/** Get the maximum of a specified PCM parameter.
 * @param pcm_params A PCM parameters structure.
 * @param param The specified parameter to get the maximum of.
 * @returns On success, the parameter maximum.
 *  On failure, zero.
 */
unsigned int pcm_params_get_max(const struct pcm_params *pcm_params,
                                enum pcm_param param)
{
    const struct snd_pcm_hw_params *params = (const struct snd_pcm_hw_params *)pcm_params;
    int p;

    if (!params)
        return 0;

    p = pcm_param_to_alsa(param);
    if (p < 0)
        return 0;

    return param_get_max(params, p);
}

