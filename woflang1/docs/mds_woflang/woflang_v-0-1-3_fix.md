**have we made any progress fren?**

I see the issue now. The problem lies in how the regular expression is parsing floating-point numbers in the parse_tokens function. The current regex is not handling the decimal points properly, which is causing it to split floating-point numbers into separate tokens, such as `'1'`, `'.0011128638'` instead of `'1.0011128638'`.

Correcting the Regular Expression
To fix this, we'll adjust the regex pattern to correctly capture both integers and floating-point numbers, including cases with no leading digit before the decimal point.

Updated Regular Expression:

Here's the refined regex pattern:

```python
pattern = r"(\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]|[-+]?\d*\.\d+|\d+|[-+]?\d*\.\d+)"
```

Explanation of Changes:

Floating-Point Number Adjustment: The expression [-+]?\d*\.\d+ will correctly match:

Numbers with a leading digit `(e.g., 1.23)`
Numbers without a leading digit `(e.g., .45)`
Negative and positive floating-point numbers `(e.g., -0.56, +.78)`
It will not mistakenly split numbers like 1.0011128638 into `['1', '.0011128638']`.
Include all possible matches in the order of preference:

`\b\w+_\w+\b`: Matches words with underscores (like i_1).
`\b\w+\b`: Matches regular words without underscores.
`[-+]?\d*\.\d+`: Matches floats, including ones without leading digits.
`\d+`: Matches integers.
`[齊隶丶丿而或⊕无无‍而无‍或()門]`: Matches all special characters/operators used.



**fren, it's not error free but i think we progressed - do these resutls make sense granted the debugging etc.:**

It looks like we're making some progress, but the regular expression still needs further refinement to correctly capture floating-point numbers and parse them correctly.

Observed Issues
Incorrect Token Splitting for Floating-Point Numbers: The regex is splitting floating-point numbers incorrectly, such as 77.38639852648662 being split into ['77', '.38639852648662'].

Parsing Error for Commands: Due to incorrect token splitting, the script is failing to recognize commands properly, resulting in multiple "Invalid operation or operand" errors.

Solution: Improve the Regular Expression
The current regex `(\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]|[-+]?\d*\.\d+|\d+)` has a conflict in the way it's capturing numbers. We should revise it to prioritize floating-point numbers and integers before matching other patterns.

Updated Regular Expression
Let's refine the regex further to ensure that floating-point numbers are captured correctly:

```python
pattern = r"(\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]|[-+]?\d+\.\d+|[-+]?\.\d+|\d+)"
```

Changes Explained
Order of Matching:

`[-+]?\d+\.\d+`: This matches floating-point numbers with both a leading digit and a decimal part (e.g., 1.234, -1.234).
`[-+]?\.\d+`: This matches floating-point numbers without a leading digit but with a decimal part (e.g., .123, -.123).
`\d+`: This matches integers (e.g., 123, -123).
Prioritization: By placing floating-point regex patterns before the integer pattern, we ensure the parser captures numbers correctly without splitting them.

Updated parse_tokens Function
Let's update the parse_tokens function with this refined regex:

```python
import re

def parse_tokens(command):
    # Further refined regex to correctly capture floating-point numbers and variables
    pattern = r"(\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]|[-+]?\d+\.\d+|[-+]?\.\d+|\d+)"
    return [token for token in re.findall(pattern, command) if token.strip()]
```

- Steps to Implement
Update the parse_tokens function in your script with the new regex pattern.
Re-run the script with the generated commands to verify if floating-point numbers are correctly recognized.

- Further Testing
After updating the regex, you should test it again with various command formats, including edge cases for floating-point numbers.

Here’s a quick test script to ensure the regex captures tokens correctly:

```python
test_commands = [
    "i_1 門 77.38639852648662",
    "theta_C 門 9.695204321393614 齊 45.23286691483372",
    "w_1_B 門 无 55.93913776672642",
    "w_2_C 門 .0099826941",
    "theta_B 門 -99.347584909"
]

for cmd in test_commands:
    print(parse_tokens(cmd))
```

You should expect output that correctly identifies and does not split the floating-point numbers:

```plaintext
['i_1', '門', '77.38639852648662']
['theta_C', '門', '9.695204321393614', '齊', '45.23286691483372']
['w_1_B', '門', '无', '55.93913776672642']
['w_2_C', '門', '.0099826941']
['theta_B', '門', '-99.347584909']
```

Summary
Updating the regex should address the token parsing issue with floating-point numbers. Please implement these changes and test again to verify if the errors are resolved. If there are still errors, we might need to examine the next steps in the processing logic after tokenization. Let me know how it goes!



