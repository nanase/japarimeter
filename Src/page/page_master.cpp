#include "page_master.hpp"

void PageMaster::initialize() {
  this->state = PageKind::openingAct;
  this->changePage();
}

void PageMaster::pressMenuButton() {
  int8_t stateIndex = static_cast<int8_t>(this->state);
  PageKind nextKind = PageStates[stateIndex].pressMenu;

  if (nextKind != PageKind::none) {
    this->state = nextKind;
    this->changePage();
  }
}

void PageMaster::pressNextButton() {
  int8_t stateIndex = static_cast<int8_t>(this->state);
  PageKind nextKind = PageStates[stateIndex].pressNext;

  if (nextKind != PageKind::none) {
    this->state = nextKind;
    this->changePage();
  }
}

void PageMaster::longPressMenuButton() {
  int8_t stateIndex = static_cast<int8_t>(this->state);
  PageKind nextKind = PageStates[stateIndex].longPressMenu;

  if (nextKind != PageKind::none) {
    this->state = nextKind;
    this->changePage();
  }
}

void PageMaster::longPressNextButton() {
  int8_t stateIndex = static_cast<int8_t>(this->state);
  PageKind nextKind = PageStates[stateIndex].longPressNext;

  if (nextKind != PageKind::none) {
    this->state = nextKind;
    this->changePage();
  }
}

void PageMaster::update() {
  if (this->page->update()) {
    int8_t stateIndex = static_cast<int8_t>(this->state);
    PageKind nextKind = PageStates[stateIndex].nextPage;

    if (nextKind != PageKind::none) {
      this->state = nextKind;
      this->changePage();
    }
  }
}

void PageMaster::changePage() {
  delete this->page;

  switch (this->state) {
    case PageKind::openingAct:
      this->page = new OpeningActPage();
      break;

    case PageKind::temperatureHumidity:
      this->page = new TemperatureHumidityPage();
      break;

    case PageKind::temperature:
      this->page = new TemperaturePage();
      break;

    case PageKind::humidity:
      this->page = new HumidityPage();
      break;

    case PageKind::pressure:
      this->page = new PressurePage();
      break;

    default:
      break;
  }

  this->page->initialize();
}
