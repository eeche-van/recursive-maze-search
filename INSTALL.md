# 🛠️ Installation Guide

Welcome! This guide will help you set up the development environment required to build and run this project.

This project is written in **C** and uses the **Simple DirectMedia Layer (SDL2)** graphics library.

Whether you're completely new to C programming or just getting started with SDL2, follow the steps below and you should have everything working within a few minutes.

---

# 📋 Requirements

Before running this project, make sure you have:

- Windows 10 or Windows 11
- Visual Studio Code
- MSYS2
- GCC Compiler (MinGW-w64)
- SDL2 Library

---

# Step 1 — Install Visual Studio Code

Download Visual Studio Code from:

https://code.visualstudio.com/

After installation, install the following extension:

- C/C++ (Microsoft)

This provides:

- IntelliSense
- Code completion
- Debugging
- Compiler integration

---

# Step 2 — Install MSYS2

Download MSYS2:

https://www.msys2.org/

Install using the default location:

```text
C:\msys64
```

Once installed, open:

```text
MSYS2 UCRT64
```

> ⚠️ Do NOT use the "MSYS" terminal.
>
> Use **UCRT64** for this project.

---

# Step 3 — Update MSYS2

Inside the UCRT64 terminal, run:

```bash
pacman -Syu
```

If prompted to close the terminal, do so.

Reopen **MSYS2 UCRT64** and run:

```bash
pacman -Syu
```

again.

---

# Step 4 — Install the Compiler

Install GCC and build tools by simply copy paste this command and then proceed with 'Enter' button to download all the ucrt64 repositories.

```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

This installs:

- GCC
- G++
- GDB
- Make
- pkg-config

Verify installation:

```bash
gcc --version
```

---

# Step 5 — Install SDL2

Install SDL2 using:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-SDL2
```

Optional libraries (not required for this project):

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-SDL2_image
pacman -S --needed mingw-w64-ucrt-x86_64-SDL2_ttf
pacman -S --needed mingw-w64-ucrt-x86_64-SDL2_mixer
```

---

# Step 6 — Add GCC to Windows PATH

Add the following directory to your Windows User PATH.

```text
C:\msys64\ucrt64\bin
```

To do this:

1. Search **Environment Variables**
2. Open **Edit the system environment variables**
3. Click **Environment Variables**
4. Under User Variables, select **Path**
5. Click **Edit**
6. Click **New**
7. Add

```text
C:\msys64\ucrt64\bin
```

8. Restart VS Code.

---

# Step 7 — Verify the Installation

Open a terminal and run:
```bash
gcc --version
```

You should see something similar to:
```text
gcc (Rev...)
```

Next,
```bash
pkg-config --modversion sdl2
```

should output the installed SDL2 version.

Finally,
```bash
pkg-config --cflags --libs sdl2
```

should return compiler and linker flags instead of an error.

---

# Step 8 — Clone this Repository

Clone the repository. Change YOUR_USERNAME with your GitHub username.
```bash
git clone https://github.com/YOUR_USERNAME/recursive-maze-search.git
```

Move into the project folder.
```bash
cd recursive-maze-search
```

---

# Step 9 — Build the Project

Compile using GCC.
```bash
gcc mazealg.c -o maze.exe $(pkg-config --cflags --libs sdl2)
```
---
# Step 10 — Run
Execute the application.
```bash
./maze.exe
```
The SDL window should open.
---

# 🧩 Common Problems

## Issue 1: "stdio.h cannot be found"

Your compiler has not been installed correctly.

Run:

```bash
gcc --version
```

If this fails, reinstall the GCC toolchain.

---

## Issue 2: "SDL2/SDL.h cannot be found"

SDL2 has not been installed.

Install it using:

```bash
pacman -S mingw-w64-ucrt-x86_64-SDL2
```

---

## Issue 3: "gcc is not recognized"

The compiler is not in your PATH.

Add:

```text
C:\msys64\ucrt64\bin
```

to your Windows PATH.

Restart VS Code.

---

## Issue 4: VS Code still shows red squiggles

Open Command Palette.

```
Ctrl + Shift + P
```

Run

```
C/C++: Reset IntelliSense Database
```

then reload the VS Code window.

---

# 📚 Learning Resources

If you're new to C or SDL2, these resources are excellent places to start.

### C Programming

https://www.learn-c.org/

### SDL2 Documentation

https://wiki.libsdl.org/

### Lazy Foo' Productions SDL2 Tutorials

https://lazyfoo.net/tutorials/SDL/

---

# 🚀 Next Steps

Once everything is working, try extending the project by implementing:

- Breadth-First Search (BFS)
- A* Pathfinding
- Random Maze Generation
- Search Animation
- Adjustable Grid Sizes
- Performance Statistics

Experimenting with these features is a great way to deepen your understanding of algorithms, graphics programming, and software design.

---

Happy coding! 🎉

If you find this project helpful or have suggestions for improvements, feel free to open an issue or contact me.
