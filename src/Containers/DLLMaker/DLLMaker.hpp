#include<utils.hpp>

namespace Mortis
{
	template<typename TDLLMaker>
	class BaseDLL : public Mortis::Singleton<TDLLMaker>
	{
		friend Mortis::Singleton<TDLLMaker>;
	protected:
		bool Initialize(const HMODULE& hModule, PCONTEXT pCtx) {
			return static_cast<TDLLMaker*>(this)->Initialize(hModule, pCtx);
		}
		bool Uninitialize(const HMODULE& hModule, PCONTEXT pCtx) {
			return static_cast<TDLLMaker*>(this)->Uninitialize(hModule, pCtx);
		}
		bool Listen_Thread_Create(const HMODULE& hModule) {
			return static_cast<TDLLMaker*>(this)->Listen_Thread_Create(hModule);
		}
		bool Listen_Thread_Destroy(const HMODULE& hModule) {
			return static_cast<TDLLMaker*>(this)->Listen_Thread_Destroy(hModule);
		}
	};
}

#define MAKE_DEFAULT_DLLMAKER \
	friend BOOL APIENTRY ::DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);

#define MAKE_EXTERN_DLL \
	extern "C" BOOL APIENTRY ::DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);

#define DEFAULT_MAKE_DLL(DLLClass) \
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) \
{\
	bool bRet = false;\
	switch (ul_reason_for_call)\
	{\
	case DLL_PROCESS_ATTACH:\
		bRet = DLLClass::Instance().Initialize(hModule,reinterpret_cast<PCONTEXT>(lpReserved));\
		break;\
	case DLL_THREAD_ATTACH:\
		bRet = DLLClass::Instance().Listen_Thread_Create(hModule);\
		break;\
	case DLL_THREAD_DETACH:\
		bRet = DLLClass::Instance().Listen_Thread_Destroy(hModule);\
		break;\
	case DLL_PROCESS_DETACH:\
		bRet = DLLClass::Instance().Uninitialize(hModule,reinterpret_cast<PCONTEXT>(lpReserved));\
		break;\
	}\
	return bRet;\
}