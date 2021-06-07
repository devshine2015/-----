/* Generated by Together */

#include "StdAfx.h"
#include "Point.h"
#include "SubMap.h"
#include "Entity.h"
#include "GameAppNet.h"
#include "Character.h"
#include "Config.h"
#include "EntityAlloc.h"
#include "GameApp.h"

_DBC_USING

Entity::Entity():m_cat(0),m_ID(0)
{T_B
	m_pCStateCellHead	=0;
	m_pCStateCellTail = 0;
	m_submap	=0;
	m_sAngle	=0;
	memset(&m_STerritory, 0, sizeof(Circle));

	m_SExistCtrl.sState = enumEXISTS_WAITING;
	m_SExistCtrl.sStopState = enumEXISTS_WAITING;
	m_SExistCtrl.ulTick = GetTickCount();
	m_SExistCtrl.lWitherTime = 10 * 1000;
	m_SExistCtrl.lResumeTime = 10 * 1000;

	m_bActiveEyeshot = true;
	m_bValid = false;

	m_CLog.SetEnable(g_bLogEntity);
	//m_CLog.SetLogName("Î´ÃüÃûLog");
	m_CLog.SetLogName("Unnamed Log");
T_E}

void Entity::Free()
{T_B
	g_pGameApp->m_pCEntSpace->ReturnEntity(m_lHandle);
T_E}

void Entity::Initially()
{T_B
	m_CLog.SetEnable(g_bLogEntity);
	//m_CLog.SetLogName("Î´ÃüÃûLog");
m_CLog.SetLogName("Unnamed Log");
	m_bValid = true;
	memset(&m_shape, 0, sizeof(Square));
	memset(&m_STerritory, 0, sizeof(Circle));
	m_sAngle = 0;
	m_submap	=0;
	m_pCStateCellHead	=0;
	m_pCStateCellTail = 0;
	m_pCEyeshotCellNext = 0;
	m_pCEyeshotCellLast = 0;
	SetBirthCity("");
	SetBirthMap("");
	m_sAngle	=0;
	m_CEvent.Init();
	m_SExistCtrl.sState = enumEXISTS_WAITING;
	m_SExistCtrl.sStopState = enumEXISTS_WAITING;
	m_SExistCtrl.ulTick = GetTickCount();
	m_SExistCtrl.lWitherTime = 10 * 1000;
	m_SExistCtrl.lResumeTime = 10 * 1000;
	m_name[0]	='\0';
	m_bActiveEyeshot = true;

	m_usAreaAttr[0] = m_usAreaAttr[1] = 0;
	m_ucIslandID[0] = m_ucIslandID[1] = 0;

	m_pCEyeshotHost = 0;

T_E}

void Entity::Finally()
{T_B
	m_cat		=0;
	m_ID		=0;
	m_SExistCtrl.sState = enumEXISTS_WITHERING;
	m_bValid = false;
	m_pCEyeshotHost = 0;
T_E}

void Entity::WritePK(WPACKET& wpk)			//Ð´ÈëÍæ¼Ò±¾Éí¼°ÆäËùÓÐ¸½¼Ó½á¹¹(ÈçÕÙ»½ÊÞµÈ)µÄËùÓÐÊý¾Ý
{T_B
	//ToDo:Ð´Èë×Ô¼ºµÄÊý¾Ý
	WRITE_LONG(wpk, m_cat);
	WRITE_LONG(wpk, m_ID);
	//WRITE_LONG(wpk, GetShape().centre.x);
	//WRITE_LONG(wpk, GetShape().centre.y);
	//WRITE_LONG(wpk, GetShape().radius);
	WRITE_SEQ(wpk, m_name,uShort(strlen(m_name)+1));

	Char *szLogName = m_CLog.GetLogName();
	WRITE_SEQ(wpk, szLogName,uShort(strlen(szLogName)+1));
T_E}

void Entity::ReadPK(RPACKET& rpk)			//ÖØ¹¹Íæ¼Ò±¾Éí¼°ÆäËùÓÐ¸½¼Ó½á¹¹(ÈçÕÙ»½ÊÞµÈ)
{T_B
	//ToDo:¶Á³ö×Ô¼ºµÄÊý¾Ý
	m_cat	=(short)(READ_LONG(rpk));
	m_ID	= READ_LONG(rpk);
	//Square	SShape;
	//SShape.centre.x	=READ_LONG(rpk);
	//SShape.centre.y	=READ_LONG(rpk);
	//SShape.radius	=READ_LONG(rpk);
	//SetInitShape(SShape);

	strcpy(m_name, READ_STRING(rpk));

	Char szLogName[1024];
	strcpy(szLogName, READ_STRING(rpk));
	m_CLog.SetLogName(szLogName);
T_E}

