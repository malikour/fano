# fano
simple file anonymizer
<pre>
# cat file
Apr 14 08:39:33 n14 dbus-daemon[1127]: [system] Successfully activated service 'org.freedesktop.nm_dispatcher'
Apr 14 08:39:33 n14 systemd[1]: Started Network Manager Script Dispatcher Service.
Apr 14 08:39:43 n14 systemd[1]: NetworkManager-dispatcher.service: Succeeded.
Apr 14 09:12:32 n14 systemd[1]: Starting dnf makecache...
Apr 14 09:12:32 n14 dnf[190045]: Updating Subscription Management repositories.
Apr 14 09:12:32 n14 dnf[190045]: Unable to read consumer identity
Apr 14 09:12:32 n14 dnf[190045]: This system is not registered to Red Hat Subscription Management. You can use subscription-manager to register.
Apr 14 09:12:32 n14 dnf[190045]: Metadata cache refreshed recently.
Apr 14 09:12:32 n14 systemd[1]: dnf-makecache.service: Succeeded.
Apr 14 09:12:32 n14 systemd[1]: Started dnf makecache.

# ./fano
Usage: ./fano file_to_anonymize
/etc/dic is a text file which contains all strings to remove

# cat /etc/dic
org.freedesktop.nm_dispatcher
dnf

# ./fano file

# cat file.ano
Apr 14 08:39:33 n14 dbus-daemon[1127]: [system] Successfully activated service 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXX'
Apr 14 08:39:33 n14 systemd[1]: Started Network Manager Script Dispatcher Service.
Apr 14 08:39:43 n14 systemd[1]: NetworkManager-dispatcher.service: Succeeded.
Apr 14 09:12:32 n14 systemd[1]: Starting XXX makecache...
Apr 14 09:12:32 n14 XXX[190045]: Updating Subscription Management repositories.
Apr 14 09:12:32 n14 XXX[190045]: Unable to read consumer identity
Apr 14 09:12:32 n14 XXX[190045]: This system is not registered to Red Hat Subscription Management. You can use subscription-manager to register.
Apr 14 09:12:32 n14 XXX[190045]: Metadata cache refreshed recently.
Apr 14 09:12:32 n14 systemd[1]: XXX-makecache.service: Succeeded.
Apr 14 09:12:32 n14 systemd[1]: Started XXX makecache.

# 
</pre>
