//
// Created by codegen
//

#include <utility>
#include <unordered_map>
#include <functional>
#include "unit.h"
#include "damage.h"
#include "recovery.h"

namespace GeneratedCard {

    inline std::shared_ptr<Core::Unit> MakeUnit() {
        return std::make_shared<Core::Unit>();
    }

    inline std::shared_ptr<Core::Damage> MakeDamage() {
        return std::make_shared<Core::Damage>();
    }

    inline std::shared_ptr<Core::Recovery> MakeRecovery() {
        return std::make_shared<Core::Recovery>();
    }

    extern std::unordered_map<int32_t, std::function<std::shared_ptr<Core::Card>()>> HashTable;
}
