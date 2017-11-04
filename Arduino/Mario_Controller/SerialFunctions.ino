void serialEvent(){
    HardwareSerial &mySerial = Serial;
    cmd = 0;

    if( mySerial.available() ){
        cmd = mySerial.read();
    }
    mySerial.flush();
}

void serialEvent2(){
    HardwareSerial &mySerial = Serial2;
    cmd = 0;

    if( mySerial.available() ){
        cmd = mySerial.read();
    }
    mySerial.flush();
}
