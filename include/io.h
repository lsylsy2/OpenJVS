#ifndef IO_H_
#define IO_H_

#include <stdio.h>
#include <stdlib.h>

#define JVS_MAX_STATE_SIZE 16

typedef enum
{
    BUTTON_TEST = 1 << 7, // System Buttons
    BUTTON_TILT_1 = 1 << 6,
    BUTTON_TILT_2 = 1 << 5,
    BUTTON_TILT_3 = 1 << 4,
    BUTTON_TILT_4 = 1 << 3,
    BUTTON_TILT_5 = 1 << 2,
    BUTTON_TILT_6 = 1 << 1,
    BUTTON_TILT_7 = 1 << 0,
    BUTTON_START = 1 << 15, // Player Buttons
    BUTTON_SERVICE = 1 << 14,
    BUTTON_UP = 1 << 13,
    BUTTON_DOWN = 1 << 12,
    BUTTON_LEFT = 1 << 11,
    BUTTON_RIGHT = 1 << 10,
    BUTTON_1 = 1 << 9,
    BUTTON_2 = 1 << 8,
    BUTTON_3 = 1 << 7,
    BUTTON_4 = 1 << 6,
    BUTTON_5 = 1 << 5,
    BUTTON_6 = 1 << 4,
    BUTTON_7 = 1 << 3,
    BUTTON_8 = 1 << 2,
    BUTTON_9 = 1 << 1,
    BUTTON_10 = 1 << 0,
    ANALOGUE_1 = 0, // Analogue Inputs
    ANALOGUE_2 = 1,
    ANALOGUE_3 = 2,
    ANALOGUE_4 = 3,
    ANALOGUE_5 = 4,
    ANALOGUE_6 = 5,
    ANALOGUE_7 = 6,
    ANALOGUE_8 = 7,
    ANALOGUE_9 = 8,
    ANALOGUE_10 = 9,
    ROTARY_1 = 0, // Rotary Inputs
    ROTARY_2 = 1,
    ROTARY_3 = 2,
    ROTARY_4 = 3,
    ROTARY_5 = 4,
    ROTARY_6 = 5,
    ROTARY_7 = 6,
    ROTARY_8 = 7,
    ROTARY_9 = 8,
    ROTARY_10 = 9,
} JVSInput;

static const struct
{
    const char *string;
    JVSInput input;
} jvsInputConversion[] = {
    {"BUTTON_TEST", BUTTON_TEST},
    {"BUTTON_TILT_1", BUTTON_TILT_1},
    {"BUTTON_TILT_2", BUTTON_TILT_2},
    {"BUTTON_TILT_3", BUTTON_TILT_3},
    {"BUTTON_TILT_4", BUTTON_TILT_4},
    {"BUTTON_TILT_5", BUTTON_TILT_5},
    {"BUTTON_TILT_6", BUTTON_TILT_6},
    {"BUTTON_TILT_7", BUTTON_TILT_7},
    {"BUTTON_START", BUTTON_START},
    {"BUTTON_SERVICE", BUTTON_SERVICE},
    {"BUTTON_UP", BUTTON_UP},
    {"BUTTON_DOWN", BUTTON_DOWN},
    {"BUTTON_LEFT", BUTTON_LEFT},
    {"BUTTON_RIGHT", BUTTON_RIGHT},
    {"BUTTON_1", BUTTON_1},
    {"BUTTON_2", BUTTON_2},
    {"BUTTON_3", BUTTON_3},
    {"BUTTON_4", BUTTON_4},
    {"BUTTON_5", BUTTON_5},
    {"BUTTON_6", BUTTON_6},
    {"BUTTON_7", BUTTON_7},
    {"BUTTON_8", BUTTON_8},
    {"BUTTON_9", BUTTON_9},
    {"BUTTON_10", BUTTON_10},
    {"ANALOGUE_1", ANALOGUE_1},
    {"ANALOGUE_2", ANALOGUE_2},
    {"ANALOGUE_3", ANALOGUE_3},
    {"ANALOGUE_4", ANALOGUE_4},
    {"ANALOGUE_5", ANALOGUE_5},
    {"ANALOGUE_6", ANALOGUE_6},
    {"ANALOGUE_7", ANALOGUE_7},
    {"ANALOGUE_8", ANALOGUE_8},
    {"ANALOGUE_9", ANALOGUE_9},
    {"ANALOGUE_10", ANALOGUE_10},
    {"ROTARY_1", ROTARY_1},
    {"ROTARY_2", ROTARY_2},
    {"ROTARY_3", ROTARY_3},
    {"ROTARY_4", ROTARY_4},
    {"ROTARY_5", ROTARY_5},
    {"ROTARY_6", ROTARY_6},
    {"ROTARY_7", ROTARY_7},
    {"ROTARY_8", ROTARY_8},
    {"ROTARY_9", ROTARY_9},
    {"ROTARY_10", ROTARY_10},
};

