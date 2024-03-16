import os, sys
#sys.path.append("/home/kafka/tenstorrent/tt-metal/dist/zz")
os.environ['TT_METAL_HOME'] = '/home/kafka/tenstorrent/tt-metal'

import tt_lib as ttl
print(ttl.device.GetNumPCIeDevices())
device = ttl.device.CreateDevice(0)
ttl.device.SetDefaultDevice(device)

import torch
torch_random_tensor = torch.rand(32, 32, dtype=torch.bfloat16).reshape(1, 1, 32, 32)

tt_tensor = ttl.tensor.Tensor(torch_random_tensor, ttl.tensor.DataType.BFLOAT16)
tt_tensor = tt_tensor.to(ttl.tensor.Layout.TILE)
