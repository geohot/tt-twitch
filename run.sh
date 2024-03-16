#!/bin/bash
TT_METAL_HOME=/home/kafka/tenstorrent/tt-metal
clang++ -std=c++20 main.cc -I$TT_METAL_HOME -I$TT_METAL_HOME/tt_metal -I$TT_METAL_HOME/tt_metal/third_party/fmt \
  -I$TT_METAL_HOME/tt_metal/hw/inc/grayskull -I$TT_METAL_HOME/tt_metal/third_party/umd -I$TT_METAL_HOME/tt_metal/third_party/umd/src/firmware/riscv/grayskull \
  -I$TT_METAL_HOME/tt_metal/hw/inc -L/home/kafka/tenstorrent/tt-metal/build/lib -ltt_metal -lyaml-cpp

