#include "game_state.hpp"

void GameState::triggerSubscriptions() {
    auto &events = this->eventManager;
    if (!events) return;

    if (this->roomListModel) this->roomListModel->triggerSubscriptions();
    if (this->addAdjacentRoomModel) this->addAdjacentRoomModel->triggerSubscriptions();
    if (this->crewListModel) this->crewListModel->triggerSubscriptions();
    if (this->adjacentRoomListRoomDetailsModel) this->adjacentRoomListRoomDetailsModel->triggerSubscriptions();
    if (this->currentRoomModel) this->currentRoomModel->triggerSubscriptions();
    if (this->crewMemberInRoomDetailsModel) this->crewMemberInRoomDetailsModel->triggerSubscriptions();
}
