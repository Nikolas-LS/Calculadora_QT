# Calculadora Qt MVC (Básica + Científica)

Projeto em **Qt Widgets (C++17)** com arquitetura em **camadas (Model / Controller / Views)**.  
Interface construída **via código C++** (sem arquivos `.ui`), **tema escuro**, **grade uniforme (5 colunas)**, **memória (MC/MR/M+)**, **tratamento de erros** e **estilização por QSS**.

---

## 🔎 Visão geral

- **Framework:** Qt 6 (preferível) ou Qt 5 — Qt Widgets  
- **Build system:** CMake ≥ 3.16  
- **Arquitetura:** Model + Controller + Views (MVC em camadas)  
- **Plataformas:** Windows, Linux, macOS (kits Desktop)

---

## 📁 Estrutura de Pastas
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
**Papel de cada pasta:**

- **models/** → regras de negócio e operações matemáticas (unárias e binárias) + memória.  
- **controllers/** → interpreta cliques, controla estado/fluxo (entrada, acumulador, operador) e conversa com Model e Views.  
- **views/** → widgets C++ que montam os **QGridLayout** (5 colunas), conectam sinais e exibem display/status/indicador de memória.  
- **main.cpp** → inicializa a aplicação e abre a janela principal.

---

## 🧱 Arquitetura

### Model — `CalculatorModel`
- **Unárias:** `sin`, `cos`, `tan`, `√`, `log10`, `ln`, **`x²`**, **`%`**  
- **Binárias:** `+`, `−`, `×`, `÷`, `x^y`  
- **Memória:** `MC`, `MR`, `M+`  
- **Validações/Erros:** divisão por zero; `√` de número negativo; `log/ln` com `x ≤ 0`; resultados não finitos.

### Controller — `CalculatorController`
- Conectado às duas views; reage ao **texto do botão** (ex.: `"7"`, `"+"`, `"x^y"`, `"sin"`, `"√"`, **`"x^2"`/`"x²"`**, **`"%"`**, `"π"`, `"e"`).  
- Gerencia **entrada atual**, **acumulador** e **operador pendente**; executa `=` e atualiza display/indicadores.  
- Usa `QLocale` para conversão/saída numérica.

### Views — `BasicCalculatorView` e `ScientificCalculatorView`
- Montagem **programática** com `QGridLayout` (5 colunas por linha, **sem espaços vazios**).  
- Emitem um único sinal `buttonClicked(QString token)` por botão.  
- Mostram **display** (alinhado à direita), **status** (mensagens de erro/info) e **indicador “M”** (memória ativa).

---

## 🎨 Tema e estilo

- **Dark theme** aplicado em `MainWindow::applyTheme()` via **Qt StyleSheet (QSS)**:
  - Display escuro, texto claro, cantos arredondados.  
  - **Operadores em azul**, botão **C em vermelho**, botões numéricos em cinza.  
- Fácil de personalizar (cores, fontes, raio de borda) alterando o QSS.

---

## 🧩 Layout dos botões (5 colunas por linha)

**Básica**
```plaintext
MC MR M+ ± C
7 8 9 x² ÷
4 5 6 % ×
1 2 3 = −
0 00 . = +
```


**Científica**
```plaintext
MC MR M+ ± C
sin cos tan √ log
7 8 9 ÷ ln
4 5 6 × x^y
1 2 3 − π
0 . = + e
```

- **Display** ocupa **toda a largura** (mesmo comprimento do grid).  
- **Símbolos grandes e legíveis**: **×**, **÷**, **x²**, **√**, **π**, **e**.

---

## ⚙️ Funcionalidades

- Operações **básicas e científicas** (acima).  
- **Constantes:** `π` e `e`.  
- **Sinal:** `±` inverte o valor atual.  
- **Decimal:** `.` (compatível com `QLocale`).  
- **Memória:** `MC` (limpa), `MR` (recupera), `M+` (acumula).  
- **Mensagens de erro** no status (ex.: “Divisão por zero”, “ln(x) com x≤0”).

---

## 🛠️ Ferramentas

- **Qt Creator** (IDE) — Widgets  
- **CMake** (build system)  
- **Compiladores Desktop:** MinGW/Clang/MSVC (Windows), GCC/Clang (Linux), Clang (macOS)

---

## 🚀 Como compilar e executar

### Qt Creator (recomendado)
1. **File → Open…** e selecione o `CMakeLists.txt`.  
2. Escolha um **Kit Desktop** (Qt 6 preferível; Qt 5 funciona).  
3. Configure, **Build**, e **Run**.

### Linha de comando

```bash
# Linux/macOS
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
./QtDualCalculator_UIv2

:: Windows (PowerShell/Prompt)
mkdir build && cd build
cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
.\QtDualCalculator_UIv2.exe
