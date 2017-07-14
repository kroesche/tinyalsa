/* pcm-format.c
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

#include <tinyalsa/pcm-format.h>

/** Determines the number of bits occupied by a @ref pcm_format.
 * @param format A PCM format.
 * @return The number of bits associated with @p format
 * @ingroup libtinyalsa-pcm
 */
unsigned int pcm_format_to_bits(enum pcm_format format)
{
    switch (format) {
    case PCM_FORMAT_S32_LE:
    case PCM_FORMAT_S32_BE:
    case PCM_FORMAT_S24_LE:
    case PCM_FORMAT_S24_BE:
        return 32;
    case PCM_FORMAT_S24_3LE:
    case PCM_FORMAT_S24_3BE:
        return 24;
    default:
    case PCM_FORMAT_S16_LE:
    case PCM_FORMAT_S16_BE:
        return 16;
    case PCM_FORMAT_S8:
        return 8;
    };
}

