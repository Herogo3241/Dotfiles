#!/bin/bash

if xrandr | grep -q "HDMI-0 connected"; then
  ~/.screenlayout/dual.sh
  sleep 0.5
  notify-send "Dual Screen Mode Activated" -i "video-display"
else
  ~/.screenlayout/single.sh
  sleep 0.5
  notify-send "Single Screen Mode Activated" -i "video-display"

fi



