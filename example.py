from typing import Any
import os

TT_METAL_HOME = os.getenv("TT_METAL_HOME")
def compile(src_data_in:str, src_data_out:str, src_compute:str, circular_buffer_options, compute_config):
  pass

# allocate in DRAM
def alloc(sz:int):
  pass

# DRAM <- host
def copyin(dest:Any, src:memoryview):
  pass

# host <- DRAM
def copyout(dest:memoryview, src:Any):
  pass