typedef enum
{
    SYSTEM = 0,
    PLAYER_1 = 1,
    PLAYER_2 = 2,
    PLAYER_3 = 3,
    PLAYER_4 = 4,
} JVSPlayer;

static const struct
{
    const char *string;
    JVSPlayer player;
} jvsPlayerConversion[] = {
    {"SYSTEM", SYSTEM},
    {"PLAYER_1", PLAYER_1},
    {"PLAYER_2", PLAYER_2},
    {"PLAYER_3", PLAYER_3},
    {"PLAYER_4", PLAYER_4},
};

typedef struct
{
    int coinCount[JVS_MAX_STATE_SIZE];
    int inputSwitch[JVS_MAX_STATE_SIZE];
    int analogueChannel[JVS_MAX_STATE_SIZE];
    int gunChannel[JVS_MAX_STATE_SIZE];
    int rotaryChannel[JVS_MAX_STATE_SIZE];
	int idolmasterIsScreenPressed;
} JVSState;

typedef struct
{
    char *name;
    unsigned char commandVersion;
    unsigned char jvsVersion;
    unsigned char commsVersion;
    unsigned char players;
    unsigned char switches;
    unsigned char coins;
    unsigned char analogueInChannels;
    unsigned char analogueInBits;
    unsigned char rotaryChannels;
    unsigned char keypad;
    unsigned char gunChannels;
    unsigned char gunXBits;
    unsigned char gunYBits;
    unsigned char generalPurposeInputs;
    unsigned char card;
    unsigned char hopper;
    unsigned char generalPurposeOutputs;
    unsigned char analogueOutChannels;
    unsigned char displayOutRows;
    unsigned char displayOutColumns;
    unsigned char displayOutEncodings;
    unsigned char backup;
    char *displayName;
} JVSCapabilities;

/* Define the IO files here */
static const JVSCapabilities SEGA_TYPE_3_IO = {
    .name = "SEGA CORPORATION;I/O BD JVS;837-14572;Ver1.00;2005/10",
    .commandVersion = 0x13,
    .jvsVersion = 0x20,
    .commsVersion = 0x10,
    .players = 2,
    .switches = 14,
    .analogueInBits = 10,
    .analogueInChannels = 8,
    .generalPurposeOutputs = 20,
    .coins = 2,
    .displayName = "Sega Type 3 IO"};

static const JVSCapabilities SEGA_TYPE_1_IO;

static const JVSCapabilities NAMCO_JYU_IO = {
    .name = "namco ltd.;JYU-PCB;Ver1.00;JPN,2Coins 2Guns",
    .players = 2,
    .switches = 12,
    .commandVersion = 0x11,
    .jvsVersion = 0x20,
    .commsVersion = 0x10,
    .coins = 2,
    .generalPurposeOutputs = 16,
    .gunChannels = 2,
    .gunXBits = 16,
    .gunYBits = 16,
    .displayName = "Namco JYU IO"};

static const JVSCapabilities NAMCO_FCB_IO = {
    .name = "namco ltd.;FCB;Ver1.02;JPN,TouchPanel&Multipurpose",
    .commandVersion = 0x13,
    .jvsVersion = 0x20,
    .commsVersion = 0x30,
    .players = 0x01, //01 01 10 00
    .switches = 0x10,
    .coins = 0x02, //02 02 00 00
    .analogueInChannels = 0x07, //03 07 0A 00
	.analogueInBits = 0x0a,
	.rotaryChannels = 0x02, //04 02 00 00
    .gunXBits = 0x10, //06 10 10 01
    .gunYBits = 0x10,
    .gunChannels = 0x01,
    .generalPurposeOutputs = 0x06, //12 06 00 00
	.analogueOutChannels = 0x02, //13 02 00 00
    .displayName = "Namco FCB IO"};

static const struct
{
    const char *string;
    const JVSCapabilities capabilities;
} jvsCapabilitiesConversion[] = {
    {"SEGA_TYPE_3_IO", SEGA_TYPE_3_IO},
    {"NAMCO_JYU_IO", NAMCO_JYU_IO},
    {"NAMCO_FCB_IO", NAMCO_FCB_IO}};

JVSCapabilities *getCapabilities();
JVSState *getState();

int initIO(JVSCapabilities *capabilitiesSetup);
int setSwitch(JVSPlayer player, JVSInput switchNumber, int value);
int incrementCoin(JVSPlayer player);
int setAnalogue(JVSInput channel, double value);
int setGun(JVSInput channel, double value);
int setRotary(JVSInput channel, int value);

JVSInput jvsInputFromString(char *jvsInputString);
JVSPlayer jvsPlayerFromString(char *jvsPlayerString);
int jvsCapabilitiesFromString(JVSCapabilities *capabilities, char *jvsCapabilitiesString);
#endif // IO_H_
