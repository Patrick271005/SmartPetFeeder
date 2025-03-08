String CapacityCheck()
{
  String test;//used to print on webpage
  digitalWrite(trig,LOW);
  delayMicroseconds(5);
  digitalWrite(trig,HIGH);//set up unltrasonic sensor
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  duration = pulseIn(echo,HIGH);//how long sound wave travels
  distance = (duration/2) / 29.1; //divide by 2 echo and back ,29.1=converts to cm

  Serial.print(distance);
  Serial.print("cms");
  Serial.println();
  delay(250);

 if(distance <= 8)//Placeholder value for dist will change when i know how big my stoarge will be 
    {
      digitalWrite(full, HIGH);
      digitalWrite(half, LOW);
      digitalWrite(empty, LOW);

      lcd.clear();
      lcd.setCursor(0, 0); // start to print at the first row
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.setCursor(0, 1);
      lcd.print("Storage is full");
      delay(1000);

    }

   else if(distance <= 16)
    {
      digitalWrite(half, HIGH);
      digitalWrite(empty, LOW);
      digitalWrite(full, LOW);

      lcd.clear();
      lcd.setCursor(0, 0); // start to print at the first row
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.setCursor(0, 1);
      lcd.print("Storage is half");
      delay(1000);
    }
  

  else if(distance <= 25.26)
    {
      digitalWrite(empty, HIGH);
      digitalWrite(half, LOW);
      digitalWrite(full, LOW);

      lcd.clear();
      lcd.setCursor(0, 0); // start to print at the first row
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.setCursor(0, 1);
      lcd.print("Storage is empty");
      delay(1000);
    }
  else
  {
    digitalWrite(empty, LOW);
    digitalWrite(half, LOW);
    digitalWrite(full, LOW);

      lcd.clear();
      lcd.setCursor(0, 1); // start to print at the first row
      lcd.print("Unable to measure capacity: ");
      delay(1000);
  }

  test = String(distance);//calculates distance and then returns it to webserver
  return test;
}