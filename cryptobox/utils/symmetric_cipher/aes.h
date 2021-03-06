/*
This file is part of BitPunch
Copyright (C) 2015 Frantisek Uhrecky <frantisek.uhrecky[what here]gmail.com>>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*#ifndef AES_H
#define AES_H

#include <bitpunch/config.h>*/
#include "mbedtls/aes.h"
#include "mbedtls/gcm.h"
//#include <mbedtls/aes.h>
//#include <mbedtls/gcm.h>


//#ifdef BPU_CONF_AES
#include <stdint.h>
#define AES_BLOCK_SIZE 16
#define BITS_PER_BYTE 8

#include <bitpunch/math/gf2types.h>

/**
 * The function encrypts a message and provides auth tag.
 * @param  out[out] an output vector
 * @param  in[in]  an input
 * @param  tag[out] an auth tag
 * @param  iv[in] an initialization vector
 * @return                0 on succes else, non-zero value
 */
int BPU_gf2VecAesEncandTag(BPU_T_GF2_Vector *out,const BPU_T_GF2_Vector *in, BPU_T_GF2_Vector *tag, BPU_T_GF2_Vector *key,  BPU_T_GF2_Vector *iv);

/**
 * The function decrypts a message and provides auth tag.
 * @param  out[out] an output vector
 * @param  in[in]  an input
 * @param  tag[in] an auth tag
 * @param  iv[in] an initialization vector
 * @return                0 on succes else, non-zero value
 */
int BPU_gf2VecAesDecandTag(BPU_T_GF2_Vector *out,const BPU_T_GF2_Vector *in, BPU_T_GF2_Vector *tag, BPU_T_GF2_Vector *key,  BPU_T_GF2_Vector *iv);

//#endif // BPU_CONF_AES

//#endif // AES_H

