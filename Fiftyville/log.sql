-- Keep a log of any SQL queries you execute as you solve the mystery.

-- First .schema

-- Check the description of the crime happened at the given time & location.
SELECT description
  FROM crime_scene_reports
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND street = 'Humphrey Street';

-- Two incidents happened that day. Only one is related to theft. Other is related to littering.

-- The witnesses could be the accomplice. So, finding the names of the witnesses from the interviews table and checked their transcripts.
SELECT name, transcript
  FROM interviews
 WHERE year = 2021
   AND month = 7
   AND day = 28;

-- Found two transcripts with the name Eugene, so check how many Eugenes are in the 'people' table.
SELECT name
  FROM people
 WHERE name = 'Eugene';
-- Found out that there is only one Eugene. So, proceeding accordingly.

-- Findling the names of the three witnesses from the list of people who gave interviews on July 28, 2021. The crime report said that the witnesses mentioned "bakery" in their transcripts. They also order the results alphabetically by the names of witnesses.
SELECT name, transcript
  FROM interviews
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND transcript LIKE '%bakery%'
 ORDER BY name;
-- Witnesses are Eugene, Raymond, and Ruth.


-- Eugene gave clues. The thief was withdrawing money from the ATM on Leggett Street. So, check the account number of the person who did that transaction.
SELECT account_number, amount
  FROM atm_transactions
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND atm_location = 'Leggett Street'
   AND transaction_type = 'withdraw';

-- Finding the names associated with the corresponding account numbers. Putting these names in the 'Suspect List'
SELECT name, atm_transactions.amount
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
  JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
 WHERE atm_transactions.year = 2021
   AND atm_transactions.month = 7
   AND atm_transactions.day = 28
   AND atm_transactions.atm_location = 'Leggett Street'
   AND atm_transactions.transaction_type = 'withdraw';


-- Raymond gave clues. As leaving the bakery, they called a person and talked for less than a minute. They asked the person on the other end of the call to buy a flight ticket for the earliest flight on July 29, 2021.
-- First, finding the information about the airport in Fiftyville would be the origin of the thief's flight.
SELECT abbreviation, full_name, city
  FROM airports
 WHERE city = 'Fiftyville';

-- Finding the flights on July 29 from Fiftyville airport and ordering them by time.
SELECT flights.id, full_name, city, flights.hour, flights.minute
  FROM airports
  JOIN flights
    ON airports.id = flights.destination_airport_id
 WHERE flights.origin_airport_id =
       (SELECT id
          FROM airports
         WHERE city = 'Fiftyville')
   AND flights.year = 2021
   AND flights.month = 7
   AND flights.day = 29
 ORDER BY flights.hour, flights.minute;

-- The first flight arrives at 8:20 at LaGuardia Airport in New York City (Flight id- 36). This could be the place where the thief went to.
-- Checking the list of passengers on that flight. Putting them all in the 'Suspect List' Ordering the names according to their passport numbers.
SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
  FROM people
  JOIN passengers
    ON people.passport_number = passengers.passport_number
  JOIN flights
    ON passengers.flight_id = flights.id
 WHERE flights.year = 2021
   AND flights.month = 7
   AND flights.day = 29
   AND flights.hour = 8
   AND flights.minute = 20
 ORDER BY passengers.passport_number;

-- Checking the phone call records to find the person who bought the tickets.
-- Firstly, checking the caller's possible names and putting them in the 'Suspect List', ordering them according to the durations of the calls.
SELECT name, phone_calls.duration
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.caller
 WHERE phone_calls.year = 2021
   AND phone_calls.month = 7
   AND phone_calls.day = 28
   AND phone_calls.duration <= 60
 ORDER BY phone_calls.duration;

-- Secondly, check the possible names of the call-receiver. Ordering them according to the durations of the calls.
SELECT name, phone_calls.duration
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.receiver
 WHERE phone_calls.year = 2021
   AND phone_calls.month = 7
   AND phone_calls.day = 28
   AND phone_calls.duration <= 60
   ORDER BY phone_calls.duration;


-- Ruth gave clues- The thief drove away in a car from the bakery within 10 minutes of the theft. They were so checking the license plates of vehicles within that time frame. Then, check out the names of those cars' owners. They could be suspects.
SELECT name, bakery_security_logs.hour, bakery_security_logs.minute
  FROM people
  JOIN bakery_security_logs
    ON people.license_plate = bakery_security_logs.license_plate
 WHERE bakery_security_logs.year = 2021
   AND bakery_security_logs.month = 7
   AND bakery_security_logs.day = 28
   AND bakery_security_logs.activity = 'exit'
   AND bakery_security_logs.hour = 10
   AND bakery_security_logs.minute >= 15
   AND bakery_security_logs.minute <= 25
 ORDER BY bakery_security_logs.minute;


-- Bruce must be the thief as he is present in all four lists, A list of passengers, a list of people who did the specific atm transactions, a list of people who called, and a list of people who drove away in cars from the bakery.
-- He must have escaped to New York City as he took the New York City flight.
-- Robin must be the accomplice who purchased the flight ticket and helped Bruce escape to New York City.
