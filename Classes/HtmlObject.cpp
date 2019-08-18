//////////////////////////////////////////////////////////////////////////////////////////CHtmlObject.cpp//////////////////////////////////////////////////author: JesonYang////////////////////////
 
#pragma once
 
/*****************************************************************************************************************
created: 2011/12/03
author: JesonYang
blog: http://blog.csdn.net/yc7369
*****************************************************************************************************************/
 
 
#include "HtmlObject.h"
#include "HtmlHelper.h"
//
BOOL CHtmlObject::IsSpace(TCHAR tcLetter)
{
	//以下字符在HTML标记里都算是空格。
	return (tcLetter == _T(' ') || tcLetter == _T('\r') || tcLetter == _T('\n') || tcLetter == _T('\t'));
}
 
CHtmlObject::CHtmlObject(void)
{
	m_pszSnapshotBuffer = NULL;
	m_nSnapshotBufferLen = 0;
	m_nSnapshotStringLen = 0;
	m_pstHead = NULL;
	m_pstTail = NULL;
}
 
CHtmlObject::~CHtmlObject(void)
{
	DeleteSnapshot();
}
//
CHtmlObject::tagNode * CHtmlObject::InnerAllocNode()
{
	CHtmlObject::tagNode * pstResult = new CHtmlObject::tagNode;
	if (pstResult)
	{
		::ZeroMemory((LPVOID)pstResult, sizeof(CHtmlObject::tagNode));
	}
	return pstResult;
}
void CHtmlObject::InnerFreeNode(CHtmlObject::tagNode * lpstNode)
{
	if (lpstNode)
		delete lpstNode;
}
void CHtmlObject::InnerLinkNextNode(tagNode * lpstNode)
{
	//链接到“尾”结点。
	//1：如果没有“头”节点，那么表示链表是“空”的。
	//2：如果已经存“头”节点，那么就链接新节点到“尾”节点，并重新记录“尾”节点指针。
	if (m_pstHead == NULL)
	{
		m_pstHead = lpstNode;
		m_pstTail = lpstNode;
	}
	else
	{
		m_pstTail->s_pstNext = lpstNode;
		m_pstTail = lpstNode;
	}
 
 
#ifdef _DEBUG
 
	if (lpstNode->s_pszKey)
	{
		::OutputDebugString(_T("--"));
		::OutputDebugString(lpstNode->s_pszKey);
		::OutputDebugString(_T("--\r\n"));
	}
	if (lpstNode->s_pszValue)
	{
		::OutputDebugString(_T("--"));
		::OutputDebugString(lpstNode->s_pszValue);
		::OutputDebugString(_T("--\r\n"));
	}
 
#endif //_DEBUG
 
}
void CHtmlObject::InnerLinkRightNode(tagNode * lpstTagNode, tagNode * lpstNode)
{
	//链接到“属性”的“头”节点。
	//1：把现有的“属性”链表，链接到当前新节点的下。
	//2：把当前节点做为“头”节点保存。
	lpstNode->s_pstRight = lpstTagNode->s_pstRight;
	lpstTagNode->s_pstRight = lpstNode;
 
#ifdef _DEBUG
	if (lpstNode->s_pszKey)
	{
		::OutputDebugString(_T("-->"));
		::OutputDebugString(lpstNode->s_pszKey);
		::OutputDebugString(_T("<--\r\n"));
	}
	if (lpstNode->s_pszValue)
	{
		::OutputDebugString(_T("-->"));
		::OutputDebugString(lpstNode->s_pszValue);
		::OutputDebugString(_T("<--\r\n"));
	}
#endif //_DEBUG
}
void CHtmlObject::InnerCleanupNode()
{
	//循环清除所有节点。如果存在“属性”节点一并清除。
	CHtmlObject::tagNode * pstPrev = NULL;
	while (m_pstHead)
	{
		pstPrev = m_pstHead;
		m_pstHead = m_pstHead->s_pstNext;
		//first
		InnerCleanupRightNode(pstPrev);
		//second
		InnerFreeNode(pstPrev);
	}
	m_pstHead = NULL;
	m_pstTail = NULL;
}
void CHtmlObject::InnerCleanupRightNode(CHtmlObject::tagNode * lpstNode)
{
	//循环清除所有“属性”节点。
	CHtmlObject::tagNode * pstHead = lpstNode->s_pstRight;
	CHtmlObject::tagNode * pstPrev = NULL;
	while (pstHead)
	{
		pstPrev = pstHead;
		pstHead = pstHead->s_pstRight;
		InnerFreeNode(pstPrev);
	}
	pstHead = NULL;
	pstPrev = NULL;
}
//
void CHtmlObject::AutoTakeSnapshot(PBYTE lpszString, UINT nStringLen)
{
 
	if (lpszString && nStringLen > 0)
	{
		//根据数据头自动判断是否需要转换数据到当前应程所使用的编码。
		if (nStringLen >= 2)
		{
			if (lpszString[0] == 0xFF && lpszString[1] == 0xFE) // skip 0xFF,0xFE
			{
				TakeSnapshot(lpszString + 2, nStringLen - 2, CHtmlObject::CHARSET_UNICODE);
			}
			else if (lpszString[0] == 0xEF && lpszString[1] == 0xBB && lpszString[2] == 0xBF)// skip 0xEF,0xBB,0xBF
			{
				TakeSnapshot(lpszString + 3, nStringLen - 3, CHtmlObject::CHARSET_UTF8);
			}
			else
			{
				TakeSnapshot(lpszString, nStringLen, CHtmlObject::CHARSET_MULTIBYTE);
			}
		}
		else
		{
			TakeSnapshot(lpszString, nStringLen, CHtmlObject::CHARSET_MULTIBYTE);
		}
	}
}
void CHtmlObject::TakeSnapshot(PBYTE lpszString, UINT nStringLen, UINT nFromCharset)
{
	//delete old snapshot
	DeleteSnapshot();
 
	if (lpszString && nStringLen > 0)
	{
 
		//transform to TCHAR
 
		if (CHtmlHelper::CHARSET_UTF8 == nFromCharset)
		{
 
#ifdef _UNICODE 
 
			m_nSnapshotBufferLen = nStringLen;
			m_pszSnapshotBuffer = new TCHAR[m_nSnapshotBufferLen];
 
			::memset((LPVOID)m_pszSnapshotBuffer, 0, m_nSnapshotBufferLen*sizeof(TCHAR));
			m_nSnapshotStringLen = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)lpszString, nStringLen, m_pszSnapshotBuffer, m_nSnapshotBufferLen);
#else
			::OutputDebugString(_T("no support"));
 
#endif //_UNICODE
 
		}
		else if (CHtmlHelper::CHARSET_UNICODE == nFromCharset)
		{
 
#ifdef _UNICODE 
 
			m_nSnapshotBufferLen = nStringLen;
			m_pszSnapshotBuffer = new TCHAR[m_nSnapshotBufferLen];
 
			::memset((LPVOID)m_pszSnapshotBuffer, 0, m_nSnapshotBufferLen*sizeof(TCHAR));
			::memcpy((LPVOID)m_pszSnapshotBuffer, lpszString, nStringLen);
 
#else
 
			m_nSnapshotBufferLen = nStringLen / 2 + 1;
			m_pszSnapshotBuffer = new TCHAR[m_nSnapshotBufferLen];
 
			::memset((LPVOID)m_pszSnapshotBuffer, 0, m_nSnapshotBufferLen*sizeof(TCHAR));
			m_nSnapshotStringLen = ::WideCharToMultiByte(CP_ACP, 0, (LPWSTR)lpszString, nStringLen, (LPSTR)m_pszSnapshotBuffer, m_nSnapshotBufferLen, NULL, NULL);
 
#endif //_UNICODE
 
		}
		else
		{
 
#ifdef _UNICODE 
 
			m_nSnapshotBufferLen = nStringLen;
			m_pszSnapshotBuffer = new TCHAR[m_nSnapshotBufferLen];
 
			::memset(m_pszSnapshotBuffer, 0, m_nSnapshotBufferLen*sizeof(TCHAR));
			m_nSnapshotStringLen = ::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)lpszString, nStringLen, m_pszSnapshotBuffer, m_nSnapshotBufferLen);
