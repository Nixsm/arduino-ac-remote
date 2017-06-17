#ifdef ESP8266
  #include <IRsend.h>
#else
  #include <IRremote.h>
#endif

const uint16_t khz = 38;

#ifdef ESP8266
IRsend irsend(4);
#else
IRsend irsend;
#endif

char temperatures[16][4] = {
  "F00",
  "708",
  "B04",
  "30C",
  "D02",
  "50A",
  "906",
  "10E",
  "E01",
  "609",
  "A05",
  "20D",
  "C03",
  "40B",
  "807",
  "00F"
};

enum Speed {
  One = 0, Two, Three, Auto
};

struct List {
  uint16_t data[197];
  uint16_t counter = 0;
};

struct KomecoController {
  char* getSpeedAsParameter(Speed airSpeed) {
    switch (airSpeed) {
      case One:
        return "A956";
      case Two:
        return "AD52";
      case Three:
        return "A35C";
      case Auto:  
        return "A758";
    }
  }
  void addToList(List& data, unsigned int value) {
    data.data[data.counter++] = value;
  }

  byte hexToByte(char hex) {
    if (hex >= '0' && hex <= '9') {
      return hex - '0';
    }
    return hex - 'A' + 10;
  }

  unsigned int highEndRawData[2] = {500, 1570};

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

  void addParameterToData(char* parameter, List& data) {
    addBytesToData(parameter, 4, data);
  }

  void addTemperatureToData(int temp, char mode, List& data) {
    unsigned int realTempIndex = temp - 16;
    char* temperature = temperatures[realTempIndex];

    temperature[1] = mode;
    addBytesToData(temperature, 3, data);
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
    addTemperatureToData(25, 'B', data);
    addChecksumToData("45", data);
    addFooterToData(data);

    irsend.sendRaw(data.data, data.counter, khz);
  }

  void setSpeedTo(Speed airSpeed) {
    List data;
    addHeaderToData(data);
    addCommandToData("5FA0", data);
    addParameterToData(getSpeedAsParameter(airSpeed), data);
    addTemperatureToData(25, 'B', data);
    addChecksumToData("45", data);
    addFooterToData(data);

    irsend.sendRaw(data.data, data.counter, khz); 
  }

  void setSleepModeTo(bool sleepy) {
    List data;
    addHeaderToData(data);
    addCommandToData("6F90", data);

    char *sleepMode = sleepy ? "21DE" : "A15E";

    addParameterToData(sleepMode, data);
    addTemperatureToData(25, 'B', data);
    addChecksumToData("45", data);
    addFooterToData(data);

    irsend.sendRaw(data.data, data.counter, khz);
  }

  void setTemperatureTo(int temperature) {
    List data;
    addHeaderToData(data);
    addCommandToData("BF40", data);

    addParameterToData("A956", data);
    addTemperatureToData(temperature, 'B', data);
    addChecksumToData("45", data);
    addFooterToData(data);

    irsend.sendRaw(data.data, data.counter, khz);
  }

  void setup() {
#ifdef ESP8266
    irsend.begin();
#endif
  }
};
