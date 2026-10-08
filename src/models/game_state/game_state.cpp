#include "game_state.hpp"

void GameState::triggerSubscriptions() {
    auto &events = this->eventManager;
    if (!events) return;

    if (this->roomListModel) this->roomListModel->triggerSubscriptions();
}
