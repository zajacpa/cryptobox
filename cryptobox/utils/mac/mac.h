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
#ifndef MAC_H
#define MAC_H

#include <bitpunch/config.h>

#ifdef BPU_CONF_MAC
#include <stdint.h>

#include <bitpunch/math/gf2types.h>

int BPU_gf2VecComputeHMAC(BPU_T_GF2_Vector *out, const BPU_T_GF2_Vector *in, const BPU_T_GF2_Vector *key);

#endif // BPU_CONF_MAC

#endif // MAC_H

