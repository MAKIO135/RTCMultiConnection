void serialEvent(){
    readSerial( Serial );
}

void serialEvent2(){
    readSerial( Serial2 );
}

void readSerial( HardwareSerial & mySerial ){
    if( mySerial.available() ){
        cmd = mySerial.read();
        Serial.println( "Command received: " + String( cmd ) );
    }
    mySerial.flush();
}