#else
 
			m_nSnapshotBufferLen = nStringLen;
			m_pszSnapshotBuffer = new TCHAR[m_nSnapshotBufferLen];
 
			::memset((LPVOID)m_pszSnapshotBuffer, 0, m_nSnapshotBufferLen*sizeof(TCHAR));
			::memcpy((LPVOID)m_pszSnapshotBuffer, lpszString, nStringLen);
 
#endif //_UNICODE
 
		}
	}
}
void CHtmlObject::DeleteSnapshot()
{
	//先清除树型表。
	InnerCleanupNode();
 
	if (m_pszSnapshotBuffer)
		delete[]m_pszSnapshotBuffer;
 
	m_pszSnapshotBuffer = NULL;
	m_nSnapshotBufferLen = 0;
	m_nSnapshotStringLen = 0;
}
//
void CHtmlObject::Parse()
{
#ifdef _AFX
	CString strTrace;
	strTrace.Format(_T("CHtmlObject::Parse() --begin-->(%d)\r\n"), ::GetTickCount());
	::OutputDebugString(strTrace);
#endif //_AFX
 
	InnerParse();
 
#ifdef _AFX
	strTrace.Format(_T("CHtmlObject::Parse() --end-->(%d)\r\n"), ::GetTickCount());
	::OutputDebugString(strTrace);
#endif //_AFX
}
//
void CHtmlObject::InnerParse()
{
	LPTSTR pszFind = m_pszSnapshotBuffer;
 
	//跳过所有“空格”
	while (*pszFind != _T('\0') && CHtmlObject::IsSpace(*pszFind))
	{
		//下一个字符
		pszFind++;
	}
	//直到碰到'\0'就退出
	do
	{
		// 不是“\0”，并且第一个字符为“<”则置换为“\0”，否则什么也不做。
		//这么写的原因就在于InnerSplitContent()返回后 “<”可能已经被置换成“\0”。
		if (*pszFind != _T('\0') && *pszFind == _T('<'))
		{
			//把“<”置换为“\0”,做为结尾。
			*pszFind = _T('\0');
			//下一个字符。
			pszFind++;
		}
 
		// 不是“\0”
		if (*pszFind != _T('\0'))
		{
			//是否为注释
			if (*pszFind == _T('!'))
			{
				//申请一个点节。
				tagNode *pstNode = InnerAllocNode();
				//解析注释，返回的是注释后面的内容。
				pszFind = InnerSplitComment(pstNode, pszFind);
				//链接到“链表”。（下）
				InnerLinkNextNode(pstNode);
			}
			else
			{
				//申请一个点节。
				tagNode *pstNode = InnerAllocNode();
				//解析tag，返回的是tag后面的内容。
				pszFind = InnerSplitTag(pstNode, pszFind);
				//解析content返回的是content后面的内容。
				pszFind = InnerSplitContent(pstNode, pszFind);
				//链接到“链表”。（下）
				InnerLinkNextNode(pstNode);
			}
		}
 
	} while (*pszFind != _T('\0'));
}
LPTSTR CHtmlObject::InnerSplitComment(CHtmlObject::tagNode * lpstNode, LPTSTR lpszTagString)
{
	LPTSTR pszFind = lpszTagString;
	//指向注释开头(已经跳过“<”字符)
	lpstNode->s_pszKey = pszFind;
	//如果为 <!-- *** -->
	if (::_tcsnicmp(pszFind + 1, _T("--"), 2) == 0)
	{
		//跳过注释标记“头”，开始查找。
		pszFind += 3;
		//查找到注释结尾，并给结尾加“\0”。
		while (::_tcsnicmp(pszFind, _T("-->"), 3) != 0)
		{
			//下一个字符
			pszFind++;
		}
		//不是“\0”
		if (*pszFind != _T('\0'))
		{
			//把“>”置换为“\0”,做为注释结尾
			*(pszFind + 2) = _T('\0');
			//指向新的节点或内容。
			pszFind += 3;
		}
 
	}
	//否则为 <! *** >
	else
	{
		//查找到注释结尾，并给结尾加“\0”。
		while (*pszFind != _T('\0') && *pszFind != _T('>'))
		{
			//下一个字符
			pszFind++;
		}
		//不能是“\0”
		if (*pszFind != _T('\0'))
		{
			//把“>”置换为“\0”,做为注释结尾。
			*pszFind = _T('\0');
			//指向新的节点或内容。
			pszFind++;
		}
	}
 
	//找到一个“<”
	while (*pszFind != _T('\0') && *pszFind != _T('<'))
	{
		//下一个字符
		pszFind++;
	}
 
	return pszFind;
}
LPTSTR CHtmlObject::InnerSplitTag(CHtmlObject::tagNode * lpstNode, LPTSTR lpszTagString)
{
	LPTSTR pszFind = lpszTagString;
 
	//指向开头(已经跳过“<”字符)
	lpstNode->s_pszKey = pszFind;
	//查找tag结尾，并给结尾加“\0”。
	while (*pszFind != _T('\0') && *pszFind != _T('>') && !CHtmlObject::IsSpace(*pszFind))
	{
		//下一个字符
		pszFind++;
	}
 
	//不是“\0”
	if (*pszFind != _T('\0'))
	{
		if (*pszFind == _T('>'))
		{
			//把“>”置换为“\0”,做为注释结尾。
			*pszFind = _T('\0');
			//指向新的节点或内容。
			pszFind++;
			//此tag没有属性,什么也不做了。
 
		}
		else
		{
			//把“space,\r,\n,\t ”置换为“\0”,做为注释结尾。
			*pszFind = _T('\0');
			//指向新的节点或内容。
			pszFind++;
 
			//如果不是结束标记，表示此tag有“属性”还需要解析“属性”。
			if (*lpstNode->s_pszKey != _T('/'))
			{
				//跳过所有“空格”,找到第一个属性。
				while (*pszFind != _T('\0') && CHtmlObject::IsSpace(*pszFind))
				{
					//下一个字符
					pszFind++;
				}
				//循环分析“属性”。
				while (*pszFind != _T('\0') && *pszFind != _T('<') && *pszFind != _T('>'))
				{
					//例：
					// key="value" key=value
					//跳过空格
					while (*pszFind != _T('\0') && CHtmlObject::IsSpace(*pszFind))
					{
						//下一个字符
						pszFind++;
					}
 
					//不是“\0”
					if (*pszFind != _T('\0'))
					{
						//申请一个点节。
						tagNode *pstAttributeNode = InnerAllocNode();
						//指向“属性”Key。
						pstAttributeNode->s_pszKey = pszFind;
 
						//查找key的末尾.
						while (*pszFind != _T('\0') && *pszFind != _T('=') && *pszFind != _T('>'))
						{
							//下一个字符
							pszFind++;
						}
						//不是“\0”
						if (*pszFind != _T('\0'))
						{
							if (*pszFind == _T('>'))
							{
								//把“>”置换为“\0”,做为结尾。
								*pszFind = _T('\0');
								//指向新的节点或内容。
								pszFind++;
								//链接到“链表”（右）。
								InnerLinkRightNode(lpstNode, pstAttributeNode);
								//已经碰到“>”,需要跳出。
								break;
							}
							else
							{
								//把“=”置换为“\0”,做为结尾。
								*pszFind = _T('\0');
								//指向新的节点或内容。
								pszFind++;
 
								//不是“\0”
								if (*pszFind != _T('\0'))
								{
									if (*pszFind == _T('"'))
									{
										//跳过“"”
										pszFind++;
										//指向“属性”key的Value。
										pstAttributeNode->s_pszValue = pszFind;
 
										//查找Value的末尾.
										while (*pszFind != _T('\0') && *pszFind != _T('\"') && *pszFind != _T('>'))
										{
											//下一个字符
											pszFind++;
										}
										//不是“\0”
										if (*pszFind != _T('\0'))
										{
											//把“",> ”置换为“\0”,做为结尾。
											*pszFind = _T('\0');
											//指向新的节点或内容。
											pszFind++;
										}
									}
									else if (*pszFind == _T('\''))
									{
										//跳过“'”
										pszFind++;
										//指向“属性”key的Value。
										pstAttributeNode->s_pszValue = pszFind;
 
										//查找Value的末尾.
										while (*pszFind != _T('\0') && *pszFind != _T('\'') && *pszFind != _T('>'))
										{
											//下一个字符
											pszFind++;
										}
										//不是“\0”
										if (*pszFind != _T('\0'))
										{
											//把“",<space> ”置换为“\0”,做为结尾。
											*pszFind = _T('\0');
											//指向新的节点或内容。
											pszFind++;
										}
									}
									else
									{
										//指向“属性”key的Value。
										pstAttributeNode->s_pszValue = pszFind;
										//查找Value的末尾.
										while (*pszFind != _T('\0') && *pszFind != _T(' ') && *pszFind != _T('>'))
										{
											//下一个字符
											pszFind++;
										}
										//不是“\0”
										if (*pszFind != _T('\0'))
										{
											//把“ ”置换为“\0”,做为结尾。
											*pszFind = _T('\0');
											//指向新的节点或内容。
											pszFind++;
										}
									}
 
								}
							}
 
						}
 
						//链接到“链表”（右）。
						InnerLinkRightNode(lpstNode, pstAttributeNode);
					}
				}
 
				//跳过这个无用的字符。
				if (*pszFind == _T('>'))
				{
					//指向新的节点或内容。
					pszFind++;
				}
			}
		}
	}
 
	return pszFind;
}
LPTSTR CHtmlObject::InnerSplitContent(CHtmlObject::tagNode * lpstNode, LPTSTR lpszTagString)
{
	LPTSTR pszFind = lpszTagString;
 
	if (::_tcsnicmp(lpstNode->s_pszKey, _T("script"), 6) == 0)
	{
		pszFind = InnerSplitScript(lpstNode, pszFind);
	}
	else if (::_tcsnicmp(lpstNode->s_pszKey, _T("style"), 5) == 0)
	{
		pszFind = InnerSplitStyle(lpstNode, pszFind);
	}
	else
	{
		pszFind = InnerSplitText(lpstNode, pszFind);
	}
 
	return pszFind;
}
LPTSTR CHtmlObject::InnerSplitText(CHtmlObject::tagNode * lpstNode, LPTSTR lpszTagString)
{
	LPTSTR pszFind = lpszTagString;
 
	//跳过所有“空格”
	while (*pszFind != _T('\0') && CHtmlObject::IsSpace(*pszFind))
	{
		//下一个字符
		pszFind++;
	}
 
	//如果 _T('<') 表示没有文本。
	if (*pszFind != _T('<'))
	{
		//指向可见文本。
		lpstNode->s_pszValue = pszFind;
		//查找文本结尾。
		while (*pszFind != _T('\0') && *pszFind != _T('<') && !CHtmlObject::IsSpace(*pszFind))
		{
			//下一个字符
			pszFind++;
		}
		//不是“\0”
		if (*pszFind != _T('\0'))
		{
			if (*pszFind == _T('<'))
			{
				//把“<”置换为“\0”,做为结尾。
				*pszFind = _T('\0');
				//指向新的节点或内容。
				pszFind++;
			}
			else
			{
				//把“space,\r,\n,\t,”置换为“\0”,做为结尾。
				*pszFind = _T('\0');
				//指向新的节点或内容。
				pszFind++;
 
				//找到一个“<”
				while (*pszFind != _T('\0') && *pszFind != _T('<'))
				{
					//下一个字符
					pszFind++;
				}
			}
		}
	}
 
	return pszFind;
}
LPTSTR CHtmlObject::InnerSplitScript(tagNode * lpstNode, LPTSTR lpszTagString)
{
	LPTSTR pszFind = lpszTagString;
 
 
#define  SCRIPT_MARK_MAX			1024
	UINT nMarkIndex = 0;
	TCHAR szMark[SCRIPT_MARK_MAX] = { _T('\0') }; //max 1024
 
	//跳过所有“空格”
	while (*pszFind != _T('\0') && CHtmlObject::IsSpace(*pszFind))
	{
		//下一个字符
		pszFind++;
	}
 
	if (*pszFind != _T('\0') && *pszFind != _T('<'))
	{
		//指向可见文本。
		lpstNode->s_pszValue = pszFind;
 
		while (*pszFind != _T('\0'))
		{
			//如果字符被“'，"”包围则为字符串，这期间不计算注释。
			if (szMark[nMarkIndex] != _T('\'') && szMark[nMarkIndex] != _T('\"'))
			{
				//如果是// abc 则跳过。
				if (::_tcsnicmp(pszFind, _T("//"), 2) == 0)
				{
					//跳过注释“头”。
					pszFind += 2;
					//查找注释“尾”。
					while (*pszFind != _T('\0') && *pszFind != _T('\n'))
					{
						pszFind++;
					}
					//跳过注释“尾”。
					if (*pszFind != _T('\0'))
						pszFind++;
 
				}
				//如果是/* abc */则跳过。
				else if (::_tcsnicmp(pszFind, _T("/*"), 2) == 0)
				{
					//跳过注释“头”。
					pszFind += 2;
					//查找注释“尾”。
					while (::_tcsnicmp(pszFind, _T("*/"), 2) != 0)
					{
						pszFind++;
					}
					//跳过注释“尾”。
					if (*pszFind != _T('\0'))
						pszFind += 2;
				}
 
			}
 
			if (*pszFind == _T('\\') &&
				(*(pszFind + 1) == _T('\\') ||
				*(pszFind + 1) == _T('(') || *(pszFind + 1) == _T(')') ||
				*(pszFind + 1) == _T('[') || *(pszFind + 1) == _T(']') ||
				*(pszFind + 1) == _T('{') || *(pszFind + 1) == _T('}') ||
				*(pszFind + 1) == _T('\'') ||
				*(pszFind + 1) == _T('\"')))
			{
				//转意字符
				pszFind += 2;
 
			}
			else if (*pszFind == _T('{') || *pszFind == _T('(') || *pszFind == _T('[') || (*pszFind == _T('\'') || *pszFind == _T('\"')))
			{
				if (szMark[nMarkIndex] != _T('\'') && szMark[nMarkIndex] != _T('\"'))
				{
					if (nMarkIndex < SCRIPT_MARK_MAX)
					{
						if (nMarkIndex == 0 && szMark[nMarkIndex] == _T('\0'))
							szMark[nMarkIndex] = *pszFind;
						else
							szMark[++nMarkIndex] = *pszFind;
					}
				}
				else if (szMark[nMarkIndex] == *pszFind)
				{
					if (nMarkIndex >0)
						szMark[nMarkIndex--] = _T('\0');
					else
						szMark[nMarkIndex] = _T('\0');
				}
				pszFind++;
 
			}
			else if (*pszFind == _T('}'))
			{
				if (szMark[nMarkIndex] == _T('{'))
				{
					if (nMarkIndex >0)
						szMark[nMarkIndex--] = _T('\0');
					else
						szMark[nMarkIndex] = _T('\0');
				}
				pszFind++;
			}
			else if (*pszFind == _T(')'))
			{
				if (szMark[nMarkIndex] == _T('('))
				{
					if (nMarkIndex >0)
						szMark[nMarkIndex--] = _T('\0');
					else
						szMark[nMarkIndex] = _T('\0');
				}
				pszFind++;
			}
			else if (*pszFind == _T(']'))
			{
				if (szMark[nMarkIndex] == _T('['))
				{
					if (nMarkIndex >0)
						szMark[nMarkIndex--] = _T('\0');
					else
						szMark[nMarkIndex] = _T('\0');
				}
				pszFind++;
			}
			else if (*pszFind == _T('<') && szMark[0] == _T('\0'))  //nMarkIndex == 0 &&
			{
				//把“<”置换为“\0”,做为结尾。
				*pszFind = _T('\0');
				//指向新的节点或内容。
				pszFind++;
				break;
			}
			else
			{
				pszFind++;
			}
		}
	}
 
	return pszFind;
}
LPTSTR CHtmlObject::InnerSplitStyle(CHtmlObject::tagNode * lpstNode, LPTSTR lpszTagString)
{
	LPTSTR pszFind = lpszTagString;
 
#define  STYLE_MARK_MAX			1024
	UINT nMarkIndex = 0;
	TCHAR szMark[STYLE_MARK_MAX] = { _T('\0') }; //max 1024
 
	//跳过所有“空格”
	while (*pszFind != _T('\0') && CHtmlObject::IsSpace(*pszFind))
	{
		//下一个字符
		pszFind++;
	}
 
	if (*pszFind != _T('\0') && *pszFind != _T('<'))
	{
		//指向可见文本。
		lpstNode->s_pszValue = pszFind;
 
		while (*pszFind != _T('\0'))
		{
			//如果字符被“(，'，"”包围则为字符串，这期间不计算注释。
			if (szMark[nMarkIndex] != _T('(') && szMark[nMarkIndex] != _T('\'') && szMark[nMarkIndex] != _T('\"'))
			{
				//如果是/* abc */则跳过。
				if (::_tcsnicmp(pszFind, _T("/*"), 2) == 0)
				{
					//跳过注释“头”，查找注释“尾”。
					pszFind += 2;
					while (::_tcsnicmp(pszFind, _T("*/"), 2) != 0)
					{
						pszFind++;
					}
					//跳过注释“尾”。
					if (*pszFind != _T('\0'))
						pszFind += 2;
				}
			}
 
 
			if (*pszFind == _T('{') || *pszFind == _T('(') || *pszFind == _T('[') || (*pszFind == _T('\'') || *pszFind == _T('\"')))
			{
				if (szMark[nMarkIndex] != _T('\'') && szMark[nMarkIndex] != _T('\"'))
				{
					if (nMarkIndex < STYLE_MARK_MAX)
					{
						if (nMarkIndex == 0 && szMark[nMarkIndex] == _T('\0'))
							szMark[nMarkIndex] = *pszFind;
						else
							szMark[++nMarkIndex] = *pszFind;
					}
				}
				else if (szMark[nMarkIndex] == *pszFind)
				{
					if (nMarkIndex >0)
						szMark[nMarkIndex--] = _T('\0');
					else
						szMark[nMarkIndex] = _T('\0');
				}
				pszFind++;
 
			}
			else if (*pszFind == _T('}'))
			{
				if (szMark[nMarkIndex] == _T('{'))
				{
					if (nMarkIndex >0)
						szMark[nMarkIndex--] = _T('\0');
					else
						szMark[nMarkIndex] = _T('\0');
				}
				pszFind++;
			}
			else if (*pszFind == _T(')'))
			{
				if (szMark[nMarkIndex] == _T('('))
				{
					if (nMarkIndex >0)
						szMark[nMarkIndex--] = _T('\0');
					else
						szMark[nMarkIndex] = _T('\0');
				}
				pszFind++;
			}
			else if (*pszFind == _T(']'))
			{
				if (szMark[nMarkIndex] == _T('['))
				{
					if (nMarkIndex >0)
						szMark[nMarkIndex--] = _T('\0');
					else
						szMark[nMarkIndex] = _T('\0');
				}
				pszFind++;
			}
			else if (*pszFind == _T('<') && szMark[0] == _T('\0'))  //nMarkIndex == 0 &&
			{
				//把“<”置换为“\0”,做为结尾。
				*pszFind = _T('\0');
				//指向新的节点或内容。
				pszFind++;
				break;
			}
			else
			{
				pszFind++;
			}
		}
 
	}
 
	return pszFind;
}
 