Entity	*Entity::SearchByIDInEyeshot(cuLong culID)
{T_B
	Point	l_pos = GetShape().centre;
	Rect	l_rect = m_submap->GetEyeshot(l_pos);

	Entity	*pCEnt =0;
	for(long y =l_rect.ltop.y;y <=l_rect.rbtm.y;y++)
	{
		for(long x =l_rect.ltop.x;x <=l_rect.rbtm.x;x++)
		{
			pCEnt = m_submap->m_pCEyeshotCell[y][x].m_pCChaL;
			while (pCEnt)
			{
				if (pCEnt->m_ID == culID)
					goto End;

				pCEnt = pCEnt->m_pCEyeshotCellNext;
			}

			pCEnt = m_submap->m_pCEyeshotCell[y][x].m_pCItemL;
			while (pCEnt)
			{
				if (pCEnt->m_ID == culID)
					goto End;

				pCEnt = pCEnt->m_pCEyeshotCellNext;
			}
		}
	}

End:
	return pCEnt;
T_E}

void Entity::ActiveEyeshot(bool bActive)
{T_B
	if (m_bActiveEyeshot == bActive)
		return;
	if (!m_submap)
		return;

	m_bActiveEyeshot = bActive;
	Long	lNum = -1;
	if (bActive)
		lNum = 1;

	Point l_pt = GetPos();
	Rect l_rect = m_submap->GetEyeshot(l_pt);
	for(long y =l_rect.ltop.y;y <=l_rect.rbtm.y;y++)
	{
		for(long x =l_rect.ltop.x;x <=l_rect.rbtm.x;x++)
		{
			if (bActive)
				m_submap->ActiveEyeshotCell(x, y);
			else
				m_submap->InactiveEyeshotCell(x, y);
		}
	}
T_E}

