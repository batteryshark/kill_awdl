#!/bin/bash

# Check for root privileges
if [ "$EUID" -ne 0 ]; then
  echo "Please run as root (sudo ./uninstall.sh)"
  exit 1
fi

echo "Unloading LaunchDaemon..."
launchctl unload /Library/LaunchDaemons/com.batteryshark.kill_awdl.plist 2>/dev/null

echo "Removing LaunchDaemon configuration..."
rm /Library/LaunchDaemons/com.batteryshark.kill_awdl.plist

echo "Removing binary..."
rm /usr/local/bin/kill_awdl

echo "Done! kill_awdl has been completely removed."
