"""
Problem: 20. Valid Parentheses

Given a string containing only ()[]{}, determine whether
all brackets are correctly matched and closed.

Rules:
1. Each opening bracket must have a matching closing bracket.
2. The bracket types must match.
3. The most recently opened bracket must be closed first.

Examples:
"()"    -> True
"()[]{}" -> True
"([])"  -> True
"(]"    -> False
"([)]"  -> False

Approach:
Use a stack to remember opening brackets.
When a closing bracket appears, compare it with the
most recently stored opening bracket.

Time complexity: O(n).
Space complexity: O(n).
"""


class Solution(object):
    def isValid(self, s):
        # Store opening brackets that have not been closed yet.
        # The last element is the top of the stack.
        stack = []

        # Map each closing bracket to its required opening bracket.
        pairs = {
            ")": "(",
            "]": "[",
            "}": "{"
        }

        # Read the string from left to right.
        for char in s:
            if char in pairs:
                # This is a closing bracket.
                #
                # If the stack is empty, there is no opening bracket.
                # Otherwise, pop() removes and returns the most
                # recently stored opening bracket.
                #
                # Python evaluates 'or' from left to right.
                # If the stack is empty, pop() is not called.
                if not stack or stack.pop() != pairs[char]:
                    return False

            else:
                # The input contains only bracket characters,
                # so this must be an opening bracket.
                stack.append(char)

        # An empty stack means every opening bracket was closed.
        # Any remaining opening brackets make the string invalid.
        return not stack
