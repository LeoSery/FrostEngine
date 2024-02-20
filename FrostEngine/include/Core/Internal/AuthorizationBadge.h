#pragma once

namespace frost::core
{
	template<typename T>
	class AuthorizationBadge
	{
		friend T;
		AuthorizationBadge() {}
	};
}
