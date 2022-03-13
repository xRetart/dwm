#include <X11/XF86keysym.h>


// appearance
static const unsigned int borderpx  = 2;  // border pixel of windows
static const unsigned int snap      = 1;  // snap pixel
static const int showbar            = 1;  // 0 means no bar
static const int topbar             = 1;  // 0 means bottom bar
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#00665a";
static const char *colors[][3]      = {
    //               <fg>       <bg>       <border>
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

#define SPAWN_APP(...) (const char*[]){ __VA_ARGS__, NULL }
#define SPAWN_TERM_APP(...) SPAWN_APP("st", "-e", __VA_ARGS__)

typedef struct {
    const char *name;
    const void *cmd;
} Sp;
static Sp scratchpads[] = {
    // <name>        <cmd>
    { "spterm",      SPAWN_APP("st", "-n", "spterm") },
    { "spfm",        SPAWN_APP("st", "-n", "spfm", "-e", "vifm") },
    { "sptop",       SPAWN_APP("st", "-n", "sptop", "-e", "htop") },
    { "spkeepassxc", SPAWN_APP("keepassxc") },
	{ "sped",		 SPAWN_APP("st", "-n", "sped", "-e", "nvim") },
};

// tagging
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
    // xprop(1):
    //  WM_CLASS(STRING) = instance, class
    //  WM_NAME(STRING) = title
    //
    // <class> <instance>     <title> <tags mask> <isfloating> <monitor>
    { NULL,    "spterm",      NULL,   SPTAG(0),   1,           -1 },
    { NULL,    "spfm",        NULL,   SPTAG(1),   1,           -1 },
    { NULL,    "sptop",       NULL,   SPTAG(2),   1,           -1 },
    { NULL,    "spkeepassxc", NULL,   SPTAG(3),   1,           -1 },
    { NULL,    "sped",        NULL,   SPTAG(4),   1,           -1 },
};

// layout(s)
static const float mfact        = 0.5; // factor of master area size [0.05..0.95]
static const int nmaster        = 1;    // number of clients in master area
static const int resizehints    = 0;    // 1 means respect size hints in tiled resizals
static const int lockfullscreen = 0;    // 1 will force focus on the fullscreen window

static const Layout layouts[] = {
    // <symbol>   <arrange function>
    { "[]=",      tile },    // first entry is default
    { "><>",      NULL },    // no layout function means floating behavior
    { "[M]",      monocle },
};

