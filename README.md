# kill_awdl

A minimal, high-performance C utility to permanently disable the `awdl0` (Apple Wireless Direct Link) interface on macOS.

## Why?

The `awdl0` interface is used for AirDrop, AirPlay, and Universal Control. However, it is known to cause significant latency spikes and interference, particularly when using real-time streaming applications like Parsec, Moonlight, or online gaming.

macOS frequently re-enables this interface automatically. This utility monitors the interface state and instantly disables it whenever it comes up.

## Features

- **Extremely Lightweight**: Written in C, uses negligible system resources.
- **Fast Response**: Checks interface state every 100ms.
- **Direct Kernel Interaction**: Uses `ioctl` sockets for maximum efficiency, avoiding expensive shell command spawning.

## Installation (The "Hardcore" Way)

To install this as a system-level daemon that runs automatically at boot (and restarts if it crashes):

1. Clone the repository:
   ```bash
   git clone https://github.com/batteryshark/kill_awdl.git
   cd kill_awdl
   ```

2. Run the install script:
   ```bash
   sudo ./install.sh
   ```

This will:
- Compile the program.
- Install the binary to `/usr/local/bin/kill_awdl`.
- Install a LaunchDaemon to `/Library/LaunchDaemons/`.
- Load the service immediately.

## Uninstallation

To remove the daemon and the binary:

```bash
sudo ./uninstall.sh
```

## Manual Usage

If you prefer not to install it permanently, you can compile and run it manually:

```bash
clang -O3 -o kill_awdl kill_awdl.c
sudo ./kill_awdl
```
