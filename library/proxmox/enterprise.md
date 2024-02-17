# Dealing with enterprise
The enterprise subscription stuff can be annoying, here how to deal with it.

## Repository

Edit files `/etc/apt/sources.list.d/pve-enterprise.list` and `/etc/apt/sources.list.d/ceph.list`, comment out line with '#'. Ex:

```text
# deb https://enterprise.proxmox.com/debian/pve bookworm pve-enterprise
```

```text
# deb https://enterprise.proxmox.com/debian/ceph-quincy bookworm enterprise
```

### Use the no-subscription repository.
Edit file `vim /etc/apt/sources.list`

```text
deb http://ftp.debian.org/debian bookworm main contrib
deb http://ftp.debian.org/debian bookworm-updates main contrib

# Proxmox VE pve-no-subscription repository provided by proxmox.com,
# NOT recommended for production use
deb http://download.proxmox.com/debian/pve bookworm pve-no-subscription

# security updates
deb http://security.debian.org/debian-security bookworm-security main contrib
```

