/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-cure-medium-r-normal-*-11-*-*-*-*-*-*-*";
#define NUMCOLORS 21
static const char colors[NUMCOLORS][ColLast][21] = {
	/* border    fg        bg */
    { "#020202", "#D7D0C7", "#151515" },  // 01 - normal
    { "#020202", "#7DC1CF", "#151515" },  // 02 - selected
    { "#B3354C", "#B3354C", "#151515" },  // 03 - urgent

    { "#1A1A1A", "#1A1A1A", "#151515" },  // 04 - black
    { "#D23D3D", "#D23D3D", "#151515" },  // 05 - red
    { "#A0CF5D", "#A0CF5D", "#151515" },  // 06 - green
    { "#F39D21", "#F39D21", "#151515" },  // 07 - yellow
    { "#4E9FB1", "#4E9FB1", "#151515" },  // 08 - blue
    { "#8542FF", "#8542FF", "#151515" },  // 09 - magenta
    { "#000000", "#000000", "#000000" },  // unusable
    { "#337373", "#337373", "#020202" },  // 0B - cyan
    { "#808080", "#808080", "#020202" },  // 0C - light gray
    { "#4C4C4C", "#4C4C4C", "#020202" },  // 0D - gray
    { "#FFEE00", "#FFEE00", "#020202" },  // 0E - yellow2
/*    { "#B1D354", "#B1D354", "#020202" },  // 0F - light green */
    { "#20b2e7", "#20b2e7", "#020202" },  // 0F - White
    { "#BF9F5F", "#BF9F5F", "#020202" },  // 10 - light yellow
    { "#3995BF", "#3995BF", "#020202" },  // 11 - light blue
    { "#A64286", "#A64286", "#020202" },  // 12 - light magenta
    { "#6C98A6", "#6C98A6", "#020202" },  // 13 - light cyan
    { "#FFA500", "#FFA500", "#020202" },  // 14 - orange

    { "#0300ff", "#0300ff", "#802635" },  // 15 - warning
};

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "web", "sys", "vid", "doc" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
	{ "mplayer",  NULL,       NULL,       1 << 8,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] 		= { "dmenu_run", "-i", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],
                                       "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL  };
static const char *termcmd[]  		= { "urxvt", NULL };
static const char *webcmd[] 		= { "chromium", NULL };
static const char *dwbcmd[]			= { "dwb", NULL};
static const char *fmcmd[]			= { "pcmanfm", NULL};
static const char *voldowncmd[]    	= { "amixer", "-q", "set", "Master", "2dB-",  NULL };
static const char *volupcmd[]      	= { "amixer", "-q", "set", "Master", "2dB+",  NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = dwbcmd } },
	{ MODKEY,                       XK_q,      spawn,          {.v = webcmd } },
	{ MODKEY,						XK_e,      spawn,          {.v = fmcmd } },
	{ MODKEY,                       XK_Left,   spawn,          {.v = voldowncmd } },
	{ MODKEY,                       XK_Right,  spawn,          {.v = volupcmd } },	
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

