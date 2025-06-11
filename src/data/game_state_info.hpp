#pragma once

class PlayerVessel;
class PlayerInfo;
class JobHandler;
class GameStateInfo {
private:
    PlayerInfo* _info;
    PlayerVessel* _vessel;
    JobHandler* _jobHandler;
public:
    GameStateInfo(PlayerInfo* info, PlayerVessel* vessel, JobHandler* jobHandler) {
        _info = info;
        _vessel = vessel;
        _jobHandler = jobHandler;
    }

    PlayerInfo* getPlayerInfo() { return _info; }

    PlayerVessel* getPlayerVessel() { return _vessel; }

    JobHandler* getJobHandler() { return _jobHandler; }
};