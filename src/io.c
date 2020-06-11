#include <string.h>
#include <math.h>

#include "io.h"
#include "debug.h"

JVSCapabilities capabilities;
JVSState state;

int analogueMax;
int gunXMax;
int gunYMax;

JVSCapabilities *getCapabilities()
{
	return &capabilities;
}

JVSState *getState()
{
	return &state;
}

int initIO(JVSCapabilities *capabilitiesSetup)
{
	memcpy(&capabilities, capabilitiesSetup, sizeof(JVSCapabilities));

	for (int player = 0; player < (capabilities.players + 1); player++)
		state.inputSwitch[player] = 0;

	for (int analogueChannels = 0; analogueChannels < capabilities.analogueInChannels; analogueChannels++)
		state.analogueChannel[analogueChannels] = 0;

	for (int rotaryChannels = 0; rotaryChannels < capabilities.rotaryChannels; rotaryChannels++)
		state.rotaryChannel[rotaryChannels] = 0;

	// for (int player = 0; player < capabilities.coins; player++)
		// state.coinCount[player] = 1;

	analogueMax = pow(2, capabilities.analogueInBits) - 1;
	gunXMax = pow(2, capabilities.gunXBits) - 1;
	gunYMax = pow(2, capabilities.gunYBits) - 1;

	return 1;
}

int setSwitch(JVSPlayer player, JVSInput switchNumber, int value)
{
	if (player > capabilities.players)
	{
		printf("Error: That player does not exist.\n");
		return 0;
	}

	if (value)
	{
		state.inputSwitch[player] |= switchNumber;
	}
	else
	{
		state.inputSwitch[player] &= ~switchNumber;
	}

	return 1;
}

int setIdolmasterIsScreenPressed(int value)
{
    state.idolmasterIsScreenPressed = value;
    debug(1, "setIdolmasterIsScreenPressed %d\n", value);
    return 1;
}

int incrementCoin(JVSPlayer player)
{
	if (player == SYSTEM)
		return 0;

	state.coinCount[player - 1]++;
	return 1;
}

int setAnalogue(JVSInput channel, double value)
{
	if (channel >= capabilities.analogueInChannels)
		return 0;
	state.analogueChannel[channel] = (int)((double)value * (double)analogueMax);
	return 1;
}

int setGun(JVSInput channel, double value)
{
    if (strstr(capabilities.name, "FCB")) {
        int minValue = 0x0002;
        int maxValue = 0xffff - minValue;
        if (channel % 2 == 0)
        {
            state.gunChannel[channel] = minValue + (int)((double)value * (double)(maxValue - minValue));
        }
        else
        {
            state.gunChannel[channel] = minValue + (int)((double)((double)1.0 - value) * (double)(maxValue - minValue));
        }
        return 1;
    }
    
	if (channel % 2 == 0)
	{
		state.gunChannel[channel] = (int)((double)value * (double)gunXMax);
	}
	else
	{
		state.gunChannel[channel] = (int)((double)((double)1.0 - value) * (double)gunYMax);
	}
	return 1;
}

int setRotary(JVSInput channel, int value)
{
	if (channel >= capabilities.rotaryChannels)
		return 0;

	state.rotaryChannel[channel] = value;
	return 1;
}

JVSInput jvsInputFromString(char *jvsInputString)
{
	for (long unsigned int i = 0; i < sizeof(jvsInputConversion) / sizeof(jvsInputConversion[0]); i++)
	{
		if (strcmp(jvsInputConversion[i].string, jvsInputString) == 0)
			return jvsInputConversion[i].input;
	}
	debug(0, "Error: Could not find the JVS INPUT string specified for %s\n", jvsInputString);
	return -1;
}

JVSPlayer jvsPlayerFromString(char *jvsPlayerString)
{
	for (long unsigned int i = 0; i < sizeof(jvsPlayerConversion) / sizeof(jvsPlayerConversion[0]); i++)
	{
		if (strcmp(jvsPlayerConversion[i].string, jvsPlayerString) == 0)
			return jvsPlayerConversion[i].player;
	}
	debug(0, "Error: Could not find the JVS PLAYER string specified for %s\n", jvsPlayerString);
	return -1;
}

int jvsCapabilitiesFromString(JVSCapabilities *capabilities, char *jvsCapabilitiesString)
{
	for (long unsigned int i = 0; i < sizeof(jvsCapabilitiesConversion) / sizeof(jvsCapabilitiesConversion[0]); i++)
	{
		if (strcmp(jvsCapabilitiesConversion[i].string, jvsCapabilitiesString) == 0)
		{
			memcpy(capabilities, &jvsCapabilitiesConversion[i].capabilities, sizeof(JVSCapabilities));
			return 1;
		}
	}

	debug(0, "Error: Could not find the JVS CAPABILITIES string specified for %s\n", jvsCapabilitiesString);
	return 0;
}
