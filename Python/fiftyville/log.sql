-- First query, as suggested in video, to find crime scene description
select description from crime_scene_reports where month = 7 and day = 28 and street = 'Humphrey Street';

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. Littering took place at 16:36. No known witnesses.

-- Find interviews on or after the date of 28th July
select name, day, month, transcript from interviews where month >= 7 and day >= 28;

-- Ruth saw the thief get into a car in bakery parking lot within 10 minutes of theft and drive away. Security footage may have cars leaving the parking lot within that time frame

select hour, minute, activity, license_plate from bakery_security_logs where hour = 10 and minute > 15 and minute < 25 and day = 28 and month = 7;
--License plates during that time frame:
--+------+--------+----------+---------------+
--| hour | minute | activity | license_plate |
--+------+--------+----------+---------------+
--| 10   | 16     | exit     | 5P2BI95       |
--| 10   | 18     | exit     | 94KL13X       |
--| 10   | 18     | exit     | 6P58WS2       |
--| 10   | 19     | exit     | 4328GD8       |
--| 10   | 20     | exit     | G412CB7       |
--| 10   | 21     | exit     | L93JTIZ       |
--| 10   | 23     | exit     | 322W7JE       |
--| 10   | 23     | exit     | 0NTHK55       |
--+------+--------+----------+---------------+

-- Raymond saw the thief call someone for less than 1 minute. He head the thief say they were planning to take earliest flight out of fiftyville on the 29th - asked the person to purchase the ticket for the thief.
select caller, receiver, duration from phone_calls where  month = 7 and day = 28 and duration < 60;
-- Short calls from that day:
--+----------------+----------------+----------+
--|     caller     |    receiver    | duration |
--+----------------+----------------+----------+
--| (130) 555-0289 | (996) 555-8899 | 51       |
--| (499) 555-9472 | (892) 555-8872 | 36       |
--| (367) 555-5533 | (375) 555-8161 | 45       |
--| (499) 555-9472 | (717) 555-1342 | 50       |
--| (286) 555-6063 | (676) 555-6554 | 43       |
--| (770) 555-1861 | (725) 555-3243 | 49       |
--| (031) 555-6622 | (910) 555-3251 | 38       |
--| (826) 555-1652 | (066) 555-9701 | 55       |
--| (338) 555-6650 | (704) 555-2131 | 54       |
--+----------------+----------------+----------+

-- Eugene recognised the thief (but didn't know who) at an ATM on Leggett Street withdrawing money
