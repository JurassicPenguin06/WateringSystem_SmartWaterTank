int livello, percent, decine, unit, var, i, preset, preset2, entered;
unsigned long myTime, saveTime, diffTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //starting the serial communication
  for (i = 2; i <= 11; i++) { //setting all the used pins as OUTPUTs
      pinMode(i, OUTPUT);
  }
  preset = 0;
  preset2 = 0;
  entered = 0;
}

void display(int numero) 
{
  //Here the code can give the binary code to the CD4511 in order to output the code for the displays 
  switch (numero) {
    case 0:
	    digitalWrite(2+var, LOW);
	    digitalWrite(3+var, LOW);
	    digitalWrite(4+var, LOW);
	    digitalWrite(5+var, LOW);
	    break;
    case 1:
	    digitalWrite(2+var, HIGH);
	    digitalWrite(3+var, LOW);
	    digitalWrite(4+var, LOW);
	    digitalWrite(5+var, LOW);
	    break;
    case 2:
	    digitalWrite(2+var, LOW);
	    digitalWrite(3+var, HIGH);
	    digitalWrite(4+var, LOW);
	    digitalWrite(5+var, LOW);
	    break;
    case 3:
	    digitalWrite(2+var, HIGH);
	    digitalWrite(3+var, HIGH);
	    digitalWrite(4+var, LOW);
	    digitalWrite(5+var, LOW);
	    break;
    case 4:
	    digitalWrite(2+var, LOW);
	    digitalWrite(3+var, LOW);
	    digitalWrite(4+var, HIGH);
	    digitalWrite(5+var, LOW);
	    break;
    case 5:
	    digitalWrite(2+var, HIGH);
	    digitalWrite(3+var, LOW);
	    digitalWrite(4+var, HIGH);
	    digitalWrite(5+var, LOW);
	    break;
    case 6:
	    digitalWrite(2+var, LOW);
	    digitalWrite(3+var, HIGH);
	    digitalWrite(4+var, HIGH);
	    digitalWrite(5+var, LOW);
	    break;
    case 7:
	    digitalWrite(2+var, HIGH);
	    digitalWrite(3+var, HIGH);
	    digitalWrite(4+var, HIGH);
	    digitalWrite(5+var, LOW);
	    break;
    case 8:
	    digitalWrite(2+var, LOW);
	    digitalWrite(3+var, LOW);
	    digitalWrite(4+var, LOW);
	    digitalWrite(5+var, HIGH);
	    break;
    case 9:
	    digitalWrite(2+var, HIGH);
	    digitalWrite(3+var, LOW);
	    digitalWrite(4+var, LOW);
	    digitalWrite(5+var, HIGH);
	    break;
    default:
	    digitalWrite(2+var, LOW);
	    digitalWrite(3+var, HIGH);
	    digitalWrite(4+var, LOW);
	    digitalWrite(5+var, HIGH);
	    break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  myTime = millis();
  diffTime = 0;
  
  livello = analogRead(A0);
  percent = map(livello, 352, 1023, 99, 0);
  
  if(percent != preset)
  {
      Serial.print("livello dell'acqua: ");
      Serial.print(percent);
      Serial.println("%");
  }
  preset = percent;
  
  if(percent < 30)
  {
    if(entered == 0)
    {
	    Serial.println("Il motore sta per avviarsi");
	    saveTime = myTime;
	    entered = 1;
    }
    diffTime = myTime - saveTime;
    if((diffTime >= 1000) && (entered == 1))
    {
	    digitalWrite(10, HIGH);
	    Serial.println("Motore in funzione");
	    preset2 = 0;
	    entered = 2;
    }       
  }
  else
  {
    if((percent>=30) && (percent<90)) 
    {
	    saveTime = 0;
	    entered = 0;
	    if(preset2 == 0)
	    {
	      digitalWrite(10, HIGH);
	    }
	    else
	    {
	      digitalWrite(10, LOW);
	    }
    }
    else
    {
	    if(entered == 0)
	    {
	      Serial.println("Il motore sta per spegnersi");
	      saveTime = myTime;
	      entered = 1;
	    }
	 
	    diffTime = myTime - saveTime;
	    if((diffTime >= 1000) && (entered == 1))
	    {
	      digitalWrite(10, LOW);
	      Serial.println("Il motore si è spento");
	      preset2 = 1;
	      entered = 2;
	    }
    }
  }
  
  decine = percent/10;
  var = 4;
  display(decine);
  unit = percent%10;
  var = 0;
  display(unit);
  
  delay(1);
}