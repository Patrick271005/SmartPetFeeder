String  WeightCheck(){
  String test;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reading: ");
  val = scale.get_units();  // Get the weight in kilograms 
  lcd.print(val);
  lcd.print(" kg");
  lcd.println();
  delay(250);
  //all values in if statements need to be changed when the loadcell is calibrated correctly
  if (val < 0.2) //Turns motor if bowl is nearly empty
  {
    s1.write(90);  // Move servo to 90 degrees if weight is low
    delay(1000);
    
  }
  else
  {
    s1.write(0);// Move servo back to 0 degrees to prevent over filling
    delay(1000);
      
  }

  test = String(val);

  return test;
}



