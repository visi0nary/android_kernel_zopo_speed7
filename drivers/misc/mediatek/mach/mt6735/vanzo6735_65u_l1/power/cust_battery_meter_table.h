#ifndef _CUST_BATTERY_METER_TABLE_H
#define _CUST_BATTERY_METER_TABLE_H

#include <mach/mt_typedefs.h>

// ============================================================
// define
// ============================================================
#define BAT_NTC_10 1
#define BAT_NTC_47 0

#if (BAT_NTC_10 == 1)
#define RBAT_PULL_UP_R             16900	
#endif

#if (BAT_NTC_47 == 1)
#define RBAT_PULL_UP_R             61900	
#endif
#define RBAT_PULL_UP_VOLT          1800



// ============================================================
// ENUM
// ============================================================

// ============================================================
// structure
// ============================================================

// ============================================================
// typedef
// ============================================================
typedef struct _BATTERY_PROFILE_STRUC
{
    kal_int32 percentage;
    kal_int32 voltage;
} BATTERY_PROFILE_STRUC, *BATTERY_PROFILE_STRUC_P;

typedef struct _R_PROFILE_STRUC
{
    kal_int32 resistance; // Ohm
    kal_int32 voltage;
} R_PROFILE_STRUC, *R_PROFILE_STRUC_P;

typedef enum
{
    T1_0C,
    T2_25C,
    T3_50C
} PROFILE_TEMPERATURE;

// ============================================================
// External Variables
// ============================================================

// ============================================================
// External function
// ============================================================

// ============================================================
// <DOD, Battery_Voltage> Table
// ============================================================
#if (BAT_NTC_10 == 1)
    BATT_TEMPERATURE Batt_Temperature_Table[] = {
        {-20,68237},
        {-15,53650},
        {-10,42506},
        { -5,33892},
        {  0,27219},
        {  5,22021},
        { 10,17926},
        { 15,14674},
        { 20,12081},
        { 25,10000},
        { 30,8315},
        { 35,6948},
        { 40,5834},
        { 45,4917},
        { 50,4161},
        { 55,3535},
        { 60,3014}
    };
#endif

#if (BAT_NTC_47 == 1)
    BATT_TEMPERATURE Batt_Temperature_Table[] = {
        {-20,483954},
        {-15,360850},
        {-10,271697},
        { -5,206463},
        {  0,158214},
        {  5,122259},
        { 10,95227},
        { 15,74730},
        { 20,59065},
        { 25,47000},
        { 30,37643},
        { 35,30334},
        { 40,24591},
        { 45,20048},
        { 50,16433},
        { 55,13539},
        { 60,11210}        
    };
#endif

// T0 -10C
BATTERY_PROFILE_STRUC battery_profile_t0[] =
{
	{0,4177},
	{1,4162},
	{3,4148},
	{5,4124},
	{7,4084},
	{9,4053},
	{11,4025},
	{13,4001},
	{15,3986},
	{17,3975},
	{19,3965},
	{21,3955},
	{23,3944},
	{25,3932},
	{27,3920},
	{29,3907},
	{31,3894},
	{33,3884},
	{34,3874},
	{36,3865},
	{38,3857},
	{40,3849},
	{42,3842},
	{44,3836},
	{46,3829},
	{48,3824},
	{50,3819},
	{52,3813},
	{54,3807},
	{56,3802},
	{58,3797},
	{60,3791},
	{62,3787},
	{64,3782},
	{66,3776},
	{68,3772},
	{69,3768},
	{71,3762},
	{73,3756},
	{75,3751},
	{77,3744},
	{79,3736},
	{81,3729},
	{83,3721},
	{85,3714},
	{87,3708},
	{89,3703},
	{91,3692},
	{93,3672},
	{95,3634},
	{97,3570},
	{98,3499},
	{99,3472},
	{99,3458},
	{99,3450},
	{99,3444},
	{99,3439},
	{99,3436},
	{99,3433},
	{99,3430},
	{99,3428},
	{99,3427},
	{99,3426},
	{99,3424},
	{99,3423},
	{99,3422},
	{99,3421},
	{99,3419},
	{99,3418},
	{99,3417},
	{99,3415},
	{99,3414},
	{99,3413},
	{100,3412},
	{100,3400}
};

