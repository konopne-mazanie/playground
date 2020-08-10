#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "Queue.h"

namespace pevs {
    class InventoryHolder {
        private:
            std::vector<pevs::Queue<float>> inventory;
            float balance = 0;
            void printItem(std::ostream* out, int type) const;
        public:
            void loadInventory(const char* filename);
            void printInventory(const char* filename, int type = -1) const;
            bool sell(int item_type, int item_count, float item_price);
            void buy(int item_type, int item_count, float item_price);
    };
}