//////////////////////////////////////////////////////////////////////////////////////////CHtmlObject.cpp//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////CHtmlHelper.h//////////////////////////////////////////////////////////////////////////
 
#ifndef __JESONYANG_HTMLHELPER_H__
#define __JESONYANG_HTMLHELPER_H__
 
/*****************************************************************************************************************
created: 2011/12/03
author: JesonYang
blog: http://blog.csdn.net/yc7369
*****************************************************************************************************************/
 
#include "HtmlObject.h"
 
class CHtmlHelper :public CHtmlObject
{
public:
	CHtmlHelper(void);
	virtual ~CHtmlHelper(void);
public:
	//
	LPCTSTR GetFirstLink();
	LPCTSTR GetNextLink();
	LPCTSTR GetFirstContent();
	LPCTSTR GetNextContent();
	LPCTSTR	SearchText(LPCTSTR lpszText);
protected:
	//
	CHtmlObject::tagNode * m_pstCur;
};
 
#endif
 
 
//////////////////////////////////////////////////////////////////////////////////////////CHtmlHelper.h//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////CHtmlHelper.cpp//////////////////////////////////////////////////////////////////////////
 
#pragma once
 
/*****************************************************************************************************************
created: 2011/12/03
author: JesonYang
blog: http://blog.csdn.net/yc7369
*****************************************************************************************************************/
 
 
#include "HtmlHelper.h"
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#pragma warning(disable: 4996) 
 
