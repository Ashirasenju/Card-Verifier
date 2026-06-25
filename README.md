# CardCheck

## Description

CardCheck is a lightweight command-line tool that validates credit card numbers.

It supports the main card issuers:
- Visa
- Mastercard
- American Express

Validation is done using:
- The Luhn algorithm
- IIN (Issuer Identification Number) range checks

---

## Build

To compile the project, run:

make all

---

## Usage

cardcheck [OPTIONS] <card_number...>

You can pass one or multiple card numbers.

### Examples

cardcheck 4532015112830366
cardcheck 4532015112830366 5105105105105100

---

## Options

-h, --help     Show help message

### Example

cardcheck -h
cardcheck --help

---

## Output

For each card number, the program prints whether it is:

- VALID (passes Luhn + IIN checks)
- INVALID (fails validation)

### Example output

4532015112830366 -> VALID (Visa)
5105105105105100 -> INVALID

---


## Notes

- Only numeric card inputs are supported.
- Spaces or dashes should be removed before input (if not handled in code).
