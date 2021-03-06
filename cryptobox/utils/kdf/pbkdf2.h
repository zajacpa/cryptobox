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
//#ifndef KDF_H
//#define KDF_H

//#include <bitpunch/config.h>

#include <stdint.h>

#include <bitpunch/math/gf2types.h>

#define BPU_HASH_LEN 64


/**
 * The function derives a pseudorandom output from given inputs.
 * @param  out[out] an output vector
 * @param  pwd[in]  a password
 * @param  salt[in] a salt
 * @param  keylen[in] a size of the output
 * @return                0 on succes else, non-zero value
 */
int BPU_gf2VecKDF(BPU_T_GF2_Vector *out, const BPU_T_GF2_Vector *pwd,const BPU_T_GF2_Vector *salt, int keylen);


//#endif // KDF_H

