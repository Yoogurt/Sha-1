/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sha.cpp
 * Author: root
 *
 * Created on 2017年7月3日, 上午10:36
 */

#include "sha.hpp"
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

u64 fill_bit(u8*& string, u64 length) {

    u64 total_length = ((length >> 6) + 1) << 6;

    u8* newstring = reinterpret_cast<u8*> (malloc(total_length));

    for (int i = 0; i < length; i++)
        *(newstring + i) = *(string + i); //array copy

    *(newstring + length) |= 0x80;

    u8* end = newstring + total_length - 1;
    
      length <<= 3;  //bit

    while (length > 0) {
        *end = static_cast<u8> (length & 0xff);
        length >>= 8;
        end--;
    }

    string = newstring;
    return total_length << 3;
}

u32 f(u8 index, u32 B, u32 C, u32 D) {

    /*
     ft(B,C,D) = (B AND C) OR ((NOT B) AND D)                       ( 0 <= t <= 19)
    ft(B,C,D) = B XOR C XOR D                                   (20 <= t <= 39)
    ft(B,C,D) = (B AND C) OR (B AND D) OR (C AND D) (40 <= t <= 59)
    ft(B,C,D) = B XOR C XOR D                                   (60 <= t <= 79). 
     */

    if (index >= 0 && index <= 19)
        return (B & C) | ((~B) & D);
    else if (index >= 20 && index <= 39)
        return B ^ C ^ D;
    else if (index >= 40 && index <= 59)
        return (B & C) | (B & D) | (C & D);
    else if (index >= 60 && index <= 79)
        return B ^ C ^ D;
    else{
        abort();
        return 0;
    }

}

u32 S(u32 n, u32 X) {
    return (X << n) | (X >> 32 - n);
}

u64 K(u32 t) {
    if (t >= 0 && t <= 19)
        return 0x5A827999;
    else if (t >= 20 && t <= 39)
        return 0x6ED9EBA1;
    else if (t >= 40 && t <= 59)
        return 0x8F1BBCDC;
    else if (t >= 60 && t <= 79)
        return 0xCA62C1D6;
}

u32 u8_to_u32(u8* buffer, u32 offset) {

    u32 result = 0;
    for (u32 i = 0; i < 4; i++) {
        result <<= 8;
        result += *(buffer + offset + i);
    }
    return result;
}
