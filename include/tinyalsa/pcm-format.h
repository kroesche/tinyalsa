/* pcm-format.h
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

#ifndef TINYALSA_PCM_FORMAT_H
#define TINYALSA_PCM_FORMAT_H

#if defined(__cplusplus)
extern "C" {
#endif

/** Audio sample format of a PCM.
 * The first letter specifiers whether the sample is signed or unsigned.
 * The letter 'S' means signed. The letter 'U' means unsigned.
 * The following number is the amount of bits that the sample occupies in memory.
 * Following the underscore, specifiers whether the sample is big endian or little endian.
 * The letters 'LE' mean little endian.
 * The letters 'BE' mean big endian.
 * This enumeration is used in the @ref pcm_config structure.
 * @ingroup libtinyalsa-pcm
 */
enum pcm_format {
    /** Signed, 8-bit */
    PCM_FORMAT_S8 = 1,
    /** Signed 16-bit, little endian */
    PCM_FORMAT_S16_LE = 0,
    /** Signed, 16-bit, big endian */
    PCM_FORMAT_S16_BE = 2,
    /** Signed, 24-bit (32-bit in memory), little endian */
    PCM_FORMAT_S24_LE,
    /** Signed, 24-bit (32-bit in memory), big endian */
    PCM_FORMAT_S24_BE,
    /** Signed, 24-bit, little endian */
    PCM_FORMAT_S24_3LE,
    /** Signed, 24-bit, big endian */
    PCM_FORMAT_S24_3BE,
    /** Signed, 32-bit, little endian */
    PCM_FORMAT_S32_LE,
    /** Signed, 32-bit, big endian */
    PCM_FORMAT_S32_BE,
    /** Max of the enumeration list, not an actual format. */
    PCM_FORMAT_MAX
};

unsigned int pcm_format_to_bits(enum pcm_format format);

#if defined(__cplusplus)
}  /* extern "C" */
#endif

#endif

