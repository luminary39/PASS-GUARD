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
2. **Known-Compromised Blacklists**: Checking passwords against real-world breach and common credential datasets (SecLists, Pwdb, xato.net, NCSC, and annual breach dumps).
3. **Pattern Recognition**: Detecting obvious human patterns such as character repetitions (`aaaaaaa`), sequential runs (`123456`, `abcdef`), and keyboard walks (`qwerty`).
4. **Local Privacy**: Performing all evaluations locally in memory without persisting passwords to disk or transmitting them across the network.
5. **Explainable Findings**: Providing actionable advice and transparent risk tiers rather than an arbitrary percentage score.

---

## 🎯 Current Status & Implementation

The project is developed in staged milestones and is currently **under active development (Phase 1 Prototype)**:
- **`main.c`**: The primary application file and main entry point under active development.
- **`run.c`**: An experimental companion file sharing similar logic, used to explore and benchmark more efficient execution methods for multi-dataset scanning.

### What's Currently Working (Phase 1 Prototype)
- **Local Threat Intelligence Verification**: Evaluates candidate passwords against extensive local breach and common password datasets (featuring 31 curated collections and a deduplicated master dataset of **13,644,552 unique passwords**).
- **Character Breakdown**: Computes detailed composition metrics (uppercase, lowercase, digits, special characters, spaces, and total length).
- **Interactive Terminal Interface**: Simple interactive CLI prompt with exit condition (`0`).
- **Bounded Buffer Reads**: Enforces buffer safety on terminal input.

### In Active Development / Next Up
- Refactoring the interactive prompt into a robust loop (replacing recursive calls and resetting evaluation state between runs).
- Transitioning to modular files (`main.c`, `analyzer.c`, `patterns.c`, `database.c`, `scoring.c`).
- Implementing sequential run and repeated-character detection algorithms.

---

## 📊 Compromised Password Datasets & Master Database

To evaluate user passwords against known real-world leaks and brute-force dictionaries, PASSGUARD references a rich collection of threat-intelligence wordlists stored in `Common Passwords/`.

### How Many Passwords Are Checked Against User Input?

When a user submits a password for evaluation:
- **Total Scanned Entries Across Raw Collections**: **17,593,563 passwords** (17,593,556 non-empty entries across 31 individual datasets).
- **Total Unique Passwords Checked**: **13,644,552 unique passwords**.
- **Redundant Duplicates Eliminated**: **3,949,004 duplicate occurrences** (~22.4% overlap across different breach lists).
- **Consolidated Master Database (GitHub-Compliant Split)**: To comply with GitHub's 100 MB per-file size limitation, the unified 13,644,552-entry master dataset is organized in a dedicated directory `Common Passwords/PASS_GUARD-PASSWORD-MASTER/` split across two files:
  - **`PASS_GUARD-PASSWORD-MASTER-001.txt`**: **96.00 MB** (10,178,443 unique passwords)
  - **`PASS_GUARD-PASSWORD-MASTER-002.txt`**: **33.56 MB** (3,466,109 unique passwords)
  - Both files retain frequency-based ordering (most common credentials like `123456`, `password`, and `admin` appear at the top for near-instant sequential matches).

### Complete Dataset Breakdown

