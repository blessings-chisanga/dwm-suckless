

/* appearance */
static const unsigned int refresh_rate        = 60;  /* matches dwm's mouse event processing to your monitor's refresh rate for smoother window interactions */
static const unsigned int enable_noborder     = 1;   /* toggles noborder feature (0=disabled, 1=enabled) */
static const unsigned int borderpx            = 1;   /* border pixel of windows */
static const unsigned int snap                = 26;  /* snap pixel */
static const int swallowfloating              = 1;   /* 1 means swallow floating windows by default */
static const unsigned int systraypinning      = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int gappih              = 10;
static const unsigned int gappiv              = 10;
static const unsigned int gappbh              = 10;
static const unsigned int gapprh              = 10;

static const unsigned int systrayonleft       = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing      = 5;   /* systray spacing */
static const int systraypinningfailfirst      = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor */
static const int showsystray                  = 1;   /* 0 means no systray */
static const int showbar                      = 1;   /* 0 means no bar */
static const int topbar                       = 1;   /* 0 means bottom bar */
#define ICONSIZE                              20     /* icon size */
#define ICONSPACING                           5      /* space between icon and title */
#define SHOWWINICON                           1      /* 0 means no winicon */
static const char *fonts[]                    = { "FiraCode Nerd Font:bold:size=8"};
static const char normbordercolor[]           = "#bd93f9";
static const char normbgcolor[]               = "#282a36";
static const char normfgcolor[]               = "#f8f8f2";
static const char selbordercolor[]            = "#f5881b";
static const char selbgcolor[]                = "#bd93f9";
static const char selfgcolor[]                = "#282a36";

static const char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor },
};

static const char *const autostart[] = {
    "xset", "s", "off", NULL,
    "xset", "s", "noblank", NULL,
    "xset", "-dpms", NULL,
    NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *rofi[]  = { "rofi", "-show", "drun", NULL };



static const char ptagf[] = "[%s %s]";  /* format of a tag label */
static const char etagf[] = "[%s]";     /* format of an empty tag */
static const int lcaselbl = 0;          /* 1 means make tag label lowercase */

static const Rule rules[] = {
    /* class                instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
    { "alacritty",          NULL,     NULL,           0,         0,          1,          0,         0 },
    { NULL,                 NULL,     "Event Tester", 0,         0,          0,          1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "",      tile },    /* first entry is default */
    { "",      NULL },    /* no layout function means floating behavior */
    { "",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define STATUSBAR "dwmblocks"
/* commands */
static const char *launchercmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]     = { "alacritty", NULL };

static Key keys[] = {
    /* modifier                     key                        function        argument */
    { MODKEY,                       XK_d,                      spawn,          {.v = rofi } },    
    { MODKEY,                       XK_r,                      spawn,          {.v = launchercmd} },
    { MODKEY,                       XK_x,                      spawn,          {.v = termcmd } },
    { MODKEY,                       XK_p,                      spawn,          SHCMD ("flameshot full -p ~/Pictures/Screenshots/")},
    { MODKEY|ShiftMask,             XK_p,                      spawn,          SHCMD ("flameshot gui -p ~/Pictures/Screenshots/")},
    { MODKEY|ControlMask,           XK_p,                      spawn,          SHCMD ("flameshot gui --clipboard")},
    { MODKEY,                       XK_e,                      spawn,          SHCMD ("xdg-open .")},
    { MODKEY|ShiftMask,             XK_w,                      spawn,          SHCMD ("feh --randomize --bg-fill ~/Pictures/backgrounds/*")},
    { 0,                            XF86XK_MonBrightnessUp,    spawn,          SHCMD ("xbacklight -inc 10")},
    { 0,                            XF86XK_MonBrightnessDown,  spawn,          SHCMD ("xbacklight -dec 10")},
    { 0,                            XK_F9,                     spawn,          SHCMD ("pactl set-sink-volume @DEFAULT_SINK@ +5%")},             
    { 0,                            XK_F8,                     spawn,          SHCMD ("pactl set-sink-volume @DEFAULT_SINK@ -5%")},
    { MODKEY|ShiftMask,             XK_b,                      togglebar,      {0} },
    { MODKEY,                       XK_j,                      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,                      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,                      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,                      movestack,      {.i = -1 } },
    { MODKEY,                       XK_i,                      incnmaster,     {.i = +1 } },
    //{ MODKEY,                       XK_d,                      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,                      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,                      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_h,                      setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,             XK_l,                      setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,             XK_o,                      setcfact,       {.f =  0.00} },
    { MODKEY,                       XK_Return,                 zoom,           {0} },
    { MODKEY,                       XK_Tab,                    view,           {0} },
    { MODKEY,                       XK_q,                      killclient,     {0} },
    { MODKEY,                       XK_t,                      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,                      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,                      fullscreen,     {0} },
    { MODKEY,                       XK_space,                  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_m,                      togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_y,                      togglefakefullscreen, {0} },
    { MODKEY,                       XK_0,                      view,           {.ui = ~0 } },
    { MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    { MODKEY|ShiftMask,             XK_q,                      quit,           {0} },
    { MODKEY|ControlMask|ShiftMask, XK_r,                      spawn,          SHCMD("systemctl reboot")},
    { MODKEY|ControlMask|ShiftMask, XK_s,                      spawn,          SHCMD("systemctl suspend")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 2} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
