//
// Created by codegen
//

#include "all_generated_classes.h"

std::unordered_map<int32_t, std::function<std::shared_ptr<Core::Card>()>> GeneratedCard::HashTable = {
        {1, MakeUnit},
        {2, MakeDamage},
        {3, MakeRecovery},
};
