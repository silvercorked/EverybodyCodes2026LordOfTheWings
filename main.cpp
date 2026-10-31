
import Utils;
import BaseQuest;
import Quest1;
import Quest2;
import Quest3;

import <print>;

constexpr const u32 CurrentQuest = 3;
constexpr const bool WIP_MODE = true;

static constexpr auto shouldDisplay(const u32 questNumber) -> bool {
	return (WIP_MODE && CurrentQuest == questNumber) || (!WIP_MODE && questNumber <= CurrentQuest);
}

static constexpr auto printResults = []<typename ...ResultTypes>(const BaseQuest<ResultTypes...>& q) -> void {
	auto results = q.getSolutions();
	auto times = q.timeSolutions();
	std::println("out 1: {} | time: {}", times[0], std::get<0>(results));
	std::println("out 2: {} | time: {}", times[1], std::get<1>(results));
	std::println("out 3: {} | time: {}", times[2], std::get<2>(results));
};

template <u32 i>
static auto runEachQuest() -> void { return; }

template <u32 index, typename Head, typename ...Tail>
static auto runEachQuest() -> void {
	if constexpr (shouldDisplay(index)) {
		std::println("{}", typeid(Head).name());
		printResults(Head{});
	}
	runEachQuest<index + 1, Tail...>();
}

template <typename ...Quests>
static auto runQuests() -> void {
	runEachQuest<0, Quests...>();
}

auto main() -> int {
	runQuests<Quest1, Quest2, Quest3>();
}
