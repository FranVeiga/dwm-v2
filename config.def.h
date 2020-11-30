/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;       /* gap pixel between windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallowing floating windows by default*/
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "NotoSansMono-Regular:pixelsize=12:antialias=true:autohint=true", "JoyPixels:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

static const char col_primary[]        = "#050517";
static const char col_secondary[]        = "#f6511d";

static const unsigned int baralpha = 0xe6;
static const unsigned int borderalpha = OPAQUE;
static const char col1[]            = "#ffffff";
static const char col2[]            = "#ffffff";
static const char col3[]            = "#ffffff";
static const char col4[]            = "#ffffff";
static const char col5[]            = "#ffffff";
static const char col6[]            = "#ffffff";
static const char col7[]            = "#ffffff";
static const char col8[]            = "#ffffff";
static const char col9[]            = "#ffffff";
static const char col10[]           = "#ffffff";
static const char col11[]           = "#ffffff";
static const char col12[]           = "#ffffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]  = { col_gray3, col_primary, col_primary },
	[SchemeCol1]  = { col1,      col_primary, col_gray2 },
	[SchemeCol2]  = { col2,      col_primary, col_gray2 },
	[SchemeCol3]  = { col3,      col_primary, col_gray2 },
	[SchemeCol4]  = { col4,      col_primary, col_gray2 },
	[SchemeCol5]  = { col5,      col_primary, col_gray2 },
	[SchemeCol6]  = { col6,      col_primary, col_gray2 },
	[SchemeCol7]  = { col7,      col_primary, col_gray2 },
	[SchemeCol8]  = { col8,      col_primary, col_gray2 },
	[SchemeCol9]  = { col8,      col_primary, col_gray2 },
	[SchemeCol10] = { col10,     col_primary, col_gray2 },
	[SchemeCol11] = { col11,     col_primary, col_gray2 },
	[SchemeCol12] = { col12,     col_primary, col_gray2 },
	[SchemeSel]   = { col_gray4, col_cyan,  col_secondary  },
	[SchemeStatus]  = { col_gray3, col_primary,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray4, col_secondary,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray3, col_primary,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_gray4, col_primary,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray3, col_primary,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeStatus]  = { OPAQUE, baralpha, borderalpha  },
	[SchemeTagsSel]  = { OPAQUE, baralpha, borderalpha  },
    [SchemeTagsNorm]  = { OPAQUE, baralpha, borderalpha  },
    [SchemeInfoSel]  = { OPAQUE, baralpha, borderalpha  },
    [SchemeInfoNorm]  = { OPAQUE, baralpha, borderalpha  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "tcl.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|||",      tcl },
	{ "[D]",      deck },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_primary, "-nf", col_gray3, "-sb", col_secondary, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[]  = { "vivaldi-snapshot", NULL };
static const char *lowbrowsercmd[]  = { "qutebrowser", NULL };
static const char *screenshotcmd[]  = { "flameshot", "gui" , NULL};
static const char *alsamixercmd[] = {"st", "-e", "alsamixer" };
static const char *pavucontrolcmd[] = {"pavucontrol", NULL };
static const char *filecmd[] = { "pcmanfm", NULL };
static const char *bluetoothcmd[] = { "blueman-manager", NULL };
static const char *htopcmd[] = {"st", "-e", "htop" };
static const char *mocpcmd[] = {"st", "-e", "mocp", "-T", "nightly_theme"};
static const char *mocpskip[] = {"mocp", "-f"};
static const char *mocppause[] = {"mocp", "-G", "&"};
static const char *mocpprev[] = {"mocp", "-r", "&"};
static const char *pausecmd[] = {"playerctl", "play-pause", NULL };
static const char *previouscmd[] = {"playerctl", "previous", NULL };
static const char *nextcmd[] = {"playerctl", "next", NULL };
static const char *lessbright[] = {"sh", "-c", "xbacklight -dec 10 && sigdwmblocks 6", NULL};
static const char *morebright[] = {"sh", "-c", "xbacklight -inc 10 && sigdwmblocks 6", NULL};
static const char *volumeup[] = {"sh", "-c", "amixer set Master 5%+ && sigdwmblocks 7", NULL};
static const char *volumedown[] = {"sh", "-c", "amixer set Master 5%- && sigdwmblocks 7", NULL};
static const char *volumemute[] = {"sh", "-c", "amixer set Master toggle && sigdwmblocks 7", NULL};
static const char *shutdowncmd[] = {"/bin/sh", "dmenu_shutdown", NULL };
static const char *logoutcmd[] = {"/bin/sh", "dmenu_dwm_logout", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_u,      spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_u,      spawn,          {.v = lowbrowsercmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = filecmd } },
	{ MODKEY,                       XK_a,      spawn,          {.v = pavucontrolcmd } },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = alsamixercmd } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = bluetoothcmd } },
 	{ MODKEY,                       XK_space,  spawn,          {.v = mocpcmd } },
	{ MODKEY|ControlMask,           XK_p,      spawn,          {.v = mocpprev } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = htopcmd } },
	{ MODKEY|ShiftMask,             XK_z,      spawn,          {.v = lessbright } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = morebright } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_m,      fullscreen,     {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_minus, 		setborderpx,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_plus, 		setborderpx,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_numbersign, 	setborderpx,    {.i = 0 } },

	{ 0,                       XF86XK_AudioRaiseVolume,  spawn,          {.v = volumeup } },
	{ 0,                       XF86XK_AudioLowerVolume,  spawn,          {.v = volumedown } },
	{ 0,                       XF86XK_AudioMute,         spawn,          {.v = volumemute } },
	{ MODKEY,                  XF86XK_AudioNext,         spawn,          {.v = mocpskip } },
	{ MODKEY,                  XF86XK_AudioPlay,         spawn,          {.v = mocppause } },
	{ MODKEY,                  XF86XK_AudioPrev,         spawn,          {.v = mocpprev } },
	{ 0,                       XF86XK_AudioNext,         spawn,          {.v = nextcmd } },
	{ 0,                       XF86XK_AudioPlay,         spawn,          {.v = pausecmd } },
	{ 0,                       XF86XK_AudioPrev,         spawn,          {.v = previouscmd } },
	{ 0,                       XF86XK_MonBrightnessUp,   spawn,          {.v = morebright } },
	{ 0,                       XF86XK_MonBrightnessDown, spawn,          {.v = lessbright } },
	{ 0,                       XK_Print, spawn,          {.v = screenshotcmd } },


	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = logoutcmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
	{ MODKEY|ControlMask,			XK_r,      quit,           {1} }, 
	{ MODKEY|ShiftMask,			    XK_s,      spawn,          {.v = shutdowncmd } }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	/*{ ClkTagBar,            0,              Button1,        view,           {0} },*/
/*	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },*/
/*	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },*/
/*	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },*/
};

