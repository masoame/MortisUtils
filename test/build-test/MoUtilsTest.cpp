#include <utils.hpp>
#include <catch2/catch_test_macros.hpp>

#include<iostream>

TEST_CASE("Async Function","[Mo::Thr]")
{
	constexpr auto test_cout = 100000;
	constexpr auto run_cout = 10;

	REQUIRE([]()-> std::uint64_t {
		std::atomic_uint64_t count = 0;
		auto task = [&count] {
			for (int i = 0;i!= test_cout; ++i) {
				++count;
			}
		};
		for(int i = 0; i != run_cout; ++i) {
			Mo::Thr::Async(task).wait();
		}
		return count;
	}() == (test_cout * run_cout));

	REQUIRE([]()-> std::uint64_t {
		std::atomic_uint64_t count = 0;
		auto task = [&count] {
			for (int i = 0;i!= test_cout; ++i) {
				++count;
			}
		};
		auto funtureArr = Mo::Thr::Async(run_cout, task);
		for (auto& fu : funtureArr) {
			fu.wait();
		}
		return count;
	}() == (test_cout * run_cout));
}

TEST_CASE("Async Read Write", "[Mo::Bounded_queue]")
{
	using namespace std::chrono_literals;
	Mo::bounded_queue<int> bq(2000);

	REQUIRE([](Mo::bounded_queue<int>& bq)->bool {
		constexpr auto produce_count = 10000;
		constexpr auto consume_count = 10000;
		auto producer = [&bq]() {
			for (int i = 0; i != produce_count; ++i) {
				bq.push(i);
			}
			return true;
		};
		auto consumer = [&bq]() -> bool {
			for (int i = 0; i != consume_count; ++i) {
				auto val = bq.pop_for(500ms);
				if (val.has_value() == false) {
					return false;
				}
			}
			return true;
		};
		auto prod_future = Mo::Thr::Async(producer);
		auto cons_future = Mo::Thr::Async(consumer);

		return prod_future.get() && cons_future.get();
	}(bq) == true);

}