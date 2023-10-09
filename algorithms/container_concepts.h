#pragma once

namespace wmv {
	template<typename T, typename U>
	concept is_empty_pushable = requires(T& t)
			{
				t.push_back({});
			};

	template<typename T, typename U>
	concept is_pushable = requires(T& t, const U& u)
	{
		t.push_back(u);
	};

	template<typename T>
	concept is_popable = requires(T & t)
	{
		t.pop_back();
	};
}