void Entity::NotiChgToEyeshot(WPACKET chginf, bool bIncludeOwn)
{T_B
	SubMap		*pCMap = GetSubMap();
	Entity		*pCTarEnt;
	CCharacter	*pCTarCha;
	CCharacter	*pCSrcCha;
	pCSrcCha = this->IsCharacter();
	if (pCSrcCha && pCSrcCha->GetPlayer())
	{
		pCSrcCha = pCSrcCha->GetPlayer()->GetCtrlCha();
		pCMap = pCSrcCha->GetSubMap();
	}

	cChar		*cszSrcLogName = GetLogName();
	if (pCSrcCha)
		cszSrcLogName = pCSrcCha->GetLogName();
	if (!pCMap)
	{
		//LG("ÊÓÒ°¼¤»î´íÎó", "ÊµÌå %s ÔÚ½øÐÐÊÓÒ°Í¨¸æÊ±£¬ÆäµØÍ¼Îª¿Õ\n", GetLogName());
		LG("eye shot activation error", "when entity %s is doing eye shot notify£¬the map is null\n", GetLogName());
		return;
	}

	Point l_pos = GetPos();
	if (pCSrcCha)
		l_pos = pCSrcCha->GetPos();
	Point l_pos1 = l_pos;
	Rect l_rect = pCMap->GetEyeshot(l_pos);

	CPlayer	*pHeadPlayer = 0, *pLastPlayer = 0;
	long	x = 0, y = 0;
	long	lEntCount, lEntNum;
	try
	{
		for(y =l_rect.ltop.y;y <=l_rect.rbtm.y;y++)
		{
			for(x =l_rect.ltop.x;x <=l_rect.rbtm.x;x++)
			{
				lEntCount = 0;
				pCTarEnt = pCMap->m_pCEyeshotCell[y][x].m_pCChaL;
				lEntNum = pCMap->m_pCEyeshotCell[y][x].GetChaNum();
				while (pCTarEnt)
				{
					if (++lEntCount > lEntNum)
					{
						//LG("ÊÓÒ°¼¤»î´íÎó", "ÊÓÒ°µ¥Ôª[%d,%d]Êµ¼ÊÊµÌåÊý %d\n", x, y, lEntNum);
						LG("eye shot activation error", "eye shot cell [%d,%d] the fact entity number %d\n", x, y, lEntNum);
						break;
					}

					pCTarCha = pCTarEnt->IsCharacter();
					if (!pCTarCha || (!bIncludeOwn && pCTarEnt == this))
					{
						pCTarEnt = pCTarEnt->m_pCEyeshotCellNext;
						continue;
					}

					if(pCTarCha->IsPlayerFocusCha())
					{
						if ((pCSrcCha && pCSrcCha->CanSeen(pCTarCha)) || !pCSrcCha)
						{
							if (!pHeadPlayer)
							{
								pHeadPlayer = pCTarCha->GetPlayer();
								pLastPlayer = pHeadPlayer;
							}
							else
							{
								pLastPlayer->GetNextPlayer() = pCTarCha->GetPlayer();
								pLastPlayer = (CPlayer *)pLastPlayer->GetNextPlayer();
							}

							if (!pCTarCha->GetSubMap())
								//LG("ÊÓÒ°¼¤»î´íÎó", "ÊµÌå %s[%d,%d] ÔÚ½øÐÐÊÓÒ°Í¨¸æÊ±Ä¿±êÍæ¼Ò %s(%s)[%d,%d] µÄµØÍ¼Îª¿Õ\n",
								LG("eye shot activation error", "when entity %s[%d,%d] is doing eye shot notify, the aim player %s(%s)[%d,%d] map is null\n",
									cszSrcLogName, l_pos1.x, l_pos1.y,
									pCTarCha->GetLogName(), pCTarCha->GetPlyCtrlCha()->GetLogName(), pCTarCha->GetPos().x, pCTarCha->GetPos().y);
						}
					}

					pCTarEnt = pCTarEnt->m_pCEyeshotCellNext;
				}
			}
		}
	}
	catch (...)
	{
		//LG("ÊÓÒ°¼¤»î´íÎó", "ÊµÌå %s ÔÚ½øÐÐÊÓÒ°Í¨¸æÊ±´íÎó(×ø±ê[%d,%d]£¬ÊÓÒ°[%d,%d;%d,%d])£¬µ±Ç°ÊÓÒ°µ¥Ôª[%d,%d]\n", cszSrcLogName,
		//	l_pos1.x, l_pos1.y, l_rect.ltop.x, l_rect.ltop.y, l_rect.rbtm.x, l_rect.rbtm.y, x, y);
		LG("eye shot activation error", "entity %s eye shot notify error(coordnate [%d,%d]£¬eye shot [%d,%d;%d,%d])£¬currently eye shot cell[%d,%d]\n", cszSrcLogName,
			l_pos1.x, l_pos1.y, l_rect.ltop.x, l_rect.ltop.y, l_rect.rbtm.x, l_rect.rbtm.y, x, y);
		throw;
	}

	if (pLastPlayer)
		pLastPlayer->GetNextPlayer() = NULL;
	SENDTOCLIENT(chginf, pHeadPlayer);
T_E}

bool Entity::overlap(long &xdist, long &ydist)
{
	bool	b_retval	= false;

	if (!m_submap || !m_submap->IsValidPos(m_shape.centre.x + xdist, m_shape.centre.y + ydist))
		return true;

	//if (EdgeOverlap(xdist, ydist))
	//	b_retval = true;
	//if (!xdist && !ydist && b_retval)
	//	return b_retval;
	if (ObstacleOverlap(xdist, ydist))
		b_retval = true;

	return b_retval;
}

