-- Keep a log of any SQL queries you execute as you solve the mystery.

--Find Details of Crime
SELECT description FROM crime_scene_reports WHERE year = 2020 AND month = 07 AND day = 28 AND street LIKE 'Chamberlin Street';
--Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three 
--witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

--FIND Interviews
SELECT * FROM interviews WHERE year = 2020 AND month = 07 AND day = 28;
--RUTH: Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
--      If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--Eugene: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, 
--        I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--Raymond: As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. 
--      In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. 
--      The thief then asked the person on the other end of the phone to purchase the flight ticket.


--Get entrace details around the time of the crime
SELECT license_plate from courthouse_security_logs WHERE year = 2020 AND month = 07 AND day = 28 AND activity LIKE 'Exit' AND hour = 10 AND minute <=25 ORDER BY license_plate, hour;
--L93JTIZ ENTER: 8:18 EXIT: 10:21
--G412CB7 ENTER: 9:28 EXIT: 10:20
--94KL13X ENTER 8:23 EXIT 10:18
--6P58WS2 ENTER 9:20 EXIT 10:18
--5P2BI95 ENTER 9:15 EXIT 10:16
--4328GD8 ENTER 9:14 EXIT 10:19
--322W7JE ENTER 8:36 EXIT 10:23
--0NTHK55 ENTER 8:42 EXIT 10:23

--GET ATM details
SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 07 AND day = 28 AND atm_location LIKE 'Fifer Street' AND transaction_type LIKE 'withdraw';
--28500762 | 48
--28296815 | 20
--76054385 | 60
--49610011 | 50
--16153065 | 80
--25506511 | 20
--81061156 | 30
--26013199 | 35

--GET call details
SELECT * FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60;
--id | caller | receiver | year | month | day | duration
--221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
--224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
--233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
--251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
--254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
--255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
--261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
--279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
--281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54

--Get Flight Details
SELECT flights.id from flights 
JOIN airports ON flights.origin_airport_id = airports.id
WHERE year = 2020 AND month = 07 AND day = 29 AND airports.city LIKE 'Fiftyville'
ORDER BY hour, minute
LIMIT 1;
--36


--FIND Theif
SELECT name from people 
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60) 
AND license_plate IN(SELECT license_plate from courthouse_security_logs WHERE year = 2020 AND month = 07 AND day = 28 AND activity LIKE 'Exit' AND hour = 10 AND minute <=25) 

INTERSECT

SELECT name FROM people
JOIN bank_accounts ON people.id = person_id
WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 07 AND day = 28 AND atm_location LIKE 'Fifer Street' AND transaction_type LIKE 'withdraw')

INTERSECT

SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = 36;
--ERNEST!

--Find Destination
SELECT city FROM airports 
JOIN flights ON flights.destination_airport_id = airports.id
WHERE flights.id = 36;
--London

--Find Accomplice
SELECT name FROM people
JOIN phone_calls on people.phone_number = phone_calls.receiver
WHERE caller IN (SELECT phone_number from people where name LIKE 'Ernest') AND year = 2020 AND month = 07 AND day = 28 AND duration < 60;
--Berthold