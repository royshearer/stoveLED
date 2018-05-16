//File myFile;
//
//void setupSD() {
  //  if (!SD.begin(4)) {
  //    Serial.println("initialization failed!");
  //    return;
  //  }
  //  Serial.println("initialization done.");
  //  if (SD.exists("test.txt")) {
  //    SD.remove("test.txt");
  //  }
//}
//
//void writeSD(){
//  int SDWrite(int PeopleCount) {
//    //getDateTime();
//    myFile = SD.open("test.txt", FILE_WRITE);
//    if (myFile) {
//      Serial.print("Writing");
//      Serial.print(" ");
//      Serial.print(PeopleCount);
//      myFile.println(PeopleCount);
//      myFile.close();
//      Serial.println("done.");
//    } else {
//      Serial.println("error opening test.txt");
//    }
//  }
//}
