//YouTube|Tech at Home

int Mic_Pin = A0;
int Moisture_Pin = A1;
int mic_Value,moisture_Value;

void setup()
{
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT); 
}

void loop()
{
  mic_Value = analogRead(A0);
  moisture_Value= analogRead(A1);
  
  Serial.print("mic_Value = ");
  Serial.print(mic_Value);
  Serial.print("\t\t\t");
  Serial.print("moisture_Value = ");
  Serial.print(moisture_Value);
  Serial.print("\n");
  delay(200);
}
