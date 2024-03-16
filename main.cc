#include "tt_metal/host_api.hpp"
using namespace tt;
using namespace tt::tt_metal;

int main(int argc, char **argv) {
  Device *device = CreateDevice(0);
  CommandQueue& cq = device->command_queue();

  const int N = 1024;

  // allocate L1
  tt::tt_metal::InterleavedBufferConfig l1_config{
    .device=device,
    .size=0x2000,  // actually *120
    .page_size=0x2000,
    .buffer_type = tt_metal::BufferType::L1
  };
  std::shared_ptr<tt::tt_metal::Buffer> l1_buffer = CreateBuffer(l1_config);

  // allocate dram
  tt_metal::InterleavedBufferConfig dram_config{
    .device=device,
    //.size=N*N*2,
    .size=0x1000,
    .page_size=0x1000,
    //.page_size=N*N*2,
    .buffer_type = tt_metal::BufferType::DRAM
  };
  std::shared_ptr<tt::tt_metal::Buffer> src0_dram_buffer = CreateBuffer(dram_config);
  std::shared_ptr<tt::tt_metal::Buffer> src1_dram_buffer = CreateBuffer(dram_config);
  std::shared_ptr<tt::tt_metal::Buffer> dst_dram_buffer = CreateBuffer(dram_config);

  printf("0x%x 0x%x 0x%x\n", src0_dram_buffer->address(), src1_dram_buffer->address(), dst_dram_buffer->address());
  printf("%lu %lu\n", src0_dram_buffer->noc_coordinates().x, src0_dram_buffer->noc_coordinates().y);
  printf("%lu %lu\n", src1_dram_buffer->noc_coordinates().x, src1_dram_buffer->noc_coordinates().y);
  printf("%lu %lu\n", dst_dram_buffer->noc_coordinates().x, dst_dram_buffer->noc_coordinates().y);

  {
    std::vector<uint32_t> input_vec;
    for (int i = 0; i < 0x400; i++) input_vec.push_back(13);
    EnqueueWriteBuffer(cq, src0_dram_buffer, input_vec, false);
  }

  {
    std::vector<uint32_t> input_vec;
    for (int i = 0; i < 0x400; i++) input_vec.push_back(7);
    EnqueueWriteBuffer(cq, src1_dram_buffer, input_vec, false);
  }


  // build kernel
  Program program = CreateProgram();
  CoreRange core({0, 0}, {0, 0});
  KernelHandle kernel_id = CreateKernel(program, "../tt-twitch/kernel.cpp", core,
    DataMovementConfig{.processor = DataMovementProcessor::RISCV_0, .noc = NOC::RISCV_0_default});

  const std::vector<uint32_t> runtime_args = {
    l1_buffer->address(),
    src0_dram_buffer->address(),
    src1_dram_buffer->address(),
    dst_dram_buffer->address(),
  };

  SetRuntimeArgs(program, kernel_id, core, runtime_args);

  // run kernel
  EnqueueProgram(cq, program, false);
  Finish(cq);

  // read output
  std::vector<uint32_t> result_vec;
  EnqueueReadBuffer(cq, dst_dram_buffer, result_vec, true);
  printf("result: %d\n", result_vec[0]);

  assert(CloseDevice(device));
}
