#ifndef COMMBASE_H
#define COMMBASE_H
#include <string>

typedef void (*pNetRunCallback)();
typedef unsigned int sender_handle;
typedef unsigned int receiver_handle;
#define ErrorHandle 0x90000000
#define __CommBase(c) private:	friend CommBase<c>;
#define defaultPartitiontName	"__BUILT-IN PARTITION__"
template<typename T> 
class CommBase 
{
public:
	static CommBase & GetInstance() 
	{  
		static T instance;    
		return instance;  
	}  
	static CommBase* GetInstancePtr() 
	{   
		return &GetInstance();  
	}  
	virtual sender_handle publish    (int dataSize,const char* tblname, const char* dbname) =0;
	virtual receiver_handle subscribe  (int dataSize,const char* tblname, const char* dbname) =0;
	virtual bool sendData   (int index, const void* data,const char* topicName,const char* partitiontName){ return false;};
	virtual bool sendData   (int index, sender_handle hand, const void* data){ return false;};
	virtual int  recvData   (int& id,char* data,const char* topicName,const char* partitiontName){ return 0;};//return recived data bytes ret=0:NOData;ret<0:error)
	virtual inline const char* getLastError(){ return NULL;};
protected:
	CommBase(){};
	virtual ~CommBase(){};
private:
	CommBase(const CommBase &){};  
	CommBase& operator = (const CommBase &);  
};

//interface function
#ifndef _DDSLIB
	typedef bool	(*dds_publish)(int, const char*, const char* );   
	dds_publish	    publish;
	typedef bool	(*dds_subscribe)(int, const char*, const char*); 
	dds_subscribe   subscribe;
	typedef bool	(*dds_sendData)(int, char*, const char*, const char*); 
	dds_sendData    sendData;
	typedef bool	(*dds_recvData)(int&,char*,const char*,const char*); 
	dds_recvData    recvData;
	typedef char*	(*dds_getLastError)(); 
	dds_getLastError    getLastError;
#endif
////
//function call macros
#ifdef _DEBUG
#define DDSDLL "ddslibd.dll"
#else
#define DDSDLL "ddslib.dll"
#endif

#define FunDef(s)\
	s=(dds_##s)GetProcAddress(hinst, #s);

#define InitDDS()\
	HINSTANCE hinst = LoadLibraryA(DDSDLL);\
	FunDef(publish)\
	FunDef(subscribe)\
	FunDef(sendData)\
	FunDef(recvData)\
	FunDef(getLastError)\

////
#endif // COMMBASE_H
