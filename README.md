
# arch-update-helper

**A Systray Utility for Checking Arch Linux Updates and Installing Them**

---

## Features

- Automatically checks for updates every **10 minutes** using an AUR helper.
- Sends notifications and updates the systray icon when updates are available.
- Clickable icon to open a terminal and run the AUR helper, even if no updates are available.
- **Default terminal**: `kitty`  
  **Default AUR helper**: `yay`  
  (Customizable via a simple configuration file.)

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/arch-update-helper.git
   cd arch-update-helper
   ```
2. Run the installation script:
   ```bash
   sudo ./install.sh
   ```
3. The installation script performs the following:
   - Installs the binary to `/usr/bin/Arch-Update-Helper`.
   - Adds a default configuration file to `/etc/skel/.config/arch-update-helper`.
   - Creates a user-specific configuration file in `~/.config/arch-update-helper` for the installing user.
   - Adds a `.desktop` file to `/etc/xdg/autostart` for system-wide autostart functionality.

4. **Configuration for Multiple Users**:
   - New users will inherit the default config from `/etc/skel`.
   - Existing users must manually create the configuration file in their home directories.

---

## Configuration

Customize the terminal and AUR helper by editing the configuration file at `~/.config/arch-update-helper`.

### Default Configuration:
```bash
terminal=kitty
aur_helper=yay
```

### Example:
If you want to use `alacritty` as your terminal and `paru` as your AUR helper:
```bash
terminal=alacritty
aur_helper=paru
```

Any other terminal emulator or AUR helper must be explicitly set in this file.

---

## License

This project is licensed under the **GPLv3 License**.

---

## Contributing

Contributions and feedback are welcome! Open a pull request or issue to share improvements or suggestions.
