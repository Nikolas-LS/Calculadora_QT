# Qt MVC Calculator (Basic + Scientific)

Project in **Qt Widgets (C++17)** with a **layered architecture (Model / Controller / Views)**.  
Interface built **via C++ code** (no `.ui` files), **dark theme**, **uniform grid (5 columns)**, **memory (MC/MR/M+)**, **error handling**, and **QSS styling**.

---

## Overview

- **Framework:** Qt 6 (preferred) or Qt 5 — Qt Widgets  
- **Build system:** CMake ≥ 3.16  
- **Architecture:** Model + Controller + Views (Layered MVC)  
- **Platforms:** Windows, Linux, macOS (Desktop kits)

---

## Folder Structure
```plaintext
QtDualCalculator_UIv2/
├─ CMakeLists.txt
└─ src/
   ├─ main.cpp
   ├─ models/
   │  ├─ CalculatorModel.h
   │  └─ CalculatorModel.cpp
   ├─ controllers/
   │  ├─ CalculatorController.h
   │  └─ CalculatorController.cpp
   └─ views/
      ├─ MainWindow.h
      ├─ MainWindow.cpp
      ├─ BasicCalculatorView.h
      ├─ BasicCalculatorView.cpp
      ├─ ScientificCalculatorView.h
      └─ ScientificCalculatorView.cpp
```
**Role of each folder:**

- **models/** → business rules and mathematical operations (unary and binary) + memory.  
- **controllers/** → interprets clicks, controls state/flow (input, accumulator, operator), and communicates with the Model and Views.  
- **views/** → C++ widgets that build the **QGridLayout** (5 columns), connect signals, and display the screen/status/memory indicator.  
- **main.cpp** → initializes the application and opens the main window.

---

## Architecture

### Model — `CalculatorModel`
- **Unary:** `sin`, `cos`, `tan`, `√`, `log10`, `ln`, **`x²`**, **`%`**  
- **Binary:** `+`, `−`, `×`, `÷`, `x^y`  
- **Memory:** `MC`, `MR`, `M+`  
- **Validations/Errors:** division by zero; `√` of a negative number; `log/ln` with `x ≤ 0`; non-finite results.

### Controller — `CalculatorController`
- Connected to both views; reacts to the **button text** (e.g., `"7"`, `"+"`, `"x^y"`, `"sin"`, `"√"`, **`"x^2"`/`"x²"`**, **`"%"`**, `"π"`, `"e"`).  
- Manages the **current input**, **accumulator**, and **pending operator**; executes `=` and updates the display/indicators.  
- Uses `QLocale` for numeric conversion/output.

### Views — `BasicCalculatorView` and `ScientificCalculatorView`
- **Programmatic** assembly with `QGridLayout` (5 columns per row, **no empty spaces**).  
- Emits a single `buttonClicked(QString token)` signal per button.  
- Shows the **display** (right-aligned), **status** (error/info messages), and **“M” indicator** (active memory).

---

## Theme and Styling

- **Dark theme** applied in `MainWindow::applyTheme()` via **Qt StyleSheet (QSS)**:
  - Dark display, light text, rounded corners.  
  - **Operators in blue**, **C button in red**, numeric buttons in gray.  
- Easy to customize (colors, fonts, border radius) by modifying the QSS.

---

## Button Layout (5 columns per row)

**Basic**
```plaintext
MC MR M+ ± C
7 8 9 x² ÷
4 5 6 % ×
1 2 3 = −
0 00 . = +
```

**Scientific**
```plaintext
MC MR M+ ± C
sin cos tan √ log
7 8 9 ÷ ln
4 5 6 × x^y
1 2 3 − π
0 . = + e
```

- **Display** takes up the **full width** (same length as the grid).  
- **Large and readable symbols**: **×**, **÷**, **x²**, **√**, **π**, **e**.

---

## Features

- **Basic and scientific** operations (above).  
- **Constants:** `π` and `e`.  
- **Sign:** `±` inverts the current value.  
- **Decimal:** `.` (`QLocale` compatible).  
- **Memory:** `MC` (clear), `MR` (recall), `M+` (accumulate).  
- **Error messages** in the status bar (e.g., "Division by zero", "ln(x) with x≤0").

---

## Tools

- **Qt Creator** (IDE) — Widgets  
- **CMake** (build system)  
- **Desktop Compilers:** MinGW/Clang/MSVC (Windows), GCC/Clang (Linux), Clang (macOS)

---

## How to Build and Run

### Qt Creator (recommended)
1. **File → Open…** and select the `CMakeLists.txt`.  
2. Choose a **Desktop Kit** (Qt 6 preferred; Qt 5 works).  
3. Configure, **Build**, and **Run**.

### Command Line

```bash
# Linux/macOS
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
./QtDualCalculator_UIv2

:: Windows (PowerShell/Command Prompt)
mkdir build && cd build
cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
.\QtDualCalculator_UIv2.exe
```
