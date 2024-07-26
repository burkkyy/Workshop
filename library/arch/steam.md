```bash
caleb@burke ~$ sudo pacman -S steam
resolving dependencies...
:: There are 7 providers available for lib32-vulkan-driver:
:: Repository multilib
   1) lib32-amdvlk  2) lib32-nvidia-utils  3) lib32-vulkan-intel  4) lib32-vulkan-nouveau
   5) lib32-vulkan-radeon  6) lib32-vulkan-swrast  7) lib32-vulkan-virtio

Enter a number (default=1):
Which one do I pick? I installed nvidia during arch install
```

Since you have installed Nvidia drivers during the Arch installation, you should choose the lib32-nvidia-utils option to ensure compatibility with your Nvidia GPU. So, you should enter 2 when prompted.

