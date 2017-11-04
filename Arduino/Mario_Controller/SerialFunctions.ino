void serialEvent(){
    HardwareSerial &mySerial = Serial;
    cmd = 0;

    if( mySerial.available() ){
        cmd = mySerial.read();
    }
}

void serialEvent2(){
    HardwareSerial &mySerial = Serial2;
    cmd = 0;

    if( mySerial.available() ){
        cmd = mySerial.read();
    }
}
