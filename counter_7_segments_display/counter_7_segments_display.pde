void setup() {
 pinMode(2,OUTPUT); 
 pinMode(3,OUTPUT); 
 pinMode(4,OUTPUT); 
 pinMode(5,OUTPUT); 
 pinMode(6,OUTPUT); 
 pinMode(7,OUTPUT); 
 pinMode(8,OUTPUT); 
 pinMode(9,OUTPUT); 
 digitalWrite(9,0);
}

void loop() {
 number9();
 delay(1000);
 number8();
 delay(1000);
 number7();
 delay(1000);
 number6();
 delay(1000);
 number5();
 delay(1000);
 number4();
 delay(1000);
 number3();
 delay(1000);
 number2();
 delay(1000);
 number1();
 delay(1000);
 number0();
 delay(1000);

}

void number9() {
 digitalWrite(2,1); 
 digitalWrite(3,1); 
 digitalWrite(4,1); 
 digitalWrite(5,0); 
 digitalWrite(6,0); 
 digitalWrite(7,1); 
 digitalWrite(8,1);  
}

void number8() {
 digitalWrite(2,1); 
 digitalWrite(3,1); 
 digitalWrite(4,1); 
 digitalWrite(5,1); 
 digitalWrite(6,1); 
 digitalWrite(7,1); 
 digitalWrite(8,1);  
}

void number7() {
 digitalWrite(2,1); 
 digitalWrite(3,1); 
 digitalWrite(4,1); 
 digitalWrite(5,0); 
 digitalWrite(6,0); 
 digitalWrite(7,0); 
 digitalWrite(8,0);  
}

void number6() {
 digitalWrite(2,1); 
 digitalWrite(3,0); 
 digitalWrite(4,1); 
 digitalWrite(5,1); 
 digitalWrite(6,1); 
 digitalWrite(7,1); 
 digitalWrite(8,1);  
}

void number5() {
 digitalWrite(2,1); 
 digitalWrite(3,0); 
 digitalWrite(4,1); 
 digitalWrite(5,1); 
 digitalWrite(6,0); 
 digitalWrite(7,1); 
 digitalWrite(8,1);  
}

void number4() {
 digitalWrite(2,0); 
 digitalWrite(3,1); 
 digitalWrite(4,1); 
 digitalWrite(5,0); 
 digitalWrite(6,0); 
 digitalWrite(7,1); 
 digitalWrite(8,1);  
}

void number3() {
 digitalWrite(2,1); 
 digitalWrite(3,1); 
 digitalWrite(4,1); 
 digitalWrite(5,1); 
 digitalWrite(6,0); 
 digitalWrite(7,0); 
 digitalWrite(8,1);  
}

void number2() {
 digitalWrite(2,1); 
 digitalWrite(3,1); 
 digitalWrite(4,0); 
 digitalWrite(5,1); 
 digitalWrite(6,1); 
 digitalWrite(7,0); 
 digitalWrite(8,1);  
}

void number1() {
 digitalWrite(2,0); 
 digitalWrite(3,1); 
 digitalWrite(4,1); 
 digitalWrite(5,0); 
 digitalWrite(6,0); 
 digitalWrite(7,0); 
 digitalWrite(8,0);  
}

void number0() {
 digitalWrite(2,1); 
 digitalWrite(3,1); 
 digitalWrite(4,1); 
 digitalWrite(5,1); 
 digitalWrite(6,1); 
 digitalWrite(7,1); 
 digitalWrite(8,0);  
}
