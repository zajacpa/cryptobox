/*
This file is part of BitPunch
Copyright (C) 2015 Frantisek Uhrecky <frantisek.uhrecky[what here]gmail.com>

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
#include "aes.h"

/*#ifdef BPU_CONF_AES


#include "mbedtls/config.h"
#include "mbedtls/platform.h"*/

#include <bitpunch/debugio.h>
#include <bitpunch/math/gf2.h>


int BPU_gf2VecAesEncandTag(BPU_T_GF2_Vector *out, const BPU_T_GF2_Vector *in,BPU_T_GF2_Vector *tag,  BPU_T_GF2_Vector *key,  BPU_T_GF2_Vector *iv){
    //TODO: PADDING + CHECKS
   BPU_T_GF2_Vector *add = NULL;
   BPU_gf2VecMalloc(&add,1);
    //uint8_t output[out->len/8];
    uint8_t *output = (uint8_t*) malloc (out->len);
    uint8_t tagg[tag->len/8];
    if (in->len % 16 && in->len < 128) {
            fprintf(stderr, "input vector len %d, should be divisible by 16", in->len);
            BPU_gf2VecFree(&add);
            return 1;
    }
    mbedtls_gcm_context gcm_ctx;
    mbedtls_gcm_init(&gcm_ctx);

    if(mbedtls_gcm_setkey(&gcm_ctx, MBEDTLS_CIPHER_ID_AES, (uint8_t *) key->elements, 256) != 0){
        BPU_gf2VecFree(&add);
        mbedtls_gcm_free(&gcm_ctx);
        return 1;
    }

    //mbedtls_aes_crypt_cbc(&enc_ctx, MBEDTLS_AES_ENCRYPT, in->len / (BITS_PER_BYTE), (uint8_t *) iv->elements,(uint8_t *) in->elements, output);
    if(mbedtls_gcm_crypt_and_tag(&gcm_ctx, MBEDTLS_GCM_ENCRYPT, in->len / (BITS_PER_BYTE), (uint8_t *) iv->elements, iv->len / (BITS_PER_BYTE), (uint8_t *) add->elements, 1, (uint8_t *) in->elements, output, tag->len / (BITS_PER_BYTE), tagg) != 0){
        BPU_gf2VecFree(&add);
        mbedtls_gcm_free(&gcm_ctx);
        return 1;
    }
    memcpy(out->elements, output, out->len / 8);
    memcpy(tag->elements, tagg, tag->len / 8);
    BPU_gf2VecFree(&add);
    mbedtls_gcm_free(&gcm_ctx);

    return 0;
}

int BPU_gf2VecAesDecandTag(BPU_T_GF2_Vector *out,  const BPU_T_GF2_Vector *in,BPU_T_GF2_Vector *tag, BPU_T_GF2_Vector *key,  BPU_T_GF2_Vector *iv){
    BPU_T_GF2_Vector *add = NULL;
    BPU_gf2VecMalloc(&add,1);
    int err = 0;
    //uint8_t output[out->len/8];
    uint8_t *output = (uint8_t*) malloc (out->len);
    if (in->len % 16) {
            BPU_printWarning("input vector len %d, should be divisible by 16", in->len);
    }
    mbedtls_gcm_context dec_ctx;
    //BPU_printGf2Vec(in);
    mbedtls_gcm_init(&dec_ctx);
    if(mbedtls_gcm_setkey(&dec_ctx, MBEDTLS_CIPHER_ID_AES, (uint8_t *) key->elements, 256) != 0) {
        BPU_gf2VecFree(&add);
        mbedtls_gcm_free(&dec_ctx);
        return 1;
    }

    err = mbedtls_gcm_auth_decrypt(&dec_ctx,in->len / (BITS_PER_BYTE), (uint8_t *) iv->elements, iv->len / (BITS_PER_BYTE), (uint8_t *) add->elements, 1, (uint8_t *) tag->elements,  tag->len / (BITS_PER_BYTE), (uint8_t *) in->elements, output);
    if(err != 0){
        BPU_printError("Could not decrypt\n");
        BPU_printError("The error code is %d\n", err);
        mbedtls_gcm_free(&dec_ctx);
        BPU_gf2VecFree(&add);
        return 1;
    }

    memcpy(out->elements, output, out->len / 8);
    mbedtls_gcm_free(&dec_ctx);
    BPU_gf2VecFree(&add);
    return 0;
}


//#endif
