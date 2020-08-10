#pragma once

#include <memory>
#include <iostream>
#include <fstream>
#include "BinTree.h"

void printMenu(bool isTree);
void play(std::unique_ptr<pevs::BinTree>& pBtree);
bool getNewAnimal(std::unique_ptr<std::string>& animal, std::unique_ptr<std::string>& question);