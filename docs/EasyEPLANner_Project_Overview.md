# EasyEPLANner Project Overview

> **Note**: This document describes the [EasyEPLANner](https://github.com/savushkin-r-d/EasyEPLANner) project, which is part of the savushkin-r-d ecosystem alongside the ptusa_engineer and ptusa_ai projects. EasyEPLANner provides the EPLAN integration component for the overall industrial automation workflow.

## Table of Contents
1. [Project Introduction](#project-introduction)
2. [Architecture and Components](#architecture-and-components)
3. [Component Interactions](#component-interactions)
4. [Existing Documentation](#existing-documentation)
5. [Similar Projects Comparison](#similar-projects-comparison)
6. [Supported Controllers](#supported-controllers)
7. [Getting Started](#getting-started)

---

## Project Introduction

**EasyEPLANner** is an open-source add-in for **EPLAN Electric P8 version 2.9** - a professional electrical engineering CAD software. The project aims to bridge the gap between electrical design documentation and industrial automation software, reducing the workload for both Automation Engineers and Software Engineers.

> **Compatibility Note**: The add-in was developed for EPLAN Electric P8 version 2.9. For compatibility with newer EPLAN versions, please check the [official repository](https://github.com/savushkin-r-d/EasyEPLANner) for the latest information.

### Key Purpose
- Automate the generation of PLC (Programmable Logic Controller) code from EPLAN electrical designs
- Describe technological objects (Tanks, Boilers, etc.), their operations, steps, and restrictions
- Generate Lua files for uploading to industrial controllers
- Provide a unified workflow between electrical design and control system programming

### Technology Stack
- **Language**: C# (.NET Framework)
- **IDE Integration**: EPLAN Electric P8 API
- **Generated Code**: Lua programming language
- **License**: MIT

---

## Architecture and Components

The EasyEPLANner project is organized into several key modules, each responsible for specific functionality:

### 1. **Device Management** (`src/Device/`)
Handles all device-related operations in the project.

| Component | Description |
|-----------|-------------|
| `Device.cs`, `IDevice.cs` | Core device abstraction and interface |
| `DeviceManager.cs` | Manages all devices in the project |
| `DeviceTypeEnum.cs` | Enumerations for device types (sensors, actuators, etc.) |
| `DeviceSubTypeEnum.cs` | Sub-type classifications for devices |
| `IODevice.cs`, `IIODevice.cs` | I/O device abstractions |
| `IOChannel.cs`, `IIOChannel.cs` | I/O channel management |
| `Parameter.cs`, `Property.cs` | Device parameters and properties |
| `Tag.cs`, `ITag.cs` | Tag management for devices |
| `IODevices/` | Specific device type implementations |

### 2. **Technical Objects** (`src/TechObject/`)
Manages technological objects and their hierarchical structure.

| Component | Description |
|-----------|-------------|
| `TechObjectManager.cs` | Central manager for all technical objects |
| `ITechObjectManager.cs` | Interface for technical object management |
| `TechObjectXMLMaker.cs` | XML generation for technical objects |
| `TechObjectChecker.cs` | Validation strategies for technical objects |
| `Base/` | Base technological object definitions |
| `ObjectsTree/` | Tree structure for object hierarchy |

### 3. **I/O System** (`src/IO/`)
Manages Input/Output modules and their configuration.

| Component | Description |
|-----------|-------------|
| `IOManager.cs`, `IIOManager.cs` | Central I/O management |
| `IOModule.cs`, `IIOModule.cs` | I/O module abstractions |
| `IOModuleInfo.cs` | Module information and metadata |
| `IONode.cs`, `IIONode.cs` | I/O node management |
| `IOLinkCalculator.cs` | IO-Link calculations |
| `View/`, `ViewModel/` | UI components for I/O configuration |

### 4. **EPLAN Project Manager** (`src/EProjectManager/`)
Handles integration with EPLAN projects.

| Component | Description |
|-----------|-------------|
| `EProjectManager.cs` | Main EPLAN project manager |
| `EplanEventListener.cs` | Event handling for EPLAN actions |
| `SelectInteractionWhileEditModes.cs` | User interaction handlers |
| `InsertMacrosInteraction.cs` | Macro insertion functionality |

### 5. **Editor** (`src/Editor/`)
Provides the user interface for editing project data.

| Component | Description |
|-----------|-------------|
| `NewEditorControl.cs` | Main editor control (85KB+ of code) |
| `TreeViewItem.cs`, `ITreeViewItem.cs` | Tree view components |
| `ObjectProperty.cs` | Property editor components |
| `Editor.cs`, `IEditor.cs` | Core editor functionality |
| `Controls/` | Additional UI controls |
| `ImportExport/` | Import/export functionality |
| `ObjectAdder/` | Object creation wizards |

### 6. **Lua Generation** (`src/Lua/`)
Templates and configurations for Lua code generation.

| File | Description |
|------|-------------|
| `mainPattern.plua` | Main Lua pattern template |
| `sys.lua` | System functions |
| `sys_io_modules.lua` | I/O modules configuration (37KB) |
| `sys_io_nodes.lua` | I/O nodes configuration |
| `sys_base_objects_initializer.lua` | Base objects initialization |
| `sys_iolink_devices.lua` | IO-Link devices configuration |
| `sys_restriction.lua` | Restriction handling |
| `sys_wago_device_importer.lua` | WAGO device import |
| `modbus_exchange_pattern.lua` | Modbus communication patterns |

### 7. **File Savers** (`src/FileSavers/`)
Handles export to various formats.

| Component | Description |
|-----------|-------------|
| `PrgLuaSaver.cs` | Saves Lua program files |
| `ProjectDescriptionSaver.cs` | Saves project descriptions |
| `SVGStatisticsSaver.cs` | Generates SVG statistics |
| `Excel/` | Excel export functionality |
| `XML/` | XML export functionality |

### 8. **Supporting Modules**

| Module | Path | Description |
|--------|------|-------------|
| **InterprojectExchange** | `src/InterprojectExchange/` | Data exchange between projects |
| **ModbusExchange** | `src/ModbusExchange/` | Modbus communication setup |
| **Configuration** | `src/Configuration/` | Project configuration |
| **StaticHelper** | `src/StaticHelper/` | Utility functions |
| **Extensions** | `src/Extensions/` | Extension methods |
| **Logs** | `src/Logs/` | Logging functionality |
| **LuaInterface** | `src/LuaInterface/` | Lua interpreter integration |
| **PxcIolinkConfiguration** | `src/PxcIolinkConfiguration/` | Phoenix Contact IO-Link config |
| **ProjectImportICP** | `src/ProjectImportICP/` | ICP project import |

### 9. **Main Forms**
| File | Description |
|------|-------------|
| `DFrm.cs` | Device form (61KB) |
| `ModeFrm.cs` | Mode/operation form (44KB) |
| `ModulesBindingUpdater.cs` | Module binding updates (40KB) |
| `ProjectManager.cs` | Overall project management (33KB) |

---

## Component Interactions

```
┌─────────────────────────────────────────────────────────────────────────┐
│                            EPLAN Electric P8                            │
│                         (Electrical CAD Software)                       │
└─────────────────────────────────────────────────────────────────────────┘
                                     │
                                     ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                    EasyEPLANner Add-In (C#/.NET)                        │
│  ┌──────────────────┐  ┌──────────────────┐  ┌──────────────────┐      │
│  │   EProjectManager │  │  EplanEventListener│  │   ProjectManager  │      │
│  │   (EPLAN API)     │◄─┤  (Event Handling)  │──►│  (Coordination)   │      │
│  └────────┬─────────┘  └──────────────────┘  └────────┬─────────┘      │
│           │                                           │                 │
│           ▼                                           ▼                 │
│  ┌──────────────────────────────────────────────────────────────────┐  │
│  │                        Device Manager                             │  │
│  │  • Reads device data from EPLAN project                          │  │
│  │  • Creates Device objects with parameters, channels, tags        │  │
│  └──────────────────────────────────────────────────────────────────┘  │
│           │                                                            │
│           ▼                                                            │
│  ┌──────────────────────────────────────────────────────────────────┐  │
│  │                    Technical Object Manager                       │  │
│  │  • Creates TechObjects (Tanks, Boilers, etc.)                    │  │
│  │  • Defines operations, steps, restrictions                       │  │
│  │  • Links devices to objects                                       │  │
│  └──────────────────────────────────────────────────────────────────┘  │
│           │                                                            │
│           ▼                                                            │
│  ┌──────────────────────────────────────────────────────────────────┐  │
│  │                         IO Manager                                │  │
│  │  • Manages IO Nodes (PLCs, couplers)                             │  │
│  │  • Configures IO Modules (DI, DO, AI, AO)                        │  │
│  │  • Binds devices to physical channels                            │  │
│  └──────────────────────────────────────────────────────────────────┘  │
│           │                                                            │
│           ▼                                                            │
│  ┌────────────────────┐  ┌────────────────────┐  ┌──────────────────┐ │
│  │    Editor (UI)     │  │   File Savers      │  │  Lua Templates   │ │
│  │  • Tree view       │  │  • Lua export      │  │  • sys.lua       │ │
│  │  • Property editor │  │  • XML export      │  │  • io_modules    │ │
│  │  • Validation      │  │  • Excel export    │  │  • patterns      │ │
│  └────────────────────┘  └────────┬───────────┘  └────────┬─────────┘ │
└─────────────────────────────────────────────────────────────────────────┘
                                    │                        │
                                    ▼                        ▼
                    ┌──────────────────────────────────────────────────────┐
                    │              Generated Lua Files                     │
                    │  • main.lua           • prg.lua                     │
                    │  • io.lua             • objects.lua                 │
                    │  • restrictions.lua   • modbus_exchange.lua         │
                    └──────────────────────────────────────────────────────┘
                                            │
                                            ▼
                    ┌──────────────────────────────────────────────────────┐
                    │              Industrial Controllers                  │
                    │  • Phoenix Contact PLCnext                           │
                    │  • WAGO PFC200                                       │
                    └──────────────────────────────────────────────────────┘
```

### Data Flow
1. **EPLAN Project** → Contains electrical schematics with device data
2. **EasyEPLANner** → Reads and processes electrical data via EPLAN API
3. **Device Manager** → Creates device objects from EPLAN symbols
4. **TechObject Manager** → User defines process logic using the editor
5. **IO Manager** → Maps devices to physical I/O channels
6. **File Savers** → Generates Lua code from all configurations
7. **Controllers** → Receive and execute the generated Lua programs

---

## Existing Documentation

### Official Documentation Structure

| Documentation | Path | Language | Description |
|---------------|------|----------|-------------|
| **Main README** | `/ReadMe.md` | English | Project overview and build instructions |
| **User Manual** | `/docs/user_manual/ReadMe.md` | Russian | Comprehensive user guide (~285KB) |
| **Developer Manual** | `/docs/developer_manual/ReadMe.md` | Russian | Developer documentation (~119KB) |
| **Russian README** | `/docs/ru/readme.md` | Russian | Russian version of main README |
| **German README** | `/docs/de/readme.md` | German | German version of main README |
| **Code of Conduct** | `/docs/CODE_OF_CONDUCT.md` | English | Community behavior guidelines |
| **Contributing Guide** | `/docs/contributing.md` | Russian | How to contribute |
| **Code Style** | `/docs/codestyle.md` | Russian | C# and Lua coding standards |

### User Manual Contents (Russian)
The user manual (`/docs/user_manual/ReadMe.md`) includes:
- Project naming conventions
- Add-in description and usage
- EPLAN connection setup
- Auto-generated Lua file descriptions
- Project directory configuration
- Version management
- Device types and configurations
- Technical object definitions
- Operation and step management
- Restriction handling

### Developer Manual Contents
The developer manual (`/docs/developer_manual/ReadMe.md`) provides:
- Architecture overview
- Class diagrams
- API documentation
- Extension development guide
- Testing guidelines

### External Resources
- **Slack Channel**: easyEPLANner.slack.com (contact the project maintainers for an invitation)
- **Google Groups**: easyeplanner
- **EPLAN API Help**: https://www.eplan.help/

---

## Similar Projects Comparison

### 1. **Suplanus EPLAN Projects**

The Suplanus organization (by Johann Weiher) provides several EPLAN-related tools:

| Project | Stars | Description | Comparison with EasyEPLANner |
|---------|-------|-------------|------------------------------|
| **EPLAN-Scripting** | 57 ⭐ | Scripting book examples | Educational focus; EasyEPLANner is production-ready |
| **EplanScriptingProjectBySuplanus** | 39 ⭐ | Collection of EPLAN scripts | Individual scripts vs. integrated solution |
| **Suplanus.Sepla** | 29 ⭐ | EPLAN API wrapper library | Library vs. complete application |
| **Suplanus.Eplan.Database** | 4 ⭐ | Entity Framework for EPLAN databases | Database focus only |

**Key Differences**:
- Suplanus projects are scripting utilities and libraries
- EasyEPLANner is a complete application for PLC code generation
- EasyEPLANner includes UI, code generation, and controller support

### 2. **OpenPLC and IEC 61131-3 Projects**

| Project | Description | Comparison |
|---------|-------------|------------|
| **OpenPLC Runtime** | Open-source PLC runtime | Runtime execution vs. code generation |
| **beremiz** | IEC 61131-3 IDE | Standalone IDE vs. EPLAN integration |
| **MATIEC** | IEC 61131-3 compiler | Compiler only, no CAD integration |

**Key Differences**:
- OpenPLC/Beremiz are standalone PLC development environments
- EasyEPLANner integrates with professional CAD (EPLAN)
- EasyEPLANner generates Lua, not IEC 61131-3 languages

### 3. **Commercial Alternatives**

| Product | Vendor | Comparison |
|---------|--------|------------|
| **EPLAN EEC One** | EPLAN | Official EPLAN engineering tool; proprietary |
| **TIA Portal** | Siemens | Integrated engineering; vendor-specific |
| **Studio 5000** | Rockwell | Complete automation suite; proprietary |
| **CODESYS** | 3S-Smart | Multi-vendor; different workflow |

**Key Differences**:
- Commercial products are proprietary and expensive
- EasyEPLANner is open-source (MIT license)
- EasyEPLANner specifically targets Phoenix Contact and WAGO controllers

### 4. **easyplc-school**
| Aspect | easyplc-school | EasyEPLANner |
|--------|----------------|--------------|
| Purpose | Educational platform | Production tool |
| Target | Learning PLC concepts | Real engineering projects |
| Integration | Standalone web app | EPLAN integration |
| Controllers | Simulated | Real hardware (PLCNext, PFC200) |

### Comparison Summary Table

| Feature | EasyEPLANner | Suplanus Tools | OpenPLC | Commercial |
|---------|--------------|----------------|---------|------------|
| **Open Source** | ✅ MIT | ✅ Various | ✅ | ❌ |
| **EPLAN Integration** | ✅ Full | ✅ Scripts | ❌ | Varies by vendor |
| **Code Generation** | ✅ Lua | ❌ | ❌ | ✅ IEC 61131 |
| **GUI Editor** | ✅ | ❌ | ✅ | ✅ |
| **Multi-language Docs** | ✅ EN/RU/DE | ✅ EN | ✅ | ✅ |
| **Phoenix Contact Support** | ✅ | ❌ | ✅ | ✅ |
| **WAGO Support** | ✅ | ❌ | ✅ | ✅ |
| **Active Development** | ✅ | ⚠️ | ✅ | ✅ |
| **Community** | Slack, Google Groups | GitHub | Forums | Vendor support |

---

## Supported Controllers

### 1. Phoenix Contact PLCnext
- **Repository**: https://github.com/plcnext
- Modern Linux-based PLC platform
- Open ecosystem supporting multiple languages
- Industrial IoT integration

### 2. WAGO PFC200
- **Repository**: https://github.com/WAGO
- Versatile fieldbus coupler/controller
- Wide I/O module selection
- CODESYS-based programming option

---

## Getting Started

### Prerequisites
- EPLAN Electric P8 version 2.9 (check repository for newer version support)
- .NET Framework (compatible with EPLAN version)
- Visual Studio (for development)

### Installation
```bash
# Clone with submodules
git clone --recurse-submodules https://github.com/savushkin-r-d/EasyEPLANner.git

# If already cloned, initialize submodules
git submodule update --init --recursive
```

### Building
1. Open `src/EasyEPlanner.sln` in Visual Studio
2. Build the solution
3. Install the add-in in EPLAN Electric P8

### Community
- **Slack**: easyEPLANner.slack.com (request access via GitHub issues or Google Groups)
- **Google Groups**: https://groups.google.com/forum/#!forum/easyeplanner
- **Issues**: https://github.com/savushkin-r-d/EasyEPLANner/issues

---

## Conclusion

EasyEPLANner represents a unique open-source solution that bridges electrical CAD design (EPLAN) with industrial controller programming. Unlike general-purpose PLC IDEs or scripting libraries, it provides an integrated workflow specifically designed for engineers working with EPLAN and targeting Phoenix Contact or WAGO controllers.

The project's strengths include:
- **Integration**: Tight coupling with EPLAN Electric P8
- **Automation**: Reduces manual coding effort
- **Open Source**: MIT license, active community
- **Documentation**: Comprehensive multi-language docs

Areas for potential improvement:
- Broader controller support
- English documentation expansion
- Additional export formats (IEC 61131-3)

---

*Document created: January 2026*  
*Based on analysis of: https://github.com/savushkin-r-d/EasyEPLANner*
