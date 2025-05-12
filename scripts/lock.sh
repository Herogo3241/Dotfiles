#!/bin/bash

# Temporary file
img=/tmp/slockbg.png

# Take a screenshot
maim "$img"

# Optionally blur it
magick "$img" -blur 0x8 "$img"

# Set it as the background
xsetroot -solid black
xloadimage -onroot -fullscreen "$img"

# Start slock
i3lock -i "$img"

# Cleanup
rm "$img"

