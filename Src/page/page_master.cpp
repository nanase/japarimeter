#include "japarimeter/page_master.hpp"

void PageMaster::initialize() {
  this->state = PageKind::openingAct;
  this->changePage();
}

void PageMaster::pressAButton() {
  if (this->page->onPressButtonA()) {
    int8_t stateIndex = static_cast<int8_t>(this->state);
    PageKind nextKind = PageStates[stateIndex].pressA;

    if (nextKind != PageKind::none) {
      this->state = nextKind;
      this->changePage();
    }
  }
}

void PageMaster::pressBButton() {
  if (this->page->onPressButtonB()) {
    int8_t stateIndex = static_cast<int8_t>(this->state);
    PageKind nextKind = PageStates[stateIndex].pressB;

    if (nextKind != PageKind::none) {
      this->state = nextKind;
      this->changePage();
    }
  }
}

void PageMaster::longPressAButton() {
  if (this->page->onLongPressButtonA()) {
    int8_t stateIndex = static_cast<int8_t>(this->state);
    PageKind nextKind = PageStates[stateIndex].longPressA;

    if (nextKind != PageKind::none) {
      this->state = nextKind;
      this->changePage();
    }
  }
}

void PageMaster::longPressBButton() {
  if (this->page->onLongPressButtonB()) {
    int8_t stateIndex = static_cast<int8_t>(this->state);
    PageKind nextKind = PageStates[stateIndex].longPressB;

    if (nextKind != PageKind::none) {
      this->state = nextKind;
      this->changePage();
    }
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

    case PageKind::di:
      this->page = new DIPage();
      break;

    case PageKind::altitude:
      this->page = new AltitudePage();
      break;

    case PageKind::version1:
      this->page = new Version1Page();
      break;

    case PageKind::version2:
      this->page = new Version2Page();
      break;

    default:
      break;
  }

  this->page->initialize();
}
