# EasyEPLANner: C# to C++ Migration Overview

This document provides a high-level overview of the steps needed to migrate the [EasyEPLANner](https://github.com/savushkin-r-d/EasyEPLANner) project from C# to C++.

---

## Potential Motivations for Migration

Before proceeding, consider the business and technical drivers for this migration:
- **Performance requirements** - C++ offers lower-level control and potentially better performance
- **Platform portability** - C++ can target platforms without .NET runtime
- **Integration needs** - Easier integration with existing C++ codebases or embedded systems
- **Licensing considerations** - Avoiding .NET runtime dependencies
- **Team expertise** - Leveraging existing C++ skills

> **Note:** Ensure the expected benefits outweigh the significant development effort required.

---

## High-Level Steps

---

### 1. **Assessment & Planning**
- Inventory all C# source files, dependencies, and external libraries
- Map EPLAN API usage and identify C++ interoperability options
- Define target platforms (Windows with Visual Studio, cross-platform with CMake)
- Establish coding standards and C++ version requirements (C++17/C++20)

### 2. **Architecture Design**
- Design equivalent C++ class hierarchies for core components:
  - Device management (`Device/`, `IO/`)
  - Technological objects (`TechObject/`)
  - Project management (`EProjectManager/`)
  - Lua integration (`Lua/`, `LuaInterface/`)
  - File I/O and serialization (`FileSavers/`)
- Choose C++ libraries for:
  - GUI framework (Qt, wxWidgets, or native Win32/WinUI)
  - Lua bindings (sol2, LuaBridge, or raw Lua C API)
  - JSON/XML parsing (nlohmann/json, rapidjson, pugixml)
  - Logging (spdlog, glog)

### 3. **EPLAN API Integration**
- Evaluate EPLAN's C++ API support or COM interop requirements
- Design wrapper/adapter layer for EPLAN integration
- Consider maintaining a thin C++/CLI bridge if EPLAN only provides .NET APIs

### 4. **Core Library Migration**
- Port business logic and data models first (Device, IO, TechObject)
- Implement memory management strategy (smart pointers, RAII)
- Convert C# interfaces to C++ abstract classes/concepts
- Replace .NET collections with STL containers

### 5. **UI Layer Migration**
- Port Windows Forms (`DFrm.cs`, `ModeFrm.cs`) to chosen C++ GUI framework
- Implement TreeView/ListView components for editor functionality
- Migrate resource files and localization

### 6. **Lua Integration Rebuild**
- Replace NLua/LuaInterface with C++ Lua binding library
- Port Lua script generation and execution logic
- Maintain compatibility with existing Lua file formats

### 7. **Testing & Validation**
- Set up C++ testing framework (Google Test, Catch2)
- Port existing unit tests from C#
- Create integration tests for EPLAN interaction
- Validate Lua file generation matches C# output

### 8. **Build System & CI/CD**
- Configure CMake or MSBuild projects
- Set up CI pipelines for Windows builds
- Create installer/deployment packages

---

## Key Considerations

| Area | C# Current | C++ Recommendation |
|------|-----------|-------------------|
| GUI Framework | Windows Forms | Qt or wxWidgets |
| Lua Binding | NLua/LuaInterface | sol2 or LuaBridge |
| JSON/XML | System.Text.Json/System.Xml | nlohmann/json, pugixml |
| Unit Testing | NUnit/MSTest | Google Test |
| Memory Management | Garbage Collection | Smart pointers (RAII) |
| Build System | MSBuild (.csproj) | CMake |

---

## Risk Factors

1. **EPLAN API Compatibility** - EPLAN primarily supports .NET; may require C++/CLI bridge
2. **GUI Complexity** - Windows Forms have rich designer support; C++ alternatives require more manual work
3. **Development Time** - A complete from-scratch rewrite would take 6-12 months; the phased approach below can spread this over time
4. **Team Skills** - Requires C++ expertise with modern idioms

---

## Recommended Approach

Consider a **phased migration** to reduce risk and allow incremental delivery:

| Phase | Scope | Estimated Duration |
|-------|-------|-------------------|
| Phase 1 | Core libraries (Device, IO, TechObject) as standalone C++ modules | 2-3 months |
| Phase 2 | Keep EPLAN integration in C# with interop to C++ libraries | 1-2 months |
| Phase 3 | Gradually migrate UI components | 2-4 months |
| Phase 4 | Complete C++ solution or maintain hybrid if EPLAN requires .NET | 1-3 months |

---

*Document created: January 2026*
*For: savushkin-r-d/EasyEPLANner migration planning*
