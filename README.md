# kill_awdl

A minimal, high-performance C utility to permanently disable the `awdl0` (Apple Wireless Direct Link) interface on macOS.

## Why?

The `awdl0` interface is used for AirDrop, AirPlay, and Universal Control. However, it is known to cause significant latency spikes and interference, particularly when using real-time streaming applications like Parsec, Moonlight, or online gaming.

macOS frequently re-enables this interface automatically. This utility monitors the interface state and instantly disables it whenever it comes up.

## Features

- **Extremely Lightweight**: Written in C, uses negligible system resources.
- **Fast Response**: Checks interface state every 100ms.
- **Direct Kernel Interaction**: Uses `ioctl` sockets for maximum efficiency, avoiding expensive shell command spawning.

## Compilation

Compile the program using `clang`:

```bash
clang -O3 -o kill_awdl kill_awdl.c
```

## Usage

Run the executable with `sudo` (required to control network interfaces):

```bash
sudo ./kill_awdl
```

Keep the terminal window open, or run it in a `tmux`/`screen` session to keep it active in the background.
