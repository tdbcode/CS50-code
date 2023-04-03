-- First query, as suggested in video, to find crime scene description
select description from crime_scene_reports where month = 7 and day = 28 and street = 'Humphrey Street';

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. Littering took place at 16:36. No known witnesses.

-- Find interviews on or after the date of 28th July
select name, day, month, transcript from interviews where month >= 7;

-- Ruth saw the thief get into a car in bakery parking lot within 10 minutes of theft and drove away. Security footage may have cars leaving the parking lot within that time frame
-- Eugene saw the thief at an ATM on Leggett Street withdrawing money
-- Raymond saw the thief call someone for less than 1 minute. He head the thief say they were planning to take earliest flight out of fiftyville on the 29th - asked the person to purchase the ticket for the thief.


