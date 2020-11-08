# DigDef: Dig and Defend

Dig the lunar grounds and defend your miner from enemies!

A submission for GitHub [Game Off 2020](https://itch.io/jam/game-off-2020)
under the theme "Moonshot".

## Build

Clone this repo with:

```
git clone https://github.com/deltadex7/digdef.git --recurse-submodules
```

This will also clone raylib v3.0 from its [source][raylib-src]

Build script taken from [dependency-less raylib projects scripts][rl-scr].

### Dependencies

The only dependency is the C compiler. On Windows, you'll need to install
[Visual Studio][visual-studio], or its standalone [build tools][vs-tools].
Make sure the compiler path is set in line 37 of
[`build-windows.bat`](build-windows.bat).

### Script customization

First of all, the scripts have a few variables at the very top, which
are supposed to be configured for each project separately:

- `GAME_NAME` variable is used for the executable name.
- `SOURCES` is a list of .c source files, divided by spaces, which are
  going to be compiled and linked with raylib to create the final
  executable. You can use wildcards, so if you have all your .c files
  in a directory called `src`, you can just set `SOURCES` to
  `../../src/*.c`. Note: the paths should be either absolute, or
  relative to `builds/platform`, hence `../../`, or relative to
  workspace directory: `./`.
- `RAYLIB_SRC` should point to the raylib/src directory.
  In this case, it points to `./lib/raylib/src`, which links directly to
  the original raylib repo as a submodule.
- `CC` and `GCC` defines the compiler to build the program and raylib
  respectively. raylib uses `GCC`, as it is a C library. `CC` should be a
  C++ compiler, like `g++` or `clang++`. They can be overridden at execution
  by passing in the environment variables before executing the script.

### Compilation flags

- `-Os` (`/O1` with MSVC, `-O2` with clang\*) is used for release
  builds, to save space. Since it's a good practice to make your games
  run on the slowest possible systems, only a few games would benefit
  from additional runtime performance on almost all systems. Other
  flags: `-flto` (`/GL` and `/LTCG` for MSVC) in release builds, `-O0 -g` (`/Od /Zi` for MSVC) in debug builds.
- `-Wall -Wextra -Wpedantic` (`/Wall` for MSVC) are used for warnings.

\* Clang 7.0.1 seems to have problems compiling with `-flto` and `-Os`
enabled at the same time, so `-Os` is replaced with `-O2` for clang.

## Command line arguments

The build scripts accept some flags, which can be given either one at
a time (`-d -c -r`) or in bunches (`-dcr`). Here's a description of
all of the flags.

- `-h` Describes all the flags, and a few example commands
- `-d` Faster builds that have debug symbols, and enable warnings
- `-u` Run upx\* on the executable after compilation (before -r)
- `-r` Run the executable after compilation
- `-c` Remove the temp/(debug|release) directory, ie. full recompile
- `-q` Suppress this script's informational prints
- `-qq` Suppress all prints, complete silence
- `-v` cl.exe normally prints out a lot of superficial information, as
  well as the MSVC build environment activation scripts, but these are
  mostly suppressed by default. If you do want to see everything, use
  this flag.

\* This is mostly here to make building simple "shipping" versions
easier, and it's a very small bit in the build scripts. The option
requires that you have upx installed and on your path, of course.

#### Examples

| What the command does                                       | Command                           |
| ----------------------------------------------------------- | --------------------------------- |
| Build a release build, on Windows                           | `build-windows.bat`               |
| Build a release build, full recompile, on Linux             | `./build-linux.sh -c`             |
| Build a debug build using clang and run, on macOS           | `CC=clang++ ./build-osx.sh -d -r` |
| Build in debug, run, don't print at all, on Linux with `sh` | `sh build-linux.sh -drqq`         |

[visual-studio]: https://visualstudio.microsoft.com/downloads/
[vs-tools]: https://visualstudio.microsoft.com/downloads/
[rl-scr]: https://github.com/raysan5/raylib/tree/master/projects/scripts
[raylib-src]: https://github.com/raysan5/raylib/tree/3.0.0
