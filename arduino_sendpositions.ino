int pot1 = 0;
int pot2 = 0;

int inByte;

const short leftPotent = 9; // potentiometer 
const short rightPotent = 10; // potentiometer 

const short ledLeft = 9; // Analog output pin that the LED is attached to
const short ledRight = 10; // Analog output pin that the LED is attached to

bool led1state = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0)
  {
    // Read the last keypress
    inByte = Serial.read();

    if (inByte == 'P') sendPositions();

    if (inByte == 'L')
    {
      // Toggle the LED state, on-off
      if (led1state)
      {
        led1state = false;
        analogWrite(ledLeft, 0);
      } 
      else 
      {
        led1state = true;
        analogWrite(ledLeft, 255);
      }
    }
  }

  delay(20);
}

// Print the values from the left and right potentiometers
void sendPositions()
{
  pot1 = analogRead(leftPotent);
  pot2 = analogRead(rightPotent);

  Serial.print(getPadded(pot1));
  Serial.print("-");
  Serial.println(getPadded(pot2));
}

// Map the light brightness to the output of the left and right potentiometers
void changeLightState()
{
  analogWrite(ledLeft, map(pot1, 0, 1023, 0, 255));
  analogWrite(ledRight, map(pot2, 0, 1023, 0, 255));
}

// Convert any number to four values in length
String getPadded(int num)
{
  char buff[5];
  char padded[6];

  sprintf(buff, "%.4u", num);

  for(int i = 0; i < 5; i++)
  {
    padded[i] = buff[i];
  }
  padded[5] = '\0';

  return String(padded);
}

