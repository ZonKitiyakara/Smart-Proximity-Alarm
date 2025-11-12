 //this is where i initialize all the components to the pins of the arduino
  const int trigPin = 13;
  const int echoPin = 12;

  const int passiveBuzzer = 11; //passiveBuzzers make noise from DC current

  //LEDs
  const int greenLED = 10;
  const int yellowLED = 9;
  const int redLED = 8;

  long duration; 
  double distance;

  double maxDistance = 12;// in inches how far we want our sensor to detect. So it doesn't detect stuff that isn't related

  //i need to volume control my buzzer
  const uint8_t buzzerLevel = 60; //60 for more quiet

void setup() {
  // put your setup code here, to run once:
//the set up is used to set up pin output and inputs, serial communication, and sensor initialization(basically im setting up what role each pin will play)

//pinMode(pin, mode) function configures a specific pin to behave as either input(reads a signal from a button or sensor), output(send a signal-> like turning on LED or motor). Just thnk input reads the signal from sensor and output will activate ensor
//digitalRead() allows the pin voltage of the input to be read
//digitalWrite(pin, value) sets an output pin to either high(turns LED on) or low(turns LED 0ff)
 

//so essentially pinMode(13, output) will send a signal to the component 
//pinMode(13, input) will read a signal from the component

// yoiu can use digital read by doing int state = digitalRead(pin). So essentially digital read reads the voltage of that pin. so either high or low. We can use that to make if conditions.
//digital write is used to send a signal(voltage)( out of a pin that you set as output). so digitalWrite(pin, high)-> sends 5V (turning something on), digitalWrite(pin, low) sends 0V meaning turning something off

//NOTE BIGGEST THING IS IF ITS OUTPUT I SEND VOLTAGE FROM THAT PIN TO COMPONENT. IF ITS INPUT I DONT SEND ANY VOLTAGE. ICCCCCCCC*******

pinMode(trigPin, OUTPUT); //so basically pin 13 will send signal to component to trigger the motion sensor essentially
pinMode(echoPin, INPUT); //echo is the wave that comes back representing how long the sound wave took to return
pinMode(passiveBuzzer, OUTPUT); //output because we want to activate it(send voltage to it)
pinMode(greenLED, OUTPUT);
pinMode(yellowLED, OUTPUT);
pinMode(redLED, OUTPUT);

//setting all components to start off basicallyu setting the default
analogWrite(passiveBuzzer, 0); //buzzer off
digitalWrite(greenLED, LOW);
digitalWrite(redLED, LOW);
digitalWrite(yellowLED, LOW);
//so basically this starts the communication between the arduino and the computer. 9600 is the bit rate so the speed the computer and the arduino are talking to eachother. That number is set so they talk at the same rate
Serial.begin(9600);
//u need this every time



//now digital write-> now im setting pins to either high or low

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Add a timeout so no-echo doesn't look like 0 inches



  /*Here is where we made the change !!! so initially when it didn't detect anything, the system would do 0 inches.
  which is less than 12 so it would start flickering. SO what we did was add a time out
  so if no echo within 30 ms-> pulseIn stops and returns 0. So if duration returns as 0, we just treat it as a huge numhber so far away. 
  NICEEE wowww


  */
  duration = pulseIn(echoPin, HIGH, 30000); // 30,000 us = 30 ms

  if (duration == 0) {
    // No echo -> treat as "far away" so LEDs/buzzer stay off
    distance = 1e6; // any huge number works
  } else {
    // Convert normally
    distance = (duration * 0.0343 / 2.0) / 2.54; // cm -> inches
  }

  // light up based on distance (unchanged)
  if(distance < maxDistance) 
    digitalWrite(greenLED, HIGH);
  else
    digitalWrite(greenLED, LOW);

  if(distance < maxDistance * 0.66) 
    digitalWrite(yellowLED, HIGH);
  else
    digitalWrite(yellowLED, LOW);

  if(distance < maxDistance * 0.33) {
    digitalWrite(redLED, HIGH);
    analogWrite(passiveBuzzer, buzzerLevel);
  } else {
    digitalWrite(redLED, LOW);
    analogWrite(passiveBuzzer, 0);
  }

  Serial.print("Distance: ");
  if (duration == 0) Serial.println("No echo");
  else              Serial.println(distance);

  // (Optional but helpful) small settle time
  delay(60);
}

