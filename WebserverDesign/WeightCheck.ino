String  WeightCheck(){
  String test;
  //scale.begin(15, 2);
  //scale.set_scale(-211.765); 
  //scale.tare(); 
   Serial.print("read: \t\t");
  Serial.println(scale.read(),1); 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reading: ");
  val = scale.get_units(5);
  if (val<0)
  {val=0;} // Get the weight in kilograms 
  lcd.print(val);
  lcd.print(" kg");
  lcd.println();
  delay(250);
  //all values in if statements need to be changed when the loadcell is calibrated correctly
  if (val < 100) //Turns motor if bowl is nearly empty
  {
    s1.write(90);  // Move servo to 90 degrees if weight is low to dispense food 
    delay(1000);
    
  }
  else
  {
    s1.write(0);// Move servo back to 0 degrees to prevent over filling
    delay(1000);
      
  }

  test = String(val);

  return test;
  scale.power_down();             // put the ADC in sleep mode
  delay(2000);
  scale.power_up();
}



