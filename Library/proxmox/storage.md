# Storage in proxmox

## Single hdd
If you only have one disk on your proxmox node, you might aswell delete
local-lvm to gain way more storage. How to do that:

1. Go to Datacenter/storage and remove local-lvm

2. Go to your node's console and run:

```bash
lvremove /dev/pve/data
lvresize -l +100%FREE /dev/pve/root
resize2fs /dev/mapper/pve-root
```

