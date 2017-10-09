int OpenPin = 6;
int ClosePin = 7;
int Redlight = 8;
int GreenLight = 9;

String key = String("asdf"); //key code
String entered = String("00000"); //variable for entered code by user

int keylength = 5;

bool status = false; //if key is corret, also acts as a check

double time1 = 0; //time key is entered
double time2 = 0; //time elapsed since key has been entered

int index = 0; //length of key code

void setup()
{
	Serial.begin(9600);

	pinMode(OpenPin, OUTPUT);
	pinMode(ClosePin, OUTPUT);
	pinMode(Redlight, OUTPUT);
	pinMode(GreenLight, OUTPUT);

	digitalWrite(OpenPin, LOW);
	digitalWrite(ClosePin, HIGH);
	digitalWrite(Redlight, LOW);
	digitalWrite(GreenLight, LOW);

	time2 = millis();

	Serial.print("please enter code \n");

}



void loop()
{
	if (entered == key && status == false) 
	{
		status = true;
		time1 = millis();
		Serial.print("unlocked");

	}

	else if (entered != key)
	{
		digitalWrite(Redlight, HIGH);
		status = false;
    	//Serial.print("Locked \n");
    	delay(500);
    	//Serial.print(entered);
    	//Serial.print('\n');
	}



	if (status == true)
	{
		digitalWrite(OpenPin, HIGH);
		digitalWrite(ClosePin, LOW);
		pinMode(Redlight, LOW);
		pinMode(GreenLight, HIGH);	
		time2 = millis();
		Serial.print("opened \n");
		delay(500);
	}

	if (time2 - time1 > 10000 && status == true)
	{
		status = false;
		digitalWrite(OpenPin, LOW);
		digitalWrite(ClosePin, HIGH);
		digitalWrite(Redlight, HIGH);
		digitalWrite(GreenLight, LOW);
		entered = "00000";	
		Serial.print("timeout \n");
		delay(100);
	}


}

void serialEvent()
{
	while(Serial.available())
	{
	    
	    	
	    	{
          		if(Serial.read() == '\n')
	            {
	              break;
	            }
	    		entered = Serial.readString();
	    		index = index + 1;
         
			}
		

	}
	
	index = 0;

}
