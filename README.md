# Nord themed DWM setup

This repo is my personal configuration for my main machine, I was a long time i3 user but had to switch because i3 was freezing when I had dual monitors connected. I decided to look into DWM and I'm very happy with it. The keybindings were really not my style at all so these are much i3/vim inspired. 

This repo is mostly for myself, because I have two of the same machines that I needed to clone the configuration for. But if anyone is interested, here ya go. 

Some (most) of these scripts were not written by me, I just modified them. I will try to credit those that I can if any info can be found about them. 


## Requirements:
 - ### [DWM](https://dwm.suckless.org/) - Window Manager

 - ### [DWMbar](https://github.com/joestandring/dwm-bar) - Status bar
  - > Configuration files included in scripts for both


 - ### [rofi](https://github.com/davatorium/rofi) - Application launcher

  - [dmenu](https://tools.suckless.org/dmenu/) - Application launcher

 - > Configuration files included in scripts for both

 - [feh](https://wiki.archlinux.org/title/feh) -- Only if you are a fellow Arch user who wants to have to write their own scripts just to set a Desktop background

 - [dwmbar](https://github.com/joestandring/dwm-bar) - Tmux module included in dwmbar folder

### Nord Everything
<img src=/screenshots/dwm.png width="1000px">

Every wallpaper is Nord themed. Most of them came from repos like \
`https://github.com/linuxdotexe/nordic-wallpapers`
`https://github.com/dxnst/nord-backgrounds`

Also dwm itself, Rofi/Drun, etc. for the whole Nord experience.

### Installation

Install dwm, dwmbar, rofi, dmenu, drun, feh (and tmux, alacritty, Neovim, etc. ripgrep, fd, fzf, if you want the full terminal workflow experience. But no configs for those included here)

 After installing, swap out config.h for the one in this repo, and place the diff config files and scripts where they need to go.

- I am going to assume if you are an arch user that you will know how to configure these assorted scripts, but here is a very quick rundown:

 `wallpaper` needs to be edited with the location of where you put the desktop backgrounds, `chmod +x` and put into /usr/bin

Place `config.rasi` into your `/home/$USER/.config/rofi` directory

and place `rofi-power-menu` into /usr/bin

[rofi-power-menu](https://github.com/jluttine/rofi-power-menu) is also included, but is avail as an AUR package. This needs to be chmod +x and placed into /usr/bin as well.

`config` - is for dwmbar, and `tmux.sh` is an additional module that needs to be placed in the modules directory of your dwmbar installation.


I'm probably typing this all for nothing, as I will be the only one using this. But hey, if you end up using it I hope you enjoy it.

Any questions or cannot install/configure something, just open an issue.


### Have cool Nord themed stuff or wallpapers to add? Open a PR!
