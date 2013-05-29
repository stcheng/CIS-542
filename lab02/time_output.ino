unsigned long time;

// This method is called once
void setup(){
  // sets the transfer rate to 9600 baud
  Serial.begin(9600);
}

// This method is called repeatedly
void loop(){
  Serial.print("Time: ");
  time = millis();
  // Print time since program started
  Serial.println(time);
  // Wait a second so as not to send massive amounts of data
  delay(1000);
}
