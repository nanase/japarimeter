#ifndef __PAGE_MASTER_H
#define __PAGE_MASTER_H

#include <stdint.h>

#include "japarimeter/page.hpp"

enum class PageKind : int8_t {
  none = -1,

  openingAct = 0,

  temperature         = 1,
  humidity            = 2,
  pressure            = 3,
  temperatureHumidity = 4,
  di                  = 5,
  altitude            = 6,

  version1 = 7,
  version2 = 8,
};

typedef struct {
  PageKind pressMenu;
  PageKind pressNext;
  PageKind longPressMenu;
  PageKind longPressNext;
  PageKind nextPage;
} PageInfo;

const PageInfo PageStates[] = {
  // 0: openingAct
  { PageKind::none, PageKind::none, PageKind::none, PageKind::none, PageKind::version2 },

  // 1: temperature
  { PageKind::version1, PageKind::humidity, PageKind::none, PageKind::none, PageKind::none },

  // 2: humidity
  { PageKind::version1, PageKind::pressure, PageKind::none, PageKind::none, PageKind::none },

  // 3: pressure
  { PageKind::version1, PageKind::temperatureHumidity, PageKind::none, PageKind::none, PageKind::none },

  // 4: temperatureHumidity
  { PageKind::version1, PageKind::di, PageKind::none, PageKind::none, PageKind::none },

  // 5: DI (Disconfort Index)
  { PageKind::version1, PageKind::altitude, PageKind::none, PageKind::none, PageKind::none },

  // 6: altitude
  { PageKind::version1, PageKind::temperature, PageKind::none, PageKind::none, PageKind::none },

  // 7: version1
  { PageKind::version2, PageKind::temperature, PageKind::none, PageKind::none, PageKind::none },

  // 7: version2
  { PageKind::version1, PageKind::temperature, PageKind::none, PageKind::none, PageKind::none },
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
