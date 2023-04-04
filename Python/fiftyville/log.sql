-- First query, as suggested in video, to find crime scene description
select description from crime_scene_reports where month = 7 and day = 28 and street = 'Humphrey Street';

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. Littering took place at 16:36. No known witnesses.

-- Find interviews on or after the date of 28th July
select name, day, month, transcript from interviews where month >= 7 and day >= 28;

-- Ruth saw the thief get into a car in bakery parking lot within 10 minutes of theft and drive away. Security footage may have cars leaving the parking lot within that time frame

select hour, minute, activity, license_plate from bakery_security_logs where hour = 10 and minute >= 15 and minute <= 25 and day = 28 and month = 7;
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

-- Eugene recognised the thief (but didn't know who) at an ATM earlier in the day on Leggett Street withdrawing money
select account_number, amount from atm_transactions where month = 7 and day = 28 and atm_location = 'Leggett Street' and transaction_type = 'withdraw';
-- account numbers and amount withdrawn from leggett street on that day
--+----------------+--------+
--| account_number | amount |
--+----------------+--------+
--| 28500762       | 48     |
--| 28296815       | 20     |
--| 76054385       | 60     |
--| 49610011       | 50     |
--| 16153065       | 80     |
--| 25506511       | 20     |
--| 81061156       | 30     |
--| 26013199       | 35     |
--+----------------+--------+

-- find people's name and phone numbers from the licence plate's found in the bakery logs on that day and time of exit
select name, phone_number from people where license_plate IN (select license_plate from bakery_security_logs where hour = 10 and minute > 15 and minute < 25 and day = 28 and month = 7 and activity='exit');
--+---------+----------------+
--|  name   |  phone_number  |
--+---------+----------------+
--| Vanessa | (725) 555-4692 |
--| Barry   | (301) 555-4174 |
--| Iman    | (829) 555-5269 |
--| Sofia   | (130) 555-0289 |
--| Luca    | (389) 555-5198 |
--| Diana   | (770) 555-1861 |
--| Kelsey  | (499) 555-9472 |
--| Bruce   | (367) 555-5533 |
--+---------+----------------+

select name from people where phone_number IN(select caller from phone_calls where  month = 7 and day = 28 and duration < 60);
--List of suspects who made calls that day under 1 minute long
--+---------+
--|  name   |
--+---------+
--| Kenny   |
--| Sofia   |
--| Benista |
--| Taylor  |
--| Diana   |
--| Kelsey  |
--| Bruce   |
--| Carina  |
--+---------+

select name from people where phone_number IN(select receiver from phone_calls where  month = 7 and day = 28 and duration < 60);
--List of potential accomplices
--+------------+
--|    name    |
--+------------+
--| James      |
--| Larry      |
--| Anna       |
--| Jack       |
--| Melissa    |
--| Jacqueline |
--| Philip     |
--| Robin      |
--| Doris      |
--+------------+

-- Look for earliest flight from Fiftyville airport that day and where it goes to

select name from airports where id IN (
    select destination_airport_id from flights where day = 29 and month = 7 and origin_airport_id IN (
        select id from airports where city = 'Fiftyville') ORDER BY hour, minute ASC LIMIT 1);

--+---------------+
--|     city      |
--+---------------+
--| New York City |
--+---------------+


-- Now we get the ID of that flight as we know the city for the answers.txt
select id from flights where day = 29 and month = 7 and origin_airport_id IN (
    select id from airports where city = 'Fiftyville')
        ORDER BY hour, minute ASC LIMIT 1;


--REDUNDANT:
--select MIN(hour) from flights
  --  where day = 29 and month = 7 and
    --origin_airport_id IN (select id from airports where city = 'Fiftyville');

--+-----------+
--| MIN(hour) |
--+-----------+
--| 8         |
--+-----------+

--REDUNDANT:
-- Now we know the hour we can use this query to select the first flight from Fiftyville with this hour.

--select city from airports where id in (
--select destination_airport_id from flights where hour = (select MIN(hour) from flights
  --  where day = 29 and month = 7 and
    --origin_airport_id IN (select id from airports where city = 'Fiftyville')) ORDER BY hour, minute ASC LIMIT 1);

--+------------------------+
--| destination_airport_id |
--+------------------------+
--| 1                      |
--+------------------------+

-- get passport numbers of all the passengers on that flight
select passport_number from passengers where flight_id in (
    select id from flights where day = 29 and month = 7 and origin_airport_id IN (
    select id from airports where city = 'Fiftyville')
        ORDER BY hour, minute ASC LIMIT 1);

--+-----------------+
--| passport_number |
--+-----------------+
--| 7214083635      |
--| 1695452385      |
--| 5773159633      |
--| 1540955065      |
--| 8294398571      |
--| 1988161715      |
--| 9878712108      |
--| 8496433585      |
--+-----------------+

-- start bringing it all together by merging queries

select name from people
where people.license_plate IN (select license_plate from bakery_security_logs where hour = 10 and minute >= 15 and minute <= 25 and day = 28 and month = 7)
AND
people.phone_number IN (select caller from phone_calls where  month = 7 and day = 28 and duration < 60);

Reducing suspects down
+--------+
|  name  |
+--------+
| Sofia  |
| Diana  |
| Kelsey |
| Bruce  |
+--------+

-- then we need to include flight passenger passport number

select name from people
where people.license_plate IN (select license_plate from bakery_security_logs where hour = 10 and minute >= 15 and minute <= 25 and day = 28 and month = 7)
AND
people.phone_number IN (select caller from phone_calls where  month = 7 and day = 28 and duration < 60)
AND
people.passport_number IN (
    select passport_number from passengers where flight_id in (
        select id from flights where day = 29 and month = 7 and origin_airport_id IN (
            select id from airports where city = 'Fiftyville')
                ORDER BY hour, minute ASC LIMIT 1)
);

--+--------+
--|  name  |
--+--------+
--| Sofia  |
--| Kelsey |
--| Bruce  |
--+--------+

--Now we need to work out the ATM transaction

select name from people
where people.license_plate IN (select license_plate from bakery_security_logs where hour = 10 and minute >= 15 and minute <= 25 and day = 28 and month = 7)
AND
people.phone_number IN (select caller from phone_calls where  month = 7 and day = 28 and duration < 60)
AND
people.passport_number IN (
    select passport_number from passengers where flight_id in (
        select id from flights where day = 29 and month = 7 and origin_airport_id IN (
            select id from airports where city = 'Fiftyville')
                ORDER BY hour, minute ASC LIMIT 1)
AND

select account_number, amount from atm_transactions where month = 7 and day = 28 and atm_location = 'Leggett Street' and transaction_type = 'withdraw';


);