bool Entity::EdgeOverlap(long& xdist, long& ydist)
{T_B
	bool	l_retval = false;

	//±¸·ÝÏÂÀ´×÷ÎªÒ»¸öÒÆ¶¯·½ÏòµÄ¼ÇÂ¼
	const long lc_xdist = xdist;
	const long lc_ydist = ydist;
	//¼ì²éÊÇ·ñÔ½³öµØÍ¼

	Square l_shape, SSrcShape = GetShape();

	l_shape.radius = SSrcShape.radius;
	//x·½Ïò
	const Rect	&area = m_submap->GetRange();
	bool	l_flag = false;
	l_shape.centre.x = SSrcShape.centre.x + xdist;
	long l_xdlt = (l_shape.centre.x - l_shape.radius) - area.ltop.x;
	if (l_xdlt < 0)
	{
		l_flag = true;
		xdist -= l_xdlt;
	}
	else
	{
		l_xdlt = (l_shape.centre.x + l_shape.radius) - area.rbtm.x;
		if (l_xdlt > 0)
		{
			l_flag = true;
			xdist -= l_xdlt;
		}
	}
	if (l_flag)
	{
		l_retval = true;
		if (lc_xdist != 0)
		{
			ydist = (lc_ydist * xdist) / lc_xdist;
		}
	}
	//y·½Ïò
	l_flag = false;
	l_shape.centre.y = SSrcShape.centre.y + ydist;
	long l_ydlt = (l_shape.centre.y - l_shape.radius) - area.ltop.y;
	if (l_ydlt < 0)
	{
		l_flag = true;
		ydist -= l_ydlt;
	}
	else
	{
		l_ydlt = (l_shape.centre.y + l_shape.radius) - area.rbtm.y;
		if (l_ydlt > 0)
		{
			l_flag = true;
			ydist -= l_ydlt;
		}
	}
	if (l_flag)
	{
		l_retval = true;
		if (lc_ydist != 0)
		{
			xdist = (lc_xdist * ydist) / lc_ydist;
		}
	}

	return l_retval;
T_E}

//bool Entity::ObstacleOverlap(long &xdist, long &ydist)
//{
//	Short	sUnitSX, sUnitEX, sUnitSY, sUnitEY;
//	Short	sUnitWidth, sUnitHeight;
//	Point	SPos = GetPos();
//
//	sUnitWidth = m_submap->GetBlockCellWidth();
//	sUnitHeight = m_submap->GetBlockCellHeight();
//
//	sUnitSX = Short(SPos.x / sUnitWidth);
//	sUnitEX = Short((SPos.x + xdist) / sUnitWidth);
//	sUnitSY = Short(SPos.y / sUnitHeight);
//	sUnitEY = Short((SPos.y + ydist) / sUnitHeight);
//
//	if (sUnitSX == sUnitEX && sUnitSY == sUnitEY)
//	{
//		if (m_submap->IsBlock(sUnitSX, sUnitSY))
//		{
//			xdist = 0, ydist = 0;
//			return true;
//		}
//		else
//			return false;
//	}
//
//	bool	bIs45Dir = false;
//	if (xdist == ydist)
//	{
//		Short	sModelX = Short(SPos.x % sUnitWidth);
//		Short	sModelY = Short(SPos.y % sUnitHeight);
//		if (sModelX == sModelY)
//			bIs45Dir = true;
//	}
//	else if (-1 * xdist == ydist)
//	{
//		Short	sModelX = Short(SPos.x % sUnitWidth);
//		Short	sModelY = Short(SPos.y % sUnitHeight);
//		if (sUnitWidth - sModelX == sModelY || sModelX == sUnitHeight - sModelY)
//			bIs45Dir = true;
//	}
//
//	if (bIs45Dir)
//	{
//		Char	chXDir = 1;
//		Char	chYDir = 1;
//		if (sUnitSX > sUnitEX)
//			chXDir = -1;
//		if (sUnitSY > sUnitEY)
//			chYDir = -1;
//
//		Short	sLoop = (sUnitEX - sUnitSX) * chXDir;
//		for (Short i = 0; i <= sLoop; i++)
//			if (m_submap->IsBlock(sUnitSX + i * chXDir, sUnitSY + i * chYDir))
//			{
//				xdist = 0, ydist = 0;
//				return true;
//			}
//	}
//	else
//	{
//		if (m_submap->IsBlock(sUnitEX, sUnitEY))
//		{
//			xdist = 0, ydist = 0;
//			return true;
//		}
//
//		if (abs(xdist) >= abs(ydist))
//		{
//			if (xdist == 0)
//				return false;
//			Long	lRSX = SPos.x, lRSY = SPos.y;
//			if (sUnitSX > sUnitEX)
//			{
//				Short	sTemp = sUnitSX;
//				sUnitSX = sUnitEX;
//				sUnitEX = sTemp;
//				lRSX += xdist;
//				lRSY += ydist;
//			}
//			for (Short x = 0; x < sUnitEX - sUnitSX; x++)
//			{
//				Long y = ydist * ((sUnitWidth - lRSX % sUnitWidth) + x * sUnitWidth) / xdist + lRSY;
//				Short sRUnitY = Short(y / sUnitHeight);
//				if (m_submap->IsBlock(sUnitSX + x, sRUnitY))
//				{
//					xdist = 0, ydist = 0;
//					return true;
//				}
//				if (m_submap->IsBlock(sUnitSX + x + 1, sRUnitY))
//				{
//					xdist = 0, ydist = 0;
//					return true;
//				}
//			}
//		}
//		else
//		{
//			if (ydist == 0)
//				return false;
//			Long	lRSX = SPos.x, lRSY = SPos.y;
//			if (sUnitSY > sUnitEY)
//			{
//				Short	sTemp = sUnitSY;
//				sUnitSY = sUnitEY;
//				sUnitEY = sTemp;
//				lRSX += xdist;
//				lRSY += ydist;
//			}
//			for (Short y = 0; y < sUnitEY - sUnitSY; y++)
//			{
//				Long x = xdist * ((sUnitHeight - lRSY % sUnitHeight) + y * sUnitHeight) / ydist + lRSX;
//				Short sRUnitX = Short(x / sUnitWidth);
//				if (m_submap->IsBlock(sRUnitX, sUnitSY + y))
//				{
//					xdist = 0, ydist = 0;
//					return true;
//				}
//				if (m_submap->IsBlock(sRUnitX, sUnitSY + y + 1))
//				{
//					xdist = 0, ydist = 0;
//					return true;
//				}
//			}
//		}
//	}
//
//	return false;
//}

