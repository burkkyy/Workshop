# Suckless
Document on installing and configuring `suckless` software. Personally I put all `suckless` software into one directory, `~/.suckless`.
```bash
mkdir ~/.suckless
```

## 1.0 - Prerequisites
```bash
pacman -S git
```

## 2.0 - dwm
`dwm` is a dynamic tiling window manager, a productive GUI for minimalist users. See [here](https://dwm.suckless.org/) for more on `dwm`.
```bash
git clone https://github.com/burkkyy/dwm.git
cd dwm/
make clean install
```

## 3.0 - st
```bash
git clone https://github.com/burkkyy/st.git
cd st/
make clean install
```
 
## 4.0 - demu
```bash
git clone https://github.com/burkkyy/dmenu.git
cd dmenu/
make clean install
```
