cmake_minimum_required(VERSION 3.2)

project (tcg)

option(BIG_ENDIAN "Big endian" OFF)

# Determine bitness
# 32 or 64 bits
set (HOST_BITS 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set (HOST_BITS 64)
endif()

set (HOST "i386" CACHE STRING "Host architecture")
set_property (CACHE HOST PROPERTY STRINGS i386 arm)

string (TOUPPER ${HOST} HOST_UPPER)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fomit-frame-pointer")
if(${HOST_BITS} EQUAL 64)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif()

if(BIG_ENDIAN)
    add_definitions (-DTARGET_WORDS_BIGENDIAN)
endif()

add_definitions (
    -DTCG_STANDALONE
    -DCONFIG_NEED_MMU
    -DCONFIG_SOFTMMU
    -DNEED_CPU_H
    -DNDEBUG
    -DTCG_TARGET_${HOST_UPPER}
    -DHOST_BITS_${HOST_BITS})

include_directories (${HOST})

add_library (tcg STATIC
    additional.c
    optimize.c
    tcg.c)

