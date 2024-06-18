# Installing Arch
I do not recommend using this document to learn how to install arch. This document is to quickly look up info for reinstalling arch. 
This document assumes you want to install arch with an encrypted drive and lvm. Installing a GUI is NOT included. See `dwm.md` for installing and configuring dwm, otherwise your on your own(i.e go to the arch wiki).

## 1.0 Setting up install
### 1.1 Burn ISO to USB
Download arch ISO from one of the [mirrors.](https://archlinux.org/download/)

```bash
sudo dd bs=4M if=/path/to/arch.iso of=/path/to/usb status=progress oflag=sync
```
Use `sudo fdisk -l` to find path to a usb device.
> NOTE: This assumes you already have a suitable usb flash drive plugged in.

### 1.2 Boot off flash drive
While booting off target system open boot menu to select usb.
(`<ESC>`, `<F2>`, `<F10>` or `<F12>` to open boot menu)

### 1.3 Connecting to Internet
If you are already connected via eth, skip this step.

#### 1.3.1 Get interface
Run `ip a` to see all interfaces, then find your wifi interface.

Ex.
```bash
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host
       valid_lft forever preferred_lft forever
2: wlan0: <BROADCAST,MULTICAST> mtu 1500 qdisc fq_codel state DOWN group default qlen 1000
    link/ether aa:bb:cc:dd:ee:ff brd ff:ff:ff:ff:ff:ff
```

In this example `wlan0` is the wifi interface.

#### 1.3.2 Connect via wifi
Replace `i` with the name of your interface.

```bash
iwctl station i get-networks
iwctl --passphrase "*Network Password*" station i connect *Network Name* 
```
> NOTE: This method won't work after an arch install unless you install `iw`

## 2.0 Set up storage 
This step will **wipe your disk**. This section assumes you want LVM partitions

### 2.1 Find block device to install onto
Use `fdisk -l` or `lsblk` to find a block device to install arch on.
`/dev/sda1` is most likely not a block device, but rather a partition of a block device `/dev/sda`.

### 2.2 Partition the block device
Replace `sdX` with your choose block device. This also might be `nvme0n1`.

Lanch `fdisk` utility into `sdX`
```bash
fdisk /dev/sdX
```

In the `fdisk` utility:
```bash
n   # new partition
default
default
+1G     # create partition with 1G

n   # new partition
default
default
+1G     # create partiton with 1G

p       # prints partitions, check for 2 partitons 1G each
n 
default 
default 
default 
t       # set type of partiton
default 
44      # set type to LVM 

p       # check last partiton takes up rest of drive
w       # write changes to drive
```

### 2.3 Format Partitions
Replace `sdX` with your first partition and `sdY` with your second partition

```bash
mkfs.fat -F32 /dev/sdX
mkfs.ext4 /dev/sdY
```

If you dont want an encrypted drive, skip 3.4. 

If you are not using LVM, go to [wiki](https://wiki.archlinux.org/title/Installation_guide) for info.

### 2.4 Setting up encrypted Partition (optional)
Replace `sdX` with target partiton.

```bash
cryptsetup luksFormat /dev/sdX
```

To open(unencrypt) disk:
```bash
cryptsetup open --type luks /dev/sdX lvm
```
> NOTE: **Open the encrypted drive before the next step**, opened drive will be in /dev/mapper/lvm

### 2.5 Configuring LVM
```bash
pvcreate /dev/mapper/lvm
vgcreate volgroup0 /dev/mapper/lvm
lvcreate -L 30GB volgroup0 -n lv_root
lvcreate -L 250GB volgroup0 -n lv_home
```

Confirm volume group and logigal volumes created successfully
```bash
vgdisplay
lvdisplay
```

Activate LVM
```bash
modprobe dm_mod # loads device_mapper module into kernel
vgscan  # checks if device_mapper finds volgroup0
vgchange -ay    # activates volume groups
```

Format logical groups
```bash
mkfs.ext4 /dev/volgroup0/lv_root
mkfs.ext4 /dev/volgroup0/lv_home
```

Mount Logical groups. Replace `sdX` with the partiton for grub. From step 3.3 this should be the second partition.
```bash
mount /dev/volgroup0/lv_root /mnt
mkdir /mnt/boot
mount /dev/sdX /mnt/boot
mkdir /mnt/home
mount /dev/volgroup0/lv_home /mnt/home
```

See [here](https://wiki.archlinux.org/title/Install_Arch_Linux_on_LVM) for more on LVM.

## 3.0 Configure current install
This is the meat and potatos of this document, this section is where `arch` is installed 
and configured.

### 3.1 Install Base Packages
Assumes you have a mounted partition to install to. (Assumes section 3.0 complete)
```bash
pacstrap -i /mnt base
```

### 3.2 Generate fstab
Assumes you have partitions you want mounted on boot, currently mount on `/mnt`.
```bash
genfstab -U -p /mnt >> /mnt/etc/fstab
cat /mnt/etc/fstab  # check fstab file for correct mounts 
```

### 3.3 Login to current arch install
```bash
arch-chroot /mnt
```
> NOTE `arch-chroot` is changing the root dir, not exactly logging in

#### 3.3.1 Set root password
```bash
passwd
```

#### 3.3.2 Create User
Replace `user` with desired username
```bash
useradd -m -g users -G wheel user   # wheel group is for sudo
passwd user
```

### 3.4 Install some essential packages
```bash
pacman -Syyuu   # 
pacman -S base-devel dosfstools grub efibootmgr lvm2 mtools
pacman -S sudo openssh neovim    # these are optional, but might aswell install them
```

#### 3.4.1 Enable ssh
```bash
systemctl enable sshd
```

### 3.5 Install linux
Up until now we have not installed linux(the kernel).
```bash
pacman -S linux linux-headers linux-lts linux-lts-headers
pacman -S linux-firmware
```
> NOTE linux lts(long-term-support) and the headers are not required, but recommended
> NOTE `linux-firmware` is not required, highly recommended

### 3.6 Install GPU drivers
GPU drivers in linux is annoying and involved to configure, see my other document in this repo `graphics_drivers.md` for more details if the following does not work for you.

#### 3.6.1 Find GPU
Find gpu brand from the following
```bash
lpci | grep -i vga
```
> NOTE if you already know you have an nvidia card but it does not show up in this step, skip this and try info from `graphics_drivers.md`.

#### 3.6.2 Install GPU driver
If you have an INTEL card:
```bash
pacman -S mesa
pacman -S intel-media-driver    # check if this package works for your card version
```

If you have an AMD card:
```bash
pacman -S mesa
pacman -S libva-mesa-driver
```

If you have an NVIDIA card:
```bash
pacman -S nvidia nvidia-utils
pacman -S nvidia-lts    # If you installed linux-lts
```
> NOTE this will probably not be enough for everything to work, especially if you have an NVIDIA card(like me). See `graphics_drivers.md` document in this repo for more details.

### 3.7 Initialize ram disk
#### 3.7.1 Edit mkinitcpio
Edit `/etc/mkinitcpio.conf`, make these changes:
```
-HOOKS=(base udev autodetect modconf kms keyboard keymap consolefont block filesystems fsck)
+HOOKS=(base udev autodetect modconf kms keyboard keymap consolefont block encrypt lvm2 filesystems fsck)
```

The HOOKS line might look different, doesnt matter just put `encrypt` and `lvm2` inbetween `block` and `filesystems`. You dont need `encrypt` if you didnt encrypt your partition.

> NOTE: the `-HOOKS` line is the line to take out, replace it with the `+HOOKS` line. Do not include `+`. 

#### 3.7.2 Generate initramfs
```bash
mkinitcpio -p linux
mkinitcpio -p linux-lts
```

### 3.8 Other configuration
#### 3.8.1 Configure locale
Uncomment your locale in `/etc/locale.gen`. Ex. in Canada mine would be `en_US.UTF-8 UTF-8`
Then generate locale with
```bash
locale-gen
```

### 3.9 Setting up boot loader
This section is where we can finally configure a bootloader and boot off of our install with the need of the iso.

#### 3.9.1 Edit grub for disk decryption
Skip if you didn't set up disk encryption. Edit `/etc/default/grub`, make these change:
```bash
-GRUB_CMDLINE_LINUX_DEFAULT="loglevel=3"
+GRUB_CMDLINE_LINUX_DEFAULT="loglevel=3 cryptdevice=/dev/sdX:volgroup0 quiet"
```
Replace `sdX` with the partition you encrypted.
> NOTE `quiet` is not required to add.

#### 3.9.2 Setup EFI partition
Recall the first `1G` partition we made in section 2.2, I will be refering to this partition as `sdX`.
```bash
mkdir /boot/EFI
mount /dev/sdX /boot/EFI
```

#### 3.9.3 Install and configure grub boot loader
```bash
grub-install --target=x68_64-efi --bootloader-id=grub_uefi --recheck
cp /usr/share/locale/en\@quot/LC_MESSAGES/grub.mo /boot/grub/locale/en.mo
grub-mkconfig -o /boot/grub/grub.cfg
```
> NOTE: This won't work for non-uefi systems

### 3.10 Finished?
```bash
systemctl enable NetworkManager     # Only if you are using NetworkManager
exit
umount -a                           # Unmount from live cd
reboot
```
If you do not have wifi after install, see `networking.md` in this dir for more.

