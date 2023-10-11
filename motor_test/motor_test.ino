int r_en = 2;
int l_en = 3;

int r_pwm = 5;
int l_pwm = 6;

void setup() {
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
}

void loop() {
digitalWrite(r_en,HIGH);
digitalWrite(l_en, HIGH);

analogWrite(r_pwm,150);
analogWrite(l_pwm,0);

}
