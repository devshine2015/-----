/* Generated by Together */

#ifndef MGRUNIT_H
#define MGRUNIT_H

/**
 * @alias 屏幕1/4单元 
 */

#include "TryUtil.h"

//class MgrUnit {
//public:
//
//	MgrUnit():m_objlst(0),m_lCount(0)
//	{
//		m_lCount = 0;
//		m_pANext = 0;
//		m_pALast = 0;
//	}
//	~MgrUnit();
//
//friend class Entity;
//friend class Movable;
//friend class CMoveAble;
//friend class CGameApp;
//friend class SubMap;
//friend class CChaSpawn;
//friend class CActiveMgrUnitL;
//
//public:    
//
//    /**
//     * @directed
//     * @supplierCardinality 0..* 
//     */
//	long 	    m_lCount;	// 激活计数
//    Entity		*m_objlst;
//
//	MgrUnit		*m_pANext; // 指向“激活的管理单元链表“的指针
//	MgrUnit		*m_pALast;
//};
//
//class CActiveMgrUnitL // 激活的管理单元链表
//{
//public:
//	CActiveMgrUnitL()
//	{T_B
//		m_pHead  = 0;
//		m_lCount = 0;
//	T_E}
//
//	inline void		Add(MgrUnit *pObj);
//	inline void		Del(MgrUnit *pObj);
//
//	inline void		BeginGet(void);
//	inline MgrUnit*	GetNext(void);
//
//	long			GetActiveNum(void) {return m_lCount;}
//
//protected:
//
//private:
//	MgrUnit	*m_pHead;
//
//	MgrUnit	*m_pCur;
//
//	long	m_lCount;
//
//};
//
//inline void CActiveMgrUnitL::Add(MgrUnit *pObj)
//{T_B
//	if (m_pHead)
//	{
//		pObj->m_pANext = m_pHead;
//		m_pHead->m_pALast = pObj;
//		pObj->m_pALast = 0;
//		m_pHead = pObj;
//	}
//	else
//		m_pHead = pObj;
//
//	m_lCount++;
//T_E}
//
//inline void CActiveMgrUnitL::Del(MgrUnit *pObj)
//{T_B
//	if (pObj != m_pHead)
//	{
//		pObj->m_pALast->m_pANext = pObj->m_pANext;
//		if (pObj->m_pANext)
//			pObj->m_pANext->m_pALast = pObj->m_pALast;
//		pObj->m_pANext = 0;
//		pObj->m_pALast = 0;
//	}
//	else
//	{
//		m_pHead = pObj->m_pANext;
//		pObj->m_pANext = 0;
//		pObj->m_pALast = 0;
//	}
//
//	m_lCount--;
//T_E}
//
//inline void CActiveMgrUnitL::BeginGet()
//{T_B
//	m_pCur = m_pHead;
//T_E}
//
//inline MgrUnit* CActiveMgrUnitL::GetNext()
//{T_B
//	MgrUnit	*pRet = m_pCur;
//
//	if (m_pCur)
//		m_pCur = m_pCur->m_pANext;
//
//	return pRet;
//T_E}
//
#endif //MGRUNIT_H