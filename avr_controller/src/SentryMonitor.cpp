/*
 *        Copyright (C) 2112 Garrett Brown <gbruin@ucla.edu>
 *
 *  This Program is free software; you can redistribute it and/or modify it
 *  under the terms of the Modified BSD License.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *     3. Neither the name of the organization nor the
 *        names of its contributors may be used to endorse or promote products
 *        derived from this software without specific prior written permission.
 *
 *  This Program is distributed AS IS in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "SentryMonitor.h"
#include "GPIO.h"
#include "BeagleBoardAddressBook.h"
#include "ArduinoAddressBook.h"
#include "ParamServer.h"

#include <unistd.h> // for usleep()
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int main(int argc, char **argv)
{
	SentryMonitor justdoit;
	justdoit.Main();
	return 0;
}

void SentryMonitor::Main()
{
	cout << "Opening Arduino port" << endl;
	GPIO gpio(ARDUINO_BRIDGE1);
	gpio.Open();
	gpio.SetDirection(GPIO::OUT, 0);

	// Connect to the Arduino
	m_arduino.Open(ARDUINO_PORT);

	usleep(1000000); // 1s

	gpio.SetValue(1);

	cout << "Uploading Sentry" << endl;
	ParamServer::Sentry sentry;
	m_arduino.CreateFSM(sentry.GetString());

	int timeout = 0;
	string samples;
	while (timeout <= 5000)
	{
		string response;
		// Publish period = 1ms / 2 samples * 128 samples / message = 64ms
		if (m_arduino.Receive(FSM_ENCODER, response, 128))
		{
			// Parse the response manually
			if (response.length() <= 4)
			{
				cout << "Error: Invalid message length (" << response.length() << ")" << endl;
				break; // Invalid message
			}

			const uint8_t *bytes = reinterpret_cast<const uint8_t*>(response.c_str());
			unsigned int sampleCount = bytes[3];
			// Make sure we don't overshoot the size of the array
			if (sampleCount >  8 * (response.length() - 4))
			{
				cout << "Error: Invalid samples size (" << sampleCount << ")" << endl;
				break;
			}

			bytes += 4; // Fast-forward to pertinent data

			for (unsigned int i = 0; i < sampleCount; i++)
			{
				samples.push_back(bytes[i / 8] & (1 << (i % 8)) ? '1' : '0');
				samples.push_back(' ');
			}

			timeout = 0;
		}
		else
		{
			if (samples.length())
			{
				// Finished gathering our set of samples
				Process(samples);
				samples = "";
			}
			timeout += 128;
			// Report every second
			if (timeout % 1000 < 128)
				cout << "Timeout (" << timeout << " ms)..." << endl;
		}
	}
	cout << "Finished receiving data" << endl;
	m_arduino.DestroyFSM(sentry.GetString());
	gpio.SetValue(0);
}

void SentryMonitor::Process(const string &samples)
{
	static char i = '0';

	//get the current time from the clock -- one second resolution
	string filename = CurrentDateTime() + "-" + i + ".txt";
	ofstream myfile;
	myfile.open(filename.c_str());
	myfile << samples;
	myfile.close();

	if (i++ == '9')
		i = '0';

	cout << "Samples:" << endl;
	cout << samples << endl << endl;
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string SentryMonitor::CurrentDateTime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://www.cplusplus.com/reference/clibrary/ctime/strftime/
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return buf;
}