CHtmlHelper::CHtmlHelper()
{
 
}
CHtmlHelper::~CHtmlHelper()
{
 
}
//
LPCTSTR CHtmlHelper::GetFirstLink()
{
	LPCTSTR pszResult = NULL;
 
	m_pstCur = m_pstHead;
 
	while (m_pstCur && !pszResult)
	{
		if (0 != ::_tcsnicmp(m_pstCur->s_pszKey, _T("script"), 6) &&
			0 != ::_tcsnicmp(m_pstCur->s_pszKey, _T("style"), 5))
		{
			CHtmlObject::tagNode * pstAttributeCur = m_pstCur->s_pstRight;
			while (pstAttributeCur)
			{
				if (0 == ::_tcsnicmp(pstAttributeCur->s_pszKey, _T("href"), 4) ||
					0 == ::_tcsnicmp(pstAttributeCur->s_pszKey, _T("src"), 3))
				{
					//return
					pszResult = pstAttributeCur->s_pszValue;
					break;
				}
				else
				{
					pstAttributeCur = pstAttributeCur->s_pstRight;
				}
			}
		}
		m_pstCur = m_pstCur->s_pstNext;
	}
 
	return pszResult;
}
 
LPCTSTR CHtmlHelper::GetNextLink()
{
	LPCTSTR pszResult = NULL;
 
	while (m_pstCur && !pszResult)
	{
		if (0 != ::_tcsnicmp(m_pstCur->s_pszKey, _T("script"), 6) &&
			0 != ::_tcsnicmp(m_pstCur->s_pszKey, _T("style"), 5))
		{
			CHtmlObject::tagNode * pstAttributeCur = m_pstCur->s_pstRight;
			while (pstAttributeCur)
			{
				if (0 == ::_tcsnicmp(pstAttributeCur->s_pszKey, _T("href"), 4) ||
					0 == ::_tcsnicmp(pstAttributeCur->s_pszKey, _T("src"), 3))
				{
					//return
					pszResult = pstAttributeCur->s_pszValue;
					break;
				}
				else
				{
					pstAttributeCur = pstAttributeCur->s_pstRight;
				}
			}
		}
 
		m_pstCur = m_pstCur->s_pstNext;
	}
 
	return pszResult;
}
 
