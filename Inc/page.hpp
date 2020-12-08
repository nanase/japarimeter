#ifndef __PAGE_H
#define __PAGE_H

class Page
{
public:
  virtual void updateWholeScreen() = 0;
  virtual void update() = 0;

  virtual ~Page() {}
};

class PressurePage : public Page
{
public:
  void updateWholeScreen();
  void update();
};

class TemperatureHumidityPage : public Page
{
public:
  void updateWholeScreen();
  void update();
};

#endif
