# **Arch-Update-Helper**  

**A Systray Utility for Checking Arch Linux Updates and Installing Them**  

---

## **Features**  

- Automatically checks for updates every **10 minutes** using your chosen AUR helper.  
- Sends notifications and updates the systray icon when updates are available.  
- Clickable icon that opens a terminal to run the AUR helper, even if no updates are available.  
- **Default terminal**: `kitty`  
  **Default AUR helper**: `yay`  
  *(Customizable via a simple two-line configuration file.)*  

---

## **Installation**  

1. **Clone the repository:**  
   ```bash
   git clone https://github.com/silverhadch/arch-update-helper.git
   cd arch-update-helper
   ```  

2. **Run the installation script:**  
   ```bash
   ./install.sh
   ```  

3. **What the installation script does:**  
   - Compiles the binary.  
   - Installs the binary to `/usr/bin/Arch-Update-Helper`.  
   - Adds a default configuration file to `/etc/skel/.config/arch-update-helper`.  
   - Creates a user-specific configuration file in `~/.config/arch-update-helper` for the user running the script.  
   - Adds a `.desktop` file to `/etc/xdg/autostart` for system-wide autostart functionality.  

4. **Configuration for multiple users:**  
   - A default backup configuration is stored in `/etc/skel`.  
   - If other users want to customize the AUR helper or terminal, a two-line configuration file will be automatically created in their home directories upon their first use of the helper.  

---

## **Configuration**  

You can customize the terminal emulator and AUR helper by editing (or creating, if it doesn't exist) the configuration file at `~/.config/arch-update-helper`.  

### **Default Configuration:**  
```bash
terminal=kitty
aur_helper=yay
```  

### **Example:**  
To use `alacritty` as your terminal emulator and `paru` as your AUR helper:  
```bash
terminal=alacritty
aur_helper=paru
```  

Other terminal emulators or AUR helpers must be explicitly set in this file.  

### **Tested AUR Helpers and Terminals:**  
- **AUR Helpers**: `paru`, `yay`  
- **Terminals**: `gnome-terminal`, `foot`, `kitty`, `alacritty`, `xterm`  

> **Note:** `konsole` was tested but failed to close automatically.  

---

## **License**  

This project is licensed under the **GPLv3 License**.  

---

## **Contributing**  

Contributions and feedback are welcome! Open a pull request or an issue to share improvements or suggestions.  