LPCTSTR CHtmlHelper::GetFirstContent()
{
	LPCTSTR pszResult = NULL;
 
	m_pstCur = m_pstHead;
 
	while (m_pstCur && !pszResult)
	{
		if (0 != ::_tcsnicmp(m_pstCur->s_pszKey, _T("script"), 6) &&
			0 != ::_tcsnicmp(m_pstCur->s_pszKey, _T("style"), 5))
		{
			if (m_pstCur->s_pszValue)
				pszResult = m_pstCur->s_pszValue;
		}
 
		m_pstCur = m_pstCur->s_pstNext;
	}
 
	return pszResult;
}
LPCTSTR CHtmlHelper::GetNextContent()
{
	LPCTSTR pszResult = NULL;
 
	while (m_pstCur && !pszResult)
	{
		if (0 != ::_tcsnicmp(m_pstCur->s_pszKey, _T("script"), 6) &&
			0 != ::_tcsnicmp(m_pstCur->s_pszKey, _T("style"), 5))
		{
			if (m_pstCur->s_pszValue)
				pszResult = m_pstCur->s_pszValue;
		}
 
		m_pstCur = m_pstCur->s_pstNext;
	}
 
	return pszResult;
}
//
LPCTSTR CHtmlHelper::SearchText(LPCTSTR lpszText)
{
	LPCTSTR pszResult = NULL;
 
	CHtmlObject::tagNode *pstCur = m_pstHead;
 
	while (pstCur && !pszResult)
	{
		if (0 != ::_tcsnicmp(pstCur->s_pszKey, _T("script"), 6) &&
			0 != ::_tcsnicmp(pstCur->s_pszKey, _T("style"), 5))
		{
			if (pstCur->s_pszValue)
			{
				if ((NULL != ::StrStrI(pstCur->s_pszValue, lpszText)))
					pszResult = pstCur->s_pszValue;
			}
		}
 
		pstCur = pstCur->s_pstNext;
	}
 
	return pszResult;
}
 
 
 