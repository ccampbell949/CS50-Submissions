-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND year = 2020
AND street = "Chamberlin Street";

--Theft of the CS50 duck took place at 10:15am at the 
--Chamberlin Street courthouse. Interviews were conducted 
--today with three witnesses who were present at the time — 
--each of their interview transcripts mentions the courthouse.

SELECT transcript
FROM interviews
WHERE day = 28 AND month = 7 AND year = 2020;

--“Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
--“I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
--“You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
--Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.


-- First point of interest: 
--Sometime within ten minutes of the theft, I saw the 
--thief get into a car in the courthouse parking lot and
--drive away. If you have security footage from the 
--courthouse parking lot, you might want to look for 
--cars that left the parking lot in that time frame.

--Theft took place at 10.15am - time window 10.15-10.25am
--same date

SELECT name
FROM people
JOIN court_house_security_logs ON people.license_plate = courthouse_security_logs.license_plate
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit";

--Results: 
--Patrick
--Ernest
--Amber
--Danielle
--Roger
--Elizabeth
--Russell
--Evelyn

--Point of interest:
--I don't know the thief's name, but it was 
--someone I recognized. Earlier this morning, before I
--arrived at the courthouse, I was walking by the ATM on 
--Fifer Street and saw the thief there withdrawing some 
--money.


SELECT DISTINCT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street";

--Results:
--Danielle SUSPECT
--Bobby
--Madison
--Ernest SUSPECT
--Roy
--Elizabeth SUSPECT
--Victoria
--Russell SUSPECT

--Danielle, Ernest, Elizabeth and Russell appear in both lists 

--Point of interest:
----As the thief was leaving the courthouse, 
--they called someone who talked to them for 
--less than a minute. In the call, I heard the
--thief say that they were planning to take the 
--earliest flight out of Fiftyville tomorrow. The 
--thief then asked the person on the other end of 
--the phone to purchase the flight ticket.


--call less than 1min

SELECT DISTINCT name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

--Results: 
--Roger
--Evelyn
--Ernest SUSPECT
--Madison
--Russell SUSPECT
--Kimberly
--Bobby
--Victoria


--check flight passengers on earliest flight the follwoing day

SELECT name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE flight_id = (
SELECT id
FROM flights
WHERE year = 2020 AND month = 7 AND day = 29 --following morning
ORDER BY hour, minute --sort by time
LIMIT 1); --earliest / First Flight

--Results:
--Doris
--Roger
--Ernest SUSPECT
--Edward
--Evelyn
--Madison
--Bobby
--Danielle

--Thief is Ernest


--City escaped to
--use flight table

SELECT city
FROM airports
WHERE id = (
SELECT destination_airport_id
FROM flights
WHERE year = 2020 AND month = 7 AND day = 29
ORDER BY hour, minute
LIMIT 1);
--Result = London

--Accomplice
--use phonecalls less than 1min

SELECT name 
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE year =2020 AND month = 7 AND day = 28 AND duration < 60 
AND caller = (SELECT phone_number
FROM people
WHERE name = "Ernest");

--Result = Berthold
