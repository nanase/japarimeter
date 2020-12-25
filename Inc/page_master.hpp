#ifndef __PAGE_MASTER_H
#define __PAGE_MASTER_H

#include <stdint.h>

#include "page.hpp"

enum class PageKind : int8_t {
  none = -1,

  openingAct = 0,

  temperatureHumidity = 1,
  temperature         = 2,
  humidity            = 3,
  pressure            = 4,

  setting1 = 5,

  version1 = 6,
  version2 = 7,
};

typedef struct {
  PageKind pressMenu;
  PageKind pressNext;
  PageKind longPressMenu;
  PageKind longPressNext;
  PageKind nextPage;
} PageInfo;

const PageInfo PageStates[] = {
  // openingAct
  { PageKind::none, PageKind::none, PageKind::none, PageKind::none, PageKind::temperature },

  // temperatureHumidity
  { PageKind::none, PageKind::temperature, PageKind::none, PageKind::none, PageKind::none },

  // temperature
  { PageKind::none, PageKind::humidity, PageKind::none, PageKind::none, PageKind::none },

  // humidity
  { PageKind::none, PageKind::pressure, PageKind::none, PageKind::none, PageKind::none },

  // pressure
  { PageKind::none, PageKind::temperatureHumidity, PageKind::none, PageKind::none, PageKind::none },
};

class PageMaster {
 public:
  void initialize();

  void pressMenuButton();
  void pressNextButton();

  void longPressMenuButton();
  void longPressNextButton();

  void update();

 private:
  PageKind state;
  Page *page;

  void changePage();
};

#endif
