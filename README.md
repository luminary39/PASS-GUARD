# PASSGUARD

> **Password Security Auditor & Risk Assessment Engine**  
> A lightweight, privacy-first command-line security auditor written in C that evaluates passwords through pattern intelligence, common-compromised dataset lookups, and explainable risk metrics—without transmitting sensitive credentials.

> [!NOTE]
> **🚧 Project Status: Under Active Development**  
> PASSGUARD is currently in active development (Phase 1 prototype). Features, algorithms, and project architecture are continuously evolving. Planned enhancements are being rolled out in staged milestones according to the project roadmap below.

---

## 📌 Overview & Philosophy

Most legacy password checkers enforce arbitrary composition rules: requiring at least one uppercase letter, one lowercase letter, one digit, and one symbol. This approach is fundamentally flawed:
- Short, predictable passwords like `P@ssword1!` satisfy typical complexity policies but are easily cracked in seconds.
- Longer, memorable multi-word passphrases (e.g., `correct horse battery staple`) may be penalised despite offering vastly superior entropy.

**PASSGUARD** aligns with modern authentication standards (**NIST SP 800-63B**) by prioritizing:
1. **Length & Entropy**: Treating length as the primary defence against brute-force attacks.
2. **Known-Compromised Blacklists**: Checking passwords against real-world breach and common credential datasets (e.g., SecLists).
3. **Pattern Recognition**: Detecting obvious human patterns such as character repetitions (`aaaaaaa`), sequential runs (`123456`, `abcdef`), and keyboard walks (`qwerty`).
4. **Local Privacy**: Performing all evaluations locally in memory without persisting passwords to disk or transmitting them across the network.
5. **Explainable Findings**: Providing actionable advice and transparent risk tiers rather than an arbitrary percentage score.

---

## 🎯 Current Status & Implementation

The project is developed in staged milestones and is currently **under active development (Phase 1 Prototype)**. The codebase is actively evolving from an initial proof-of-concept into a decoupled, modular architecture.

### What's Currently Working (Phase 1 Prototype)
- **Local Dataset Verification**: Scans candidate passwords against a local list of common credentials (`top-20-common-SSH-passwords.txt`).
- **Character Breakdown**: Computes detailed composition metrics (uppercase, lowercase, digits, special characters, spaces, and total length).
- **Interactive Terminal Interface**: Simple interactive CLI prompt with exit condition (`0`).
- **Bounded Buffer Reads**: Enforces buffer safety on terminal input.

### In Active Development / Next Up
- Refactoring the interactive prompt into a robust loop (replacing recursive calls and resetting evaluation state between runs).
- Transitioning to modular files (`main.c`, `analyzer.c`, `patterns.c`, `database.c`, `scoring.c`).
- Implementing the sequential run and repeated-character detection algorithms.

---

## 🗺️ Project Roadmap

| Phase | Milestone | Features & Capabilities | Status |
| :---: | :--- | :--- | :---: |
| **1** | **Core Auditor** | Input validation, length analysis, character distribution, local dataset lookup, basic repetition detection. | 🔄 Active Prototype |
| **2** | **Pattern Intelligence** | Numeric/alphabetic sequence detector (forward/reverse), QWERTY keyboard walk detection, case-insensitive dataset matching. | ⏳ Planned |
| **3** | **Utility & Reports** | OS-level CSPRNG password generator, exportable sanitized text report (findings only, never raw passwords), configurable dataset paths. | ⏳ Planned |
| **4** | **Advanced Breach Check** | Privacy-preserving exposure checking via Have I Been Pwned (HIBP) API using SHA-1 range queries ($k$-anonymity). | ⏳ Roadmap |
| **5** | **Release Quality** | Modular C source separation, automated test suite, Makefile/CMake build configurations. | ⏳ Roadmap |

---

## 🏗️ Proposed System Architecture

To ensure maintainability and testability, the codebase is transitioning from a single-file prototype into clear, decoupled modules:

