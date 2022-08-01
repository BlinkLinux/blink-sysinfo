// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "modules/devices/processor_x86.h"

#include <QTextStream>

#include "base/file.h"
#include "base/unit.h"
#include "modules/devices/processor.h"

namespace sysinfo {
namespace devices {

// This function is partly based on x86cpucaps by Osamu Kayasono <jacobi@jcom.home.ne.jp>
QString getProcessorStringFamily(const QString& vendor_id, qint32 family, qint32 model) {
  if (vendor_id == "GenuineIntel") {
    if (family == 4) {
      return "i486 series";
    } else if (family == 5) {
      if (model < 4) {
        return "Pentium Classic";
      } else {
        return "Pentium MMX";
      }
    } else if (family == 6) {
      if (model <= 1) {
        return "Pentium Pro";
      } else if (model < 7) {
        return "Pentium II/Pentium II Xeon/Celeron";
      } else if (model == 9) {
        return "Pentium M";
      } else {
        return "Pentium III/Pentium III Xeon/Celeron/Core Duo/Core Duo 2";
      }
    } else if (family > 6) {
      return "Pentium 4";
    } else {
      return "i386 class";
    }
  } else if (vendor_id == "AuthenticAMD") {
    if (family == 4) {
      if (model <= 9) {
        return "AMD i80486 series";
      } else {
        return "AMD 5x86";
      }
    } else if (family == 5) {
      if (model <= 3) {
        return "AMD K5";
      } else if (model <= 7) {
        return "AMD K6";
      } else if (model == 8) {
        return "AMD K6-2";
      } else if (model == 9) {
        return "AMD K6-III";
      } else {
        return "AMD K6-2+/III+";
      }
    } else if (family == 6) {
      if (model == 1) {
        return "AMD Athlon (K7)";
      } else if (model == 2) {
        return "AMD Athlon (K75)";
      } else if (model == 3) {
        return "AMD Duron (Spitfire)";
      } else if (model == 4) {
        return "AMD Athlon (Thunderbird)";
      } else if (model == 6) {
        return "AMD Athlon XP/MP/4 (Palomino)";
      } else if (model == 7) {
        return "AMD Duron (Morgan)";
      } else if (model == 8) {
        return "AMD Athlon XP/MP (Thoroughbred)";
      } else if (model == 10) {
        return "AMD Athlon XP/MP (Barton)";
      } else {
        return "AMD Athlon (unknown)";
      }
    } else if (family > 6) {
      return "AMD Opteron/Athlon64/FX";
    } else {
      return "AMD i386 class";
    }
  } else if (vendor_id == "CyrixInstead") {
    if (family == 4) {
      return "Cyrix 5x86";
    } else if (family == 5) {
      return "Cyrix M1 (6x86)";
    } else if (family == 6) {
      if (model == 0) {
        return "Cyrix M2 (6x86MX)";
      } else if (model <= 5) {
        return "VIA Cyrix III (M2 core)";
      } else if (model == 6) {
        return "VIA Cyrix III (WinChip C5A)";
      } else if (model == 7) {
        return "VIA Cyrix III (WinChip C5B/C)";
      } else {
        return "VIA Cyrix III (WinChip C5C-T)";
      }
    } else {
      return "Cyrix i386 class";
    }
  } else if (vendor_id == "CentaurHauls") {
    if (family == 5) {
      if (model <= 4) {
        return "Centaur WinChip C6";
      } else if (model <= 8) {
        return "Centaur WinChip 2";
      } else {
        return "Centaur WinChip 2A";
      }
    } else {
      return "Centaur i386 class";
    }
  } else if (vendor_id == "GenuineTMx86") {
    return "Transmeta Crusoe TM3x00/5x00";
  }

  return "";
}

bool getProcessorList(Processors& processors) {
  QString content;
  if (!readTextFile(kProcCpuInfo, content)) {
    return false;
  }

  QTextStream stream(&content);
  QString line;
  Processor processor;
  bool processor_init = false;

  while (stream.readLineInto(&line)) {
    const QStringList parts = line.split(':');
    if (parts.length() != 2) {
      continue;
    }
    const QString name = parts.at(0).trimmed();
    const QString value = parts.at(1).trimmed();

    if (name.startsWith("processor")) {
      // finish previous
      if (processor_init) {
        processor.family_model = getProcessorStringFamily(processor.vendor_id, processor.family_id, processor.model_id);
        processors.append(processor);
      }
      // start next
      processor = Processor{};
      processor.id = value.toInt();
      processor.is_little_endian = isLittleEndian();
      processor_init = true;
      continue;
    }

    if (name == "physical id") {
      processor.physical_id = value.toInt();
    } else if (name == "cpu cores") {
      processor.cpu_cores = value.toInt();
    } else if (name == "core id") {
      processor.core_id = value.toInt();

    } else if (name == "model name") {
      processor.model_name = value;
    } else if (name == "vendor_id") {
      processor.vendor_id = value;
    } else if (name == "flags") {
      const QStringList flags = value.split(' ');
      for (const auto& flag: flags) {
        processor.flags.append(ProcessorFlag{
            .name = flag,
            .description = getFlagDescription(flag),
        });
      }

    } else if (name == "power management") {
      processor.power_management = value;
    } else if (name == "microcode") {
      processor.microcode = value;
    } else if (name == "bugs") {
      const QStringList bugs = value.split(' ');
      for (const auto& bug: bugs) {
        processor.bugs.append(ProcessorBug{
            .name = bug,
            .description = getBugDescription(bug),
        });
      }

    } else if (name == "cache size") {
      processor.cache_size = parseMemSize(value);
    } else if (name == "model") {
      processor.model_id = value.toInt();
    } else if (name == "cpu family") {
      processor.family_id = value.toInt();
    } else if (name == "stepping") {
      processor.stepping = value.toInt();

    } else if (name == "cpu MHz") {
      processor.cpu_mhz = value.toFloat();
    } else if (name == "bogomips") {
      processor.bogomips = value.toFloat();

    } else if (name == "fpu") {
      processor.has_fpu = true;
    }
  }

  processor.family_model = getProcessorStringFamily(processor.vendor_id, processor.family_id, processor.model_id);
  processors.append(processor);

  return true;
}

///sources:
// - https://unix.stackexchange.com/a/43540
// - https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git/tree/arch/x86/include/asm/cpufeatures.h?id=refs/tags/v4.9
// - hardinfo: modules/devices/x86/processor.c
QString getFlagDescription(const QString& name) {
  static const QMap<QString, QString> flags = {
      // Intel-defined CPU features, CPUID level 0x00000001 (edx)
      // See also Wikipedia and table 2-27 in Intel Advanced Vector Extensions Programming Reference
      {"fpu", "Onboard FPU (floating point support)"},
      {"vme", "Virtual 8086 mode enhancements"},
      {"de", "Debugging Extensions (CR4.DE)"},
      {"pse", "Page Size Extensions (4MB memory pages)"},
      {"tsc", "Time Stamp Counter (RDTSC)"},
      {"msr", "Model-Specific Registers (RDMSR, WRMSR)"},
      {"pae", "Physical Address Extensions (support for more than 4GB of RAM)"},
      {"mce", "Machine Check Exception"},
      {"cx8", "CMPXCHG8 instruction (64-bit compare-and-swap)"},
      {"apic", "Onboard APIC"},
      {"sep", "SYSENTER/SYSEXIT"},
      {"mtrr", "Memory Type Range Registers"},
      {"pge", "Page Global Enable (global bit in PDEs and PTEs)"},
      {"mca", "Machine Check Architecture"},
      {"cmov", "CMOV instructions (conditional move) (also FCMOV)"},
      {"pat", "Page Attribute Table"},
      {"pse36", "36-bit PSEs (huge pages)"},
      {"pn", "Processor serial number"},
      {"clflush", "Cache Line Flush instruction"},
      {"dts", "Debug Store (buffer for debugging and profiling instructions), or alternately: digital thermal sensor"},
      {"acpi", "ACPI via MSR (temperature monitoring and clock speed modulation)"},
      {"mmx", "Multimedia Extensions"},
      {"fxsr", "FXSAVE/FXRSTOR, CR4.OSFXSR"},
      {"sse", "Intel SSE vector instructions"},
      {"sse2", "SSE2"},
      {"ss", "CPU self snoop"},
      {"ht", "Hyper-Threading"},
      {"tm", "Automatic clock control (Thermal Monitor)"},
      {"ia64",
       "Intel Itanium Architecture 64-bit (not to be confused with Intel's 64-bit x86 architecture with flag x86-64 or \"AMD64\" bit indicated by flag lm)"},
      {"pbe", "Pending Break Enable (PBE# pin) wakeup support"},
/* AMD-defined CPU features, CPUID level 0x80000001
 * See also Wikipedia and table 2-23 in Intel Advanced Vector Extensions Programming Reference */
      {"syscall", "SYSCALL (Fast System Call) and SYSRET (Return From Fast System Call)"},
      {"mp", "Multiprocessing Capable."},
      {"nx", "Execute Disable"},
      {"mmxext", "AMD MMX extensions"},
      {"fxsr_opt", "FXSAVE/FXRSTOR optimizations"},
      {"pdpe1gb", "One GB pages (allows hugepagesz=1G)"},
      {"rdtscp", "Read Time-Stamp Counter and Processor ID"},
      {"lm", "Long Mode (x86-64: amd64, also known as Intel 64, i.e. 64-bit capable)"},
      {"3dnow", "3DNow! (AMD vector instructions, competing with Intel's SSE1)"},
      {"3dnowext", "AMD 3DNow! extensions"},
/* Transmeta-defined CPU features, CPUID level 0x80860001 */
      {"recovery", "CPU in recovery mode"},
      {"longrun", "Longrun power control"},
      {"lrti", "LongRun table interface"},
/* Other features, Linux-defined mapping */
      {"cxmmx", "Cyrix MMX extensions"},
      {"k6_mtrr", "AMD K6 nonstandard MTRRs"},
      {"cyrix_arr", "Cyrix ARRs (= MTRRs)"},
      {"centaur_mcr", "Centaur MCRs (= MTRRs)"},
      {"constant_tsc", "TSC ticks at a constant rate"},
      {"up", "SMP kernel running on UP"},
      {"art", "Always-Running Timer"},
      {"arch_perfmon", "Intel Architectural PerfMon"},
      {"pebs", "Precise-Event Based Sampling"},
      {"bts", "Branch Trace Store"},
      {"rep_good", "rep microcode works well"},
      {"acc_power", "AMD accumulated power mechanism"},
      {"nopl", "The NOPL (0F 1F) instructions"},
      {"xtopology", "cpu topology enum extensions"},
      {"tsc_reliable", "TSC is known to be reliable"},
      {"nonstop_tsc", "TSC does not stop in C states"},
      {"extd_apicid", "has extended APICID (8 bits)"},
      {"amd_dcm", "multi-node processor"},
      {"aperfmperf", "APERFMPERF"},
      {"eagerfpu", "Non lazy FPU restore"},
      {"nonstop_tsc_s3", "TSC doesn't stop in S3 state"},
      {"mce_recovery", "CPU has recoverable machine checks"},
/* Intel-defined CPU features, CPUID level 0x00000001 (ecx)
 * See also Wikipedia and table 2-26 in Intel Advanced Vector Extensions Programming Reference */
      {"pni", "SSE-3 (\"Prescott New Instructions\")"},
      {"pclmulqdq", "Perform a Carry-Less Multiplication of Quadword instruction - accelerator for GCM)"},
      {"dtes64", "64-bit Debug Store"},
      {"monitor", "Monitor/Mwait support (Intel SSE3 supplements)"},
      {"ds_cpl", "CPL Qual. Debug Store"},
      {"vmx", "Hardware virtualization, Intel VMX"},
      {"smx", "Safer mode TXT (TPM support)"},
      {"est", "Enhanced SpeedStep"},
      {"tm2", "Thermal Monitor 2"},
      {"ssse3", "Supplemental SSE-3"},
      {"cid", "Context ID"},
      {"sdbg", "silicon debug"},
      {"fma", "Fused multiply-add"},
      {"cx16", "CMPXCHG16B"},
      {"xtpr", "Send Task Priority Messages"},
      {"pdcm", "Performance Capabilities"},
      {"pcid", "Process Context Identifiers"},
      {"dca", "Direct Cache Access"},
      {"sse4_1", "SSE-4.1"},
      {"sse4_2", "SSE-4.2"},
      {"x2apic", "x2APIC"},
      {"movbe", "Move Data After Swapping Bytes instruction"},
      {"popcnt", "Return the Count of Number of Bits Set to 1 instruction (Hamming weight, i.e. bit count)"},
      {"tsc_deadline_timer", "Tsc deadline timer"},
      {"aes/aes-ni", "Advanced Encryption Standard (New Instructions)"},
      {"xsave", "Save Processor Extended States: also provides XGETBY,XRSTOR,XSETBY"},
      {"avx", "Advanced Vector Extensions"},
      {"f16c", "16-bit fp conversions (CVT16)"},
      {"rdrand", "Read Random Number from hardware random number generator instruction"},
      {"hypervisor", "Running on a hypervisor"},
/* VIA/Cyrix/Centaur-defined CPU features, CPUID level 0xC0000001 */
      {"rng", "Random Number Generator present (xstore)"},
      {"rng_en", "Random Number Generator enabled"},
      {"ace", "on-CPU crypto (xcrypt)"},
      {"ace_en", "on-CPU crypto enabled"},
      {"ace2", "Advanced Cryptography Engine v2"},
      {"ace2_en", "ACE v2 enabled"},
      {"phe", "PadLock Hash Engine"},
      {"phe_en", "PHE enabled"},
      {"pmm", "PadLock Montgomery Multiplier"},
      {"pmm_en", "PMM enabled"},
/* More extended AMD flags: CPUID level 0x80000001, ecx */
      {"lahf_lm", "Load AH from Flags (LAHF) and Store AH into Flags (SAHF) in long mode"},
      {"cmp_legacy", "If yes HyperThreading not valid"},
      {"svm", "\"Secure virtual machine\": AMD-V"},
      {"extapic", "Extended APIC space"},
      {"cr8_legacy", "CR8 in 32-bit mode"},
      {"abm", "Advanced Bit Manipulation"},
      {"sse4a", "SSE-4A"},
      {"misalignsse",
       "indicates if a general-protection exception (#GP) is generated when some legacy SSE instructions operate on unaligned data. Also depends on CR0 and Alignment Checking bit"},
      {"3dnowprefetch", "3DNow prefetch instructions"},
      {"osvw", "indicates OS Visible Workaround, which allows the OS to work around processor errata."},
      {"ibs", "Instruction Based Sampling"},
      {"xop", "extended AVX instructions"},
      {"skinit", "SKINIT/STGI instructions"},
      {"wdt", "Watchdog timer"},
      {"lwp", "Light Weight Profiling"},
      {"fma4", "4 operands MAC instructions"},
      {"tce", "translation cache extension"},
      {"nodeid_msr", "NodeId MSR"},
      {"tbm", "Trailing Bit Manipulation"},
      {"topoext", "Topology Extensions CPUID leafs"},
      {"perfctr_core", "Core Performance Counter Extensions"},
      {"perfctr_nb", "NB Performance Counter Extensions"},
      {"bpext", "data breakpoint extension"},
      {"ptsc", "performance time-stamp counter"},
      {"perfctr_l2", "L2 Performance Counter Extensions"},
      {"mwaitx", "MWAIT extension (MONITORX/MWAITX)"},
/* Auxiliary flags: Linux defined - For features scattered in various CPUID levels */
      {"cpb", "AMD Core Performance Boost"},
      {"epb", "IA32_ENERGY_PERF_BIAS support"},
      {"hw_pstate", "AMD HW-PState"},
      {"proc_feedback", "AMD ProcFeedbackInterface"},
      {"intel_pt", "Intel Processor Tracing"},
/* Virtualization flags: Linux defined */
      {"tpr_shadow", "Intel TPR Shadow"},
      {"vnmi", "Intel Virtual NMI"},
      {"flexpriority", "Intel FlexPriority"},
      {"ept", "Intel Extended Page Table"},
      {"vpid", "Intel Virtual Processor ID"},
      {"vmmcall", "prefer VMMCALL to VMCALL"},
/* Intel-defined CPU features, CPUID level 0x00000007:0 (ebx) */
      {"fsgsbase", "{RD/WR}{FS/GS}BASE instructions"},
      {"tsc_adjust", "TSC adjustment MSR"},
      {"bmi1", "1st group bit manipulation extensions"},
      {"hle", "Hardware Lock Elision"},
      {"avx2", "AVX2 instructions"},
      {"smep", "Supervisor Mode Execution Protection"},
      {"bmi2", "2nd group bit manipulation extensions"},
      {"erms", "Enhanced REP MOVSB/STOSB"},
      {"invpcid", "Invalidate Processor Context ID"},
      {"rtm", "Restricted Transactional Memory"},
      {"cqm", "Cache QoS Monitoring"},
      {"mpx", "Memory Protection Extension"},
      {"avx512f", "AVX-512 foundation"},
      {"avx512dq", "AVX-512 Double/Quad instructions"},
      {"rdseed", "The RDSEED instruction"},
      {"adx", "The ADCX and ADOX instructions"},
      {"smap", "Supervisor Mode Access Prevention"},
      {"clflushopt", "CLFLUSHOPT instruction"},
      {"clwb", "CLWB instruction"},
      {"avx512pf", "AVX-512 Prefetch"},
      {"avx512er", "AVX-512 Exponential and Reciprocal"},
      {"avx512cd", "AVX-512 Conflict Detection"},
      {"sha_ni", "SHA1/SHA256 Instruction Extensions"},
      {"avx512bw", "AVX-512 Byte/Word instructions"},
      {"avx512vl", "AVX-512 128/256 Vector Length extensions"},
/* Extended state features, CPUID level 0x0000000d:1 (eax) */
      {"xsaveopt", "Optimized XSAVE"},
      {"xsavec", "XSAVEC"},
      {"xgetbv1", "XGETBV with ECX = 1"},
      {"xsaves", "XSAVES/XRSTORS"},
/* Intel-defined CPU QoS sub-leaf, CPUID level 0x0000000F:0 (edx) */
      {"cqm_llc", "LLC QoS"},
/* Intel-defined CPU QoS sub-leaf, CPUID level 0x0000000F:1 (edx) */
      {"cqm_occup_llc", "LLC occupancy monitoring"},
      {"cqm_mbm_total", "LLC total MBM monitoring"},
      {"cqm_mbm_local", "LLC local MBM monitoring"},
/* AMD-defined CPU features, CPUID level 0x80000008 (ebx) */
      {"clzero", "CLZERO instruction"},
      {"irperf", "instructions retired performance counter"},
/* Thermal and Power Management leaf, CPUID level 0x00000006 (eax) */
      {"dtherm", "digital thermal sensor"}, /* formerly dts */
      {"ida", "Intel Dynamic Acceleration"},
      {"arat", "Always Running APIC Timer"},
      {"pln", "Intel Power Limit Notification"},
      {"pts", "Intel Package Thermal Status"},
      {"hwp", "Intel Hardware P-states"},
      {"hwp_notify", "HWP notification"},
      {"hwp_act_window", "HWP Activity Window"},
      {"hwp_epp", "HWP Energy Performance Preference"},
      {"hwp_pkg_req", "HWP package-level request"},
/* AMD SVM Feature Identification, CPUID level 0x8000000a (edx) */
      {"npt", "AMD Nested Page Table support"},
      {"lbrv", "AMD LBR Virtualization support"},
      {"svm_lock", "AMD SVM locking MSR"},
      {"nrip_save", "AMD SVM next_rip save"},
      {"tsc_scale", "AMD TSC scaling support"},
      {"vmcb_clean", "AMD VMCB clean bits support"},
      {"flushbyasid", "AMD flush-by-ASID support"},
      {"decodeassists", "AMD Decode Assists support"},
      {"pausefilter", "AMD filtered pause intercept"},
      {"pfthreshold", "AMD pause filter threshold"},
      {"avic", "Virtual Interrupt Controller"},
/* Intel-defined CPU features, CPUID level 0x00000007:0 (ecx) */
      {"pku", "Protection Keys for Userspace"},
      {"ospke", "OS Protection Keys Enable"},
/* AMD-defined CPU features, CPUID level 0x80000007 (ebx) */
      {"overflow_recov", "MCA overflow recovery support"},
      {"succor", "uncorrectable error containment and recovery"},
      {"smca", "Scalable MCA"},
  };

  return flags.value(name);
}

QString getBugDescription(const QString& name) {
  static const QMap<QString, QString> flags = {
      /* bug workarounds */
      {"f00f", "Intel F00F bug"},
      {"fdiv", "FPU FDIV"},
      {"coma", "Cyrix 6x86 coma"},
      {"tlb_mmatch", "AMD Erratum 383"},
      {"apic_c1e", "AMD Erratum 400"},
      {"11ap", "Bad local APIC aka 11AP"},
      {"fxsave_leak", "FXSAVE leaks FOP/FIP/FOP"},
      {"clflush_monitor", "AAI65, CLFLUSH required before MONITOR"},
      {"sysret_ss_attrs", "SYSRET doesn't fix up SS attrs"},
      {"espfix", "IRET to 16-bit SS corrupts ESP/RSP high bits"},
      {"null_seg", "Nulling a selector preserves the base"},         /* see: detect_null_seg_behavior() */
      {"swapgs_fence", "SWAPGS without input dep on GS"},
      {"monitor", "IPI required to wake up remote CPU"},
      {"amd_e400", "AMD Erratum 400"},
      {"cpu_insecure", "CPU is affected by meltdown attack and needs kernel page table isolation"},
      {"cpu_meltdown", "CPU is affected by meltdown attack and needs kernel page table isolation"},
      {"spectre_v1", "CPU is affected by Spectre variant 1 attack with conditional branches"},
      {"spectre_v2", "CPU is affected by Spectre variant 2 attack with indirect branches"},
      {"spec_store_bypass", "Speculative execution exploit Variant 4"},
      {"swapgs", "A vulnerability that utilizes the branch prediction"},
      {"itlb_multihit",
       "An erratum where some processors may incur a machine check error, possibly resulting in an unrecoverable CPU lockup, when an instruction fetch hits multiple entries in the instruction TLB"},
      {"srbds",
       "Allows MDS MDS - Microarchitectural Data Sampling techniques to infer values returned from special register accesses"},
      {"mmio_stale_data", "A class of memory-mapped I/O (MMIO) vulnerabilities that can expose data"},
      {"retbleed",
       "A variant of the Spectre vulnerability which exploits retpoline, which was intended as a mitigation for speculative execution attacks"},
  };
  return flags.value(name);
}

QString getPowerDescription(const QString& name) {
  // from arch/x86/kernel/cpu/powerflags.h
  static const QMap<QString, QString> flags = {
      {"ts", "temperature sensor"},
      {"fid", "frequency id control"},
      {"vid", "voltage id control"},
      {"ttp", "thermal trip"},
      {"tm", "hardware thermal control"},
      {"stc", "software thermal control"},
      {"100mhzsteps", "100 MHz multiplier control"},
      {"hwpstate", "hardware P-state control"},
      {"cpb", "core performance boost"},
      {"eff_freq_ro", "Readonly aperf/mperf"},
      {"proc_feedback", "processor feedback interface"},
      {"acc_power", "accumulated power mechanism"},
  };

  return flags.value(name);
}

}  // namespace devices
}  // namespace sysinfo
