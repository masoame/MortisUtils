#include<utils.hpp>

namespace Mortis
{
	template<typename TDLLMaker>
	class BaseDLL : public Mortis::Singleton<TDLLMaker>
	{
		friend Mortis::Singleton<TDLLMaker>;
	public:
		bool bRet = true;
	protected:

		void Initialize(const HMODULE& hModule, PCONTEXT pCtx) {
			bRet = static_cast<TDLLMaker*>(this)->Initialize(hModule, pCtx);
		}
		void Uninitialize(const HMODULE& hModule, PCONTEXT pCtx) {
			bRet = static_cast<TDLLMaker*>(this)->Uninitialize(hModule, pCtx);
		}
		void Listen_Thread_Create(const HMODULE& hModule) {
			bRet = static_cast<TDLLMaker*>(this)->Listen_Thread_Create(hModule);
		}
		void Listen_Thread_Destroy(const HMODULE& hModule) {
			bRet = static_cast<TDLLMaker*>(this)->Listen_Thread_Destroy(hModule);
		}
	};
}

#define DEFAULT_MAKE_DLL(DLLClass) \
using namespace Mortis; \
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) \
{\
	using namespace Mortis;\
	switch (ul_reason_for_call)\
	{\
	case DLL_PROCESS_ATTACH:\
		DLLClass::Instance().Initialize(hModule,reinterpret_cast<PCONTEXT>(lpReserved));\
		break;\
	case DLL_THREAD_ATTACH:\
		DLLClass::Instance().Listen_Thread_Create(hModule);\
		break;\
	case DLL_THREAD_DETACH:\
		DLLClass::Instance().Listen_Thread_Destroy(hModule);\
		break;\
	case DLL_PROCESS_DETACH:\
		DLLClass::Instance().Uninitialize(hModule,reinterpret_cast<PCONTEXT>(lpReserved));\
		break;\
	}\
	return static_cast<BOOL>(DLLClass::Instance().bRet);\
}