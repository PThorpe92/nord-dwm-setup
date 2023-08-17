/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"Input Mono:size=13"};
static const char col_gray1[] = "#3b4252";
static const char col_gray2[] = "#2f3441";
static const char col_gray3[] = "#eceff4";
static const char col_gray4[] = "#49688e";
static const char col_cyan[] = "#00FFFF";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    // Normal mode      ice white  Nord grey  Darker Nord grey
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    // Selection mode DarkNord
    [SchemeSel] = {col_gray2, col_gray4, col_cyan},
};

// Some alternate nord colors
/*     8 normal colors
*     "black", "red3", "green3", "yellow3", "blue2", "magenta3", "cyan3",
*     "gray90", "#3b4252",  black    /
*     "#bf616a",            red      /
*     "#a3be8c",            green    /
*     "#ebcb8b",            yellow   /
*     "#81a1c1",            blue     /
*     "#b48ead",            magenta  /
*     "#88c0d0",            cyan     /
*     "#e5e9f0",            white    /
/
/     / 8 bright colors
/     "gray50", "red", "green", "yellow", "#5c5cff", "magenta", "cyan", "white",
/     "#4c566a", / black
/     "#bf616a", / red
/     "#a3be8c", / green
/     "#ebcb8b", / yellow
/     "#81a1c1", / blue
/     "#b48ead", / magenta
/     "#8fbcbb", / cyan
/     "#eceff4", / white
/ };
*/
static unsigned int defaultrcs = 257;

static const char *tags[] = {"", "", " ", "", "",
                             "", "", "",  ""};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"[M]", monocle},
};
// ^^^
// Personally, I only use these two layouts. This is obviously quite opinionated
// but so are the rest of the settings here. All the keybindings are very i3
// like
// except for the j and k by default switch between window focus, instead of h
// and l
// which I like better because it's now much easier to resize windows with h and
// l

/* key definitions */
#define FORCE_VSPLIT 1
#define MODKEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static const char *dmenucmd[] = {"rofi", "-show", "drun", NULL};
static const char *termcmd[] = {"alacritty", NULL};
static const char *monitorcmd[] = {"xrandr", "--output", "HDMI-1", "--right-of",
                                   "eDP-1",  "--auto",   NULL};
static const char *powercmd[] = {"rofi", "-show", "powermenu:rofi-power-menu",
                                 NULL};
static const char *screenshotcmd[] = {"flameshot", "gui", NULL};
static const char *pavucontrolcmd[] = {"pavucontrol", NULL};
static const char *upvol[] = {"/usr/bin/pactl", "set-sink-volume", "0", "+5%",
                              NULL};
static const char *downvol[] = {"/usr/bin/pactl", "set-sink-volume", "0", "-5%",
                                NULL};
static const char *mutevol[] = {"/usr/bin/pactl", "set-sink-mute", "0",
                                "toggle", NULL};
static const char *light_up[] = {"/usr/bin/light", "-A", "5", NULL};
static const char *light_down[] = {"/usr/bin/light", "-U", "5", NULL};
static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_y | ShiftMask, spawn, {.v = monitorcmd}},
    {MODKEY, XK_0, spawn, {.v = powercmd}},
    {0, XK_Print, spawn, {.v = screenshotcmd}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = downvol}},
    {0, XF86XK_AudioMute, spawn, {.v = mutevol}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol}},
    {0, XF86XK_AudioMicMute, spawn,
     SHCMD("/usr/bin/pactl set-source-mute 0 toggle")},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = light_up}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = light_down}},
    {MODKEY | ControlMask, XK_u, spawn, {.v = pavucontrolcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_p, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY | ShiftMask, XK_h, focusmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_l, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
