#pragma once
#if !defined( __SHA1_H__ )
#define __SHA1_H__

typedef unsigned int uint;

#define one_block_size_bytes    64 
#define one_block_size_uints    16 
#define block_expend_size_uints 80 

#define SHA1HASHLENGTHBYTES 20
#define SHA1HASHLENGTHUINTS 5

typedef uint* Block;
typedef uint  ExpendBlock[ block_expend_size_uints ];

const uint H[ 5 ] = {
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0
};

auto cycle_shift_left( uint val, int bit_count ) -> uint;
auto bring_to_human_view( uint val ) -> uint;

auto sha1( char* message, uint msize_bytes ) -> uint*;

#endif
