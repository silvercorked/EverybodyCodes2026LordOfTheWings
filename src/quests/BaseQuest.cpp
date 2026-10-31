
module BaseQuest;

ParsedQuestStrings::ParsedQuestStrings(u32 year, u32 quest) : _parsed1{}, _parsed2{}, _parsed3{} {
	auto p1 = FileReadUtils::readProblemFile(year, quest, 1);
	auto p2 = FileReadUtils::readProblemFile(year, quest, 2);
	auto p3 = FileReadUtils::readProblemFile(year, quest, 3);

	if (p1.has_value()) {
		this->_parsed1 = p1.value();
	}
	if (p2.has_value()) {
		this->_parsed2 = p2.value();
	}
	if (p3.has_value()) {
		this->_parsed3 = p3.value();
	}
}
