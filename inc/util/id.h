#pragma once
#include <cstdint>
#include "type_name.h"

namespace TUPLE_UTIL_NAMESPACE {
	struct id {
		template<typename T>
		consteval id(std::type_identity<T> value) : id(type_name<T>()) { }
		consteval id(std::string_view str) : hash(0) {
			#ifdef UINT64_MAX
				static constexpr std::size_t ROTATE = 7;
				static constexpr std::size_t SEED = 0x517CC1B727220A95ULL;
			#elifdef UINT32_MAX
				static constexpr std::size_t ROTATE = 5;
				static constexpr std::size_t SEED = 0x9E3779B9UL;
			#else
				static constexpr std::size_t ROTATE = 3;
				static constexpr std::size_t SEED = 0x9E37U;
			#endif
			
			std::size_t count = str.size();
			std::size_t index = 0;
			
			auto consume = [&]<typename T>(std::type_identity<T>) {
				alignas(T) char buffer[sizeof(T)];
				str.copy(buffer, sizeof(T), index);
				hash = (std::rotl(hash, ROTATE) ^ std::bit_cast<T>(buffer)) * SEED;
				count -= sizeof(T);
				index += sizeof(T);
			};
			
			while (count >= sizeof(std::size_t)) {
				consume(std::type_identity<std::size_t>{});
			}
			
			#ifdef UINT64_MAX
				if constexpr (sizeof(std::size_t) > 8) if (count >= 4) {
					consume(std::type_identity<uint64_t>{});
				}
			#endif

			#ifdef UINT32_MAX
				if constexpr (sizeof(std::size_t) > 4) if (count >= 4) {
					consume(std::type_identity<uint32_t>{});
				}
			#endif
				
			#ifdef UINT16_MAX
				if constexpr (sizeof(std::size_t) > 2) if (count >= 2) {
					consume(std::type_identity<uint16_t>{});
				}
			#endif

			#ifdef UINT8_MAX
				if (count >= 1) {
					consume(std::type_identity<uint8_t>{});
				}
			#endif
		}

		constexpr friend bool operator==(const id& lhs, const id& rhs) { return lhs.hash == rhs.hash; }
		constexpr friend auto operator<=>(const id& lhs, const id& rhs) { return lhs.hash <=> rhs.hash; }
	
		std::size_t hash;
	};
}

namespace std {
	template<> 
	struct hash<TUPLE_UTIL_NAMESPACE::id> {
		constexpr hash() = default;
		constexpr std::size_t operator()(TUPLE_UTIL_NAMESPACE::id id) const {
			return id.hash;
		}
	};
}