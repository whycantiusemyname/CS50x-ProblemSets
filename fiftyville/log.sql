-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT id,description FROM crime_scene_reports WHERE year = 2025
AND month = 7
AND day = 28
AND street = 'Humphrey Street';
-- 295 10.15 am bakery. 3 witnesses
SELECT name,transcript FROM interviews
WHERE year = 2025
AND month = 7
AND day = 28;
-- Ruth    |<10min thiefcar bakery parking lot
--Eugene  |someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
--Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call,earliest flight tomorrow. person on the other end buy it.
SELECT hour,minute,activity,license_plate FROM bakery_security_logs
WHERE year = 2025
AND month = 7
AND day = 28;
--10:14 in and many outs 16-35.
SELECT account_number,transaction_type,amount FROM atm_transactions
WHERE year = 2025
AND month = 7
AND day = 28 AND atm_location = 'Leggett Street';
--see the calls thief may called
SELECT caller,receiver,duration FROM phone_calls
WHERE year = 2025
AND month = 7
AND day = 28 AND duration <= 60;
--
SELECT name,phone_number,passport_number,license_plate FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
WHERE year = 2025
AND month = 7
AND day = 28
)
AND phone_number IN (
    SELECT caller FROM phone_calls
WHERE year = 2025
AND month = 7
AND day = 28 AND duration <= 60
);
--sus people who went to the parking lot and made a call
SELECT Origin.full_name,Origin.city,Origin.abbreviation,Destination.full_name,Destination.city,Destination.abbreviation,hour,minute,flights.id FROM flights
JOIN airports AS Origin ON flights.origin_airport_id = Origin.id
JOIN airports AS Destination ON flights.destination_airport_id =Destination.id
WHERE year = 2025
AND month = 7
AND day = 29 ORDER BY hour ASC;
--flight in 8.20 to LaGuardia,New York,id 36
SELECT account_number,creation_year FROM bank_accounts
WHERE person_id IN (SELECT id FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
WHERE year = 2025
AND month = 7
AND day = 28
)
AND phone_number IN (
    SELECT caller FROM phone_calls
WHERE year = 2025
AND month = 7
AND day = 28 AND duration <= 60
)
);
--get sus bro's account
SELECT name
FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE person_id IN (
    SELECT id FROM people
        WHERE license_plate IN (
            SELECT license_plate FROM bakery_security_logs
            WHERE year = 2025
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute <=25
            )
        AND phone_number IN (
            SELECT caller FROM phone_calls
            WHERE year = 2025
            AND month = 7
            AND day = 28 AND duration <= 60
            )
    )
AND account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2025
    AND month = 7
    AND day = 28 AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
);
-- got who take the money and made the call and went to parking lot.
SELECT name,people.id,phone_number,passport_number
FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE person_id IN (
    SELECT id FROM people
        WHERE license_plate IN (
            SELECT license_plate FROM bakery_security_logs
            WHERE year = 2025
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute <=25
            AND activity = 'exit'
            )
        AND phone_number IN (
            SELECT caller FROM phone_calls
            WHERE year = 2025
            AND month = 7
            AND day = 28 AND duration <= 60
            )
    )
AND account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2025
    AND month = 7
    AND day = 28 AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    JOIN flights ON passengers.flight_id = flights.id
    WHERE flights.id = 36
);
--gooooot it!!!!!! Bruce is the theif!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--686048 (367) 555-5533 5773159633
SELECT caller,receiver,duration FROM phone_calls
WHERE year = 2025
AND month = 7
AND day = 28
AND duration <= 60
AND caller = '(367) 555-5533';
--got receiver (375) 555-8161
SELECT name FROM people
WHERE phone_number = '(375) 555-8161';
--got robin.
