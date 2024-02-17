# Storage in proxmox

## Single hdd
If you only have a few disks on your proxmox, you can free up a lot of storage by deleting local-lvm. How to do that:

1. In the web GUI, Go to Datacenter and then storage and remove `local-lvm`

2. Go to your node's console and run:

```bash
lvremove /dev/pve/data
lvresize -l +100%FREE /dev/pve/root
resize2fs /dev/mapper/pve-root
```
