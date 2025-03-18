# Post Install

Assuming you just finished [arch install guide and you're looking for more information]("./installation.md")

## 1. Make install more usable

### 1.1 Add users group to suders

Switch to super user via `su` then run `EDITOR=nvim visudo`.
Uncomment `%wheel ALL=(ALL:ALL) ALL`. Users in group wheel are now sudoers.

### 1.2 Pacman mirrors and keyring

#### 1.2.1 Mirrors

Edit `/etc/pacman,d/mirrorlist` and add mirrors. See https://wiki.archlinux.org/title/Mirrors

#### 1.2.2 Keyring

```sh
pamcan-key --init
pacman-key --populate
```

### 1.3 AUR helper

Install `yay` via

```sh
sudo pacman -S --needed git base-devel && git clone https://aur.archlinux.org/yay-bin.git && cd yay-bin && makepkg -si
```

## 2. Quality of life changes

### 2.1 Change hostname of system

Edit `/etc/hostname`. Only make it your system hostname.

```
hostname
```

## 3. config

I use a `config` utility for installing rest of system config.

1. Install git

```sh
pacman -S git jq
```

2. Pull config repo

```sh
git clone https://github.com/burkkyy/config.git
```

3. Init config

```sh
cd config
./config.sh init
```
