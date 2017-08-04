int stepper_diretion_in=2;
int stepper_direction_out=13;

void setup() {
  // put your setup code here, to run once:
  pinMode(stepper_diretion_in,INPUT);
  pinMode(stepper_direction_out,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(stepper_diretion_in)==HIGH)
  digitalWrite(stepper_direction_out,HIGH);
  else
  digitalWrite(stepper_direction_out,LOW);

}
