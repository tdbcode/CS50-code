-- First query, as suggested in video, to find crime scene description
select description from crime_scene_reports where month = 7 and day = 28 and street = 'Humphrey Street';

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. Littering took place at 16:36. No known witnesses.

-- Find interviews on or after the date of 28th July
select name, transcript from interviews where month >= 7 and day >= 28;

-- theft got into car in bakery parking lot within 10 minutes of theft and drove away. Security footage may have cars leaving the parking lot within that time frame


