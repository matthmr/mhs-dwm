/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 2;       /* snap pixel */
static const int custom_bh          = 28;
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
/*NOTE(mh): Added from diff (barpadding)*/
static const int vertpad            = 0;
static const int sidepad            = 0;
/*NOTE(mh): Added from diff (fullgaps)*/
static const unsigned int gappx     = 10;
/*NOTE(mh): Added from diff*/
static const int focusonwheel				= 0;
static const char *fonts[]          = { "JetBrains Mono:size=14:antialias=true", "monospace:size=14" }; /*NOTE(mh): Chaging colors -/+*/
static const char col_black[]       	= "#222222";
static const char col_gray[]        	= "#444444";
static const char col_gray_light[]  	= "#bbbbbb";
static const char col_white[]       	= "#eeeeee";
static const char col_manjaro_dark[]	= "#1a1a1a";
static const char col_manjaro_light[]	= "#303030";
static const char col_manjaro_light2[]= "#d3d3d3";
static const char col_manjaro_light3[]= "#8a8a8a";
static const char *colors[][3]      	= {
	/*               fg         bg         					border   */
	[SchemeNorm] = { col_white, col_manjaro_light, 	col_gray 	},					// for active
	[SchemeSel]  = { col_white, col_manjaro_dark,		col_manjaro_light2 }, // for inactive
	/*NOTE(mh): Applied from diff*/
	[SchemeTagsSel]  = { col_white, col_manjaro_light, "#000000" },
	[SchemeTagsNorm] = { col_manjaro_light3, col_manjaro_light, "#000000" },					// for active

};

/* tagging */
// static const char *ontags[] = { ... };
static const char *alttags[] = { "•", "•", "•", "•" };
static const char *tags[] = { "◦", "◦", "◦", "◦" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
/*NOTE(mh): Changed this for debugging purposes, chage this back when finished*/
#define MODKEY Mod4Mask
//#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define ALT Mod1Mask

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
* NOTE(mh): Commented to patch another command launcher */
static const char *dmenucmd[] = { "rofi", "-show", "run", NULL};
static const char *tmuxterm[]  = { "alacritty", "--command", "tmux", "new" , "-A", NULL };
static const char *term[]      = { "alacritty", NULL };
static const char* clipmenu[]   = { "clipmenu", "-i", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	/* Mod                          Keysym     *func           Arg      */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = clipmenu } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = tmuxterm } },
	{ MODKEY|ShiftMask|ControlMask, XK_Return, spawn,          {.v = term } },
	{ MODKEY,                       XK_s,      swapbarpos,     {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_p,      setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_m,      setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	/* NOTE(mh): Maybe this will work?*/
	{ MODKEY|ShiftMask,							XK_F10,		 zoom,					 {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	//{ MODKEY,                     XK_Tab,    view,           {0} },
	/*NOTE(mh): Added from diff (2)*/
	{ ALT, 		        					    XK_Tab,       shiftviewclients, { .i = +1 } },
	{ ALT, 		   					          XK_backslash, shiftviewclients, { .i = -1 } },
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
	/*NOTE(mh): Gotta manually apply these*/
	{ MODKEY,							XK_F1,		 tagall,		 { .ui = 1 << 0 } }, // 1
	{ MODKEY,							XK_F2,		 tagall,		 { .ui = 1 << 1 } }, // 2
	{ MODKEY,							XK_F3,		 tagall,		 { .ui = 1 << 2 } }, // 4
	{ MODKEY,							XK_F4,		 tagall,		 { .ui = 1 << 3 } }, // 8
	{ MODKEY|ShiftMask,		XK_F1,		sendall,		 { .ui = 1 << 0} },
	{ MODKEY|ShiftMask,		XK_F2,		sendall,		 { .ui = 1 << 1} },
	{ MODKEY|ShiftMask,		XK_F3,		sendall,		 { .ui = 1 << 2} },
	{ MODKEY|ShiftMask,		XK_F4,		sendall,		 { .ui = 1 << 3} },
	{ MODKEY|ControlMask,	XK_F1,	 	grabtag,		 { .v = "1" } },
	{ MODKEY|ControlMask,	XK_F2,		grabtag,		 { .v = "2" } },
	{ MODKEY|ControlMask,	XK_F3,		grabtag,		 { .v = "3" } },
	{ MODKEY|ControlMask,	XK_F4,		grabtag,		 { .v = "4" } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	/*NOTE(mh): Kill all visible clients*/
	{ MODKEY|ShiftMask,             XK_x,      killall,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = tmuxterm } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

