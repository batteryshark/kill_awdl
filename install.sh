#!/bin/bash

# Check for root privileges
if [ "$EUID" -ne 0 ]; then
  echo "Please run as root (sudo ./install.sh)"
  exit 1
fi

echo "Compiling kill_awdl..."
clang -O3 -o kill_awdl kill_awdl.c

echo "Installing binary to /usr/local/bin/..."
mv kill_awdl /usr/local/bin/
chmod 755 /usr/local/bin/kill_awdl

echo "Installing LaunchDaemon..."
cp com.batteryshark.kill_awdl.plist /Library/LaunchDaemons/
chmod 644 /Library/LaunchDaemons/com.batteryshark.kill_awdl.plist
chown root:wheel /Library/LaunchDaemons/com.batteryshark.kill_awdl.plist

echo "Loading LaunchDaemon..."
# Unload if it was already loaded to force a refresh
launchctl unload /Library/LaunchDaemons/com.batteryshark.kill_awdl.plist 2>/dev/null
launchctl load /Library/LaunchDaemons/com.batteryshark.kill_awdl.plist

echo "Done! kill_awdl is now running and will start automatically at boot."