```text
PASS-GUARD/
├── .gitignore                      # Git ignore rules (binaries, PDFs, IDE, OS files)
├── README.md                       # Repository documentation
├── PASSGUARD_Project_Concept_Document.pdf # Specification & project concept blueprint
├── next-feature-updates.txt        # Feature tracking & planned SecLists integration
├── main.c                          # Current application entry point & auditor logic
├── Common Passwords/               # Local password datasets & wordlists
│   └── top-20-common-SSH-passwords.txt
└── src/                            # Target modular source code (Milestone Refactor)
    ├── main.c                      # CLI menu loop and user flow control
    ├── analyzer.c / .h             # Length & character metrics coordinator
    ├── patterns.c / .h             # Repetitions, sequential runs, keyboard patterns
    ├── database.c / .h             # Safe file streaming & dictionary lookups
    ├── scoring.c / .h              # Explainable heuristic risk categorisation
    ├── generator.c / .h            # Cryptographically secure random password generator
    └── reports.c / .h              # Sanitised audit report generation
```

### Data Flow Pipeline
$$\text{User Input} \longrightarrow \text{Validation} \longrightarrow \text{Dataset Lookup} \longrightarrow \text{Pattern Analysis} \longrightarrow \text{Risk Synthesis} \longrightarrow \text{Actionable Verdict}$$

---

## 🔒 Security & Privacy Principles

1. **Zero Raw Password Storage**: Passwords remain exclusively in volatile memory during the active audit cycle and are never written to disk, logs, or reports.
2. **Local-First Execution**: The core auditor runs completely offline. No third-party network requests are required for routine checks.
3. **Privacy-Preserving Network Protocol ($k$-Anonymity)**: When remote breach checking (HIBP) is enabled in later phases, only the first 5 characters of the SHA-1 hash are transmitted. The raw password and complete hash never leave the machine.
4. **Honest Risk Categorisation**: No heuristic score can guarantee that a password is uncrackable. Results are presented as risk indicators rather than mathematical proofs of safety.

---

## 🚀 Getting Started

### Prerequisites
- A standard C compiler supporting **C99 / C11** (e.g. `gcc`, `clang`, or MSVC).
- Make or CMake (optional, for build automation).

### Compilation

#### Using GCC (MinGW / MSYS2 / Linux / macOS):
```bash
gcc -Wall -Wextra -std=c11 main.c -o passguard
```

#### Using MSVC (Visual Studio Developer Command Prompt):
```cmd
cl /W4 /std:c11 main.c /Fe:passguard.exe
```

### Running the Auditor

Ensure the `Common Passwords/` directory with `top-20-common-SSH-passwords.txt` is located in the working directory alongside the executable:

```bash
# On Windows
.\passguard.exe

# On Linux / macOS
./passguard
```

---

## 🧪 Demonstration & Test Cases

| Scenario | Input Example | Expected Finding |
| :--- | :--- | :--- |
| **Common Password** | `admin123` | Flagged as found in local breach dataset. |
| **Short Password** | `Ab1!` | Warns about insufficient length (< 8 chars, recommendations for 15+). |
| **Character Repetition** | `aaaaaaa!` | Flagged for excessive repeated character sequence. |
| **Sequential Pattern** | `Password12345` | Sequential number walk (`12345`) identified and flagged. |
| **Robust Passphrase** | `hazel-beacon-quantum-path` | Recognised as strong length-based passphrase despite lack of complex symbols. |

---

## 📚 References & Standards

- **NIST Special Publication 800-63B**: *Digital Identity Guidelines — Authentication and Lifecycle Management*  
  [NIST SP 800-63B-4](https://pages.nist.gov/800-63-4/sp800-63b.html)
- **Have I Been Pwned (HIBP)**: *Pwned Passwords API & k-Anonymity Mathematical Model*  
  [HIBP API Documentation](https://haveibeenpwned.com/API/v3#PwnedPasswords)
- **SecLists**: *Common Credentials & Security Tester Lists by Daniel Miessler*  
  [SecLists GitHub Repository](https://github.com/danielmiessler/SecLists)

---

## 📄 License

This project is created for educational and security portfolio purposes. Distributed under the [MIT License](LICENSE) (or academic equivalent).
