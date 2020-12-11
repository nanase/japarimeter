#ifndef __PAGE_H
#define __PAGE_H

class Page {
 public:
  virtual ~Page() {}

  void initialize();
  void update();

 protected:
  virtual void drawWholeScreen() = 0;
  virtual void draw()            = 0;
};

class PressurePage : public Page {
 protected:
  void drawWholeScreen();
  void draw();
};

class TemperaturePage : public Page {
 protected:
  void drawWholeScreen();
  void draw();
};

class HumidityPage : public Page {
 protected:
  void drawWholeScreen();
  void draw();
};

class TemperatureHumidityPage : public Page {
 protected:
  void drawWholeScreen();
  void draw();
};

#endif
