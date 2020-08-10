#include "InventoryHolder.h"

namespace pevs {
    void InventoryHolder::loadInventory(const char* filename) {
        std::ifstream in_file(filename);
        if (!in_file.is_open()) {
            std::cout << "[ERR] Can not load file" << std::endl;
            return;
        }
        do {
            int item_type = -1;
            char operation = '\0';
            int item_count = 0;
            float item_price = 0.0;

            if (!(in_file >> item_type >> operation >> item_count >> item_price)) continue;
            
            if (operation == 'K') {
                buy(item_type, item_count, item_price);
            } else if (operation == 'P') {
                if (!sell(item_type, item_count, item_price)) std::cout << "[ERR] Unable to sell this much, item type: " << item_type << std::endl;
            }
        } while (!in_file.eof());
        in_file.close();
    }

    void InventoryHolder::printItem(std::ostream* out, int type) const {
        if (!inventory[type].lenght()) return;
        *(out) << "Item " << type << std::endl;
        float price = *(inventory[type].get(0));
        int count = 1;
        for (int i = 1; i < inventory[type].lenght(); i++) {
            float current_price = *(inventory[type].get(i));
            if (price == current_price) count++;
            else {
                char buffer[30];
                sprintf(buffer, "%4d units @ %4.2f EUR", count, price);
                *(out) << buffer << std::endl;
                price = current_price;
                count = 1;
            }
        }
        char buffer[30];
        sprintf(buffer, "%4d units @ %4.2f EUR", count, price);
        *(out) << buffer << std::endl;
    }

    void InventoryHolder::printInventory(const char* filename, int type) const {
        std::ostream* out = &std::cout;
        std::ofstream file;
        if (filename) {
            file.open(filename);
            out = &file;
        }

        if (type < 0) {
            for (int type = 0; type < inventory.size(); type++) {
                if (!inventory[type].lenght()) continue;
                printItem(out, type);
            }
            *(out) << "Balance: " << balance << " EUR" << std::endl;
        }
        else {
            if (type >= inventory.size()) std::cout << "[ERR] Bad item type" << std::endl;
            else printItem(out, type);
        }
        if (filename) file.close();
    }

    bool InventoryHolder::sell(int item_type, int item_count, float item_price) {
        if (inventory.size() <= item_type) return false;
        if (inventory[item_type].lenght() < item_count) return false;
        for (int i = 0; i < item_count; i++) balance-= inventory[item_type].pop();
        return true;
    }

    void InventoryHolder::buy(int item_type, int item_count, float item_price) {
        if (inventory.size() <= item_type) {
            for (int i = inventory.size(); i < (item_type + 1); i++) inventory.emplace_back(pevs::Queue<float>()); // initialize queue for type and its possible predecessors
        }
        for (int i = 0; i < item_count; i++) inventory[item_type].push(item_price);
        balance+= ((float) item_count) * item_price;
    }

}