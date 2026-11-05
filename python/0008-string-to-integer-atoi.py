"""
Problem: 8. String to Integer (atoi)

Convert a string into a 32-bit signed integer manually.

Rules:
1. Ignore leading spaces.
2. Read one optional '+' or '-' sign.
3. Read consecutive digits until a non-digit or the end of the string.
4. Return 0 if no digits were read.
5. Clamp the result to [-2147483648, 2147483647].

Examples:
"42"           -> 42
"   -042"      -> -42
"1337c0d3"     -> 1337
"words and 987" -> 0
"0-1"         -> 0
"999999999999" -> 2147483647

Approach:
Move through the string with an index.
Build the number one digit at a time using:
number = number * 10 + digit

Time complexity: O(n), where n is the string length.
Space complexity: O(1).
"""


class Solution(object):
    def myAtoi(self, s):
        # Index of the character currently being read.
        i = 0
        n = len(s)

        # STEP 1: Skip spaces at the beginning.
        # Check the index before accessing s[i].
        while i < n and s[i] == " ":
            i += 1

        # STEP 2: Read one optional sign.
        # Assume a positive number unless a minus sign is found.
        sign = 1

        if i < n and s[i] in "+-":
            if s[i] == "-":
                sign = -1

            # Move past the sign to the next character.
            i += 1

        # The negative range allows an absolute value of 2**31.
        # The positive range allows a maximum of 2**31 - 1.
        limit = 2**31 if sign == -1 else 2**31 - 1

        # Store the number's magnitude separately from its sign.
        number = 0

        # STEP 3: Read consecutive digit characters.
        # Stop at the first non-digit; do not search further.
        while i < n and "0" <= s[i] <= "9":
            # Convert a digit character to its numeric value.
            # Example: ord("4") - ord("0") equals 4.
            digit = ord(s[i]) - ord("0")

            # Shift existing digits left and append the new digit.
            # Example: 4 * 10 + 2 becomes 42.
            # Leading zeros are handled naturally by this calculation.
            number = number * 10 + digit

            # STEP 4: Clamp values outside the required range.
            # Further digits cannot make the magnitude smaller,
            # so we can return immediately when the limit is exceeded.
            if number > limit:
                return sign * limit

            # Move to the next character.
            i += 1

        # Apply the sign.
        # If no digits were read, number is still 0.
        return sign * number
