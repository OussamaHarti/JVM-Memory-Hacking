# Memory Hacking the JVM

> **A Minecraft radar achieved through JVM “memory hacking” using nothing but `ReadProcessMemory`**
> ![Radar](https://i.ibb.co/Rw4tvtB/radar.png)

---

## Table of Contents
- [Description](#description)
- [Operating Principle](#operating-principle)  
  - [1. Finding static regions](#1-finding-static-regions)  
  - [2. Pattern scanning](#2-pattern-scanning)  
  - [3. Pointers & multipliers](#3-pointers--multipliers)
- [FAQ](#faq)
- [Security & Legal Notes](#security--legal-notes)
- [License](#license)

---

## Description
`MemoryRadarJVM` is a proof of concept showing that you can read internal data structures of the **Java Virtual Machine** (JVM)—notoriously hard to “memory-hack”—without resorting to the **Java Native Interface (JNI)**. The project uses only `ReadProcessMemory` to locate and track stable memory regions, outputting an in-game **radar** for *Minecraft*.

Its main goal is educational: explaining how to reverse-engineer the JVM, locate dynamic pointers and calculate offsets even when the Java heap size changes.

---

## Operating Principle

### 1. Finding static regions
1. Launch *Minecraft* with a modest memory budget (e.g., `RAM: 2 GB`) to reduce fragmentation.  
2. Use **Cheat Engine → Memory View → Scan** to locate regions whose contents stay constant during the session. (You can further refine the search with “Find out what writes to this address” and “Find out what accesses this address” in Cheat Engine)

### 2. Pattern scanning
- **Primary byte pattern**: extract a characteristic byte set from the regions you just found.  
- **Secondary patterns**: a recurring value signature or a pattern of *changing* values—handy to weed out false positives.  
- The C++ code performs a **scan** over the entire process until every match is found.

```cpp
Scanner::byteScanner(Scanner::minecraft_handle, target, &start_addr, &end_addr,
                     nullptr, nullptr, results, false, nullptr);
```

### 3. Pointers & multipliers
The JVM builds a chain of 4 Bytes pointers leading to structures that contain:

- **Player position**
- **Nearby entities**

When you change the heap size (`RAM: 4 GB+`), those pointers can become `value × multiplier`.

1. Find a **pointer near the main memory region** with Cheat Engine once again. (You can infer the need for a multiplier from the ASM that Cheat Engine shows via *“Find out what accesses this address”*.)
   ```asm
   mov r10d,[r12+r8*8+00000188]
   ```
   Here, `r8*8` means that with those RAM settings the multiplier is 8.  
2. Compute `multiplier = mainRegionAddress / 4BytesPointer`.  
3. Hard-code the `multiplier` like this:

```cpp
ASM_PTR_MULTIPLIER =
    round((double)tmp / (double)Scanner::convertBytes<uint32_t>(mem, i));
```

With this mechanism the radar keeps working regardless of the selected memory profile.

---

> **Note:** The project has no JNI dependencies or external libraries. What you see is a trimmed-down extract of a much larger code base; WinForms was used here purely for convenience. In real projects you’d likely switch to OpenGL (used in the main project) or DirectX.

---

## FAQ
> **Why not JNI?**  
> JNI requires internal hooks into Java classes. The aim of this project is to show the same result can be achieved externally with pure syscalls.

> **Does it work with Lunar/Feather?**  
> Yes, it works with almost any client as long as *Minecraft* is between 1.18 and 1.20.4. For other versions you only need minor code tweaks because the JVM emits slightly different memory layouts.

> **Can I apply this method to other Java apps?**  
> In theory, yes—but the patterns will differ.

---

## Security & Legal Notes
- This repository is **for educational use only**; using it in violation of *Minecraft*’s or third-party servers’ Terms of Service is at your own risk.  
- None of the code attempts to bypass kernel-mode anti-cheat protections.

---

## License
Distributed under the **MIT License**. See `LICENSE` for details.
