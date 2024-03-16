#include <cstdint>
#include "debug/dprint.h"  // required in all kernels using DPRINT

void kernel_main() {
  DPRINT << "printing from kernel" << ENDL();
  std::uint32_t l1 = get_arg_val<uint32_t>(0);
  std::uint32_t src0_dram = get_arg_val<uint32_t>(1);
  std::uint32_t src1_dram = get_arg_val<uint32_t>(2);
  std::uint32_t dst_dram = get_arg_val<uint32_t>(3);

  std::uint64_t src0_dram_noc = get_noc_addr(1, 0, src0_dram);
  std::uint64_t src1_dram_noc = get_noc_addr(1, 0, src1_dram);
  std::uint64_t dst_dram_noc = get_noc_addr(1, 0, dst_dram);

  DPRINT << "addrs  " << HEX() << src0_dram << "  " << src0_dram_noc << " l1 " << l1 << ENDL();

  noc_async_read(src0_dram_noc, l1, 0x1000);
  noc_async_read_barrier();
  noc_async_read(src1_dram_noc, l1+0x1000, 0x1000);
  noc_async_read_barrier();

  noc_async_write(l1, dst_dram_noc, 0x1000);
  noc_async_write_barrier();
}
