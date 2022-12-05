/*!
	@file   lib_unix_time.h
	@brief  <brief description here>
	@t.odo	-
	---------------------------------------------------------------------------

	MIT License
	Copyright (c) 2021 Federico Carnevale, Ioannis Deligiannis
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
/******************************************************************************
* Preprocessor Definitions & Macros
******************************************************************************/

#define DEFAULT_2020 1577833200 // Years:2020 Month:01 Day:01 H:00 Min:00 Sec:00

/******************************************************************************
* Includes
******************************************************************************/

#include "lib_unix_time.h"

/******************************************************************************
* Enumerations, structures & Variables
******************************************************************************/

/******************************************************************************
* Declaration | Static Functions
******************************************************************************/

/******************************************************************************
* Definition  | Static Functions
******************************************************************************/

/******************************************************************************
* Definition  | Public Functions
******************************************************************************/

i_status date_form_unix(uint64_t t,uint16_t* years,uint8_t* month,uint8_t* day,uint8_t* hours,uint8_t* minutes, uint8_t* seconds)
{
 	uint32_t a,b,c,d,e,f;
	uint64_t _sec,_min,_h;

	
	if(t < 1) // Negative Unix time values are not supported
		return I_ERROR; //t = 0;

	// Clear milliseconds
	// date->milliseconds = 0;
	// Retrieve hours, minutes and seconds
	_sec = t % 60;
	t /= 60;
	_min = t % 60;
	t /= 60;
	_h = t % 24;
	t /= 24;

	// Convert Unix time to date
	a = (uint32_t) ((4 * t + 102032) / 146097 + 15);
	b = (uint32_t) (t + 2442113 + a - (a / 4));
	c = (20 * b - 2442) / 7305;
	d = b - 365 * c - (c / 4);
	e = d * 1000 / 30601;
	f = d - e * 30 - e * 601 / 1000;

	// January and February are counted as months 13 and 14 of the previous year
	if(e <= 13)
	{
		c -= 4716;
		e -= 1;
	}
	else
	{
		c -= 4715;
		e -= 13;
	}

	// Retrieve year, month and day
	*years = c;
	*month = e;
	*day = f;
	*minutes = _min;
	*seconds = _sec;
	*hours = _h;

	return I_OK;
}

i_status unix_from_date(uint16_t years,uint8_t month,uint8_t day,uint8_t hours,uint8_t minutes, uint8_t seconds,uint64_t* unix)
{
	uint16_t y;
	uint8_t m,d;
	uint64_t t;
	
	y = years; // Year	
	m = month; // Month of year	
	d = day; // Day of month

	// January and February are counted as months 13 and 14 of the previous year
	if(m <= 2)
	{
		m += 12;
		y -= 1;
	}
	
	t = (365 * y) + (y / 4) - (y / 100) + (y / 400); // Convert years to days	
	t += (30 * m) + (3 * (m + 1) / 5) + d; // Convert months to days	
	t -= 719561; // Unix time starts on January 1st, 1970	
	t *= 86400; // Convert days to seconds	
	t += (3600 * hours) + (60 * minutes) + seconds; // Add hours, minutes and seconds
	*unix = t; // Return Unix time
	
	return I_OK;

}

/******************************************************************************
* EOF - NO CODE AFTER THIS LINE
******************************************************************************/