| # | Dataset File | File Size | Total Entries | Unique Passwords Contributed | Description / Source Category |
| :-: | :--- | :---: | :---: | :---: | :--- |
| **M1** | **`PASS_GUARD-PASSWORD-MASTER/PASS_GUARD-PASSWORD-MASTER-001.txt`** | **96.00 MB** | **10,178,443** | **10,178,443** | **Consolidated Master Part 1 (Top ~10.18M unique passwords)** |
| **M2** | **`PASS_GUARD-PASSWORD-MASTER/PASS_GUARD-PASSWORD-MASTER-002.txt`** | **33.56 MB** | **3,466,109** | **3,466,109** | **Consolidated Master Part 2 (Remaining ~3.47M unique passwords)** |
| 1 | `top-passwords-shortlist.txt` | 194 B | 25 | 25 | Critical high-risk top passwords |
| 2 | `top-20-common-SSH-passwords.txt` | 180 B | 22 | 19 | Common default SSH credentials & hardware logins |
| 3 | `worst-passwords-2017-top100-slashdata.txt` | 742 B | 100 | 79 | Top 100 worst passwords (SlashData 2017) |
| 4 | `10k-most-common.txt` | 73.0 KB | 10,001 | 9,898 | Top 10,000 most frequent web credentials |
| 5 | `100k-most-used-passwords-NCSC.txt` | 835.5 KB | 99,840 | 91,062 | UK National Cyber Security Centre (NCSC) breach list |
| 6 | `twentieth_century_dates_1900_2020.txt` | 405.1 KB | 45,012 | 37,945 | Common date combinations (`DDMMYYYY` / `MMDDYYYY`) |
| 7 | `2020-200_most_used_passwords.txt` | 1.6 KB | 197 | 9 | Annual top 200 used passwords (2020) |
| 8 | `2023-200_most_used_passwords.txt` | 1.8 KB | 200 | 39 | Annual top 200 used passwords (2023) |
| 9 | `2024-197_most_used_passwords.txt` | 1.7 KB | 197 | 7 | Annual top 197 used passwords (2024) |
| 10 | `2025-199_most_used_passwords.txt` | 1.8 KB | 199 | 19 | Annual top 199 used passwords (2025 projection) |
| 11 | `500-worst-passwords.txt` | 3.5 KB | 499 | 0 | 500 common worst credentials (fully covered) |
| 12 | `Pwdb_top-1000.txt` | 8.0 KB | 1,000 | 3 | Pwdb leak corpus — Top 1K |
| 13 | `Pwdb_top-10000.txt` | 80.5 KB | 10,000 | 92 | Pwdb leak corpus — Top 10K |
| 14 | `Pwdb_top-100000.txt` | 828.5 KB | 100,000 | 23,997 | Pwdb leak corpus — Top 100K |
| 15 | `Pwdb_top-1000000.txt` | 8.76 MB | 1,000,000 | 862,695 | Pwdb leak corpus — Top 1 Million |
| 16 | `Pwdb_top-10000000.txt` | 94.46 MB | 10,000,000 | 8,991,756 | Pwdb leak corpus — Top 10 Million |
| 17 | `darkweb2017_top-10.txt` | 81 B | 10 | 0 | Darkweb dumps (2017) — Top 10 (fully covered) |
| 18 | `darkweb2017_top-100.txt` | 802 B | 99 | 0 | Darkweb dumps (2017) — Top 100 (fully covered) |
| 19 | `darkweb2017_top-1000.txt` | 8.16 KB | 999 | 0 | Darkweb dumps (2017) — Top 1K (fully covered) |
| 20 | `darkweb2017_top-10000.txt` | 82.6 KB | 9,999 | 10 | Darkweb dumps (2017) — Top 10K |
| 21 | `medical-devices.txt` | 1.29 KB | 173 | 128 | Default and hardcoded medical device passwords |
| 22 | `probable-v2_top-12000.txt` | 100.2 KB | 12,645 | 0 | Probable-Wordlists v2 Top 12K (fully covered) |
| 23 | `probable-v2_top-1575.txt` | 12.3 KB | 1,575 | 0 | Probable-Wordlists v2 Top 1,575 (fully covered) |
| 24 | `probable-v2_top-207.txt` | 1.62 KB | 207 | 0 | Probable-Wordlists v2 Top 207 (fully covered) |
| 25 | `xato-net-10-million-passwords-10.txt` | 75 B | 10 | 0 | xato.net research set — Top 10 (fully covered) |
| 26 | `xato-net-10-million-passwords-100.txt` | 738 B | 100 | 0 | xato.net research set — Top 100 (fully covered) |
| 27 | `xato-net-10-million-passwords-1000.txt` | 7.4 KB | 1,000 | 0 | xato.net research set — Top 1K (fully covered) |
| 28 | `xato-net-10-million-passwords-10000.txt` | 76.5 KB | 10,000 | 5 | xato.net research set — Top 10K |
| 29 | `xato-net-10-million-passwords-100000.txt` | 781.9 KB | 100,000 | 1,540 | xato.net research set — Top 100K |
| 30 | `xato-net-10-million-passwords-1000000.txt` | 8.56 MB | 1,000,000 | 374,824 | xato.net research set — Top 1 Million |
| 31 | `xato-net-10-million-passwords.txt` | 48.31 MB | 5,189,454 | 3,250,400 | xato.net research set — Full 5.18M corpus |

---

## 🏗️ Project Architecture & Repository Structure

