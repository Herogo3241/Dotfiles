
#dwmstatus
dwmstatus 2>&1 >/dev/null &


#notification manager - dunst
dunst &


#picom compositor for blur and transparency
picom --config ~/.config/picom/picom.conf &

sleep 0.5
~/.config/scripts/monitor.sh

#wallpaper
feh --bg-center Pictures/Wallpaper/waves.png

exec dwm
