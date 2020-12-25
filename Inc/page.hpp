#ifndef __PAGE_H
#define __PAGE_H

#include <stdio.h>

class Page {
 public:
  virtual ~Page() {}

  void initialize();
  bool update();

 protected:
  virtual void drawWholeScreen() = 0;
  virtual bool draw()            = 0;
};

class OpeningActPage : public Page {
 protected:
  void drawWholeScreen();
  bool draw();
};

class PressurePage : public Page {
 protected:
  void drawWholeScreen();
  bool draw();
};

class TemperaturePage : public Page {
 protected:
  void drawWholeScreen();
  bool draw();
};

class HumidityPage : public Page {
 protected:
  void drawWholeScreen();
  bool draw();
};

class TemperatureHumidityPage : public Page {
 protected:
  void drawWholeScreen();
  bool draw();
};

#endif