### Current Repository Layout
```text
PASS-GUARD/
├── .gitignore                                 # Git ignore patterns (binaries, IDE artifacts, OS files)
├── .vscode/                                   # VS Code editor configuration
├── LICENSE                                    # License agreement
├── README.md                                  # Comprehensive documentation & dataset analysis
├── PASSGUARD_Project_Concept_Document.pdf    # Concept blueprint & architectural specification
├── next-feature-updates.txt                   # Planned feature queue & roadmap notes
├── main.c                                     # Primary application entry point & auditor logic (in development)
├── main.exe                                   # Compiled binary for main.c
├── run.c                                      # Companion test file evaluating efficient multi-dataset scanning
├── run.exe                                    # Compiled binary for run.c
└── Common Passwords/                          # Threat intelligence datasets & master wordlists
    ├── PASS_GUARD-PASSWORD-MASTER/            # Dedicated directory for GitHub-compliant split master wordlist
    │   ├── PASS_GUARD-PASSWORD-MASTER-001.txt # Part 1 (96.00 MB, 10,178,443 unique passwords)
    │   └── PASS_GUARD-PASSWORD-MASTER-002.txt # Part 2 (33.56 MB, 3,466,109 unique passwords)
    ├── 100k-most-used-passwords-NCSC.txt
    ├── 10k-most-common.txt
    ├── 2020-200_most_used_passwords.txt
    ├── 2023-200_most_used_passwords.txt
    ├── 2024-197_most_used_passwords.txt
    ├── 2025-199_most_used_passwords.txt
    ├── 500-worst-passwords.txt
    ├── darkweb2017_top-*.txt                  # (Top 10, 100, 1000, 10000 dumps)
    ├── medical-devices.txt
    ├── probable-v2_top-*.txt                  # (Top 207, 1575, 12000 lists)
    ├── Pwdb_top-*.txt                         # (Top 1K, 10K, 100K, 1M, 10M dumps)
    ├── top-20-common-SSH-passwords.txt
    ├── top-passwords-shortlist.txt
    ├── twentieth_century_dates_1900_2020.txt
    ├── worst-passwords-2017-top100-slashdata.txt
    └── xato-net-10-million-passwords*.txt     # (Subsets and full 5.18M list)
```

### Planned Modular Target Architecture (`src/`)
As the project advances into subsequent phases, the monolithic prototypes will transition into decoupled modules:
```text
src/
├── main.c                 # CLI menu loop and user flow orchestration
├── analyzer.c / .h        # Character distribution & length metrics
├── patterns.c / .h        # Repetitions, sequential runs, keyboard patterns
├── database.c / .h        # Memory-efficient file streaming & hash/binary lookups
├── scoring.c / .h         # Explainable risk categorisation engine
├── generator.c / .h       # Cryptographically secure random password generator
└── reports.c / .h         # Sanitised audit report generator
```

### Data Flow Pipeline
$$\text{User Input} \longrightarrow \text{Validation} \longrightarrow \text{Dataset Lookup (13.6M Passwords)} \longrightarrow \text{Pattern Analysis} \longrightarrow \text{Risk Synthesis} \longrightarrow \text{Actionable Verdict}$$

---

## 🗺️ Project Roadmap

| Phase | Milestone | Features & Capabilities | Status |
| :---: | :--- | :--- | :---: |
| **1** | **Core Auditor** | Input validation, length analysis, character distribution, local dataset lookup (13.6M breach entries), basic repetition detection. | 🔄 Active Prototype |
| **2** | **Pattern Intelligence** | Numeric/alphabetic sequence detector (forward/reverse), QWERTY keyboard walk detection, case-insensitive dataset matching. | ⏳ Planned |
| **3** | **Utility & Reports** | OS-level CSPRNG password generator, exportable sanitized text report (findings only, never raw passwords), configurable dataset paths. | ⏳ Planned |
| **4** | **Advanced Breach Check** | Privacy-preserving exposure checking via Have I Been Pwned (HIBP) API using SHA-1 range queries ($k$-anonymity). | ⏳ Roadmap |
| **5** | **Release Quality** | Modular C source separation (`src/`), automated test suite, Makefile/CMake build configurations. | ⏳ Roadmap |

---

## 🔒 Security & Privacy Principles

1. **Zero Raw Password Storage**: Passwords remain exclusively in volatile memory during the active audit cycle and are never written to disk, logs, or reports.
2. **Local-First Execution**: The core auditor runs completely offline. No third-party network requests are required for routine checks.
3. **Privacy-Preserving Network Protocol ($k$-Anonymity)**: When remote breach checking (HIBP) is enabled in later phases, only the first 5 characters of the SHA-1 hash are transmitted. The raw password and complete hash never leave the machine.
4. **Honest Risk Categorisation**: No heuristic score can guarantee that a password is uncrackable. Results are presented as risk indicators rather than mathematical proofs of safety.

---

## 🚀 Getting Started

### Prerequisites
- A standard C compiler supporting **C99 / C11** (e.g., `gcc`, `clang`, or MSVC).
- Make or CMake (optional, for build automation).

### Compilation

#### Using GCC (MinGW / MSYS2 / Linux / macOS):
```bash
# Compile primary application
gcc -Wall -Wextra -std=c11 main.c -o passguard

# Compile experimental runner (optional)
gcc -Wall -Wextra -std=c11 run.c -o run_test
```

#### Using MSVC (Visual Studio Developer Command Prompt):
```cmd
# Compile primary application
cl /W4 /std:c11 main.c /Fe:passguard.exe

# Compile experimental runner (optional)
cl /W4 /std:c11 run.c /Fe:run_test.exe
```

### Running the Auditor

Ensure the `Common Passwords/` directory is located in the working directory alongside the executable:

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

PASS-GUARD is available for educational, research, and personal learning purposes only.

Commercial use, resale, or integration into commercial products is prohibited without prior written permission from the author.

Copyright © 2026 Sadman Sakib.