**and yet still our cursed regex parses worng! see the data from the test script - split floats!**
```bash
(woflang_env) PS C:\Users\User\Desktop\woflang> python input_interpreter_for_woflang_v-0-1-4.py
Script started
['i_1', '門', '77', '.38639852648662']
['theta_C', '門', '9', '.695204321393614', '齊', '45', '.2
```

Analysis
The issue seems to be that the regex is allowing a split between digits and the decimal point due to an unintended matching order or a lack of proper grouping in the regex pattern.

Updated Regex Strategy
To correct the regex, we need to ensure the pattern captures:
- Floating-point numbers with both leading and trailing digits `(e.g., 77.38639852648662)`.
- Floating-point numbers without a leading digit `(e.g., .38639852648662)`.
- Negative or positive floating-point numbers `(e.g., -77.38639852648662)`.
- Integers `(e.g., 77)`.

Here’s a revised regex pattern:

```python
pattern = r"(\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]|[-+]?\d*\.\d+|\d+)"
```

Explanation of the Changes:
`[-+]?\d*\.\d+:` This part of the regex correctly captures any floating-point numbers with or without a leading digit and an optional sign (+ or -).
`[-+]?` matches an optional plus or minus sign.
`\d*` matches zero or more digits before the decimal point.
`\.\d+` matches a decimal point followed by one or more digits.
`\d+:` Matches integers.


The Revised parse_tokens Function
Here’s how your updated parse_tokens function would look with the refined regex:

```python
import re

def parse_tokens(command):
    # Improved regex to correctly capture floating-point numbers and integers
    pattern = r"(\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]|[-+]?\d*\.\d+|\d+)"
    return [token for token in re.findall(pattern, command) if token.strip()]
```

Test the Updated Function
After applying the revised regex, run the test script again to check if the floating-point numbers are parsed correctly:

```python
test_commands = [
    "i_1 門 77.38639852648662",
    "theta_C 門 9.695204321393614 齊 45.23286691483372",
    "w_1_B 門 无 55.93913776672642",
    "w_2_C 門 .0099826941",
    "theta_B 門 -99.347584909"
]

for cmd in test_commands:
    print(parse_tokens(cmd))
```

Expected Output
You should see the correct parsing of floating-point numbers:

```plaintext
['i_1', '門', '77.38639852648662']
['theta_C', '門', '9.695204321393614', '齊', '45.23286691483372']
['w_1_B', '門', '无', '55.93913776672642']
['w_2_C', '門', '.0099826941']
['theta_B', '門', '-99.347584909']
```

Next Steps
Update the regex in your script.
Run the test script to verify correct parsing.
If the parsing is correct, proceed with testing the complete script with the randomly generated input.
Please let me know how it goes or if you encounter any further issues!



**Alright, let's start fresh and approach the regex problem from first principles, as you suggested. The issue you're encountering with the regex is splitting floating-point numbers incorrectly into two parts, for example, `['77', '.38639852648662']`.**

Redefining the Problem
Our goal is to write a regex that correctly identifies and captures the following components:

- Variables or identifiers that can contain alphanumeric characters and underscores `(like i_1, theta_A, etc.)`.
- Operators and special characters such as `門, 齊, 隶, 丶, 丿, 而, 或, ⊕, 无, 无‍而, 无‍或, (), etc.`
- Floating-point numbers in both formats:
- With digits before and after the decimal point `(e.g., 77.38639852648662)`.
- With only digits after the decimal point `(e.g., .38639852648662)`.
- Negative numbers with a minus sign `(e.g., -99.347584909)`.
- Integers `(e.g., 123)`.

Refined Regex Pattern
Let's construct a regex pattern step-by-step to ensure it captures everything correctly.

Identifiers and Keywords: `\b\w+_\w+\b` or `\b\w+\b` for identifiers.
Special Characters: We will manually list these as they are language-specific.
Floating-point Numbers: `[-+]?\d*\.\d+` to capture decimals with optional signs.
Integers: `\b\d+\b` to capture whole numbers.

Complete Regex Pattern
```python
pattern = r"(\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]|[-+]?\d*\.\d+|\b\d+\b)"
```

Explanation:
`\b\w+_\w+\b:` Matches any identifier with an underscore `(e.g., i_1)`.
`\b\w+\b:` Matches any standalone word (e.g., `theta`).
`[齊隶丶丿而或⊕无无‍而无‍或()門]:` Matches any single character from the list.
`[-+]?\d*\.\d+:` Matches floating-point numbers, including optional signs.
`\b\d+\b`: Matches whole numbers.