// T1 0C
BATTERY_PROFILE_STRUC battery_profile_t1[] =
{
	{0,4172},
	{1,4144},
	{3,4117},
	{4,4094},
	{6,4078},
	{7,4061},
	{9,4041},
	{11,4023},
	{12,4006},
	{14,3995},
	{15,3986},
	{17,3978},
	{18,3970},
	{20,3961},
	{22,3951},
	{23,3943},
	{25,3934},
	{26,3925},
	{28,3916},
	{29,3906},
	{31,3895},
	{33,3884},
	{34,3872},
	{36,3861},
	{37,3852},
	{39,3842},
	{40,3836},
	{42,3829},
	{44,3824},
	{45,3819},
	{47,3813},
	{48,3807},
	{50,3804},
	{51,3800},
	{53,3797},
	{55,3794},
	{56,3791},
	{58,3787},
	{59,3785},
	{61,3783},
	{62,3780},
	{64,3778},
	{66,3775},
	{67,3774},
	{69,3771},
	{70,3768},
	{72,3765},
	{73,3761},
	{75,3757},
	{77,3753},
	{78,3748},
	{80,3742},
	{81,3736},
	{83,3730},
	{85,3722},
	{86,3714},
	{88,3705},
	{89,3700},
	{91,3697},
	{92,3691},
	{94,3676},
	{96,3636},
	{97,3571},
	{98,3491},
	{99,3455},
	{99,3431},
	{99,3413},
	{100,3400},
	{100,3391},
	{100,3383},
	{100,3377},
	{100,3371},
	{100,3367},
	{100,3364},
	{100,3364}
};

// T2 25C
BATTERY_PROFILE_STRUC battery_profile_t2[] =
{
	{0,4183},
	{1,4164},
	{2,4148},
	{4,4133},
	{5,4118},
	{7,4104},
	{8,4091},
	{10,4078},
	{11,4066},
	{13,4053},
	{14,4040},
	{16,4026},
	{17,4014},
	{19,4003},
	{20,3993},
	{21,3983},
	{23,3973},
	{24,3964},
	{26,3955},
	{27,3945},
	{29,3936},
	{30,3928},
	{32,3919},
	{33,3911},
	{35,3901},
	{36,3892},
	{38,3881},
	{39,3867},
	{41,3856},
	{42,3846},
	{43,3837},
	{45,3831},
	{46,3824},
	{48,3819},
	{49,3813},
	{51,3809},
	{52,3804},
	{54,3800},
	{55,3796},
	{57,3793},
	{58,3790},
	{60,3787},
	{61,3784},
	{63,3781},
	{64,3779},
	{65,3777},
	{67,3775},
	{68,3773},
	{70,3769},
	{71,3763},
	{73,3759},
	{74,3753},
	{76,3748},
	{77,3744},
	{79,3739},
	{80,3735},
	{82,3729},
	{83,3723},
	{84,3715},
	{86,3710},
	{87,3701},
	{89,3691},
	{90,3687},
	{92,3685},
	{93,3680},
	{95,3665},
	{96,3620},
	{98,3551},
	{99,3446},
	{100,3288},
	{100,3288},
	{100,3288},
	{100,3288},
	{100,3288},
	{100,3288}
};