bool Entity::ObstacleOverlap(long &xdist, long &ydist)
{
	Short	sUnitSX, sUnitEX, sUnitSY, sUnitEY;
	Short	sUnitWidth, sUnitHeight;
	Point	SPos = GetPos();

	sUnitWidth = m_submap->GetBlockCellWidth();
	sUnitHeight = m_submap->GetBlockCellHeight();

	sUnitSX = Short(SPos.x / sUnitWidth);
	sUnitEX = Short((SPos.x + xdist) / sUnitWidth);
	sUnitSY = Short(SPos.y / sUnitHeight);
	sUnitEY = Short((SPos.y + ydist) / sUnitHeight);

	if (sUnitSX == sUnitEX && sUnitSY == sUnitEY)
	{
		if (m_submap->IsBlock(sUnitSX, sUnitSY))
		{
			xdist = 0, ydist = 0;
			return true;
		}
	}

	bool	bIs45Dir = false;
	if (xdist == ydist)
	{
		Short	sModelX = Short(SPos.x % sUnitWidth);
		Short	sModelY = Short(SPos.y % sUnitHeight);
		if (sModelX == sModelY)
			bIs45Dir = true;
	}
	else if (-1 * xdist == ydist)
	{
		Short	sModelX = Short(SPos.x % sUnitWidth);
		Short	sModelY = Short(SPos.y % sUnitHeight);
		if (sUnitWidth - sModelX == sModelY || sModelX == sUnitHeight - sModelY)
			bIs45Dir = true;
	}

	if (bIs45Dir)
	{
		Char	chXDir = 1;
		Char	chYDir = 1;
		if (sUnitSX > sUnitEX)
			chXDir = -1;
		if (sUnitSY > sUnitEY)
			chYDir = -1;

		Short	sLoop = (sUnitEX - sUnitSX) * chXDir;
		for (Short i = 0; i <= sLoop; i++)
			if (m_submap->IsBlock(sUnitSX + i * chXDir, sUnitSY + i * chYDir))
			{
				xdist = 0, ydist = 0;
				return true;
			}
	}
	else
	{
		if (sUnitSX > sUnitEX)
		{
			Short	sTemp = sUnitSX;
			sUnitSX = sUnitEX;
			sUnitEX = sTemp;
		}
		if (sUnitSY > sUnitEY)
		{
			Short	sTemp = sUnitSY;
			sUnitSY = sUnitEY;
			sUnitEY = sTemp;
		}

		float v0[2]; v0[0] = (float)SPos.x, v0[1] = (float)SPos.y;
		float v1[2]; v1[0] = (float)(SPos.x + xdist), v1[1] = (float)(SPos.y + ydist);
		float p1[2], p2[2], p3[2], p4[2];
		for (Short x = sUnitSX; x <= sUnitEX; x++)
		{
			for (Short y = sUnitSY; y <= sUnitEY; y++)
			{
				if (m_submap->IsBlock(x, y))
				{
					p1[0] = (float)(x * sUnitWidth), p1[1] = (float)(y * sUnitHeight);
					p2[0] = (float)(p1[0] + sUnitWidth - 1), p2[1] = p1[1];
					p3[0] = p2[0], p3[1] = (float)(p2[1] + sUnitHeight - 1);
					p4[0] = p1[0], p4[1] = p3[1];

					if(LineIntersection(v0, v1, p1, p2, FALSE) || LineIntersection(v0, v1, p2, p3, FALSE)
						|| LineIntersection(v0, v1, p3, p4, FALSE) || LineIntersection(v0, v1, p4, p1, FALSE))
					{
						xdist = 0, ydist = 0;
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool Entity::IsLiveing(void)
{T_B
	CFightAble	*pCObj = IsFightAble();
	if (!pCObj)
		return true;
	else if (pCObj->m_CChaAttr.GetAttr(ATTR_HP) > 0)
		return true;

	return false;
T_E}

CStateCellNode* Entity::EnterStateCell(CStateCell *pStateCell, CChaListNode *pEntiNode, bool bIsIn)
{
	CStateCellNode	*pCMgrNode = g_pGameApp->m_StateCellNodeHeap.Get();
	pCMgrNode->m_pCStateCell = pStateCell;
	pCMgrNode->m_pCChaNode = pEntiNode;
	if (bIsIn) // ×÷ÎªÊ×½Úµã¼ÓÈë
	{
		pCMgrNode->m_pCLast = 0;
		if (pCMgrNode->m_pCNext = m_pCStateCellHead)
			m_pCStateCellHead->m_pCLast = pCMgrNode;
		else
			m_pCStateCellTail = pCMgrNode;
		m_pCStateCellHead = pCMgrNode;
	}
	else
	{
		pCMgrNode->m_pCNext = 0;
		if (pCMgrNode->m_pCLast = m_pCStateCellTail)
			m_pCStateCellTail->m_pCNext = pCMgrNode;
		else
			m_pCStateCellHead = pCMgrNode;
		m_pCStateCellTail = pCMgrNode;
	}

	return pCMgrNode;
}

void Entity::OutMgrUnit(CStateCellNode *pCMgrNode)
{
	if (pCMgrNode->m_pCLast)
		pCMgrNode->m_pCLast->m_pCNext = pCMgrNode->m_pCNext;
	if (pCMgrNode->m_pCNext)
		pCMgrNode->m_pCNext->m_pCLast = pCMgrNode->m_pCLast;
	if (m_pCStateCellHead == pCMgrNode)
		if (m_pCStateCellHead = pCMgrNode->m_pCNext)
			m_pCStateCellHead->m_pCLast = 0;
	if (m_pCStateCellTail == pCMgrNode)
		if (m_pCStateCellTail = pCMgrNode->m_pCLast)
			m_pCStateCellTail->m_pCNext = 0;
	pCMgrNode->m_pCLast = 0;
	pCMgrNode->m_pCNext = 0;
	pCMgrNode->Free();
}

void Entity::SetCenterMgrNode(CStateCellNode *pCMgrNode)
{
	if (pCMgrNode == m_pCStateCellHead)
		return;

	if (pCMgrNode->m_pCLast)
		pCMgrNode->m_pCLast->m_pCNext = pCMgrNode->m_pCNext;
	if (pCMgrNode->m_pCNext)
		pCMgrNode->m_pCNext->m_pCLast = pCMgrNode->m_pCLast;
	if (m_pCStateCellHead == pCMgrNode)
		m_pCStateCellHead = pCMgrNode->m_pCNext;
	if (m_pCStateCellTail == pCMgrNode)
		m_pCStateCellTail = pCMgrNode->m_pCLast;

	pCMgrNode->m_pCLast = 0;
	if (pCMgrNode->m_pCNext = m_pCStateCellHead)
		m_pCStateCellHead->m_pCLast = pCMgrNode;
	else
		m_pCStateCellTail = pCMgrNode;
	m_pCStateCellHead = pCMgrNode;
}

SSkillStateUnit* Entity::GetAreaState(dbc::uChar uchStateID)
{
	if (!m_pCStateCellHead || !m_pCStateCellHead->m_pCStateCell)
		return 0;
	return m_pCStateCellHead->m_pCStateCell->m_CSkillState.GetSStateByID(uchStateID);
}

void Entity::RefreshArea(void)
{
	uShort	usAreaAttr;
	uChar	uchIsland;
	Short	sUnitWidth, sUnitHeight;
	Short	sUnitX, sUnitY;
	m_submap->GetTerrainCellSize(&sUnitWidth, &sUnitHeight);
	sUnitX = Short(m_shape.centre.x / sUnitWidth);
	sUnitY = Short(m_shape.centre.y / sUnitHeight);
	m_submap->GetTerrainCellAttr(sUnitX, sUnitY, usAreaAttr);
	m_submap->GetTerrainCellIsland(sUnitX, sUnitY, uchIsland);

	if (m_usAreaAttr[1] != usAreaAttr || m_ucIslandID[1] != uchIsland)
		AreaChange();

	m_usAreaAttr[0] = m_usAreaAttr[1];
	m_usAreaAttr[1] = usAreaAttr;
	m_ucIslandID[0] = m_ucIslandID[1];
	m_ucIslandID[1] = uchIsland;
}

void Entity::RefreshArea(Point *pSrcPos)
{
	Short	sUnitWidth, sUnitHeight;
	m_submap->GetTerrainCellSize(&sUnitWidth, &sUnitHeight);
	Short	sUnitX, sUnitY;
	sUnitX = Short(m_shape.centre.x / sUnitWidth);
	sUnitY = Short(m_shape.centre.y / sUnitHeight);

	if ((pSrcPos->x / sUnitWidth == sUnitX) && (pSrcPos->y / sUnitHeight == sUnitY))
		return;

	uShort	usAreaAttr;
	uChar	uchIsland;
	m_submap->GetTerrainCellAttr(sUnitX, sUnitY, usAreaAttr);
	m_submap->GetTerrainCellIsland(sUnitX, sUnitY, uchIsland);

	if (m_usAreaAttr[1] != usAreaAttr || m_ucIslandID[1] != uchIsland)
		AreaChange();

	m_usAreaAttr[0] = m_usAreaAttr[1];
	m_usAreaAttr[1] = usAreaAttr;
	m_ucIslandID[0] = m_ucIslandID[1];
	m_ucIslandID[1] = uchIsland;
}

dbc::Short Entity::GetEyeshotWidth(void)
{
	if (!GetSubMap()) return 0;
	return GetSubMap()->GetEyeshotWidth();
}

bool Entity::IsInEyeshot(Entity *pCTarEnti)
{
	if (!pCTarEnti)
		return false;
	if (!GetSubMap())
		return false;
	if (GetSubMap() != pCTarEnti->GetSubMap())
		return false;
	Point	SEyeshotC = GetPos(), STarEyeshotC = pCTarEnti->GetPos();
	GetSubMap()->GetEyeshotCenter(SEyeshotC);
	GetSubMap()->GetEyeshotCenter(STarEyeshotC);
	dbc::Short	sEyeshotW = GetEyeshotWidth();
	dbc::Short	sEyeshotH = GetEyeshotHeight();
	if (abs(SEyeshotC.x - STarEyeshotC.x) <= sEyeshotW && abs(SEyeshotC.y - STarEyeshotC.y) <= sEyeshotH)
		return true;

	return false;
}

void Entity::WriteEventInfo(WPACKET &pk)
{
	WRITE_LONG(pk, GetID());
	if (IsCharacter())
		WRITE_CHAR(pk, 1);
	else
		WRITE_CHAR(pk, 2);
	GetEvent().WriteInfo(pk);
}

void Entity::SynEventInfo(void)
{
	WPACKET WtPk	=GETWPACKET();
	WRITE_CMD(WtPk, CMD_MC_EVENT_INFO);	//Í¨¸æÐÐ¶¯
	WriteEventInfo(WtPk);
	NotiChgToEyeshot(WtPk, false);
}

SubMap* Entity::GetSubMapFar(void)
{
	SubMap	*pCMap = GetSubMap();
	if (!pCMap)
	{
		CCharacter	*pCMainCha;
		CCharacter	*pCCha = this->IsCharacter();
		if (pCCha)
		{
			pCMainCha = pCCha->GetPlyMainCha();
			CMapRes	*pCMapRes = g_pGameApp->FindMapByName(pCMainCha->GetBirthMap(), true);
			if (pCMapRes)
				pCMap = pCMapRes->GetCopy();
		}
	}

	return pCMap;
}

void NotiPkToWorld(WPACKET chginf)
{T_B
    SENDTOWORLD(chginf);
T_E}