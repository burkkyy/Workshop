# Some lan problems with common fixes

Before any fixes, figure out name of the network device 
(it's NOT gonna be not lo)

```bash
ip a
```
```text
1: lo: ...
    ...
2: eth0: ...
    ...
```

In the following methods, eth0 is the name of my network device.

## Method 1
Try turning it off and on again

```bash
sudo ip link dev eth0 down
sudo ip link dev eth0 up
```

## Method 2
First make sure `systemd-networkd` is up, and then check the network 
device's status with `networkctl`

```bash
systemctl status systemd-networkd   # start and enable if not up
networkctl status eth0
```

## Method 3
Check `/etc/systemd/network/eth.network`. If file does not exist, try
writing:

```text
[Match]
Name=eth0

[Network]
DHCP=yes
```

Then repeat Method 1

