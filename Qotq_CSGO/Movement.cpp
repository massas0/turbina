#include "Movement.h"

void CMovement::Bhop(C_BaseEntity* pLocal, CUserCmd* cmd) {
	if (cmd->buttons & IN_JUMP) {
		if (pLocal->GetFlags() & FL_ONGROUND || pLocal->GetMoveType() & MOVETYPE_LADDER)
		{
			cmd->buttons |= IN_JUMP;
		}
		else
		{
			cmd->buttons &= ~IN_JUMP;
		}
	}
}