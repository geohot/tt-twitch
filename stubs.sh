#!/bin/bash
clang2py $TT_METAL_HOME/tt_metal/host_api.hpp --clang-args="-std=c++20 -I$TT_METAL_HOME -I$TT_METAL_HOME/tt_metal -I$TT_METAL_HOME/tt_metal/third_party/fmt \
  -I$TT_METAL_HOME/tt_metal/hw/inc/grayskull -I$TT_METAL_HOME/tt_metal/third_party/umd -I$TT_METAL_HOME/tt_metal/third_party/umd/src/firmware/riscv/grayskull \
  -I$TT_METAL_HOME/tt_metal/hw/inc"
