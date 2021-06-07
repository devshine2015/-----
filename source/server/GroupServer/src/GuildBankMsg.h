#include "Player.h"
#include <vector>

struct GuildBankMsg{
	Player* player;
	WPacket* msg;
};

std::vector<GuildBankMsg> guildBankMsgQueue[201];
std::vector<GuildBankMsg> bagOfHoldingQueue;
