#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void notify_user(const char *message) {
    // Send desktop notification
    char notify_cmd[512];
    snprintf(notify_cmd, sizeof(notify_cmd), "notify-send 'USB Event' '%s'", message);
    system(notify_cmd);

    // Play a system sound 
    system("paplay sounds/usb.wav");
}

int main() {
    struct udev *udev;
    struct udev_monitor *mon;
    struct udev_device *dev;

    udev = udev_new();
    if (!udev) {
        fprintf(stderr, "Failed to initialize udev.\n");
        return 1;
    }

    mon = udev_monitor_new_from_netlink(udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", "usb_device");
    udev_monitor_enable_receiving(mon);

    int fd = udev_monitor_get_fd(mon);

    printf("Listening for USB device events...\n");

    while (1) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        if (select(fd + 1, &fds, NULL, NULL, NULL) > 0 && FD_ISSET(fd, &fds)) {
            dev = udev_monitor_receive_device(mon);
            if (dev) {
                const char *action = udev_device_get_action(dev);
                const char *vendor = udev_device_get_sysattr_value(dev, "manufacturer");
                const char *product = udev_device_get_sysattr_value(dev, "product");

                if (action && strcmp(action, "add") == 0) {
                    char message[512];
                    snprintf(message, sizeof(message), "Device Connected:%s %s",
                             vendor ? vendor : "Unknown Vendor",
                             product ? product : "Unknown Product");
                    notify_user(message);
                }

                udev_device_unref(dev);
            }
        }
    }

    udev_unref(udev);
    return 0;
}

