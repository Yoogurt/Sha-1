/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Yoogurt
 *
 * Created on 2017年7月3日, 上午10:09
 */

#include <iostream>
#include "sha.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<fcntl.h>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv) {

    string input;
    cout<<"enter sha1 string :"<<endl;
    cin>>input;

    u8* degital_message = reinterpret_cast<u8*> (const_cast<char*> (input.c_str()));
    u64 ascii_length = input.size();

    u64 bit_length = fill_bit(degital_message, ascii_length);

    u32* buffer_1 = reinterpret_cast<u32*> (malloc(sizeof (u32) * 5));
    u32* H = reinterpret_cast<u32*> (malloc(sizeof (u32) * 5));
    u32* W = reinterpret_cast<u32*> (malloc(sizeof (u32) * 80));
    u32 TEMP;

    u32 A, B, C, D, E;

    H[0] = 0x67452301;
    H[1] = 0xEFCDAB89;
    H[2] = 0x98BADCFE;
    H[3] = 0x10325476;
    H[4] = 0xC3D2E1F0;

    for (u32 i = 0; i < bit_length; i += 512) {  // block 

        for (u32 j = 0; j < 16; j++)
            W[j] = u8_to_u32(degital_message, i + (j << 2));


        for (u32 j = 16; j < 80; j++) // W[i] = S1(W[i-3] XOR W[i-8] XOR W[i- 14] XOR W[i-16])
            W[j] = S(1, W[j - 3] ^ W[j - 8] ^ W[j - 14] ^ W[j - 16]);

        A = H[0];
        B = H[1];
        C = H[2];
        D = H[3];
        E = H[4];

        /*
            TEMP = S5(A) + ft(B,C,D) + E + W[i] + K[i]
            E=D
            D=C
            C=S30(B)
            B=A
            A=TEMP
         */
        for (u32 j = 0; j < 80; j++) {
            TEMP = S(5, A) + f(j, B, C, D) + E + W[j] + K(j);
            E = D;
            D = C;
            C = S(30, B);
            B = A;
            A = TEMP;
        }

        H[0] = H[0] + A;
        H[1] = H[1] + B;
        H[2] = H[2] + C;
        H[3] = H[3] + D;
        H[4] = H[4] + E;
    }

    printf("%x%x%x%x%x", H[0], H[1], H[2], H[3], H[4]);

    free(degital_message);
    free(buffer_1);
    free(H);
    free(W);

    return 0;
}

