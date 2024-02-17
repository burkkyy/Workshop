# Make your debian laptop stay running while closed

# Method 1

```bash
sudo systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.target
```

This will completely disable suspend

# Method 2

Edit `/etc/systemd/logind.conf`

```text
#HandleLidSwitch=suspend
#HandleLidSwitchExternalPower=suspend
```

to

```text
HandleLidSwitch=ignore
HandleLidSwitchExternalPower=ignore
```