// T3 50C
BATTERY_PROFILE_STRUC battery_profile_t3[] =
{
	{0,4189},
	{1,4170},
	{2,4155},
	{4,4139},
	{5,4124},
	{7,4110},
	{8,4097},
	{10,4083},
	{11,4071},
	{13,4058},
	{14,4046},
	{15,4033},
	{17,4021},
	{18,4010},
	{20,3999},
	{21,3988},
	{23,3978},
	{24,3967},
	{26,3958},
	{27,3948},
	{29,3939},
	{30,3930},
	{31,3922},
	{33,3913},
	{34,3905},
	{36,3896},
	{37,3887},
	{39,3875},
	{40,3861},
	{42,3848},
	{43,3839},
	{45,3832},
	{46,3825},
	{47,3820},
	{49,3813},
	{50,3809},
	{52,3804},
	{53,3800},
	{55,3795},
	{56,3792},
	{58,3788},
	{59,3784},
	{61,3782},
	{62,3779},
	{63,3777},
	{65,3774},
	{66,3771},
	{68,3769},
	{69,3763},
	{71,3754},
	{72,3746},
	{74,3741},
	{75,3736},
	{76,3730},
	{78,3726},
	{79,3722},
	{81,3717},
	{82,3712},
	{84,3704},
	{85,3697},
	{87,3690},
	{88,3681},
	{90,3673},
	{91,3672},
	{92,3668},
	{94,3660},
	{95,3631},
	{97,3577},
	{98,3500},
	{100,3381},
	{100,3381},
	{100,3381},
	{100,3381},
	{100,3381},
	{100,3381}
};

// battery profile for actual temperature. The size should be the same as T1, T2 and T3
BATTERY_PROFILE_STRUC battery_profile_temperature[] =
{
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 }
};
// T0 -10C
R_PROFILE_STRUC r_profile_t0[] =
{
	{268,4177},
	{267,4162},
	{280,4148},
	{285,4124},
	{322,4084},
	{402,4053},
	{470,4025},
	{512,4001},
	{535,3986},
	{545,3975},
	{550,3965},
	{555,3955},
	{555,3944},
	{555,3932},
	{555,3920},
	{547,3907},
	{542,3894},
	{542,3884},
	{542,3874},
	{545,3865},
	{545,3857},
	{547,3849},
	{552,3842},
	{555,3836},
	{557,3829},
	{560,3824},
	{565,3819},
	{570,3813},
	{567,3807},
	{575,3802},
	{577,3797},
	{577,3791},
	{585,3787},
	{587,3782},
	{587,3776},
	{590,3772},
	{597,3768},
	{595,3762},
	{597,3756},
	{602,3751},
	{600,3744},
	{600,3736},
	{607,3729},
	{610,3721},
	{617,3714},
	{632,3708},
	{657,3703},
	{682,3692},
	{702,3672},
	{717,3634},
	{737,3570},
	{750,3499},
	{682,3472},
	{647,3458},
	{625,3450},
	{612,3444},
	{602,3439},
	{595,3436},
	{587,3433},
	{580,3430},
	{577,3428},
	{575,3427},
	{575,3426},
	{575,3424},
	{575,3423},
	{560,3422},
	{570,3421},
	{552,3419},
	{560,3418},
	{555,3417},
	{555,3415},
	{562,3414},
	{570,3413},
	{565,3412},
	{532,3400}
};

// T1 0C
R_PROFILE_STRUC r_profile_t1[] =
{
	{225,4172},
	{225,4144},
	{245,4117},
	{270,4094},
	{292,4078},
	{302,4061},
	{305,4041},
	{312,4023},
	{315,4006},
	{320,3995},
	{325,3986},
	{332,3978},
	{337,3970},
	{337,3961},
	{337,3951},
	{342,3943},
	{345,3934},
	{347,3925},
	{347,3916},
	{345,3906},
	{340,3895},
	{335,3884},
	{330,3872},
	{322,3861},
	{320,3852},
	{312,3842},
	{315,3836},
	{312,3829},
	{317,3824},
	{320,3819},
	{320,3813},
	{317,3807},
	{322,3804},
	{327,3800},
	{327,3797},
	{332,3794},
	{335,3791},
	{332,3787},
	{337,3785},
	{340,3783},
	{337,3780},
	{340,3778},
	{340,3775},
	{345,3774},
	{342,3771},
	{342,3768},
	{345,3765},
	{342,3761},
	{342,3757},
	{347,3753},
	{347,3748},
	{347,3742},
	{350,3736},
	{352,3730},
	{350,3722},
	{352,3714},
	{352,3705},
	{362,3700},
	{385,3697},
	{417,3691},
	{447,3676},
	{477,3636},
	{560,3571},
	{730,3491},
	{640,3455},
	{582,3431},
	{532,3413},
	{502,3400},
	{480,3391},
	{467,3383},
	{450,3377},
	{432,3371},
	{420,3367},
	{420,3364},
	{420,3364}
};

