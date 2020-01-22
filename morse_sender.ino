const float time_unit   = 100;              // The length of a 'dit' or '.' in morse
const float letter_gap  = time_unit * 3;    // The length of gap between letters
const float word_gap    = time_unit * 7;    // The length of gap between words
const int LED_pin = LED_BUILTIN;            // Pin of output LED or buzzer

// - Morse code of each character is encoded as 0's(for '.') and 1's(for '_').
// - If length of morse code of character < 5, the remaining characters are 0
// - The length of morse code sequence is stored as an integer array.

const bool morse_code[37][5] = {
// Code as binary   | Letter | Morse code
  {0,1,0,0,0},        // A - .-
  {1,0,0,0,0},        // B - -...
  {1,0,1,0,0},        // C - -.-.
  {1,0,0,0,0},        // D - -..
  {0,0,0,0,0},        // E - .
  {0,0,1,0,0},        // F - ..-.
  {1,1,0,0,0},        // G - --.
  {0,0,0,0,0},        // H - ....
  {0,0,0,0,0},        // I - ..
  {0,1,1,1,0},        // J - .---
  {1,0,1,0,0},        // K - -.-
  {0,1,0,0,0},        // L - .-..
  {1,1,0,0,0},        // M - --
  {1,0,0,0,0},        // N - -.
  {1,1,1,0,0},        // O - ---
  {0,1,1,0,0},        // P - .--.
  {1,1,0,1,0},        // Q - --.-
  {0,1,0,0,0},        // R - .-.
  {0,0,0,0,0},        // S - ...
  {1,0,0,0,0},        // T - -
  {0,0,1,0,0},        // U - ..-
  {0,0,0,1,0},        // V - ...-
  {0,1,1,0,0},        // W - .--
  {1,0,0,1,0},        // X - -..-
  {1,0,1,1,0},        // Y - -.--
  {1,1,0,0,0},        // Z - --..
  {0,0,0,0,0},        //' '- Space
  {1,1,1,1,1},        // 0 - -----
  {0,1,1,1,1},        // 1 - .----
  {0,0,1,1,1},        // 2 - ..---
  {0,0,0,1,1},        // 3 - ...--
  {0,0,0,0,1},        // 4 - ....-
  {0,0,0,0,0},        // 5 - .....
  {1,0,0,0,0},        // 6 - -....
  {1,1,0,0,0},        // 7 - --...
  {1,1,1,0,0},        // 8 - ---..
  {1,1,1,1,0},        // 9 - ----.
};
const int morse_length[37] = {
  2,                  // A
  4,                  // B
  4,                  // C
  3,                  // D
  1,                  // E
  4,                  // F
  3,                  // G
  4,                  // H
  2,                  // I
  4,                  // J
  3,                  // K
  4,                  // L
  2,                  // M
  2,                  // N
  3,                  // O
  4,                  // P
  4,                  // Q
  3,                  // R
  3,                  // S
  1,                  // T
  3,                  // U
  4,                  // V
  3,                  // W
  4,                  // X
  4,                  // Y
  4,                  // Z
  0,                  //' ' - Space
  5,                  // 0
  5,                  // 1
  5,                  // 2
  5,                  // 3
  5,                  // 4
  5,                  // 5
  5,                  // 6
  5,                  // 7
  5,                  // 8
  5,                  // 9  
};

void setup() 
{
  pinMode(LED_pin,OUTPUT);
  Serial.begin(9600);
  while(!Serial)
  {
    digitalWrite(LED_pin,HIGH);
    delay(250);
    digitalWrite(LED_pin,LOW);
    delay(250);
  }
  Serial.println(" Serial communication established!");
}

void loop() 
{
  delay(1000);
  char ch;
  
  // Wait till something is transmitted via serial
  Serial.print("Waiting");
  while(!Serial.available())
  {
    Serial.print(".");
    delay(250);
  }
  
  // Read all characters in buffer and print morse code
  while(Serial.available())
  {
    ch = Serial.read();
    if(int(ch) != 10)
      print_morse(ch);
    delay(3*time_unit);
  }
}

void print_morse(char ch)
{
  int ch_i = int(ch);
  
  // Following if-else ladder converts ASCII code to the following index/codes and stores it in ch_i
  //  1) Capital and small letters      - 0 (a) to 25(z)
  //  2) ' '                            - 26
  //  3) Numbers                        - 27(0) to 36(9)
  //  4) Rest will output an error through Serial out
  
  if(ch_i > 64 && ch_i < 91)        ch_i -= 65;     // For Capital alphabets
  else
    if(ch_i > 96 && ch_i < 123)     ch_i -= 97;     // For Small alphabet letters
    else
      if(ch_i == 32)                ch_i = 26;      // For space character
      else
        if(ch_i > 47 && ch_i < 58)  ch_i -= 19;     // For numberical characters
        else
        {
          if(ch_i != 10)
            Serial.println("Invalid character!");
          return;
        }

  // Outputs the letter and code through serial output
  Serial.println();
  Serial.print(" Letter : ");
  Serial.println(ch);
  Serial.print(" Code   : ");
  Serial.println(ch_i);
  Serial.print(" Morse  : ");

  // Blinks LED to morse pattern
  blink_LED(morse_code[ch_i],morse_length[ch_i]);

  Serial.println();
}

void blink_LED(const bool code[5],int len)
{
  // This if is to check for the ' ' character, which is the only one with 0 length
  if(len == 0)
    delay(word_gap);
  
  // Loop iterates through the morse code sequence of a character
  for(int i = 0; i < len; i++)
  {
    digitalWrite(LED_pin,HIGH);
    
    // LED turns on for 1 unit for a '.'(0) and for 3 units for a '-'(1).
    if(code[i])
    {
      delay(3 * time_unit);
      Serial.print("-");
    }
    else
    {
      delay(time_unit);
      Serial.print(".");
    }
    digitalWrite(LED_pin,LOW);
    delay(letter_gap);
  }
}
