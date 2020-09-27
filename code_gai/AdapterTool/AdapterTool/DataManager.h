#pragma once

#include <queue>
//#include <mutex>
#include <boost/thread/mutex.hpp>
//#include <shared_mutex>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>


#include "Define.h"
#include "Single.h"


#define QueueData_DDS() CDataManager::DDSQueueData::Instance()
#define QueueData_TCP() CDataManager::TCPQueueData::Instance()
#define FileTransfer() CDataManager::DMFileLoadTransfer::Instance()
#define SceneResolution() CDataManager::DMSceneResolution::Instance()

namespace CDataManager
{

	////////////////////////////////////////////////////
	/// <summary>    </summary>
	///  //映射文件表、参数模型文件、信号波形文件
	/// <remarks>   吴俊霖  </remarks>
	////////////////////////////////////////////////////

	class DMFileLoadTransfer :public SingleInstance<DMFileLoadTransfer>
	{
		DECLARE_SINGLETON(DMFileLoadTransfer);

	public:

		bool Initialize();
		void TransferScenaioFile(std::string ScnFile);
		void TransferRadarFile(std::string RadarFile);
		void TransferMapFile(std::string MapFile);

		bool CheckInfos();
		bool checkRadarEntity();
		bool checkTargetEntity();

		const LVCScenarioFile & GetScenarioInfo() const;
		const RadarInfo & GetRadarsInfo() const;
		const LVCEntityMapInfoVec & GetMapInfo() const;

		//从想定实体列表中 获取雷达实体
		bool GetRadarEntity(LVCEntityInfo & EntityInfo);
		bool GetTargetEntity(std::vector<LVCEntityInfo> & EntityInfoList);

		int GetModeID();
		int GetStartTM();
	private:
		LVCScenarioFile _scn;
		RadarInfo _radar;
		LVCEntityMapInfoVec _entityMap;

		LVCEntityInfo _RadarEntity;
		std::vector<LVCEntityInfo> _TargetList;

		int _ModeID;
		int _startTM;
	};

	////////////////////////////////////////////////////
	/// <summary>    </summary>
	///  //映射文件表、每节拍的仿真实体数据、预位值
	/// <remarks>   吴俊霖  </remarks>
	////////////////////////////////////////////////////

	class DMSceneResolution :public SingleInstance<DMSceneResolution>
	{
		DECLARE_SINGLETON(DMSceneResolution);

	public:
// 		void AssignData(const SysMotionUpdate& Data);
// 		const SysMotionUpdate& GetData();
		const double GetAlphaValue() const;
		void SetAlphaValue(double Alpha);


	public:
		void SetData(const TPC_ScnPlatUpdate& plat);
		const TPC_ScnPlatUpdate GetData();
		const TPC_ScnPlatUpdate GetData_forLook();

		bool tryGetData();

		void ReleaseCmd(int no = 1);
		void WaitCmd(int ns = 0);
	private:
		std::queue<TPC_ScnPlatUpdate> _Queue;
		boost::mutex _mutex;
		typedef boost::unique_lock<boost::mutex> _tlock;

		boost::interprocess::interprocess_semaphore *_UpdataSemaphore;

		//SysMotionUpdate _data;
		//伺服角度
		double _alpha;
	};

	////////////////////////////////////////////////////
	/// <summary>    </summary>
	/// //dds域值，tcp 
	/// <remarks>   吴俊霖  </remarks>
	////////////////////////////////////////////////////
	
	class DMNetworkInfo :public SingleInstance<DMNetworkInfo>
	{
		DECLARE_SINGLETON(DMNetworkInfo);

	};

	////////////////////////////////////////////////////
	/// <summary>    </summary>
	///  网络数据中间交互层，
	/// <remarks>   吴俊霖  </remarks>
	////////////////////////////////////////////////////

	class DDSQueueData :public SingleInstance<DDSQueueData>
	{
		DECLARE_SINGLETON(DDSQueueData);

	public:
		bool Initialize();

		void Stop();

		void SetData(const BaseTypePtr Base);
		const BaseTypePtr GetData();

		void ReleaseCmd(int no = 1);
		void WaitCmd(int ns = 0);

	public:
		//发送和接收 超时，共用信号量判断
		boost::interprocess::interprocess_semaphore * GetRdyRequestSemaphore();
		bool WaitRdyRequest(int times);
		void ReleaseRdyRequest();
		int GetTPC_SysRdyNotify_tcpfunc_rs();
		void SetTPC_SysRdyNotify_tcpfunc_rs(int rs);
	private:

		/// <summary>	强制释放信号量. </summary> wujl 
		void ReleaseSpForce();
	private:
		std::queue<BaseTypePtr> _Queue;
		boost::mutex _ddsmutex;
		//HANDLE _CmdSemaphore;
		//HANDLE _DataSemaphore;
		boost::interprocess::interprocess_semaphore *_CmdSemaphore;
		/*std::unique_lock<std::shared_mutex> _unique_lock;
		std::shared_lock<std::shared_mutex> _shared_lock;*/
		bool _ReleaseForce;

		boost::interprocess::interprocess_semaphore *_RdyRequestSemaphore;
		bool _rdyRequestbackFlag;
		int TPC_SysRdyNotify_tcpfunc_rs;
	};


	////////////////////////////////////////////////////
	/// <summary>  TCP交互数据  </summary>
	///  
	/// <remarks>   吴俊霖  </remarks>
	////////////////////////////////////////////////////

	class TCPQueueData :public SingleInstance<TCPQueueData>
	{
		DECLARE_SINGLETON(TCPQueueData);

	public:
		void SetData(const buffer_type& Buffer);
		const buffer_type GetData();

		void ReleaseCmd(int no = 1);
		void WaitCmd(int ns = 0);

		//波形捷变状态
		void SetAgilityType(int RadarID,int state);
		int GetAgilityType(int RadarID);
		//非捷变下的 频点值
		void SetBeamValue(int RadarID,int value);
		int GetBeamValue(int RadarID);
	private:
		std::queue<buffer_type> _Queue;
		std::map<int, int> _AgilityMap;
		std::map<int, int> _BeamValueMap;
		boost::mutex _tcpmutex;
		typedef boost::unique_lock<boost::mutex> _tcplock;

		boost::interprocess::interprocess_semaphore *_TCPSemaphore;
	};

};