// T2 25C
R_PROFILE_STRUC r_profile_t2[] =
{
	{138,4183},
	{137,4164},
	{140,4148},
	{140,4133},
	{140,4118},
	{140,4104},
	{142,4091},
	{142,4078},
	{145,4066},
	{145,4053},
	{147,4040},
	{147,4026},
	{150,4014},
	{152,4003},
	{155,3993},
	{157,3983},
	{157,3973},
	{160,3964},
	{165,3955},
	{165,3945},
	{165,3936},
	{170,3928},
	{170,3919},
	{172,3911},
	{170,3901},
	{172,3892},
	{167,3881},
	{157,3867},
	{152,3856},
	{147,3846},
	{142,3837},
	{142,3831},
	{142,3824},
	{142,3819},
	{140,3813},
	{142,3809},
	{142,3804},
	{142,3800},
	{142,3796},
	{142,3793},
	{145,3790},
	{147,3787},
	{150,3784},
	{147,3781},
	{150,3779},
	{152,3777},
	{152,3775},
	{152,3773},
	{147,3769},
	{142,3763},
	{145,3759},
	{140,3753},
	{140,3748},
	{142,3744},
	{142,3739},
	{145,3735},
	{145,3729},
	{145,3723},
	{142,3715},
	{150,3710},
	{147,3701},
	{142,3691},
	{147,3687},
	{155,3685},
	{162,3680},
	{165,3665},
	{167,3620},
	{177,3551},
	{185,3446},
	{225,3288},
	{225,3288},
	{225,3288},
	{225,3288},
	{225,3288},
	{225,3288}
};

// T3 50C
R_PROFILE_STRUC r_profile_t3[] =
{
	{110,4189},
	{110,4170},
	{117,4155},
	{115,4139},
	{115,4124},
	{115,4110},
	{115,4097},
	{115,4083},
	{117,4071},
	{117,4058},
	{120,4046},
	{120,4033},
	{120,4021},
	{122,4010},
	{122,3999},
	{122,3988},
	{125,3978},
	{122,3967},
	{125,3958},
	{125,3948},
	{127,3939},
	{130,3930},
	{132,3922},
	{135,3913},
	{137,3905},
	{137,3896},
	{140,3887},
	{132,3875},
	{127,3861},
	{120,3848},
	{120,3839},
	{120,3832},
	{117,3825},
	{117,3820},
	{117,3813},
	{117,3809},
	{117,3804},
	{120,3800},
	{117,3795},
	{120,3792},
	{120,3788},
	{120,3784},
	{122,3782},
	{122,3779},
	{127,3777},
	{127,3774},
	{125,3771},
	{130,3769},
	{125,3763},
	{115,3754},
	{115,3746},
	{117,3741},
	{117,3736},
	{115,3730},
	{120,3726},
	{120,3722},
	{120,3717},
	{125,3712},
	{120,3704},
	{120,3697},
	{120,3690},
	{120,3681},
	{117,3673},
	{125,3672},
	{127,3668},
	{137,3660},
	{130,3631},
	{137,3577},
	{142,3500},
	{155,3381},
	{155,3381},
	{155,3381},
	{155,3381},
	{155,3381},
	{155,3381}
};

// r-table profile for actual temperature. The size should be the same as T1, T2 and T3
R_PROFILE_STRUC r_profile_temperature[] =
{
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 },
	{0  , 0 }
};    

// ============================================================
// function prototype
// ============================================================
int fgauge_get_saddles(void);
BATTERY_PROFILE_STRUC_P fgauge_get_profile(kal_uint32 temperature);

int fgauge_get_saddles_r_table(void);
R_PROFILE_STRUC_P fgauge_get_profile_r_table(kal_uint32 temperature);

#endif	//#ifndef _CUST_BATTERY_METER_TABLE_H

