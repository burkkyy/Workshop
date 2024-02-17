# Common networking problems

## vmbr0 is not active

```bash
systemctl status networking
systemctl start networking
ifreload -a
```

