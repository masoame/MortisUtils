#pragma once
#include<Utils.hpp>
namespace Mortis
{
	/*
	* singletont_thread_pool用于实现一个单例线程池，支持线程安全的任务队列和线程管理。
	* 参考项目来源: https://github.com/progschj/ThreadPool
	* 适配C++20，并增加stop_source参数，用于控制线程池的关闭。
	* 使用std::jthread替代原来的std::thread，支持stop_token参数，用于控制线程的关闭。
	*/
	class BaseThreadPool {

	public:
		explicit BaseThreadPool(std::size_t threads = std::thread::hardware_concurrency());
		~BaseThreadPool();

		template<class F, class... Args>
			requires std::invocable<F, Args...>
		auto enqueue(F&& f, Args&&... args)
			-> std::future<typename std::invoke_result<F, Args...>::type>;

		template<class Task>
			requires BC::is_packaged_task_v<Task> && (not std::is_reference_v<Task>)
		auto enqueue(const std::shared_ptr<Task>& task);
	private:

		std::vector< std::jthread > workers{};
		std::queue< std::function<void()>> tasks{};
		std::mutex queue_mutex{};
		std::condition_variable condition{};
		std::stop_source stop{};
	};

	template<class Task>
		requires BC::is_packaged_task_v<Task> && (not std::is_reference_v<Task>)
	auto BaseThreadPool::enqueue(const std::shared_ptr<Task>& task)
	{
		auto res = task->get_future();
		{
			std::unique_lock lock(queue_mutex);
			if (stop.stop_requested()) {
				throw std::runtime_error("enqueue on stopped ThreadPool");
			}
			tasks.emplace([task]() { (*task)(); });
		}
		condition.notify_one();
		return res;
	}

	template<class F, class... Args>
		requires std::invocable<F, Args...>
	auto BaseThreadPool::enqueue(F&& f, Args&&... args)
		-> std::future<typename std::invoke_result<F, Args...>::type>
	{
		using return_type = typename std::invoke_result<F, Args...>::type;
		auto task = std::make_shared<std::packaged_task<return_type()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);
		return enqueue(task);
	}

	class SingletonThreadPool : public Singleton<SingletonThreadPool>, public BaseThreadPool
	{
		friend class Singleton<SingletonThreadPool>;
	protected:
		using BaseThreadPool::BaseThreadPool;
	};
	using STreadPool = SingletonThreadPool;

	namespace Thr
	{
		template<typename F, typename... Args>
			requires std::invocable<F, Args...>
		auto Async(F&& f, Args&& ...args) {
			return STreadPool::Instance().enqueue(std::forward<F>(f), std::forward<Args>(args)...);
		}

		template<typename F, typename... Args>
			requires std::invocable<F, Args...>
		auto Async(std::size_t taskCount,const F& f,const Args& ...args) {
			using return_type = typename std::invoke_result<F, Args...>::type;
			std::vector<std::future<return_type>> results;
			results.reserve(taskCount);
			for (int i = 0; i != taskCount; ++i) {
				results.push_back(STreadPool::Instance().enqueue(f, args...));
			}
			return results;
		}
	}
};
