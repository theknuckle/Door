int redLight = 6;
int greenLight = 7;
int outputPin = 8;
int inputPin1 = 9;
int inputPin2 = 10;

initTime = millis();
finTime = millis();

boolean triggered = false;
boolean hit = false;



void setup()
{
	Serial.begin(9600)
	pinMode(redLight, OUTPUT);
	pinMode(greenLight, OUTPUT);
	pinMode(outputPin, OUTPUT);
	pinMode(inputPin1, INPUT);
	pinMode(inputPin2, INPUT);

	digitalWrite(redLight, LOW);
	digitalWrite(greenLight, HIGH);
	digitalWrite(outputPin, HIGH);


}

void loop()
{
	finTime = millis();

	int sensorValue1 = analogRead(inputPin1);
	float voltage1 = sensorValue1 * (5.0 / 1023.0);
	int sensorValue2 = analogRead(inputPin2);
	float voltage2 = sensorValue2 * (5.0 / 1023.0);
	Serial.println(voltage1);
	Serial.println(voltage2);

	int resist2 = 5 * (100/voltage1) - 100;

	if (hit == false)

	{

		if (resist2 < 20 && triggered == false)
		{
			initTime = millis();
			triggered = true;

		}

		else if (triggered = true && resist2 > 20)
		{
			if (finTime - initTime > 200)
			{
				Serial.println("false positive");
				triggered = false;
			}

			else 
			{
				Serial.println("hit");
				digitalWrite(redLight, LOW);
				digitalWrite(greenLight, HIGH);
				hit = true;
			}



		}


	}


}