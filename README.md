# UNIXTIME LIBRARY

Library for conversion from/to unix time stamp.

>The unix time stamp is a way to track time as a running total of seconds. This count starts at the Unix Epoch on January 1st, 1970 at UTC. Therefore, the unix time stamp is merely the number of seconds between a particular date and the Unix Epoch.


## Supported Hardware

- NUCLEO-L552ZE-Q

## How to use

- In your main, include `lib_unixtime.h`
- Use the functions:
    - `unix_from_date` : to convert a date into unix time.
    - `date_form_unix` : to convert a unix time into a date.


## Example

```C
//from date to unix timestamp
uint16_t years = 1997;
uint8_t month = 5;
uint8_t day = 6;
uint8_t hours =13;
uint8_t minutes = 30;
uint8_t seconds = 42;
uint64_t unix_timestamp;
unix_from_date(years,month,day,hours,minutes,seconds,&unix_timestamp); // stores the value 862918242 in unix_timestamp

//from unix timestamp to date
uint64_t t = 862918242;
date_form_unix(t,&years,&month,&day,&hours,&minutes,&seconds); // stores 1997 5 6 13 30 42
```
