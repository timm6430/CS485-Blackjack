#include "SDLView.h"
#include "BlackjackPresenter.h"
#include <sstream>

//***************************************************************************
// Constructor: SDLView
//
// Description: 
//
// Parameters:  None
//
// Returned:    None
//***************************************************************************

SDLView::SDLView() {
  mpcBlackjackPresenter = new BlackjackPresenter(this);
  mpPlayerNames.push_back(new SDLTextWidget("Player1", "", 10, 10, 1, 
    { 255,255,255,255 }));
  mpDealerWidget = new SDLTextWidget("Dealer", "", 10, 120, 1,
    { 255,255,255,255 });

  enableTextInput();

  registerTextWidget(mpPlayerNames[0]);
  registerTextWidget(mpDealerWidget);

  mcDrawableWidgets.push_back(mpPlayerNames[0]);
  mcDrawableWidgets.push_back(mpDealerWidget);
}

SDLView::~SDLView() {

  delete mpcBlackjackPresenter;
}


void SDLView::onDraw() {
}


void SDLView::onAddPlayer(std::string name) {
  long long amount;
  char playerType;
  Money cMoney;

  std::cout << "Initial Bank Amount:";
  std::cin >> amount;
  cMoney.setAmount(amount);

  do {
    std::cout << "Human (H) or Computer (C) player?";
    std::cin >> playerType;
  } while ('C' == playerType || 'H' == playerType);

  if (numPlayers + 1 <= 5) {
    addPlayer(playerType, name, cMoney);
  }
  else {
    std::cout << "Alread at max capacity";
  }
}


void SDLView::onRemovePlayer(std::string yes) {
  int playerNum;

  do {
    std::cout << "Which player would you like to remove? (Please enter player number)";
    std::cin >> playerNum;
  } while (playerNum > 0 && playerNum <= 5);

  mpcBlackjackPresenter->removePlayer(playerNum);
}

void SDLView::onSetPlayer1Name(std::string name)
{
  mpPlayerNames[0]->setData(name);
}


void SDLView::onSetPlayer2Name(std::string name)
{
  mpPlayerNames[1]->setData(name);
}


void SDLView::onSetPlayer3Name(std::string name)
{
  mpPlayerNames[2]->setData(name);
}


void SDLView::onSetPlayer4Name(std::string name)
{
  mpPlayerNames[3]->setData(name);
}


void SDLView::onSetPlayer5Name(std::string name)
{
  mpPlayerNames[4]->setData(name);
}

void SDLView::deal()
{

}

void SDLView::onClickHit() {}

void SDLView::onClickStay() {}

void SDLView::onClickSplit() {}

void SDLView::onSetBet(std::string) {}

Card SDLView::drawCard() {}

void SDLView::addBet(Money bet) {}

float SDLView::getCurrentTurn() {}

void SDLView::addPlayer(char playerType, std::string playerName, Money cBank) {

  numPlayers++;
  mpcBlackjackPresenter->addPlayer(playerName, cBank, numPlayers);
  mpPlayerNames.push_back(new SDLTextWidget("Player" + numPlayers, "",
    10, 20 * numPlayers, 1, { 255,255,255,255 }));

  if (numPlayers == 2) {

    mpPlayerNames[1]->registerStateChangeEventHandler
    (std::bind(&SDLView::onSetPlayer2NameWidget, this, mpPlayerNames[1]));

    onSetPlayer2Name(playerName);
  }
  else if (numPlayers == 3) {
  
    mpPlayerNames[2]->registerStateChangeEventHandler
    (std::bind(&SDLView::onSetPlayer2NameWidget, this, mpPlayerNames[2]));

    onSetPlayer3Name(playerName);
  }
  else if (numPlayers == 4) {

    mpPlayerNames[3]->registerStateChangeEventHandler
    (std::bind(&SDLView::onSetPlayer2NameWidget, this, mpPlayerNames[3]));

    onSetPlayer4Name(playerName);
  }
  else if (numPlayers == 5) {

    mpPlayerNames[4]->registerStateChangeEventHandler
    (std::bind(&SDLView::onSetPlayer2NameWidget, this, mpPlayerNames[4]));

    onSetPlayer5Name(playerName);
  }
}

void SDLView::removePlayer(int player) {
  for (int i = player; i < numPlayers; i++) {
    mpPlayerNames[i - 1]->setData(mpPlayerNames[i]->getData());
  }

  numPlayers--;
}

void SDLView::setNumPlayer(int players) {
  mpcBlackjackPresenter->setNumPlayers(players);
}

void SDLView::resetGame() {
  mpcBlackjackPresenter->resetGame();
}

void SDLView::quitGame() {}

void SDLView::onSetPlayer1NameWidget (SDLTextWidget* pcWidget) {
  onSetPlayer1Name(pcWidget->getData());
}
void SDLView::onSetPlayer2NameWidget (SDLTextWidget* pcWidget) {
  onSetPlayer2Name(pcWidget->getData());
}
void SDLView::onSetPlayer3NameWidget (SDLTextWidget* pcWidget) {
  onSetPlayer3Name(pcWidget->getData());
}
void SDLView::onSetPlayer4NameWidget (SDLTextWidget* pcWidget) {
  onSetPlayer4Name(pcWidget->getData());
}
void SDLView::onSetPlayer5NameWidget (SDLTextWidget* pcWidget) {
  onSetPlayer5Name(pcWidget->getData());
}

void SDLView::handleEvent(SDL_Event event) {
  int x, y;

  if (event.type == SDL_MOUSEBUTTONDOWN &&
    event.button.button == SDL_BUTTON_LEFT)
  {
    x = event.button.x;
    y = event.button.y;
    // Do something
  }
}

void SDLView::render() {
  for (auto value : mcDrawableWidgets) {
    if (value->isVisible()) {
      value->draw(*this);
    }
  }
}

void SDLView::initGame() {}