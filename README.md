# k-shell 🐚

![Language](https://img.shields.io/badge/language-C-blue)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20WSL-orange)
![Status](https://img.shields.io/badge/status-Phase%201%20Complete-green)

A custom Unix shell implementation written in C.
Designed to explore core Operating System concepts including process creation, memory management, and system calls.

![k-shell Demo](assets/k-shell.png)

## 🚀 Features

**Phase 1: The Foundation (Current)**
* **REPL Interface:** A robust Read-Eval-Print Loop handling interactive user input.
* **Process Execution:** Uses `fork()`, `execvp()`, and `wait()` to run external programs (e.g., `ls`, `grep`, `git`).
* **Native File Management:** Built-in implementation of `cp`, `mv`, `rm`, `touch`, `mkdir`, and `rmdir` using standard C I/O streams.
* **Environment Control:** Ability to modify the shell environment dynamically using `export` and `unset`.
* **Productivity Tools:** Includes `mkcd` (atomic make-and-enter) and a built-in `calc` (arithmetic engine).
* **Documentation System:** Context-aware help system (e.g., typing `help cd` gives specific usage examples).
* **Visuals:** Colored ANSI output and custom `kfetch` system branding.

## 🛠️ Built-in Commands

### Core & Navigation
| Command | Description |
| :--- | :--- |
| `cd <dir>` | Change the current working directory. |
| `mkcd <dir>` | Create a directory and immediately enter it. |
| `pwd` | Print the current working directory. |
| `exit` | Terminate the shell session safely. |
| `help [cmd]` | Display the user guide or specific command manual. |

### File Management
| Command | Description |
| :--- | :--- |
| `touch <file>` | Create a new empty file or update timestamp. |
| `rm <file>` | Delete a file permanently. |
| `mkdir <dir>` | Create a new directory. |
| `rmdir <dir>` | Remove an empty directory. |
| `cat <file>` | Display file contents to the terminal. |
| `cp <src> <dst>` | Copy a file from source to destination. |
| `mv <src> <dst>` | Move or rename a file. |

### Utilities & System
| Command | Description |
| :--- | :--- |
| `clear` | Clear the terminal screen and scrollback. |
| `whoami` | Display the current username. |
| `echo <text>` | Print text to the standard output. |
| `type <cmd>` | Identify if a command is a built-in or external executable. |
| `calc <expr>` | Perform basic arithmetic (e.g., `calc 10 + 5`). |
| `kfetch` | Display system information and shell branding. |

### Environment
| Command | Description |
| :--- | :--- |
| `env` | Print all environment variables. |
| `export <k=v>` | Create or update an environment variable. |
| `unset <key>` | Remove an environment variable. |

## ⚙️ Installation & Usage

### Prerequisites
* **OS:** Linux (Ubuntu/Fedora) or Windows (via WSL2).
* **Compiler:** GCC.
* **Build Tool:** Make.

### Building the Shell
1.  Clone the repository:
    ```bash
    git clone git@github.com:Kedrich/k-shell.git
    cd k-shell
    ```

2.  Compile using the Makefile:
    ```bash
    make
    ```

3.  Run the shell:
    ```bash
    ./k-shell
    ```

## 🧠 Learning Objectives
The primary goal of this project is to demystify Operating System internals by building them from scratch.
**Core Objectives:**
* **To understand System Calls:** specifically how `fork`, `exec`, and `wait` interact with the kernel.
* **To practice Low-Level String Parsing:** handling raw C strings without high-level abstractions.
* **To master Process Management:** managing the lifecycle of child processes and signals.
* **To explore Memory Management:** (Upcoming in Phase 2) transitioning from stack to heap allocation.

## 🗺️ Roadmap
- [x] **Phase 1:** Basic Execution & Built-ins (Completed)
- [ ] **Phase 2:** Dynamic Memory Management (Heap allocation)
- [ ] **Phase 3:** I/O Redirection (`>`, `<`) & Pipes (`|`)
- [ ] **Phase 4:** Command History & Configuration

---
*Created by Kedrich.*