# Morse-Sender
Arduino code to blink an LED or sound a buzzer to morse code of characters sent via serial port.

# What is morse code?
Morse code is a method used in telecommunication to encode text characters as standardized sequences of two different signal durations, called dots and dashes or dits and dahs. It was used for early communication, and is still used due to ease of encoding compared to other means.

# How does morse code work?
- There are 2  fundamental characters : `.` or `dit` and `-` or `dah`. 
- A signal is turned on for a particular time to send a `.` or `-`. This is how they are distinguished. 
- Typically, `-` is 3 times as long as `.`
- The gap between successive `.`s or `-`s in the code of a letter is same as length of `.`
- A combination of `.` and `-` is assigned for each letter. eg. a is `.-`
- The gap between letters is more, typically the length of `-` ie, 3 times that of gap between letters
- The gap between words is even greater, typically about 7 times that of `.`
- The chart for characters :
![Morse Code Table](https://merriam-webster.com/assets/mw/static/table/collegiate/morsecod.jpg)
