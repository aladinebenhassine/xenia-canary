#ifndef XENIA_BASE_X64_FEATURES_H_
#define XENIA_BASE_X64_FEATURES_H_

#include <cstdint>
#include <xbyak/xbyak_util.h>

namespace xe {
namespace amd64 {

enum FeatureFlags {
  kX64EmitAVX2 = 1 << 0,
  kX64EmitFMA = 1 << 1,
  kX64EmitLZCNT = 1 << 2,
  kX64EmitBMI1 = 1 << 3,
  kX64EmitBMI2 = 1 << 4,
  kX64EmitMovbe = 1 << 5,
  kX64EmitGFNI = 1 << 6,
  kX64EmitAVX512F = 1 << 7,
  kX64EmitAVX512VL = 1 << 8,
  kX64EmitAVX512BW = 1 << 9,
  kX64EmitAVX512DQ = 1 << 10,
  kX64EmitAVX512VBMI = 1 << 11,
  kX64EmitPrefetchW = 1 << 12,
  kX64EmitFMA4 = 1 << 13,
  kX64EmitTBM = 1 << 14,
  kX64EmitXOP = 1 << 15,
  kX64FastJrcx = 1 << 16,
  kX64FastLoop = 1 << 17,
  kX64FlagsIndependentVars = 1 << 18,
  kX64EmitMovdir64M = 1 << 19,
  kX64FastRepMovs = 1 << 20,
  // Add other feature flags as needed
};

inline uint64_t GetFeatureFlags() {
  uint64_t flags = 0;
  Xbyak::util::Cpu cpu;

  if (cpu.has(Xbyak::util::Cpu::tAVX2)) {
    flags |= kX64EmitAVX2;
  }
  if (cpu.has(Xbyak::util::Cpu::tFMA)) {
    flags |= kX64EmitFMA;
  }
  if (cpu.has(Xbyak::util::Cpu::tLZCNT)) {
    flags |= kX64EmitLZCNT;
  }
  if (cpu.has(Xbyak::util::Cpu::tBMI1)) {
    flags |= kX64EmitBMI1;
  }
  if (cpu.has(Xbyak::util::Cpu::tBMI2)) {
    flags |= kX64EmitBMI2;
  }
  if (cpu.has(Xbyak::util::Cpu::tMOVBE)) {
    flags |= kX64EmitMovbe;
  }
  if (cpu.has(Xbyak::util::Cpu::tGFNI)) {
    flags |= kX64EmitGFNI;
  }
  if (cpu.has(Xbyak::util::Cpu::tAVX512F)) {
    flags |= kX64EmitAVX512F;
  }
  if (cpu.has(Xbyak::util::Cpu::tAVX512VL)) {
    flags |= kX64EmitAVX512VL;
  }
  if (cpu.has(Xbyak::util::Cpu::tAVX512BW)) {
    flags |= kX64EmitAVX512BW;
  }
  if (cpu.has(Xbyak::util::Cpu::tAVX512DQ)) {
    flags |= kX64EmitAVX512DQ;
  }
  if (cpu.has(Xbyak::util::Cpu::tAVX512VBMI)) {
    flags |= kX64EmitAVX512VBMI;
  }
  if (cpu.has(Xbyak::util::Cpu::tPREFETCHW)) {
    flags |= kX64EmitPrefetchW;
  }
  // Add checks for other features as needed

  return flags;
}

}  // namespace amd64
}  // namespace xe

#endif  // XENIA_BASE_X64_FEATURES_H_
