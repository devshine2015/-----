/* Generated by Together */

#ifndef GATESERVER_H
#define GATESERVER_H

#include "dstring.h"
#include "DataSocket.h"

_DBC_USING

class GateServer
{
	friend class GroupServerApp;
public:
	// Modify by lark.li 20081119 begin
	//GateServer() :m_datasock(0){}
	GateServer() :m_datasock(0),m_bSync(false){}
	// End
	bool SetDataSock(DataSocket	*datasock)
	{
		bool l_retval =true;
		if(m_datasock && datasock)
		{
			l_retval	=false;
		}else	if(datasock)
		{
			l_retval  =datasock->SetPointer(this);
		}
		if(l_retval)
		{
			if(m_datasock)
			{
				m_datasock->SetPointer(0);
			}
			m_datasock	=datasock;
		}
		return	l_retval;
	}
	DataSocket	*GetDataSock()
	{
		return m_datasock;
	}

	// Add by lark.li 20081119 begin
	bool	IsSync(){ return m_bSync; }
	void	SetSync(bool sync = true) { m_bSync = sync; }
	// End

private:
	dstring			m_name;
	DataSocket	*	m_datasock;
	// Add by lark.li 20081119 begin
	bool		m_bSync;		// GateServer和GroupServer的同步标志
	// End
};


// Add by lark.li 20081119 begin
class GroupServerAgent
{
	friend class GroupServerApp;
public:
	GroupServerAgent() :m_datasock(0){}
	bool SetDataSock(DataSocket	*datasock)
	{
		bool l_retval =true;
		if(m_datasock && datasock)
		{
			l_retval	=false;
		}else	if(datasock)
		{
			l_retval  =datasock->SetPointer(this);
		}
		if(l_retval)
		{
			if(m_datasock)
			{
				m_datasock->SetPointer(0);
			}
			m_datasock	=datasock;
		}
		return	l_retval;
	}
	DataSocket	*GetDataSock()
	{
		return m_datasock;
	}
private:
	dstring			m_name;
	DataSocket	*	m_datasock;
};
// End

#endif //GATESERVER_H