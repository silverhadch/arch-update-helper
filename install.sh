#!/bin/bash

set -e  # Exit immediately if a command exits with a non-zero status

# Paths
BINARY_NAME="Arch-Update-Helper"
CONFIG_FILE="config/arch-update-helper"
DESKTOP_FILE="arch-update-helper.desktop"
BUILD_DIR="build"

# Installation paths
BIN_DIR="/usr/bin"
CONFIG_DIR="/etc/skel/.config"
AUTOSTART_DIR="/etc/xdg/autostart"

echo "Starting installation of $BINARY_NAME..."

# Step 1: Build the binary
echo "Building the project..."
mkdir -p "$BUILD_DIR"
cmake -B"$BUILD_DIR" -H. -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR"

# Step 2: Install the binary
echo "Installing binary to $BIN_DIR..."
sudo install -Dm755 "$BUILD_DIR/$BINARY_NAME" "$BIN_DIR/$BINARY_NAME"

# Step 3: Install the configuration file
echo "Installing configuration file to $CONFIG_DIR..."
sudo install -Dm644 "$CONFIG_FILE" "$CONFIG_DIR/arch-update-helper"

# Step 4: Install the autostart .desktop file
echo "Installing .desktop file to $AUTOSTART_DIR..."
sudo install -Dm644 "$DESKTOP_FILE" "$AUTOSTART_DIR/arch-update-helper.desktop"

# Optional: Copy config for current user if not already present
if [[ ! -f "$HOME/.config/arch-update-helper" ]]; then
    echo "Copying default config to current user's .config directory..."
    mkdir -p "$HOME/.config"
    cp "$CONFIG_FILE" "$HOME/.config/arch-update-helper"
fi

echo "Installation complete!"
echo "Binary installed to $BIN_DIR/$BINARY_NAME"
echo "Configuration file installed to $CONFIG_DIR/arch-update-helper"
echo "Autostart file installed to $AUTOSTART_DIR/arch-update-helper.desktop"

