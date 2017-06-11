#include <IRremote.h>

const int khz = 38;

IRsend irsend;

enum Temperature {
   Sixteen = 16,
   Seventeen = 17,
   Eighteen = 18,
   Nineteen = 19,
   Twenty = 20,
   TwentyOne = 21,
   TwentyTwo = 22,
   TwentyThree = 23,
   TwentyFour = 24,
   TwentyFive = 25,
   TwentySix = 26,
   TwentySeven = 27,
   TwentyEight = 28,
   TwentyNine = 29,
   Thirty = 30,
   ThirtyOne = 31
};

struct List {
  unsigned int data[197];
  int counter = 0;
};

void addToList(List& data, unsigned int value) {
  data.data[data.counter++] = value;
}


byte hexToByte(char hex) {
  if (hex >= '0' && hex <= '9') {
    return hex - '0';
  }
  return hex - 'A' + 10;
}

unsigned int highEndRawData[2] = {520, 1550};

void byteToRawData(byte bytee, List& data) {
  for (int i = 3; i >= 0; --i) {
    addToList(data, highEndRawData[0]);
    addToList(data, highEndRawData[bitRead(bytee, i)]);
  }
}

void addBytesToData(char* bytes, size_t count, List& data) {
  for (int i = 0; i < count; ++i) {
    byteToRawData(hexToByte(bytes[i]), data);    
  }
}

void addHeaderToData(List& data) {
  addToList(data, 6234);
  addToList(data, 7302);

  addBytesToData("FF00FF00", 8, data);
}

void addCommandToData(char* command, List& data) {
  addBytesToData(command, 4, data);
}

void addParameterToData(char* speed, List& data) {
  addBytesToData(speed, 4, data);
}

void addTemperatureToData(int temp, char* mode, List& data) {
  switch (temp) {
    case Sixteen:
      addBytesToData("F", 1, data);
      addModeToData(mode, data);
      addBytesToData("0", 1, data);
    break;
    case Seventeen:
      addBytesToData("7", 1, data);
      addModeToData(mode, data);
      addBytesToData("8", 1, data);    
    break;
    case Eighteen:
      addBytesToData("B", 1, data);
      addModeToData(mode, data);
      addBytesToData("4", 1, data);          
    break;
    case TwentyFive:
      addBytesToData("6", 1, data);
      addModeToData(mode, data);
      addBytesToData("9", 1, data);          
    break;
    default:
    break;
  }
}

void addModeToData(char* mode, List& data) {
  addBytesToData(mode, 1, data);
}

void addChecksumToData(char* checksum, List& data) {
  addBytesToData(checksum, 2, data);
}

void addFooterToData(List& data) {
  addBytesToData("4AB", 3, data);
  
  addToList(data, 608);
  addToList(data, 7372);
  addToList(data, 616);
}

void turnOff() {
  List data;
  addHeaderToData(data);
  addCommandToData("FF00", data);

  addParameterToData("E916", data);
  addTemperatureToData(25, "B", data);
  addChecksumToData("45", data);
  addFooterToData(data);

  irsend.sendRaw(data.data, data.counter, khz); 
}

void setTemperatureTo(int temperature) {
  List data;
  addHeaderToData(data);
  addCommandToData("BF40", data);
  
  addParameterToData("A956", data);
  addTemperatureToData(temperature, "B", data);
  addChecksumToData("45", data);
  addFooterToData(data);

  irsend.sendRaw(data.data, data.counter, khz); 
}

void setup()
{
  Serial.begin(9600);
}

void loop() {  
  
  if (Serial.available() > 1) {
    int temp = Serial.parseInt();
    Serial.println(temp);
    if (temp == 0) {
      turnOff();
    } else {
      setTemperatureTo(temp);
    }
  }
}

