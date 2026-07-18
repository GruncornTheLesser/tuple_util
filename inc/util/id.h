#pragma once
#include <cstdint>
#include "type_name.h"


namespace TUPLE_UTIL_NAMESPACE {
	struct id {
		template<typename> friend struct std::hash;
		static consteval std::size_t fx_hash(const std::string_view str) { 
			static constexpr std::size_t ROTATE = 5;
			static constexpr std::size_t SEED = sizeof(std::size_t) == 64 ? 0x517CC1b727220A95 : 0X9E3779B9;
		
			std::size_t count = str.size();
			std::size_t index = 0;

			std::size_t hash = 0;
			if constexpr (sizeof(std::size_t) == 64) {
				while (count >= 8) {
					alignas(uint64_t) char buffer[8];
					str.copy(buffer, 8, index);
					hash = (std::rotl(hash, ROTATE) ^ std::bit_cast<uint64_t>(buffer)) * SEED;
					count -= 8;
					index += 8;
				}

				if (count >= 4) {
					alignas(uint32_t) char buffer[4];
					str.copy(buffer, 4, index);
					hash = (std::rotl(hash, ROTATE) ^ std::bit_cast<uint32_t>(buffer)) * SEED;
					count -= 4;
					index += 4;
				}
			} else {
				while (count >= 4) {
					alignas(uint32_t) char buffer[4];
					str.copy(buffer, 4, index);
					hash = (std::rotl(hash, ROTATE) ^ std::bit_cast<uint32_t>(buffer)) * SEED;
					count -= 4;
					index += 4;
				}
			}

			if (count >= 2) {
				alignas(uint16_t) char buffer[2];
				str.copy(buffer, 2, index);
				hash = (std::rotl(hash, ROTATE) ^ std::bit_cast<uint16_t>(buffer)) * SEED;
				count -= 2;
				index += 2;
			}

			if (count == 1) {
				hash = (std::rotl(hash, ROTATE) ^ std::bit_cast<uint8_t>(str.back())) * SEED;
				count -= 1;
				index += 1;
			}
			
			return hash;
		}
	public:
		template<typename T>
		consteval id(std::type_identity<T> value) : hash(fx_hash(get_name<T>())) { }

		template<std::size_t N>
		consteval id(const char (&str)[N]) : hash(fx_hash(std::string_view{ str })) { }

		constexpr friend bool operator==(const id& lhs, const id& rhs) { return lhs.hash == rhs.hash; }
		constexpr friend bool operator!=(const id& lhs, const id& rhs) { return lhs.hash != rhs.hash; }

		constexpr friend bool operator<=(const id& lhs, const id& rhs) { return lhs.hash <= rhs.hash; }
		constexpr friend bool operator<(const id& lhs, const id& rhs) { return lhs.hash < rhs.hash; }

		constexpr friend bool operator>=(const id& lhs, const id& rhs) { return lhs.hash >= rhs.hash; }
		constexpr friend bool operator>(const id& lhs, const id& rhs) { return lhs.hash > rhs.hash; }

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