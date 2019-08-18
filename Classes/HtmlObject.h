//////////////////////////////////////////////////////////////////////////////////////////CHtmlObject.h//////////////////////////////////////////////////////////////////////////
 
#ifndef __JESONYANG_HTMLOBJECT_H__
#define __JESONYANG_HTMLOBJECT_H__

#include <windows.h>
#include <tchar.h>
class CHtmlObject
{
public:
	//
	static BOOL IsSpace(TCHAR tcLetter);
protected:
	struct tagNode
	{
		LPCTSTR s_pszKey;
		LPCTSTR s_pszValue;
		struct tagNode * s_pstRight; //attribute of tag
		struct tagNode * s_pstNext; //next tag
	};
public:
	CHtmlObject(void);
	virtual ~CHtmlObject(void);
	//
	enum { CHARSET_UTF8, CHARSET_UNICODE, CHARSET_MULTIBYTE }TextCharset;  //字符集类型
protected:
	//
	tagNode * InnerAllocNode();				                                //分配新的html节点
	void InnerFreeNode(tagNode * lpstNode);								    //删除html节点
	void InnerLinkNextNode(tagNode * lpstNode);                             //下一个html节点
	void InnerLinkRightNode(tagNode * lpstTagNode, tagNode * lpstNode);     //右边的节点
	void InnerCleanupNode();                                                //去除所有节点
	void InnerCleanupRightNode(tagNode * lpstNode);							//循环清除所有“属性”节点。
 
public:
	//
	void AutoTakeSnapshot(PBYTE lpszString, UINT nStringLen);  //根据数据头获取相应编码
	void TakeSnapshot(PBYTE lpszString, UINT nStringLen, UINT nFromCharset);
	void DeleteSnapshot();
	//
	void Parse();
private:
	//
	void InnerParse();
	LPTSTR InnerSplitComment(tagNode * lpstNode, LPTSTR lpszTagString);
	LPTSTR InnerSplitTag(tagNode * lpstNode, LPTSTR lpszTagString);
	LPTSTR InnerSplitContent(tagNode * lpstNode, LPTSTR lpszTagString);
	LPTSTR InnerSplitText(tagNode * lpstNode, LPTSTR lpszTagString);
	LPTSTR InnerSplitScript(tagNode * lpstNode, LPTSTR lpszTagString);
	LPTSTR InnerSplitStyle(tagNode * lpstNode, LPTSTR lpszTagString);
 
protected:
	//
	LPTSTR m_pszSnapshotBuffer;
	UINT m_nSnapshotBufferLen;
	UINT m_nSnapshotStringLen;
	//
	tagNode * m_pstHead;
	tagNode * m_pstTail;
 
};
#endif