// key definitions
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           { .ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     { .ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            { .ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      { .ui = 1 << TAG} },

// commands
static char dmenumon[2] = "0"; // component of dmenucmd, manipulated in spawn()
static const char *dmenucmd[] = SPAWN_APP("dmenu-app");
static const char *termcmd[]  = SPAWN_APP("st");


#include "movestack.c"
#include "shiftview.c"
static Key keys[] = {
    // <modifier>                   <key>                     <function>      <argument>
	/// navigation
	//// layout
    { MODKEY,                       XK_n,                     focusstack,       { .i = +1 } },
    { MODKEY,                       XK_e,                     focusstack,       { .i = -1 } },

    TAGKEYS(XK_1, 0)
    TAGKEYS(XK_2, 1)
    TAGKEYS(XK_3, 2)
    TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4)
    TAGKEYS(XK_6, 5)
    TAGKEYS(XK_7, 6)
    TAGKEYS(XK_8, 7)
    TAGKEYS(XK_9, 8)
	
	//// tags
    { MODKEY,                       XK_i,                     shiftview,        { .i = -1 } },
    { MODKEY,                       XK_o,                     shiftview,        { .i = +1 } },
    { MODKEY,                       XK_Tab,                   view,             { 0 } },
	
	/// manipulation
	//// window
    { MODKEY|ShiftMask,             XK_j,                     movestack,        { .i = +1 } },
    { MODKEY|ShiftMask,             XK_k,                     movestack,        { .i = -1 } },
    { MODKEY|ShiftMask,             XK_Return,                zoom,             { 0 } },
    { MODKEY|ShiftMask,             XK_c,                     killclient,       { 0 } },
    { MODKEY|ShiftMask,             XK_minus,                 setmfact,         { .f = -0.05 } },
    { MODKEY|ShiftMask,             XK_equal,                 setmfact,         { .f = +0.05 } },

	//// layout
    { MODKEY|ShiftMask,             XK_equal,                 incnmaster,       { .i = +1 } },
    { MODKEY|ShiftMask,             XK_minus,                 incnmaster,       { .i = -1 } },
    { MODKEY|ShiftMask,             XK_t,                     setlayout,        { .v = &layouts[0] } },
    { MODKEY|ShiftMask,             XK_f,                     setlayout,        { .v = &layouts[1] } },
    { MODKEY|ShiftMask,             XK_m,                     setlayout,        { .v = &layouts[2] } },
	
    { MODKEY|ShiftMask,             XK_space,                 setlayout,        { 0 } },
    { MODKEY|ShiftMask,             XK_space,                 togglefloating,   { 0 } },
    { MODKEY|ShiftMask,             XK_f,                     togglefullscreen, { 0 } },
    { MODKEY|ShiftMask,             XK_0,                     view,             { .ui = ~0 } },

    { MODKEY|ShiftMask,             XK_b,                     togglebar,        { 0 } },

	/// apps
	//// conventional
    { MODKEY,                       XK_p,                     spawn,            { .v = dmenucmd } },
    { MODKEY|ControlMask,           XK_Return,                spawn,            { .v = termcmd } },
    { MODKEY|ControlMask,           XK_f,                     spawn,            { .v = SPAWN_APP("firefox") } },
    { MODKEY|ControlMask,           XK_t,                     spawn,            { .v = SPAWN_APP("torbrowser-launcher") } },
    { MODKEY|ControlMask,           XK_k,                     spawn,            { .v = SPAWN_APP("keepassxc") } },
    { MODKEY|ControlMask,           XK_s,                     spawn,            { .v = SPAWN_APP("signal") } },
    { MODKEY|ControlMask,           XK_h,                     spawn,            { .v = SPAWN_TERM_APP("htop") } },
    { MODKEY|ControlMask,           XK_m,                     spawn,            { .v = SPAWN_TERM_APP("vifm") } },
    { MODKEY|ControlMask,           XK_a,                     spawn,            { .v = SPAWN_TERM_APP("anitime") } },
    { MODKEY|ControlMask,           XK_n,                     spawn,            { .v = SPAWN_TERM_APP("nvim") } },

	//// scratchpads
    { MODKEY|ControlMask,           XK_y,                     togglescratch,    { .ui = 0 } },
    { MODKEY|ControlMask,           XK_u,                     togglescratch,    { .ui = 1 } },
    { MODKEY|ControlMask,           XK_p,                     togglescratch,    { .ui = 2 } },
    { MODKEY|ControlMask,           XK_x,                     togglescratch,    { .ui = 3 } },
    { MODKEY|ControlMask,           XK_e,                     togglescratch,    { .ui = 4 } },

	/// session management
    { MODKEY|ControlMask|ShiftMask, XK_q,                     quit,             { 0 } },
    { MODKEY|ControlMask|ShiftMask, XK_s,                     spawn,            { .v = SPAWN_APP("loginctl", "suspend") } },

	/// non-wm things
    { 0,                            XF86XK_MonBrightnessDown, spawn,            { .v = SPAWN_APP("xbacklight", "-", "10") } },
    { 0,                            XF86XK_MonBrightnessUp,   spawn,            { .v = SPAWN_APP("xbacklight", "+", "10") } },
};

// button definitions
// click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin
static Button buttons[] = {
    // <click>       <event mask>    <button>        <function>      <argument>
    { ClkLtSymbol,   0,              Button1,        setlayout,      { 0 } },
    { ClkLtSymbol,   0,              Button3,        setlayout,      { .v = &layouts[2] } },
    { ClkWinTitle,   0,              Button2,        zoom,           { 0 } },
    { ClkStatusText, 0,              Button2,        spawn,          { .v = termcmd } },
    { ClkClientWin,  MODKEY,         Button1,        movemouse,      { 0 } },
    { ClkClientWin,  MODKEY,         Button2,        togglefloating, { 0 } },
    { ClkClientWin,  MODKEY,         Button1,        resizemouse,    { 0 } },
    { ClkTagBar,     0,              Button1,        view,           { 0 } },
    { ClkTagBar,     0,              Button3,        toggleview,     { 0 } },
    { ClkTagBar,     MODKEY,         Button1,        tag,            { 0 } },
    { ClkTagBar,     MODKEY,         Button3,        toggletag,      { 0 } },
};
