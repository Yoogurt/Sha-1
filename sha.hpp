/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sha.hpp
 * Author: Yoogurt
 *
 * Created on 2017年7月3日, 上午10:16
 */

#ifndef SHA_HPP
#define SHA_HPP

#include<iostream>
#include <stdint.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

u64 fill_bit(u8*&, u64);

u32 f(u8 , u32 , u32 ,u32);

u32 S(u32 , u32);

u64 K(u32);

u32 u8_to_u32(u8* , u32);

#endif /* SHA_HPP */

