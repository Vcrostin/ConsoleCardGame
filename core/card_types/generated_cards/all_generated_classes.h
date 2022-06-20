//
// Created by codegen
//

#include <utility>
#include "unit.h"
#include "damage.h"
#include "recovery.h"

namespace GeneratedCard {

    inline std::shared_ptr<Core::Unit> MakeUnit() {
        return std::shared_ptr<Core::Unit>{new Core::Unit()};
    }

    inline std::shared_ptr<Core::Damage> MakeDamage() {
        return std::shared_ptr<Core::Damage>{new Core::Damage()};
    }

    inline std::shared_ptr<Core::Recovery> MakeRecovery() {
        return std::shared_ptr<Core::Recovery>{new Core::Recovery()};
    }
}
